/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2015 Sebastian Schlenkrich

*/



#include <qlo/templatequasigaussian.hpp>

namespace QuantLibAddin {

	RealQuasiGaussianModel::RealQuasiGaussianModel(
						   const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
						         const QuantLib::Handle<QuantLib::YieldTermStructure>& hYTS,
		                         // number of yield curve factors (excluding stoch. vol)
		                         size_t                                             d,       // (d+1)-dimensional Brownian motion for [x(t), z(t)]^T
		                         // unique grid for time-dependent parameters
		                         const std::vector<QuantLib::Time>&                 times,   // time-grid of left-constant model parameter values
		                         // time-dependent parameters, left-piecewise constant on times_-grid
		                         const std::vector< std::vector<QuantLib::Real> >&  lambda,  // volatility
		                         const std::vector< std::vector<QuantLib::Real> >&  alpha,   // shift
		                         const std::vector< std::vector<QuantLib::Real> >&  b,       // f-weighting
		                         const std::vector<QuantLib::Real>&                 eta,     // vol-of-vol
		                         // time-homogeneous parameters
		                         const std::vector<QuantLib::Real>&                 delta,   // maturity of benchmark rates f(t,t+delta_i) 		
		                         const std::vector<QuantLib::Real>&                 chi,     // mean reversions
		                         const std::vector< std::vector<QuantLib::Real> >&  Gamma,   // (benchmark rate) correlation matrix
		                         // stochastic volatility process parameters
		                         QuantLib::Real                                     theta,   // mean reversion speed
 				                 const QuantLib::RealStochasticProcess::VolEvolv    volEvolv,
						   bool permanent) : RealStochasticProcess(properties,permanent) {

        libraryObject_ = boost::shared_ptr<QuantLib::RealStochasticProcess>(
			new QuantLib::RealQuasiGaussianModel( hYTS, d, times, lambda, alpha, b, eta, delta, chi, Gamma, theta, volEvolv ));
    }

	RealQGSwaptionModel::RealQGSwaptionModel(
		                    const boost::shared_ptr<ObjectHandler::ValueObject>&         properties,
						    const boost::shared_ptr<QuantLib::RealQuasiGaussianModel>&   model,
			                const std::vector<QuantLib::Time>&                           floatTimes,    // T[1], ..., T[M]
			                const std::vector<QuantLib::Real>&                           floatWeights,  // u[1], ..., u[M]
			                const std::vector<QuantLib::Time>&                           fixedTimes,    // T[1], ..., T[N]
			                const std::vector<QuantLib::Real>&                           fixedWeights,  // w[1], ..., w[N-1]
			                const std::vector<QuantLib::Time>&                           modelTimes,   // time grid for numerical integration
			                const bool                                                   useExpectedXY, // evaluate E^A [ x(t) ], E^A [ y(t) ] as expansion points
							bool permanent) : RealTDStochVolModel(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealQGSwaptionModel>(
			new QuantLib::RealQGSwaptionModel( model, floatTimes, floatWeights, fixedTimes, fixedWeights, modelTimes, useExpectedXY ) );
	}

}

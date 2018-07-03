/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2015 Sebastian Schlenkrich

*/


#include <ql/math/rounding.hpp>
#include <ql/indexes/swapindex.hpp>
#include <ql/experimental/basismodels/swaptioncfs.hpp>
#include <qlo/templatequasigaussian2.hpp>

namespace QuantLibAddin {

	QuasiGaussianModel::QuasiGaussianModel(
        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
        const QuantLib::Handle<QuantLib::YieldTermStructure>& hYTS,
        // number of yield curve factors (excluding stoch. vol)
        size_t                                             d,       // (d+1)-dimensional Brownian motion for [x(t), z(t)]^T
        // unique grid for time-dependent parameters
        const std::vector<QuantLib::Time>&                 times,   // time-grid of left-constant model parameter values
        // time-dependent parameters, left-piecewise constant on times_-grid
        const std::vector< std::vector<QuantLib::Real> >&  sigma,   // volatility
		const std::vector< std::vector<QuantLib::Real> >&  slope,   // shift
		const std::vector< std::vector<QuantLib::Real> >&  curve,   // f-weighting
        const std::vector<QuantLib::Real>&                 eta,     // vol-of-vol
        // time-homogeneous parameters
        const std::vector<QuantLib::Real>&                 delta,   // maturity of benchmark rates f(t,t+delta_i) 		
        const std::vector<QuantLib::Real>&                 chi,     // mean reversions
        const std::vector< std::vector<QuantLib::Real> >&  Gamma,   // (benchmark rate) correlation matrix
        QuantLib::Real                                     theta,   // mean reversion speed
        bool permanent) : RealStochasticProcess(properties,permanent) {

        libraryObject_ = boost::shared_ptr<QuantLib::RealStochasticProcess>(
			new QuantLib::QuasiGaussianModel( hYTS, d, times, sigma, slope, curve, eta, delta, chi, Gamma, theta ));
    }


	// do nothing, only fascilitate inheritance
	QuasiGaussianModel::QuasiGaussianModel(
		const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
		bool                                                 permanent)
		: RealStochasticProcess(properties, permanent) { }

	QGSwaprateModel::QGSwaprateModel(
		const boost::shared_ptr<ObjectHandler::ValueObject>&         properties,
		bool                                                         permanent)
		: RealStochasticProcess(properties, permanent) { }

	QGSwaprateModel::QGSwaprateModel(
		const boost::shared_ptr<ObjectHandler::ValueObject>&         properties,
		const boost::shared_ptr<QuantLib::QuasiGaussianModel>&       model,
		const std::vector<QuantLib::Time>&                           floatTimes,    // T[1], ..., T[M]
		const std::vector<QuantLib::Real>&                           floatWeights,  // u[1], ..., u[M]
		const std::vector<QuantLib::Time>&                           fixedTimes,    // T[1], ..., T[N]
		const std::vector<QuantLib::Real>&                           fixedWeights,  // w[1], ..., w[N-1]
		const std::vector<QuantLib::Time>&                           modelTimes,   // time grid for numerical integration
		const bool                                                   useExpectedXY, // evaluate E^A [ x(t) ], E^A [ y(t) ] as expansion points
		bool permanent) : RealStochasticProcess(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::QGSwaprateModel>(
			new QuantLib::QGSwaprateModel(model, floatTimes, floatWeights, fixedTimes, fixedWeights, modelTimes, useExpectedXY));
	}

	QGSwaprateModel::QGSwaprateModel(
		const boost::shared_ptr<ObjectHandler::ValueObject>&                     properties,
		const boost::shared_ptr<QuantLib::QuasiGaussianModel>&                   model,
		const boost::shared_ptr<QuantLib::Swaption>&                             swaption,
		const QuantLib::Handle<QuantLib::YieldTermStructure>&                    discountCurve,
		const QuantLib::Size                                                     timePointsPerYear,    // time grid for numerical integration
		const bool                                                               useExpectedXY, // evaluate E^A [ x(t) ], E^A [ y(t) ] as expansion points
		bool permanent) : RealStochasticProcess(properties, permanent) {
		// use swaption cash flow model
		QuantLib::SwaptionCashFlows cf(swaption, discountCurve);
		// we need to roll out the model time grid for discretisation
		QuantLib::Size numberOfRegularPoints = (QuantLib::Size) (cf.exerciseTimes()[0] * timePointsPerYear);  // this is rounded to the lower integer
		std::vector<QuantLib::Time> modelTimes(numberOfRegularPoints+1);
		modelTimes[0] = 0.0;
		for (QuantLib::Size k = 1; k < numberOfRegularPoints + 1; ++k) modelTimes[k] = modelTimes[k - 1] + 1.0 / timePointsPerYear;
		if (modelTimes[numberOfRegularPoints]<cf.exerciseTimes()[0]-1.0/365.0) modelTimes.push_back(cf.exerciseTimes()[0]);  // we want to avoid too close grid points
		else modelTimes[numberOfRegularPoints] = cf.exerciseTimes()[0];
		// finally, we may set up the model
		libraryObject_ = boost::shared_ptr<QuantLib::QGSwaprateModel>(
			new QuantLib::QGSwaprateModel(model, cf.floatTimes(), cf.floatWeights(), cf.fixedTimes(), cf.annuityWeights(), modelTimes, useExpectedXY));
	}

	QGSwaprateModel::QGSwaprateModel(
		const boost::shared_ptr<ObjectHandler::ValueObject>&                     properties,
		const boost::shared_ptr<QuantLib::QuasiGaussianModel>&                   model,
		const QuantLib::Time                                                     fixingTime,
		const boost::shared_ptr<QuantLib::SwapIndex>&                            swapIndex,
		const QuantLib::Handle<QuantLib::YieldTermStructure>&                    discountCurve,
		const QuantLib::Size                                                     timePointsPerYear,    // time grid for numerical integration
		const bool                                                               useExpectedXY, // evaluate E^A [ x(t) ], E^A [ y(t) ] as expansion points
		bool permanent) : RealStochasticProcess(properties, permanent) {
		QuantLib::Date today = discountCurve->referenceDate(); // check if this is the correct date...
		QuantLib::Date fixingDate = today + ((QuantLib::BigInteger)QuantLib::ClosestRounding(0)(fixingTime*365.0)); // assuming act/365 day counting
		QuantLib::SwapCashFlows scf(swapIndex->underlyingSwap(fixingDate), discountCurve, true);        // assume continuous tenor spreads
		// we need to roll out the model time grid for discretisation
		QuantLib::Size numberOfRegularPoints = (QuantLib::Size) (fixingTime * timePointsPerYear);  // this is rounded to the lower integer
		std::vector<QuantLib::Time> modelTimes(numberOfRegularPoints + 1);
		modelTimes[0] = 0.0;
		for (QuantLib::Size k = 1; k < numberOfRegularPoints + 1; ++k) modelTimes[k] = modelTimes[k - 1] + 1.0 / timePointsPerYear;
		if (modelTimes[numberOfRegularPoints]<fixingTime - 1.0 / 365.0) modelTimes.push_back(fixingTime);  // we want to avoid too close grid points
		else modelTimes[numberOfRegularPoints] = fixingTime;
		// finally, we may set up the model
		libraryObject_ = boost::shared_ptr<QuantLib::QGSwaprateModel>(
			new QuantLib::QGSwaprateModel(model, scf.floatTimes(), scf.floatWeights(), scf.fixedTimes(), scf.annuityWeights(), modelTimes, useExpectedXY));
	}

	QGAverageSwaprateModel::QGAverageSwaprateModel(
		const boost::shared_ptr<ObjectHandler::ValueObject>&         properties,
		const boost::shared_ptr<QuantLib::QGSwaprateModel>&                             model,
		bool                                                                            permanent)
		: QGSwaprateModel(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::QGAverageSwaprateModel>(new QuantLib::QGAverageSwaprateModel(model));
	}

	QGCalibrator::QGCalibrator(
		const boost::shared_ptr<ObjectHandler::ValueObject>&            properties,
		const boost::shared_ptr<QuantLib::QuasiGaussianModel>&          model,
		const boost::shared_ptr<QuantLib::SwaptionVolatilityStructure>& volTS,
		const std::vector< boost::shared_ptr<QuantLib::SwapIndex> >&    swapIndices,
		const QuantLib::Real                                            modelTimesStepSize,
		const bool                                                      useExpectedXY,
		const QuantLib::Real                                            sigmaMax,
		const QuantLib::Real                                            slopeMax,
		const QuantLib::Real                                            etaMax,
		const QuantLib::Real                                            sigmaWeight,
		const QuantLib::Real                                            slopeWeight,
		const QuantLib::Real                                            etaWeight,
		const QuantLib::Real                                            penaltySigma,
		const QuantLib::Real                                            penaltySlope,
		const boost::shared_ptr<QuantLib::EndCriteria>&                 endCriteria,
		bool                                                            permanent)
		: ObjectHandler::LibraryObject<QuantLib::QGCalibrator>(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::QGCalibrator>(
			new QuantLib::QGCalibrator(model, volTS, swapIndices, modelTimesStepSize, useExpectedXY, 
				sigmaMax, slopeMax, etaMax, sigmaWeight, slopeWeight, etaWeight, penaltySigma, penaltySlope, endCriteria));
	}

	// calibrated model from calibrator
	QuasiGaussianModel::QuasiGaussianModel(
		const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
		const boost::shared_ptr<QuantLib::QGCalibrator>&     calibrator,
		bool permanent)
		: RealStochasticProcess(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::RealStochasticProcess>(calibrator->calibratedModel());
	}

	QGLocalvolModel::QGLocalvolModel(
		const boost::shared_ptr<ObjectHandler::ValueObject>&            properties,
		const QuantLib::Handle<QuantLib::YieldTermStructure>&           hYTS,
		const boost::shared_ptr<QuantLib::SwaptionVolatilityStructure>& volTS,
		const QuantLib::Real                                            chi,
		const boost::shared_ptr<QuantLib::SwapIndex>&                   swapIndex,
		const std::vector<QuantLib::Time>&                              times,      // time-grid of left-constant model parameter values
		const std::vector<QuantLib::Real>&                              stdDevGrid,  // S-grid in terms of normal ATM vol stdDev's
		const QuantLib::Size                                            nPaths,
		const QuantLib::BigNatural                                      seed,
		const QuantLib::Size                                            debugLevel,
		bool                                                            permanent)
		: QuasiGaussianModel(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::QuasiGaussianModel>(new QuantLib::QGLocalvolModel(hYTS, volTS, chi, swapIndex, times, stdDevGrid, nPaths, seed, debugLevel));
	}

	QGLocalvolModelSimulation::QGLocalvolModelSimulation(
		const boost::shared_ptr<ObjectHandler::ValueObject>&         properties,
		const boost::shared_ptr<QuantLib::QGLocalvolModel>&          model,
		bool                                                         permanent)
		: RealMCSimulation(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::QGLocalvolModel::MCSimulation>(model->simulation());
	}


}

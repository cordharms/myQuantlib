/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2010 Sebastian Schlenkrich

 */

#ifndef qla_templatequasigaussianmodels_hpp
#define qla_templatequasigaussianmodels_hpp

#include <ql/types.hpp>

#include <ql/experimental/template/qgaussian/quasigaussianmodels.hpp>

#include <qlo/baseinstruments.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/pricingengines.hpp>


namespace QuantLib {
    template <class T>
    class Handle;

	class TemplateModel;
}

namespace QuantLibAddin {

    OH_LIB_CLASS(TemplateModel, QuantLib::TemplateModel);

    class RealQuasiGaussianModel : public TemplateModel {
      public:
		  RealQuasiGaussianModel(const boost::shared_ptr<ObjectHandler::ValueObject>& properties, bool permanent) : TemplateModel(properties,permanent) {}
          RealQuasiGaussianModel(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
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
							     bool permanent);
    };

	OH_LIB_CLASS(TemplateSimulation, QuantLib::TemplateSimulation);

	class RealQGMCSimulation : public TemplateSimulation {
	public:
		RealQGMCSimulation( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                              const boost::shared_ptr<QuantLib::RealQuasiGaussianModel> process,
			                  const std::vector<QuantLib::Real>&              simTimes,
							  const std::vector<QuantLib::Real>&              obsTimes,
							  size_t                                          nPaths,
							  QuantLib::BigNatural                            seed,
							  bool                                            richardsonExtrapolation,
							  bool                                            timeInterpolation,
							  bool                                            storeBrownians,
							  bool permanent);
	};


}  // namespace QuantLibAddin

#endif  // quasigaussianmodels


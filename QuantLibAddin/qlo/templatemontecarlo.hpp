/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2010 Sebastian Schlenkrich

 */

#ifndef qla_templatemontecarlo_hpp
#define qla_templatemontecarlo_hpp

#include <qlo/termstructures.hpp>

#include <ql/types.hpp>

#include <ql/experimental/template/montecarlo/montecarlomodells.hpp>



namespace QuantLib {
    template <class T>
    class Handle;

	class TemplateModel;
}

namespace QuantLibAddin {

    OH_LIB_CLASS(RealStochasticProcess, QuantLib::RealStochasticProcess);

	/*
    class RealQuasiGaussianModel : public RealStochasticProcess {
      public:
		  RealQuasiGaussianModel(const boost::shared_ptr<ObjectHandler::ValueObject>& properties, bool permanent) : RealStochasticProcess(properties,permanent) {}
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
				                 const QuantLib::RealStochasticProcess::VolEvolv    volEvolv,
							     bool permanent);
    };
	*/

	OH_LIB_CLASS(TemplateSimulation, QuantLib::TemplateSimulation);

	class RealMCSimulation : public TemplateSimulation {
	public:
		RealMCSimulation( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                          const boost::shared_ptr<QuantLib::RealStochasticProcess> process,
			              const std::vector<QuantLib::Real>&              simTimes,
						  const std::vector<QuantLib::Real>&              obsTimes,
						  size_t                                          nPaths,
						  const std::vector<QuantLib::Real>&              zcbObservTimes,
					      const std::vector<QuantLib::Real>&              zcbOffsetTimes,
						  QuantLib::BigNatural                            seed,
						  bool                                            richardsonExtrapolation,
						  bool                                            timeInterpolation,
						  bool                                            storeBrownians,
						  bool permanent);
	};

	OH_LIB_CLASS(RealMCPayoffPricerBase, QuantLib::RealMCPayoffPricer);

	class RealMCPayoffPricer : public RealMCPayoffPricerBase {
	public:
		RealMCPayoffPricer(   const boost::shared_ptr<ObjectHandler::ValueObject>&              properties,
			                  const std::vector< boost::shared_ptr<QuantLib::RealMCPayoff> >&   payoffs,
							  const boost::shared_ptr<QuantLib::RealMCSimulation>&            simulation,
			                  bool permanent);
	};

	OH_LIB_CLASS(RealMCPayoff, QuantLib::RealMCPayoff);

	class RealMCCash : public RealMCPayoff {
	public:
		RealMCCash( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			          const QuantLib::Time  t,
					  const QuantLib::Time  T,
			          bool permanent);
	};

	class RealMCVanillaOption : public RealMCPayoff {
	public:
		RealMCVanillaOption( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			          const QuantLib::Time  t,
					  const QuantLib::Time  T,
					  const QuantLib::Real  strike,
					  const QuantLib::Real  callOrPut,
			          bool permanent);
	};

	class RealMCAnnuity : public RealMCPayoff {
	public:
		RealMCAnnuity( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			             const QuantLib::Time                                 t,
						 const std::vector<QuantLib::Time>&                   payTimes,
						 const std::vector<QuantLib::Real>&                   payWeights,
			             bool permanent);
	};

	class RealMCModelSwaption : public RealMCPayoff {
	public:
		RealMCModelSwaption( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			                   const QuantLib::Time                                 t,
						       const std::vector<QuantLib::Time>&                   times,
						       const std::vector<QuantLib::Real>&                   payWeights,
							   QuantLib::Real                                       strike,
							   QuantLib::Real                                       payOrRec,
			                   bool permanent);
	};

	class RealMCGeneralSwaption : public RealMCPayoff {
	public:
		RealMCGeneralSwaption( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			                   const QuantLib::Time                                 t,
						       const std::vector<QuantLib::Time>&                   floatTimes,
						       const std::vector<QuantLib::Real>&                   floatWeights,
						       const std::vector<QuantLib::Time>&                   fixedTimes,
						       const std::vector<QuantLib::Real>&                   fixedWeights,
							   QuantLib::Real                                       strike,
							   QuantLib::Real                                       payOrRec,
			                   bool permanent);
	};

	class RealMCModelCorrelation : public RealMCPayoff {
	public:
		RealMCModelCorrelation( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
						       const std::vector<QuantLib::Time>&                   times,
			                   const QuantLib::Time                                 T1,
			                   const QuantLib::Time                                 T2,
			                   bool permanent);
	};


}  // namespace QuantLibAddin

#endif  // templatemontecarlo


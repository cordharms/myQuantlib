/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2010 Sebastian Schlenkrich

 */

#ifndef qla_templatemontecarlo_hpp
#define qla_templatemontecarlo_hpp

#include <qlo/termstructures.hpp>
#include <qlo/templatequasigaussian.hpp>

#include <ql/types.hpp>

#include <ql/experimental/template/montecarlo/montecarlomodells.hpp>
#include <ql/experimental/template/basismodel/swaptioncfs.hpp>



namespace QuantLib {
    template <class T>
    class Handle;

	class TemplateModel;
}

namespace QuantLibAddin {

    // OH_LIB_CLASS(RealStochasticProcess, QuantLib::RealStochasticProcess);

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
		RealMCGeneralSwaption( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			                   const boost::shared_ptr<QuantLib::Swaption>&           swaption,
			                   const QuantLib::Handle<QuantLib::YieldTermStructure>&  discountCurve,
			                   bool permanent);
	};

	class RealMCSwapRate : public RealMCPayoff {
	public:
		RealMCSwapRate( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			            const QuantLib::Time                                 t,
						const std::vector<QuantLib::Time>&                   floatTimes,
						const std::vector<QuantLib::Real>&                   floatWeights,
						const std::vector<QuantLib::Time>&                   fixedTimes,
						const std::vector<QuantLib::Real>&                   annuityWeights,
			            bool permanent);
		RealMCSwapRate( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			            const boost::shared_ptr<QuantLib::Swaption>&           swaption,
			            const QuantLib::Handle<QuantLib::YieldTermStructure>&  discountCurve,
			            bool permanent);
		RealMCSwapRate( const boost::shared_ptr<ObjectHandler::ValueObject>&   properties,
			            const QuantLib::Time                                   fixingTime,
			            const boost::shared_ptr<QuantLib::SwapIndex>&          swapIndex,
			            const QuantLib::Handle<QuantLib::YieldTermStructure>&  discountCurve,
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


	class RealMCForwardRateCorrelation : public RealMCPayoff {
	public:
		RealMCForwardRateCorrelation( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
						              const std::vector<QuantLib::Time>&                   times,
			                          const QuantLib::Time                                 T1,
			                          const QuantLib::Time                                 Term1,
			                          const QuantLib::Time                                 T2,
			                          const QuantLib::Time                                 Term2,
			                          bool permanent);
	};


	// MC swap stuff

	class RealMCFixedAmount : public RealMCPayoff {
	public:
		RealMCFixedAmount( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
						   const QuantLib::Real                                 amount,
			               bool                                                 permanent);
	};

	class RealMCLiborRate : public RealMCPayoff {
	public:
		RealMCLiborRate  ( const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
			               const QuantLib::Time                                    fixingTime,
				           const QuantLib::Time                                    startTime,
					       const QuantLib::Time                                    endTime,
					       const boost::shared_ptr<QuantLib::IborIndex>&           iborIndex,
					       const QuantLib::Handle<QuantLib::YieldTermStructure>&   discYTS, 
			               bool                                                    permanent);
	};

	class RealMCAxpy : public RealMCPayoff {
	public:
		RealMCAxpy       ( const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
			               const QuantLib::Real                                    a,
						   const boost::shared_ptr<QuantLib::RealMCPayoff>&        x,
						   const boost::shared_ptr<QuantLib::RealMCPayoff>&        y,
			               bool                                                    permanent);
	};

    class RealMCMax : public RealMCPayoff {
	public:
		RealMCMax       (  const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
						   const boost::shared_ptr<QuantLib::RealMCPayoff>&        x,
						   const boost::shared_ptr<QuantLib::RealMCPayoff>&        y,
			               bool                                                    permanent);
	};

    class RealMCMin : public RealMCPayoff {
	public:
		RealMCMin       (  const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
						   const boost::shared_ptr<QuantLib::RealMCPayoff>&        x,
						   const boost::shared_ptr<QuantLib::RealMCPayoff>&        y,
			               bool                                                    permanent);
	};

	class RealMCPay : public RealMCPayoff {
	public:
		RealMCPay       (  const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
						   const boost::shared_ptr<QuantLib::RealMCPayoff>&        x,
			               const QuantLib::Time                                    payTime,
			               bool                                                    permanent);
	};

	class RealMCCoupon : public RealMCPayoff {
	public:
		RealMCCoupon    (  const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
						   const boost::shared_ptr<QuantLib::RealMCPayoff>&        x,
			               const QuantLib::Time                                    startTime,
			               const QuantLib::Time                                    payTime,
			               bool                                                    permanent);
	};

	class RealMCLeg : public ObjectHandler::LibraryObject<QuantLib::RealMC::Leg> {
	public:
		RealMCLeg       (  const boost::shared_ptr<ObjectHandler::ValueObject>&                properties,
						   const std::vector< boost::shared_ptr<QuantLib::RealMC::Coupon> >&   coupons,
			               bool                                                                permanent);
	};

	class RealMCSwap : public ObjectHandler::LibraryObject<QuantLib::RealMC::Swap> {
	public:
		RealMCSwap      (  const boost::shared_ptr<ObjectHandler::ValueObject>&             properties,
						   const std::vector< boost::shared_ptr<QuantLib::RealMC::Leg> >&   legs,
			               bool                                                             permanent);
	};

	class RealMCCancellableNote : public ObjectHandler::LibraryObject<QuantLib::RealMC::CancellableNote> {
	public:
		RealMCCancellableNote (  const boost::shared_ptr<ObjectHandler::ValueObject>&            properties,
                                 const std::vector< boost::shared_ptr<QuantLib::RealMC::Leg> >&  underlyings,
				                 const std::vector< QuantLib::Time >&                            callTimes,
							     const std::vector< boost::shared_ptr<QuantLib::RealMC::Leg> >&  earlyRedemptions,
							     const std::vector< boost::shared_ptr<QuantLib::RealMC::Leg> >&  regressionVariables,
						         bool                                                            permanent);
	};

	class RealAMCPricer : public ObjectHandler::LibraryObject<QuantLib::RealAMCPricer> {
	public:
		RealAMCPricer (  const boost::shared_ptr<ObjectHandler::ValueObject>&            properties,
			             const boost::shared_ptr<QuantLib::RealMC::CancellableNote>&     note,
                         const boost::shared_ptr<QuantLib::RealMCSimulation>&            simulation,
						 const bool                                                      calculateRegression,
						 const QuantLib::Size                                            maxPolynDegree,
			             bool                                                            permanent);
	};

	class RealRegression : public ObjectHandler::LibraryObject<QuantLib::RealRegression> {
	public:
		RealRegression (  const boost::shared_ptr<ObjectHandler::ValueObject>&            properties,
			              const std::vector< std::vector<QuantLib::Real> >&               controls,
						  const std::vector<QuantLib::Real>                               observations,
				          const QuantLib::Size                                            maxDegree,
			              bool                                                            permanent);
	};



}  // namespace QuantLibAddin

#endif  // templatemontecarlo


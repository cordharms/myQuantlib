/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2010 Sebastian Schlenkrich

 */

#ifndef qla_templatemontecarlo_hpp
#define qla_templatemontecarlo_hpp

#include <qlo/termstructures.hpp>
#include <qlo/templatequasigaussian.hpp>

#include <ql/types.hpp>

#include <ql/experimental/templatemodels/montecarlo/montecarlomodells.hpp>
#include <ql/experimental/basismodels/swaptioncfs.hpp>



namespace QuantLib {
    template <class T>
    class Handle;

	class TemplateModel;
}

namespace QuantLibAddin {

	// Simulation and payoff pricer

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

	// basic (general) payoffs and payoff-operations

	OH_LIB_CLASS(RealMCPayoff, QuantLib::RealMCPayoff);

	class RealMCClone : public RealMCPayoff {
	public:
		RealMCClone(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const boost::shared_ptr<QuantLib::RealMCPayoff>&             x,
			const QuantLib::Time                                         observationTime,
			bool                                                         permanent);
	};

	class RealMCFixedAmount : public RealMCPayoff {
	public:
		RealMCFixedAmount( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
						   const QuantLib::Real                                 amount,
			               bool                                                 permanent);
	};

	class RealMCAxpy : public RealMCPayoff {
	public:
		RealMCAxpy       ( const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
			               const QuantLib::Real                                    a,
						   const boost::shared_ptr<QuantLib::RealMCPayoff>&        x,
						   const boost::shared_ptr<QuantLib::RealMCPayoff>&        y,
			               bool                                                    permanent);
	};

    class RealMCMult : public RealMCPayoff {
	public:
		RealMCMult      (  const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
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

	class RealMCCash : public RealMCPayoff {
	public:
		RealMCCash( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			          const QuantLib::Time  t,
					  const QuantLib::Time  T,
			          bool permanent);
	};

	class RealMCAsset : public RealMCPayoff {
	public:
		RealMCAsset(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const QuantLib::Time  t,
			const std::string&    alias,
			bool permanent);
	};

	class RealMCAssetBarrierNoHit : public RealMCPayoff {
	public:
		RealMCAssetBarrierNoHit(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const QuantLib::Time  tStart,
			const QuantLib::Time  tEnd,
			const QuantLib::Real  downBarrier,
			const QuantLib::Real  upBarrier,
			const QuantLib::Real  downOrUpOrBoth,
			const std::string&    alias,
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

	class RealMCCache : public RealMCPayoff {
	public:
		RealMCCache(const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
			        const boost::shared_ptr<QuantLib::RealMCPayoff>&        x,
			        bool                                                    permanent);
	};

	class RealMCLogical : public RealMCPayoff {
	public:
		RealMCLogical(const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
			          const boost::shared_ptr<QuantLib::RealMCPayoff>&        x,
			          const boost::shared_ptr<QuantLib::RealMCPayoff>&        y,
			          const std::string&                                      op,
			          bool                                                    permanent);
	};

	class RealMCIfThenElse : public RealMCPayoff {
	public:
		RealMCIfThenElse(const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
			const boost::shared_ptr<QuantLib::RealMCPayoff>&        x,
			const boost::shared_ptr<QuantLib::RealMCPayoff>&        y,
			const boost::shared_ptr<QuantLib::RealMCPayoff>&        z,
			bool                                                    permanent);
	};

	class RealMCBasket : public RealMCPayoff {
	public:
		RealMCBasket(
			const boost::shared_ptr<ObjectHandler::ValueObject>&               properties,
			const std::vector<boost::shared_ptr<QuantLib::RealMCPayoff>> &     underlyings,
			const std::vector<QuantLib::Real>&                                 weights,
			const bool                                                         rainbow,
			bool                                                               permanent);
	};


	// particular rates payoffs

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

	class RealMCLiborRate : public RealMCPayoff {
	public:
		RealMCLiborRate  ( const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
			               const QuantLib::Time                                    fixingTime,
					       const boost::shared_ptr<QuantLib::IborIndex>&           iborIndex,
					       const QuantLib::Handle<QuantLib::YieldTermStructure>&   discYTS, 
			               bool                                                    permanent);
		RealMCLiborRate(const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
			            const QuantLib::Time                                    fixingTime,
			            const QuantLib::Time                                    startTime,
			            const QuantLib::Time                                    endTime,
			            const boost::shared_ptr<QuantLib::IborIndex>&           iborIndex,
			            const QuantLib::Handle<QuantLib::YieldTermStructure>&   discYTS,
			            bool                                                    permanent);
	};

	class RealMCCashFlow : public RealMCPayoff {
	public:
		RealMCCashFlow    ( const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
						    const boost::shared_ptr<QuantLib::RealMCPayoff>&        x,
			                const QuantLib::Time                                    startTime,
			                const QuantLib::Time                                    payTime,
							const bool                                              applyZCBAdjuster,
			                bool                                                    permanent);
	};

	class RealMCScript : public RealMCPayoff {
	public:
		RealMCScript(const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
			         const std::vector< std::string >&                       keys,
			         const std::vector< boost::shared_ptr<QuantLib::RealMCPayoff> >&  payoffs,
                     const std::vector< std::string >&                       script,
			         const bool                                              overwrte,
			         bool                                                    permanent);
	};

	// Cancellable note details and pricer

	class RealMCLeg : public ObjectHandler::LibraryObject<QuantLib::RealMCLeg> {
	public:
		RealMCLeg       (  const boost::shared_ptr<ObjectHandler::ValueObject>&               properties,
						   const std::vector< boost::shared_ptr<QuantLib::RealMCCashFlow> >&  cashflows,
			               bool                                                               permanent);
	};

	class RealMCSwap : public ObjectHandler::LibraryObject<QuantLib::RealMCRates::Swap> {
	public:
		RealMCSwap      (  const boost::shared_ptr<ObjectHandler::ValueObject>&           properties,
						   const std::vector< boost::shared_ptr<QuantLib::RealMCLeg> >&   legs,
			               bool                                                           permanent);
	};

	class RealMCCancellableNote : public ObjectHandler::LibraryObject<QuantLib::RealMCCancellableNote> {
	public:
		RealMCCancellableNote (  const boost::shared_ptr<ObjectHandler::ValueObject>&          properties,
                                 const std::vector< boost::shared_ptr<QuantLib::RealMCLeg> >&  underlyings,
				                 const std::vector< QuantLib::Time >&                          callTimes,
							     const std::vector< boost::shared_ptr<QuantLib::RealMCLeg> >&  earlyRedemptions,
							     const std::vector< boost::shared_ptr<QuantLib::RealMCLeg> >&  regressionVariables,
						         bool                                                          permanent);
	};

	class RealAMCPricer : public ObjectHandler::LibraryObject<QuantLib::RealAMCPricer> {
	public:
		RealAMCPricer (  const boost::shared_ptr<ObjectHandler::ValueObject>&          properties,
			             const boost::shared_ptr<QuantLib::RealMCCancellableNote>&     note,
                         const boost::shared_ptr<QuantLib::RealMCSimulation>&          simulation,
						 const QuantLib::Real                                          regressionFraction,
						 const QuantLib::Size                                          maxPolynDegree,
			             bool                                                          permanent);
	};

	class RealRegression : public ObjectHandler::LibraryObject<QuantLib::RealRegression> {
	public:
		RealRegression (  const boost::shared_ptr<ObjectHandler::ValueObject>&            properties,
			              const std::vector< std::vector<QuantLib::Real> >&               controls,
						  const std::vector<QuantLib::Real>                               observations,
				          const QuantLib::Size                                            maxDegree,
			              bool                                                            permanent);
	};

	class RealAMCMax : public RealMCPayoff {
	public:
		RealAMCMax(const boost::shared_ptr<ObjectHandler::ValueObject>&             properties,
			       const std::vector< boost::shared_ptr<QuantLib::RealMCPayoff> >&  x,  
			       const std::vector< boost::shared_ptr<QuantLib::RealMCPayoff> >&  y,
			       const std::vector< boost::shared_ptr<QuantLib::RealMCPayoff> >&  z,  // regression variables
			       const QuantLib::Time                                             observationTime,
			       const boost::shared_ptr<QuantLib::RealMCSimulation>&             simulation,
			       const QuantLib::Size                                             maxPolynDegree,
			       bool                                                             permanent);
	};

	class RealAMCMin : public RealMCPayoff {
	public:
		RealAMCMin(const boost::shared_ptr<ObjectHandler::ValueObject>&      properties,
			const std::vector< boost::shared_ptr<QuantLib::RealMCPayoff> >&  x,
			const std::vector< boost::shared_ptr<QuantLib::RealMCPayoff> >&  y,
			const std::vector< boost::shared_ptr<QuantLib::RealMCPayoff> >&  z,  // regression variables
			const QuantLib::Time                                             observationTime,
			const boost::shared_ptr<QuantLib::RealMCSimulation>&             simulation,
			const QuantLib::Size                                             maxPolynDegree,
			bool                                                             permanent);
	};


	// more rates pricing and analysis objects

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

	// commodity payoffs

	class RealMCAverageFutureOption : public RealMCPayoff {
	public:
		RealMCAverageFutureOption( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			                       const QuantLib::Time                                 t,
						           const std::vector<QuantLib::Time>&                   settlementTimes,
						           const std::vector<QuantLib::Real>&                   settlementWeights,
					               const QuantLib::Real                                 strike,
					               const QuantLib::Real                                 callOrPut,
			                       bool                                                 permanent);
	};

	class RealMCAverageFutureCovariance : public RealMCPayoff {
	public:
		RealMCAverageFutureCovariance( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
						               const std::vector<QuantLib::Time>&                   observationTimes,
						               const std::vector<QuantLib::Time>&                   settlementTimesA,
						               const std::vector<QuantLib::Real>&                   settlementWeightsA,
					                   const QuantLib::Time                                 observationLagA,
						               const std::vector<QuantLib::Time>&                   settlementTimesB,
						               const std::vector<QuantLib::Real>&                   settlementWeightsB,
					                   const QuantLib::Time                                 observationLagB,
			                           bool                                                 useLogReturns,
			                           long                                                 calcType,
			                           bool                                                 permanent);
	};

}  // namespace QuantLibAddin

#endif  // templatemontecarlo


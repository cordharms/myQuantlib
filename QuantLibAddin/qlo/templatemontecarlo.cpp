/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2015 Sebastian Schlenkrich

*/



#include <qlo/templatemontecarlo.hpp>

namespace QuantLibAddin {

    // Simulation and payoff pricer

	RealMCSimulation::RealMCSimulation(
		                      const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                              const boost::shared_ptr<QuantLib::RealStochasticProcess> process,
			                  const std::vector<QuantLib::Real>&              simTimes,
							  const std::vector<QuantLib::Real>&              obsTimes,
							  size_t                                          nPaths,
							  QuantLib::BigNatural                            seed,
							  bool                                            richardsonExtrapolation,
							  bool                                            timeInterpolation,
							  bool                                            storeBrownians,
							  bool permanent) : TemplateSimulation(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCSimulation>(
			new QuantLib::RealMCSimulation( process, simTimes, obsTimes, nPaths, seed, richardsonExtrapolation, timeInterpolation, storeBrownians ));
	}

	RealMCPayoffPricer::RealMCPayoffPricer(
		                      const boost::shared_ptr<ObjectHandler::ValueObject>&              properties,
			                  const std::vector< boost::shared_ptr<QuantLib::RealMCPayoff> >& payoffs,
							  const boost::shared_ptr<QuantLib::RealMCSimulation>&            simulation,
			                  bool permanent) : RealMCPayoffPricerBase(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoffPricer>(
			new QuantLib::RealMCPayoffPricer( payoffs, simulation ));
	}

	RealMCClone::RealMCClone(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
		                     const boost::shared_ptr<QuantLib::RealMCPayoff>&             x,
		                     const QuantLib::Time                                         observationTime,
		                     bool                                                         permanent) : RealMCPayoff(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(new QuantLib::RealMCPayoff::Clone(x,observationTime));
	}


	RealMCFixedAmount::RealMCFixedAmount( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
						                  const QuantLib::Real                                 amount,
			                              bool                                                 permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCPayoff::FixedAmount( amount ));
	}

	RealMCAxpy::RealMCAxpy ( const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
			                 const QuantLib::Real                                    a,
						     const boost::shared_ptr<QuantLib::RealMCPayoff>&        x,
						     const boost::shared_ptr<QuantLib::RealMCPayoff>&        y,
			                 bool                                                    permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCPayoff::Axpy( a, x, y ));
	}

	RealMCMult::RealMCMult( const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
						    const boost::shared_ptr<QuantLib::RealMCPayoff>&        x,
						    const boost::shared_ptr<QuantLib::RealMCPayoff>&        y,
			                bool                                                    permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCPayoff::Mult( x, y ));
	}

	RealMCMax::RealMCMax(  const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
						   const boost::shared_ptr<QuantLib::RealMCPayoff>&        x,
						   const boost::shared_ptr<QuantLib::RealMCPayoff>&        y,
			               bool                                                    permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCPayoff::Max( x, y ));
	}

	RealMCMin::RealMCMin(  const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
						   const boost::shared_ptr<QuantLib::RealMCPayoff>&        x,
						   const boost::shared_ptr<QuantLib::RealMCPayoff>&        y,
			               bool                                                    permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCPayoff::Min( x, y ));
	}

	RealMCPay::RealMCPay(  const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
						   const boost::shared_ptr<QuantLib::RealMCPayoff>&        x,
			               const QuantLib::Time                                    payTime,
			               bool                                                    permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCPayoff::Pay( x, payTime ));
	}

	RealMCCash::RealMCCash( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			                const QuantLib::Time  t,
					        const QuantLib::Time  T,
			                bool permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCPayoff::Cash( t, T ));
	}

	RealMCAsset::RealMCAsset(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
		const QuantLib::Time  t,
		const std::string&    alias,
		bool permanent) : RealMCPayoff(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCPayoff::Asset(t, alias));
	}

	RealMCAssetBarrierNoHit::RealMCAssetBarrierNoHit(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
		const QuantLib::Time  tStart,
		const QuantLib::Time  tEnd,
		const QuantLib::Real  downBarrier,
		const QuantLib::Real  upBarrier,
		const QuantLib::Real  downOrUpOrBoth,
		const std::string&    alias,
		bool permanent) : RealMCPayoff(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCPayoff::AssetBarrierNoHit(tStart, tEnd, downBarrier, upBarrier, downOrUpOrBoth, alias));
	}

	RealMCVanillaOption::RealMCVanillaOption( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			          const QuantLib::Time  t,
					  const QuantLib::Time  T,
					  const QuantLib::Real  strike,
					  const QuantLib::Real  callOrPut,
			          bool permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCPayoff::VanillaOption( t, T, strike, callOrPut ));
	}

	RealMCCache::RealMCCache(
		        const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
		        const boost::shared_ptr<QuantLib::RealMCPayoff>&        x,
		        bool                                                    permanent) : RealMCPayoff(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>( new QuantLib::RealMCPayoff::Cache(x));
	}

	RealMCLogical::RealMCLogical(const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
		const boost::shared_ptr<QuantLib::RealMCPayoff>&        x,
		const boost::shared_ptr<QuantLib::RealMCPayoff>&        y,
		const std::string&                                      op,
		bool                                                    permanent) : RealMCPayoff(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCPayoff::Logical(x, y, op));
	}

	RealMCIfThenElse::RealMCIfThenElse(const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
		const boost::shared_ptr<QuantLib::RealMCPayoff>&        x,
		const boost::shared_ptr<QuantLib::RealMCPayoff>&        y,
		const boost::shared_ptr<QuantLib::RealMCPayoff>&        z,
		bool                                                    permanent) : RealMCPayoff(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCPayoff::IfThenElse(x, y, z));
	}

	RealMCBasket::RealMCBasket(
		const boost::shared_ptr<ObjectHandler::ValueObject>&               properties,
		const std::vector<boost::shared_ptr<QuantLib::RealMCPayoff>> &     underlyings,
		const std::vector<QuantLib::Real>&                                 weights,
		const bool                                                         rainbow,
		bool                                                               permanent) : RealMCPayoff(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCPayoff::Basket(underlyings, weights, rainbow));
	}


	// particular rates payoffs

	RealMCGeneralSwaption::RealMCGeneralSwaption( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			                   const QuantLib::Time                                 t,
						       const std::vector<QuantLib::Time>&                   floatTimes,
						       const std::vector<QuantLib::Real>&                   floatWeights,
						       const std::vector<QuantLib::Time>&                   fixedTimes,
						       const std::vector<QuantLib::Real>&                   fixedWeights,
							   QuantLib::Real                                       strike,
							   QuantLib::Real                                       payOrRec,
			                   bool permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCRates::GeneralSwaption( t, floatTimes, floatWeights, fixedTimes, fixedWeights, strike, payOrRec ));
	}

	RealMCGeneralSwaption::RealMCGeneralSwaption(
		                       const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			                   const boost::shared_ptr<QuantLib::Swaption>&           swaption,
			                   const QuantLib::Handle<QuantLib::YieldTermStructure>&  discountCurve,
			                   bool permanent) : RealMCPayoff(properties,permanent) {
		// use swaption cash flow model
		QuantLib::SwaptionCashFlows cf(swaption,discountCurve);
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCRates::GeneralSwaption( cf.exerciseTimes()[0], cf.floatTimes(), cf.floatWeights(), cf.fixedTimes(), cf.annuityWeights(), swaption->underlyingSwap()->fixedRate(), swaption->underlyingSwap()->type() ));
	}

	RealMCSwapRate::RealMCSwapRate( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			            const QuantLib::Time                                 t,
						const std::vector<QuantLib::Time>&                   floatTimes,
						const std::vector<QuantLib::Real>&                   floatWeights,
						const std::vector<QuantLib::Time>&                   fixedTimes,
						const std::vector<QuantLib::Real>&                   annuityWeights,
			            bool permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCRates::SwapRate( t, floatTimes, floatWeights, fixedTimes, annuityWeights ));
	}

	RealMCSwapRate::RealMCSwapRate( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			            const boost::shared_ptr<QuantLib::Swaption>&           swaption,
			            const QuantLib::Handle<QuantLib::YieldTermStructure>&  discountCurve,
			            bool permanent) : RealMCPayoff(properties,permanent) {
		// use swaption cash flow model
		QuantLib::SwaptionCashFlows cf(swaption,discountCurve);
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCRates::SwapRate( cf.exerciseTimes()[0], cf.floatTimes(), cf.floatWeights(), cf.fixedTimes(), cf.annuityWeights() ));
	}						

	RealMCSwapRate::RealMCSwapRate( const boost::shared_ptr<ObjectHandler::ValueObject>&   properties,
			            const QuantLib::Time                                   fixingTime,
			            const boost::shared_ptr<QuantLib::SwapIndex>&          swapIndex,
			            const QuantLib::Handle<QuantLib::YieldTermStructure>&  discountCurve,
			            bool permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCRates::SwapRate( fixingTime, swapIndex, discountCurve ));
	}

	RealMCLiborRate::RealMCLiborRate  (
		                   const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
			               const QuantLib::Time                                    fixingTime,
					       const boost::shared_ptr<QuantLib::IborIndex>&           iborIndex,
					       const QuantLib::Handle<QuantLib::YieldTermStructure>&   discYTS, 
			               bool                                                    permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCRates::LiborRate( fixingTime, iborIndex, discYTS ));
	}

	RealMCLiborRate::RealMCLiborRate(
		                  const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
		                  const QuantLib::Time                                    fixingTime,
		                  const QuantLib::Time                                    startTime,
		                  const QuantLib::Time                                    endTime,
		                  const boost::shared_ptr<QuantLib::IborIndex>&           iborIndex,
		                  const QuantLib::Handle<QuantLib::YieldTermStructure>&   discYTS,
		                  bool                                                    permanent) : RealMCPayoff(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCRates::LiborRate(fixingTime, startTime, endTime, iborIndex, discYTS));
	}

	RealMCCashFlow::RealMCCashFlow(
		                   const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
						   const boost::shared_ptr<QuantLib::RealMCPayoff>&        x,
			               const QuantLib::Time                                    startTime,
			               const QuantLib::Time                                    payTime,
						   const bool                                              applyZCBAdjuster,
			               bool                                                    permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCRates::CashFlow( x, startTime, payTime, applyZCBAdjuster ));
	}

	RealMCScript::RealMCScript(const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
		                       const std::vector< std::string >&                       keys,
		                       const std::vector< boost::shared_ptr<QuantLib::RealMCPayoff> >&  payoffs,
		                       const std::vector< std::string >&                       script,
		                       const bool                                              overwrite,
		                       bool                                                    permanent) : RealMCPayoff(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCScript(keys, payoffs, script, overwrite));
	}


	// Cancellable note details and pricer

   RealMCLeg::RealMCLeg(  const boost::shared_ptr<ObjectHandler::ValueObject>&                 properties,
						   const std::vector< boost::shared_ptr<QuantLib::RealMCCashFlow> >&   cashflows,
			               bool                                                                permanent)
						   : ObjectHandler::LibraryObject<QuantLib::RealMCLeg>(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCLeg>(
			new QuantLib::RealMCRates::Leg( cashflows ));
	}

    RealMCSwap::RealMCSwap(  const boost::shared_ptr<ObjectHandler::ValueObject>&              properties,
						     const std::vector< boost::shared_ptr<QuantLib::RealMCLeg> >&      legs,
			                 bool                                                              permanent)
						   : ObjectHandler::LibraryObject<QuantLib::RealMCRates::Swap>(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCRates::Swap>(
			new QuantLib::RealMCRates::Swap( legs ));
	}

	RealMCCancellableNote::RealMCCancellableNote (  
		                     const boost::shared_ptr<ObjectHandler::ValueObject>&          properties,
                             const std::vector< boost::shared_ptr<QuantLib::RealMCLeg> >&  underlyings,
				             const std::vector< QuantLib::Time >&                          callTimes,
							 const std::vector< boost::shared_ptr<QuantLib::RealMCLeg> >&  earlyRedemptions,
							 const std::vector< boost::shared_ptr<QuantLib::RealMCLeg> >&  regressionVariables,
						     bool                                                          permanent)
							 : ObjectHandler::LibraryObject<QuantLib::RealMCCancellableNote>(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCCancellableNote>(
			new QuantLib::RealMCCancellableNote( underlyings, callTimes, earlyRedemptions, regressionVariables ));
	}

	RealAMCPricer::RealAMCPricer (  
		                 const boost::shared_ptr<ObjectHandler::ValueObject>&            properties,
			             const boost::shared_ptr<QuantLib::RealMCCancellableNote>&       note,
                         const boost::shared_ptr<QuantLib::RealMCSimulation>&            simulation,
						 const QuantLib::Real                                            regressionFraction,
						 const QuantLib::Size                                            maxPolynDegree,
			             bool                                                            permanent)
						 : ObjectHandler::LibraryObject<QuantLib::RealAMCPricer>(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealAMCPricer>(
			new QuantLib::RealAMCPricer( note, simulation, regressionFraction, maxPolynDegree ));
	}

	RealRegression::RealRegression (
		                  const boost::shared_ptr<ObjectHandler::ValueObject>&            properties,
			              const std::vector< std::vector<QuantLib::Real> >&               controls,
						  const std::vector<QuantLib::Real>                               observations,
				          const QuantLib::Size                                            maxDegree,
			              bool                                                            permanent)
						 : ObjectHandler::LibraryObject<QuantLib::RealRegression>(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealRegression>(
			new QuantLib::RealRegression( controls, observations, maxDegree ));
	}

	RealAMCMax::RealAMCMax(
		const boost::shared_ptr<ObjectHandler::ValueObject>&             properties,
		const std::vector< boost::shared_ptr<QuantLib::RealMCPayoff> >&  x,
		const std::vector< boost::shared_ptr<QuantLib::RealMCPayoff> >&  y,
		const std::vector< boost::shared_ptr<QuantLib::RealMCPayoff> >&  z,  // regression variables
		const QuantLib::Time                                             observationTime,
		const boost::shared_ptr<QuantLib::RealMCSimulation>&             simulation,
		const QuantLib::Size                                             maxPolynDegree,
		bool                                                             permanent)
		: RealMCPayoff(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealAMCPricer::MinMax(x, y, z, observationTime, +1.0, simulation, maxPolynDegree));
	}

	RealAMCMin::RealAMCMin(
		const boost::shared_ptr<ObjectHandler::ValueObject>&             properties,
		const std::vector< boost::shared_ptr<QuantLib::RealMCPayoff> >&  x,
		const std::vector< boost::shared_ptr<QuantLib::RealMCPayoff> >&  y,
		const std::vector< boost::shared_ptr<QuantLib::RealMCPayoff> >&  z,  // regression variables
		const QuantLib::Time                                             observationTime,
		const boost::shared_ptr<QuantLib::RealMCSimulation>&             simulation,
		const QuantLib::Size                                             maxPolynDegree,
		bool                                                             permanent)
		: RealMCPayoff(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealAMCPricer::MinMax(x, y, z, observationTime, -1.0, simulation, maxPolynDegree));
	}


	// more rates pricing and analysis objects

	RealMCAnnuity::RealMCAnnuity( 
		                 const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			             const QuantLib::Time                                 t,
						 const std::vector<QuantLib::Time>&                   payTimes,
						 const std::vector<QuantLib::Real>&                   payWeights,
			             bool permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCRates::Annuity( t, payTimes, payWeights ));
	}

	RealMCModelSwaption::RealMCModelSwaption(
		                       const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			                   const QuantLib::Time                                 t,
						       const std::vector<QuantLib::Time>&                   times,
						       const std::vector<QuantLib::Real>&                   payWeights,
							   QuantLib::Real                                       strike,
							   QuantLib::Real                                       payOrRec,
			                   bool permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCRates::ModelSwaption( t, times, payWeights, strike, payOrRec ));
	}

	RealMCModelCorrelation::RealMCModelCorrelation( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
						       const std::vector<QuantLib::Time>&                   times,
			                   const QuantLib::Time                                 T1,
			                   const QuantLib::Time                                 T2,
			                   bool permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCRates::ModelCorrelation( times, T1, T2 ));
	}

	RealMCForwardRateCorrelation::RealMCForwardRateCorrelation( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
						              const std::vector<QuantLib::Time>&                   times,
			                          const QuantLib::Time                                 T1,
			                          const QuantLib::Time                                 Term1,
			                          const QuantLib::Time                                 T2,
			                          const QuantLib::Time                                 Term2,
			                          bool permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCRates::ForwardRateCorrelation( times, T1, Term1, T2, Term2 ));
	}

	// commodity payoffs

	RealMCAverageFutureOption::RealMCAverageFutureOption(
		              const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			          const QuantLib::Time                                 t,
					  const std::vector<QuantLib::Time>&                   settlementTimes,
					  const std::vector<QuantLib::Real>&                   settlementWeights,
					  const QuantLib::Real                                 strike,
					  const QuantLib::Real                                 callOrPut,
			          bool                                                 permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCCommodity::AverageFutureOption( t, settlementTimes, settlementWeights, strike, callOrPut ));
	}

	RealMCAverageFutureCovariance::RealMCAverageFutureCovariance( 
		                               const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
						               const std::vector<QuantLib::Time>&                   observationTimes,
						               const std::vector<QuantLib::Time>&                   settlementTimesA,
						               const std::vector<QuantLib::Real>&                   settlementWeightsA,
					                   const QuantLib::Time                                 observationLagA,
						               const std::vector<QuantLib::Time>&                   settlementTimesB,
						               const std::vector<QuantLib::Real>&                   settlementWeightsB,
					                   const QuantLib::Time                                 observationLagB,
			                           bool                                                 useLogReturns,
			                           long                                                 calcType,
			                           bool                                                 permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCCommodity::AverageFutureCovariance( observationTimes, settlementTimesA, settlementWeightsA, observationLagA, settlementTimesB, settlementWeightsB, observationLagB, useLogReturns, calcType ));
	}

}

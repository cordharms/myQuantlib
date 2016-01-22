/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2015 Sebastian Schlenkrich

*/



#include <qlo/templatemontecarlo.hpp>

namespace QuantLibAddin {

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

	RealMCCash::RealMCCash( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			                    const QuantLib::Time  t,
					            const QuantLib::Time  T,
			                    bool permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCPayoff::Cash( t, T ));
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



	RealMCAnnuity::RealMCAnnuity( 
		                 const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			             const QuantLib::Time                                 t,
						 const std::vector<QuantLib::Time>&                   payTimes,
						 const std::vector<QuantLib::Real>&                   payWeights,
			             bool permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCPayoff::Annuity( t, payTimes, payWeights ));
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
			new QuantLib::RealMCPayoff::ModelSwaption( t, times, payWeights, strike, payOrRec ));
	}

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
			new QuantLib::RealMCPayoff::GeneralSwaption( t, floatTimes, floatWeights, fixedTimes, fixedWeights, strike, payOrRec ));
	}

	RealMCGeneralSwaption::RealMCGeneralSwaption(
		                       const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			                   const boost::shared_ptr<QuantLib::Swaption>&           swaption,
			                   const QuantLib::Handle<QuantLib::YieldTermStructure>&  discountCurve,
			                   bool permanent) : RealMCPayoff(properties,permanent) {
		// use swaption cash flow model
		QuantLib::SwaptionCashFlows cf(swaption,discountCurve);
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCPayoff::GeneralSwaption( cf.exerciseTimes()[0], cf.floatTimes(), cf.floatWeights(), cf.fixedTimes(), cf.annuityWeights(), swaption->underlyingSwap()->fixedRate(), swaption->underlyingSwap()->type() ));
	}

	RealMCSwapRate::RealMCSwapRate( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			            const QuantLib::Time                                 t,
						const std::vector<QuantLib::Time>&                   floatTimes,
						const std::vector<QuantLib::Real>&                   floatWeights,
						const std::vector<QuantLib::Time>&                   fixedTimes,
						const std::vector<QuantLib::Real>&                   annuityWeights,
			            bool permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCPayoff::SwapRate( t, floatTimes, floatWeights, fixedTimes, annuityWeights ));
	}

	RealMCSwapRate::RealMCSwapRate( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			            const boost::shared_ptr<QuantLib::Swaption>&           swaption,
			            const QuantLib::Handle<QuantLib::YieldTermStructure>&  discountCurve,
			            bool permanent) : RealMCPayoff(properties,permanent) {
		// use swaption cash flow model
		QuantLib::SwaptionCashFlows cf(swaption,discountCurve);
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCPayoff::SwapRate( cf.exerciseTimes()[0], cf.floatTimes(), cf.floatWeights(), cf.fixedTimes(), cf.annuityWeights() ));
	}						

	RealMCSwapRate::RealMCSwapRate( const boost::shared_ptr<ObjectHandler::ValueObject>&   properties,
			            const QuantLib::Time                                   fixingTime,
			            const boost::shared_ptr<QuantLib::SwapIndex>&          swapIndex,
			            const QuantLib::Handle<QuantLib::YieldTermStructure>&  discountCurve,
			            bool permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMC::SwapRate( fixingTime, swapIndex, discountCurve ));
	}


	RealMCModelCorrelation::RealMCModelCorrelation( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
						       const std::vector<QuantLib::Time>&                   times,
			                   const QuantLib::Time                                 T1,
			                   const QuantLib::Time                                 T2,
			                   bool permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCPayoff::ModelCorrelation( times, T1, T2 ));
	}


	RealMCForwardRateCorrelation::RealMCForwardRateCorrelation( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
						              const std::vector<QuantLib::Time>&                   times,
			                          const QuantLib::Time                                 T1,
			                          const QuantLib::Time                                 Term1,
			                          const QuantLib::Time                                 T2,
			                          const QuantLib::Time                                 Term2,
			                          bool permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCPayoff::ForwardRateCorrelation( times, T1, Term1, T2, Term2 ));
	}


	RealMCAverageFutureOption::RealMCAverageFutureOption(
		              const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			          const QuantLib::Time                                 t,
					  const std::vector<QuantLib::Time>&                   settlementTimes,
					  const std::vector<QuantLib::Real>&                   settlementWeights,
					  const QuantLib::Real                                 strike,
					  const QuantLib::Real                                 callOrPut,
			          bool                                                 permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMCPayoff::AverageFutureOption( t, settlementTimes, settlementWeights, strike, callOrPut ));
	}
	// more MC stuff

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
			new QuantLib::RealMCPayoff::AverageFutureCovariance( observationTimes, settlementTimesA, settlementWeightsA, observationLagA, settlementTimesB, settlementWeightsB, observationLagB, useLogReturns, calcType ));
	}


	RealMCFixedAmount::RealMCFixedAmount( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
						                  const QuantLib::Real                                 amount,
			                              bool                                                 permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMC::FixedAmount( amount ));
	}

	RealMCLiborRate::RealMCLiborRate  (
		                   const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
			               const QuantLib::Time                                    fixingTime,
				           const QuantLib::Time                                    startTime,
					       const QuantLib::Time                                    endTime,
					       const boost::shared_ptr<QuantLib::IborIndex>&           iborIndex,
					       const QuantLib::Handle<QuantLib::YieldTermStructure>&   discYTS, 
			               bool                                                    permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMC::LiborRate( fixingTime, startTime, endTime, iborIndex, discYTS ));
	}

	RealMCAxpy::RealMCAxpy ( const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
			                 const QuantLib::Real                                    a,
						     const boost::shared_ptr<QuantLib::RealMCPayoff>&        x,
						     const boost::shared_ptr<QuantLib::RealMCPayoff>&        y,
			                 bool                                                    permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMC::Axpy( a, x, y ));
	}

	RealMCMult::RealMCMult( const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
						    const boost::shared_ptr<QuantLib::RealMCPayoff>&        x,
						    const boost::shared_ptr<QuantLib::RealMCPayoff>&        y,
			                bool                                                    permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMC::Mult( x, y ));
	}

	RealMCMax::RealMCMax(  const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
						   const boost::shared_ptr<QuantLib::RealMCPayoff>&        x,
						   const boost::shared_ptr<QuantLib::RealMCPayoff>&        y,
			               bool                                                    permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMC::Max( x, y ));
	}

	RealMCMin::RealMCMin(  const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
						   const boost::shared_ptr<QuantLib::RealMCPayoff>&        x,
						   const boost::shared_ptr<QuantLib::RealMCPayoff>&        y,
			               bool                                                    permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMC::Min( x, y ));
	}

	RealMCPay::RealMCPay(  const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
						   const boost::shared_ptr<QuantLib::RealMCPayoff>&        x,
			               const QuantLib::Time                                    payTime,
			               bool                                                    permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMC::Pay( x, payTime ));
	}

	RealMCCashFlow::RealMCCashFlow( 
		                   const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
						   const boost::shared_ptr<QuantLib::RealMCPayoff>&        x,
			               const QuantLib::Time                                    startTime,
			               const QuantLib::Time                                    payTime,
						   const bool                                              applyZCBAdjuster,
			               bool                                                    permanent) : RealMCPayoff(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMCPayoff>(
			new QuantLib::RealMC::CashFlow( x, startTime, payTime, applyZCBAdjuster ));
	}

    RealMCLeg::RealMCLeg(  const boost::shared_ptr<ObjectHandler::ValueObject>&                  properties,
						   const std::vector< boost::shared_ptr<QuantLib::RealMC::CashFlow> >&   cashflows,
			               bool                                                                  permanent)
						   : ObjectHandler::LibraryObject<QuantLib::RealMC::Leg>(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMC::Leg>(
			new QuantLib::RealMC::Leg( cashflows ));
	}

    RealMCSwap::RealMCSwap(  const boost::shared_ptr<ObjectHandler::ValueObject>&                properties,
						     const std::vector< boost::shared_ptr<QuantLib::RealMC::Leg> >&      legs,
			                 bool                                                                permanent)
						   : ObjectHandler::LibraryObject<QuantLib::RealMC::Swap>(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMC::Swap>(
			new QuantLib::RealMC::Swap( legs ));
	}

	RealMCCancellableNote::RealMCCancellableNote (  
		                     const boost::shared_ptr<ObjectHandler::ValueObject>&            properties,
                             const std::vector< boost::shared_ptr<QuantLib::RealMC::Leg> >&  underlyings,
				             const std::vector< QuantLib::Time >&                            callTimes,
							 const std::vector< boost::shared_ptr<QuantLib::RealMC::Leg> >&  earlyRedemptions,
							 const std::vector< boost::shared_ptr<QuantLib::RealMC::Leg> >&  regressionVariables,
						     bool                                                            permanent)
							 : ObjectHandler::LibraryObject<QuantLib::RealMC::CancellableNote>(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealMC::CancellableNote>(
			new QuantLib::RealMC::CancellableNote( underlyings, callTimes, earlyRedemptions, regressionVariables ));
	}

	RealAMCPricer::RealAMCPricer (  
		                 const boost::shared_ptr<ObjectHandler::ValueObject>&            properties,
			             const boost::shared_ptr<QuantLib::RealMC::CancellableNote>&     note,
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



}

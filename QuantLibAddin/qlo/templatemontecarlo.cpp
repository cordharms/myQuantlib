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



}

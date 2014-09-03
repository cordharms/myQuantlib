/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2014 Sebastian Schlenkrich

 */

#include <qlo/basisswap.hpp>


namespace QuantLibAddin {


	BasisSwap::BasisSwap( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                          const std::vector<boost::shared_ptr<Leg> >&          legPtrs,
                          const std::vector<bool>&                             payer,
                          QuantLib::Size                                       parLegIndex,
				          bool												   calcParSpread,
						  bool												   permanent)
						  : Swap(properties, legPtrs, payer, permanent) {

        std::vector<QuantLib::Leg> legs(legPtrs.size());
        boost::shared_ptr<QuantLib::Leg> qlLeg;
        for (QuantLib::Size i=0; i<legPtrs.size(); ++i) {
            legPtrs[i]->getLibraryObject(qlLeg);
            legs[i] = *qlLeg;
        }

	    libraryObject_ = boost::shared_ptr<QuantLib::BasisSwap>(new
            QuantLib::BasisSwap(legs, payer, parLegIndex, calcParSpread));
	}

	BasisSwap::BasisSwap(
		       const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
		       const boost::shared_ptr<QuantLib::BasisSwapRateHelper>& rateHelper,
			   bool                                                    permanent)
			   : Swap(properties, rateHelper->basisSwap()->legs(),rateHelper->basisSwap()->payer(),permanent)
	{
	    libraryObject_ = boost::shared_ptr<QuantLib::BasisSwap>( rateHelper->basisSwap() );
	}


	BasisSwapEngine::BasisSwapEngine( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			             const std::vector<boost::shared_ptr<QuantLib::YieldTermStructure>>& discCurves,
						 const std::vector<QuantLib::Real>&             fxForDom,
			             boost::optional<bool>                          includeSettlementDateFlows,
						 QuantLib::Date                                 settlementDate,
						 QuantLib::Date                                 npvDate,
			             bool                                           permanent)
						 : PricingEngine(properties, permanent) {
	     
		std::vector<QuantLib::Handle<QuantLib::YieldTermStructure>> dc(discCurves.size());
        for (QuantLib::Size i=0; i<discCurves.size(); ++i) {
			dc[i] = QuantLib::Handle<QuantLib::YieldTermStructure>(discCurves[i]);
        }

	    libraryObject_ = boost::shared_ptr<QuantLib::BasisSwapEngine>(new
            QuantLib::BasisSwapEngine(dc, fxForDom, includeSettlementDateFlows, settlementDate, npvDate));
	}

	TenorSwapRateHelper::TenorSwapRateHelper(
		                     const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                             QuantLib::Real                          rate,
			                 const QuantLib::Period&                 tenor,
							 // swap conventions
							 const QuantLib::Period&                 fwdStart,
							 const QuantLib::Calendar&               paymentCalendar,
                             QuantLib::BusinessDayConvention         paymentBDC,
							 bool                                    spreadOnRecLeg,
                             // pay leg details are taken from IborIndex
							 const boost::shared_ptr<QuantLib::IborIndex>&  payIndex,
							 // rec leg details are taken from IborIndex
							 const boost::shared_ptr<QuantLib::IborIndex>&  recIndex,
							 // discount curve, forward curves are taken from Ibor indices
							 const QuantLib::Handle<QuantLib::YieldTermStructure>&    discountCurve,
			                 bool                                           permanent)
		: BasisSwapRateHelper(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::RateHelper>(new
            QuantLib::TenorSwapRateHelper(rate, tenor, fwdStart, paymentCalendar, paymentBDC, spreadOnRecLeg, payIndex, recIndex, discountCurve));
    }

	XCCYSwapRateHelper::XCCYSwapRateHelper(
		                     const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			                 QuantLib::Real                   rate,
			                 const QuantLib::Period&          tenor,
							 // swap conventions
							 const QuantLib::Period&          fwdStart,
							 const QuantLib::Calendar&        spotStartCalendar,
                             QuantLib::BusinessDayConvention  payBDC,
                             QuantLib::BusinessDayConvention  recBDC,
							 bool                             spreadOnRecLeg,
                             // pay leg details are taken from IborIndex
							 const boost::shared_ptr<QuantLib::IborIndex>&  payIndex,
							 // rec leg details are taken from IborIndex
							 const boost::shared_ptr<QuantLib::IborIndex>&  recIndex,
							 // discount curve, forward curves are taken from Ibor indices
							 const QuantLib::Handle<QuantLib::YieldTermStructure>&    payDiscCurve,
							 const QuantLib::Handle<QuantLib::YieldTermStructure>&    recDiscCurve,
							 // today's fx rates FOR/DOM
							 QuantLib::Real                    payFxForDom,
							 QuantLib::Real                    recFxForDom,
							 // should the swap be fx resetable on non-spreaded leg
							 bool                              fxResetable,
			                 bool                              permanent)
    : BasisSwapRateHelper(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::RateHelper>(new
            QuantLib::XCCYSwapRateHelper(rate, tenor, fwdStart, spotStartCalendar, payBDC, recBDC, spreadOnRecLeg,
				payIndex, recIndex, payDiscCurve, recDiscCurve, payFxForDom, recFxForDom, fxResetable));
    }

	SpreadYTS::SpreadYTS (
		                const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                        const QuantLib::Handle<QuantLib::YieldTermStructure>& baseCurve,
                        const QuantLib::Handle<QuantLib::YieldTermStructure>& sprdCurve,
						const QuantLib::Real alpha,
						bool permanent )
						: YieldTermStructure(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::SpreadYTS>(
			new QuantLib::SpreadYTS(baseCurve, sprdCurve, alpha));
	}


}




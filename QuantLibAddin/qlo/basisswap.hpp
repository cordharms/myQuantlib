/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2014 Sebastian Schlenkrich

 */

#ifndef qla_basisswap_hpp
#define qla_basisswap_hpp

#include <ql/types.hpp>
#include <ql/experimental/basisswap/basisswap.hpp>
#include <ql/experimental/basisswap/basisswapengine.hpp>
#include <ql/experimental/basisswap/basisswapratehelpers.hpp>
#include <ql/experimental/basisswap/spreadyieldtermstructure.hpp>
#include <qlo/leg.hpp>
#include <qlo/swap.hpp>
#include <qlo/pricingengines.hpp>
#include <qlo/ratehelpers.hpp>
#include <qlo/yieldtermstructures.hpp>


namespace QuantLibAddin {

	class BasisSwap : public Swap {
	public:
		BasisSwap( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                   const std::vector<boost::shared_ptr<Leg> >& legPtrs,
                   const std::vector<bool>& payer,
				   QuantLib::Size           parLegIndex,
				   bool                     calcParSpread,
				   bool                     permanent);

	    BasisSwap( const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
		           const boost::shared_ptr<QuantLib::BasisSwapRateHelper>& rateHelper,
			       bool                                                    permanent);
	};

	class BasisSwapEngine : public PricingEngine {
	public:
		BasisSwapEngine( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			             const std::vector<boost::shared_ptr<QuantLib::YieldTermStructure>>& discCurves,
						 const std::vector<QuantLib::Real>&             fxForDom,
			             boost::optional<bool>                          includeSettlementDateFlows,
						 QuantLib::Date                                 settlementDate,
						 QuantLib::Date                                 npvDate,
			             bool                                           permanent);
	};

	class BasisSwapRateHelper : public RateHelper {
	public:
		BasisSwapRateHelper( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			                 bool                                           permanent)
							 : RateHelper(properties, permanent) {}
	};

	class TenorSwapRateHelper : public BasisSwapRateHelper {
	public:
		TenorSwapRateHelper( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
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
			                 bool                                           permanent);
	};

	class XCCYSwapRateHelper : public BasisSwapRateHelper {
	public:
		XCCYSwapRateHelper(  const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
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
			                 bool                              permanent);
	};

    class SpreadYTS : public YieldTermStructure {
    public:
        SpreadYTS ( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                    const QuantLib::Handle<QuantLib::YieldTermStructure>& baseCurve,
                    const QuantLib::Handle<QuantLib::YieldTermStructure>& sprdCurve,
					const QuantLib::Real alpha,
			        bool permanent );
    };


}

#endif


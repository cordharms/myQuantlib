/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2014 Sebastian Schlenkrich

 */

#ifndef qla_basisswap_hpp
#define qla_basisswap_hpp

#include <ql/types.hpp>
#include <ql/experimental/basismodels/basisswap.hpp>
#include <ql/experimental/basismodels/basisswapengine.hpp>
#include <ql/experimental/basismodels/basisswapratehelpers.hpp>
#include <ql/experimental/basismodels/fxfwdratehelper.hpp>
#include <ql/experimental/basismodels/spreadyieldtermstructure.hpp>
#include <ql/experimental/basismodels/swaptioncfs.hpp>
#include <ql/experimental/basismodels/tenorswaptionvts.hpp>
#include <ql/experimental/basismodels/tenoroptionletvts.hpp>
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


    class SwaptionCashFlows : public ObjectHandler::LibraryObject<QuantLib::SwaptionCashFlows> {
	public:
		SwaptionCashFlows ( const boost::shared_ptr<ObjectHandler::ValueObject>&   properties,
			                const boost::shared_ptr<QuantLib::Swaption>&           swaption,
			                const QuantLib::Handle<QuantLib::YieldTermStructure>&  discountCurve,
						    bool                                                   contTenorSpread,
			                bool                                                   permanent );
	};

	class TenorSwaptionVTS : public SwaptionVolatilityStructure {
	public:
		TenorSwaptionVTS( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                          const QuantLib::Handle<QuantLib::SwaptionVolatilityStructure>&  baseVTS,
		                  const QuantLib::Handle<QuantLib::YieldTermStructure>&           discountCurve,
		                  const boost::shared_ptr<QuantLib::IborIndex>&                   baseIndex,
		                  const boost::shared_ptr<QuantLib::IborIndex>&                   targIndex,
		                  const QuantLib::Period&                                         baseFixedFreq,
		                  const QuantLib::Period&                                         targFixedFreq,
		                  const QuantLib::DayCounter&                                     baseFixedDC,
		                  const QuantLib::DayCounter&                                     targFixedDC,
                          bool                                                            permanent );
	};

	OH_LIB_CLASS(TenorOptionletVTSCorrelationStructure, QuantLib::TenorOptionletVTSCorrelationStructure);

	class TwoParameterCorrelation : public TenorOptionletVTSCorrelationStructure {
	public:
		TwoParameterCorrelation( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                                 const boost::shared_ptr<QuantLib::Interpolation>&    rhoInf, 
                                 const boost::shared_ptr<QuantLib::Interpolation>&    beta, 
                                 bool                                                 permanent );
	};

	class TenorOptionletVTS : public OptionletVolatilityStructure {
	public:
		TenorOptionletVTS( const boost::shared_ptr<ObjectHandler::ValueObject>&             properties,
			               const QuantLib::Handle<QuantLib::OptionletVolatilityStructure>&  baseVTS,
			               const boost::shared_ptr<QuantLib::IborIndex>&                    baseIndex,
		                   const boost::shared_ptr<QuantLib::IborIndex>&                    targIndex,
						   const boost::shared_ptr<QuantLib::TenorOptionletVTS::CorrelationStructure>&  correlation,
                           bool                                                             permanent );

	};

    class FxFwdRateHelper : public RateHelper {
          public:
    		FxFwdRateHelper( const boost::shared_ptr<ObjectHandler::ValueObject>&  properties,
    						 const QuantLib::Currency                              baseCurrency,
    						 const QuantLib::Currency                              counterCurrency,
    						 const QuantLib::Rate                                  fxSpot,
    						 const QuantLib::Natural                               spotLag,
    		                 const QuantLib::Calendar                              spotLagCal,
    						 const QuantLib::BusinessDayConvention                 spotLagConv,
    						 const QuantLib::Period                                swapTerm,
    						 const QuantLib::Handle<QuantLib::Quote>               points,
    			             const QuantLib::Real                                  unit,
    					     const QuantLib::Handle<QuantLib::YieldTermStructure>  baseCcyDiscTermStructureHandle,
    						 const QuantLib::Handle<QuantLib::YieldTermStructure>  cntrCcyDiscTermStructureHandle,
    						 const QuantLib::FxFwdRateHelper::BootstrapType        bootstrapBaseOrCounter,
    					     bool                                                  permanent);
    	};

}

#endif


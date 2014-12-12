/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2010 Sebastian Schlenkrich

 */

#ifndef qla_templatemodells_hpp
#define qla_templatemodells_hpp

#include <ql/types.hpp>
//#include <ql/experimental/templatehullwhite/adtageo/adtageo.hpp>
//#include <ql/experimental/template/auxilliaries/MinimADVariable2.hpp>

#include <ql/experimental/template/hullwhite/hullwhitemodels.hpp>

#include <qlo/baseinstruments.hpp>

/*
#include <ql/experimental/templatehullwhite/adtageohullwhitemodel.hpp>
#include <ql/experimental/templatehullwhite/swaptionproperties.hpp>
#include <ql/experimental/templatehullwhite/fixedratebondoption.hpp>
#include <ql/experimental/templatehullwhite/bondoptionengine.hpp>
#include <ql/instruments/bonds/fixedratebond.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/experimental/templatehullwhite/sabrswaptioncube.hpp>

#include <qlo/vanillaswap.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/pricingengines.hpp>
#include <qlo/indexes/iborindex.hpp>
*/

namespace QuantLib {
    template <class T>
    class Handle;

	class TemplateModel;
}

namespace QuantLibAddin {

    OH_LIB_CLASS(TemplateModel, QuantLib::TemplateModel);

    class RealHullWhiteModel : public TemplateModel {
      public:
		  RealHullWhiteModel(const boost::shared_ptr<ObjectHandler::ValueObject>& properties, bool permanent) : TemplateModel(properties,permanent) {}
          RealHullWhiteModel(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
							 const QuantLib::Handle<QuantLib::YieldTermStructure>& hYTS,
							 const QuantLib::Real mean,
							 const std::vector<QuantLib::Time>& volaTimes,
							 const std::vector<QuantLib::Real>& volaValues,
							 bool permanent);
    };

	class MinimADHullWhiteModel : public RealHullWhiteModel {
      public:
          MinimADHullWhiteModel(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
							 const QuantLib::Handle<QuantLib::YieldTermStructure>& hYTS,
							 const QuantLib::Real mean,
							 const std::vector<QuantLib::Time>& volaTimes,
							 const std::vector<QuantLib::Real>& volaValues,
							 bool permanent);
    };

/*
	class FixedRateBondOption : public Instrument {
	public:
		FixedRateBondOption( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
							 const boost::shared_ptr<QuantLib::FixedRateBond>& underlyingBond,
							 const std::vector<QuantLib::Date>& exerciseDates,
							 const std::vector<QuantLib::Real>& dirtyStrikeValues,
						     const QuantLib::Option::Type callOrPut,
							 bool permanent);
        FixedRateBondOption ( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                              const boost::shared_ptr<QuantLib::SwaptionProperties>& swaptionProperties,
                              bool permanent);
	};

    // helper container for reference swaption properties
	// this is necessary since qlgensrc allows only a limited number of parametrs
	class SwaptionProperties : public ObjectHandler::LibraryObject<QuantLib::SwaptionProperties> {
	public:
		SwaptionProperties(    const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
							   //  fixed leg
							   const QuantLib::Rate                                    fixedRate,
							   const QuantLib::DayCounter&                             fixedDayCount,
						       const QuantLib::Period&                                 fixedTenor,
						       const QuantLib::Calendar&                               fixedCalendar,
                               const QuantLib::BusinessDayConvention                   fixedConvention,
						       //  floating leg
						       const boost::shared_ptr<QuantLib::IborIndex>&           iborIndex,
						       const QuantLib::DayCounter&                             floatDayCount,    // should be consistent to iborIndex
						       const QuantLib::Period&                                 floatTenor,       // should be consistent to iborIndex
						       const QuantLib::Calendar&                               floatCalendar,    // should be consistent to iborIndex
                               const QuantLib::BusinessDayConvention                   floatConvention,  // should be consistent to iborIndex
						       //  additional general properties
						       const QuantLib::VanillaSwap::Type                       swapType,         // payer or receiver swap
						       const QuantLib::Date                                    swapMaturity,     // we calibrate swaptions with equal swap maturities     
						       const QuantLib::BusinessDayConvention                   paymentConvention,
						       // swaption properties
					           const std::vector<QuantLib::Date>&                      exerciseDates,    // option exercise dates should be consistent to bond option exercise dates
					           const std::vector<QuantLib::Date>&                      settlementDates,  // effective (start) date of underlying swap, usually two BD after exercise
						       const QuantLib::Settlement::Type                        cashOrPhysical,
						       const QuantLib::Handle<QuantLib::YieldTermStructure>&   discountCurve,
						       const QuantLib::Handle<QuantLib::SwaptionVolatilityStructure>&  swaptionVola,
							   bool                                                    permanent);

		SwaptionProperties(    const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
                               //  fixed leg
							   const QuantLib::Rate                                    fixedRate,
							   const QuantLib::DayCounter&                             fixedDayCount,
						       const QuantLib::Period&                                 fixedTenor,
						       const QuantLib::Calendar&                               fixedCalendar,
                               const QuantLib::BusinessDayConvention                   fixedConvention,
						       //  floating leg
						       const boost::shared_ptr<QuantLib::IborIndex>&           iborIndex,
						       const QuantLib::DayCounter&                             floatDayCount,    // should be consistent to iborIndex
						       const QuantLib::Period&                                 floatTenor,       // should be consistent to iborIndex
						       const QuantLib::Calendar&                               floatCalendar,    // should be consistent to iborIndex
                               const QuantLib::BusinessDayConvention                   floatConvention,  // should be consistent to iborIndex
						       //  additional general properties
						       const QuantLib::VanillaSwap::Type                       swapType,         // payer or receiver swap
						       const QuantLib::Date                                    swapMaturity,     // we calibrate swaptions with equal swap maturities     
						       const QuantLib::BusinessDayConvention                   paymentConvention,
						       // swaption properties
                               const boost::shared_ptr<QuantLib::Schedule>&            settlementSchedule,  // anker point are the settlent dates
                               const QuantLib::Calendar&                               exerciseCalendar,
					           const QuantLib::Period&                                 exerciseOffset,      // exercise date is exerciseDate + exerciseOffset (e.g. -2D)
						       const QuantLib::Settlement::Type                        cashOrPhysical,
						       const QuantLib::Handle<QuantLib::YieldTermStructure>&             discountCurve,
						       const QuantLib::Handle<QuantLib::SwaptionVolatilityStructure>&    swaptionVola,
                               bool                                                    permanent);
	};

	class BondOptionEngine : public PricingEngine {
	public:
	    // constructor with given model and no calibration
		BondOptionEngine( const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
						  const boost::shared_ptr<QuantLib::RealHullWhiteModel>&  model,
						  const QuantLib::Size                                    dimension,
						  const QuantLib::Real                                    gridRadius,
						  const QuantLib::Real                                    bermudanTolerance,
						  bool                                                    permanent);
	    // constructor with given model and reference European prices
		BondOptionEngine( const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
						  const boost::shared_ptr<QuantLib::RealHullWhiteModel>&  model,
						  const QuantLib::Size                                    dimension,
						  const QuantLib::Real                                    gridRadius,
						  const QuantLib::Real                                    bermudanTolerance,
						  const std::vector<QuantLib::Real>&                      referenceEuropeanPrices,
						  const QuantLib::Real                                    calibToleranceVola,
						  bool                                                    permanent);

	    // constructor with given model and reference Swap
		BondOptionEngine( const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
						  const boost::shared_ptr<QuantLib::RealHullWhiteModel>&  model,
						  const QuantLib::Size                                    dimension,
						  const QuantLib::Real                                    gridRadius,
						  const QuantLib::Real                                    bermudanTolerance,
						  //    underlying vanilla swaption properties
						  const boost::shared_ptr<QuantLib::SwaptionProperties>&  swaptionProperties,
						  const QuantLib::Real                                    calibToleranceVola,
						  bool                                                    permanent);
	};

	typedef SwaptionProperties SwaptionPropertiesType;

*/


}

#endif


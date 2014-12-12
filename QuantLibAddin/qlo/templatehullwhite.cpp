/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2010 Sebastian Schlenkrich

*/


#include <qlo/baseinstruments.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/pricingengines.hpp>

#include <qlo/templatehullwhite.hpp>

namespace QuantLibAddin {

	RealHullWhiteModel::RealHullWhiteModel(
						   const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
						   const QuantLib::Handle<QuantLib::YieldTermStructure>& hYTS,
						   const QuantLib::Real mean,
						   const std::vector<QuantLib::Time>& volaTimes,
						   const std::vector<QuantLib::Real>& volaValues,
						   bool permanent) : TemplateModel(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealHullWhiteModel>(
			new QuantLib::RealHullWhiteModel( hYTS, mean, volaTimes, volaValues ));
    }

	MinimADHullWhiteModel::MinimADHullWhiteModel(
						   const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
						   const QuantLib::Handle<QuantLib::YieldTermStructure>& hYTS,
						   const QuantLib::Real mean,
						   const std::vector<QuantLib::Time>& volaTimes,
						   const std::vector<QuantLib::Real>& volaValues,
						   bool permanent) : RealHullWhiteModel(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::MinimADHullWhiteModel>(
			new QuantLib::MinimADHullWhiteModel( hYTS, mean, volaTimes, volaValues ));
    }

/*
	FixedRateBondOption::FixedRateBondOption(
							const boost::shared_ptr<ObjectHandler::ValueObject> &properties,
							const boost::shared_ptr<QuantLib::FixedRateBond> &underlyingBond,
							const std::vector<QuantLib::Date> &exerciseDates,
							const std::vector<QuantLib::Real> &dirtyStrikeValues,
							const QuantLib::Option::Type callOrPut,
							bool permanent) : Instrument(properties,permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::FixedRateBondOption>(
			new QuantLib::FixedRateBondOption(underlyingBond, exerciseDates, dirtyStrikeValues,callOrPut));
	}

    FixedRateBondOption::FixedRateBondOption(
							const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                            const boost::shared_ptr<QuantLib::SwaptionProperties>& swaptionProperties,
                            bool permanent) : Instrument(properties,permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::FixedRateBondOption>(
			new QuantLib::FixedRateBondOption(swaptionProperties));
	}


	// constructor with given model and no calibration
	BondOptionEngine::BondOptionEngine(
							const boost::shared_ptr<ObjectHandler::ValueObject> &properties,
							const boost::shared_ptr<QuantLib::RealHullWhiteModel> &model,
							const QuantLib::Size dimension,
						    const QuantLib::Real gridRadius,
							const QuantLib::Real bermudanTolerance,
							bool permanent) : PricingEngine(properties,permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::BondOptionEngine>(
			new QuantLib::BondOptionEngine(model,dimension,gridRadius,bermudanTolerance));
	}

    // constructor with given model and reference European prices
	BondOptionEngine::BondOptionEngine(
						  const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
						  const boost::shared_ptr<QuantLib::RealHullWhiteModel>&  model,
						  const QuantLib::Size                                    dimension,
						  const QuantLib::Real                                    gridRadius,
						  const QuantLib::Real                                    bermudanTolerance,
						  const std::vector<QuantLib::Real>&                      referenceEuropeanPrices,
						  const QuantLib::Real                                    calibToleranceVola,
						  bool                                                    permanent)
						  : PricingEngine(properties,permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::BondOptionEngine>(
			new QuantLib::BondOptionEngine(model,dimension,gridRadius,bermudanTolerance,
			referenceEuropeanPrices,calibToleranceVola));
	}

	// helper container for reference swaption properties
	SwaptionProperties::SwaptionProperties(
							   const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
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
							   bool                                                    permanent)
							   : ObjectHandler::LibraryObject<QuantLib::SwaptionProperties>(properties, permanent) {
	   libraryObject_ = boost::shared_ptr<QuantLib::SwaptionProperties>(
		   new QuantLib::SwaptionProperties(fixedRate,fixedDayCount,fixedTenor,fixedCalendar,fixedConvention,
				iborIndex,floatDayCount,floatTenor,floatCalendar,floatConvention,swapType,swapMaturity,paymentConvention,
				exerciseDates,settlementDates,cashOrPhysical,discountCurve,swaptionVola));
	}
	// helper container for reference swaption properties
	SwaptionProperties::SwaptionProperties(
							   const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
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
						       const QuantLib::Handle<QuantLib::YieldTermStructure>&   discountCurve,
						       const QuantLib::Handle<QuantLib::SwaptionVolatilityStructure>&  swaptionVola,
							   bool                                                    permanent)
							   : ObjectHandler::LibraryObject<QuantLib::SwaptionProperties>(properties, permanent) {
	   libraryObject_ = boost::shared_ptr<QuantLib::SwaptionProperties>(
		   new QuantLib::SwaptionProperties(fixedRate,fixedDayCount,fixedTenor,fixedCalendar,fixedConvention,
				iborIndex,floatDayCount,floatTenor,floatCalendar,floatConvention,swapType,swapMaturity,paymentConvention,
				*settlementSchedule, exerciseCalendar, exerciseOffset ,cashOrPhysical,discountCurve,swaptionVola));
	}


	// constructor with given model and reference Swap
	BondOptionEngine::BondOptionEngine(
						  const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
						  const boost::shared_ptr<QuantLib::RealHullWhiteModel>&  model,
						  const QuantLib::Size                                    dimension,
						  const QuantLib::Real                                    gridRadius,
						  const QuantLib::Real                                    bermudanTolerance,
						  //    underlying vanilla swap properties
						  const boost::shared_ptr<QuantLib::SwaptionProperties>&  swaptionProperties,
						  const QuantLib::Real                                    calibToleranceVola,
						  bool                                                    permanent) 
						  : PricingEngine(properties,permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::BondOptionEngine>(
			new QuantLib::BondOptionEngine(model,dimension,gridRadius,bermudanTolerance,
					swaptionProperties,calibToleranceVola));
	}

*/

}

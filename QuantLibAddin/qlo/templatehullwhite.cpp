/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2010 Sebastian Schlenkrich

*/



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
							 const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
							 const boost::shared_ptr<QuantLib::Swaption>&            swaption,
							 const QuantLib::Handle<QuantLib::YieldTermStructure>&   discountCurve,
							 bool                                                    contTenorSpread,						
						     bool                                                    permanent)
							 : Instrument(properties,permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::FixedRateBondOption>(
			new QuantLib::FixedRateBondOption(swaption, discountCurve, contTenorSpread));
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

}

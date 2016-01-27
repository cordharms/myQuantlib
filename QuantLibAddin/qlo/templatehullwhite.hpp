/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2010 Sebastian Schlenkrich

 */

#ifndef qla_templatemodells_hpp
#define qla_templatemodells_hpp

#include <ql/types.hpp>

#include <ql/experimental/templatemodels/hullwhite/hullwhitemodels.hpp>
#include <ql/experimental/templatemodels/hullwhite/fixedratebondoption.hpp>
#include <ql/experimental/templatemodels/hullwhite/bondoptionengine.hpp>
#include <ql/instruments/bonds/fixedratebond.hpp>
#include <ql/instruments/swaption.hpp>

#include <qlo/baseinstruments.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/pricingengines.hpp>

/*
#include <ql/experimental/templatehullwhite/adtageohullwhitemodel.hpp>
#include <ql/experimental/templatehullwhite/swaptionproperties.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/experimental/templatehullwhite/sabrswaptioncube.hpp>

#include <qlo/vanillaswap.hpp>
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

	class FixedRateBondOption : public Instrument {
	public:
		FixedRateBondOption( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
							 const boost::shared_ptr<QuantLib::FixedRateBond>& underlyingBond,
							 const std::vector<QuantLib::Date>& exerciseDates,
							 const std::vector<QuantLib::Real>& dirtyStrikeValues,
						     const QuantLib::Option::Type callOrPut,
							 bool permanent);

		FixedRateBondOption( const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
							 const boost::shared_ptr<QuantLib::Swaption>&            swaption,
							 const QuantLib::Handle<QuantLib::YieldTermStructure>&   discountCurve,
							 bool                                                    contTenorSpread,						
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
	};

}

#endif


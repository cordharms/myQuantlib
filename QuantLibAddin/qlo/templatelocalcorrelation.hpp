/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2017 Cord Harms

 */

#ifndef qla_localcorrmodel_hpp
#define qla_localcorrmodel_hpp

#include <ql/types.hpp>

#include <qlo/termstructures.hpp>
#include <qlo/pricingengines.hpp>
#include <qlo/indexes/iborindex.hpp>

#include <ql/experimental/templatemodels/multiasset/localcorrelationbsmodel.hpp>
#include <ql/experimental/termstructures/localcorrtermstructure.hpp>


namespace QuantLib {
    template <class T>
    class Handle;
}


namespace QuantLibAddin {

	OH_LIB_CLASS(LocalCorrTermStructure, QuantLib::LocalCorrTermStructure); //for abstract classes

	class LocalCorrelationBSModel : public ObjectHandler::LibraryObject<QuantLib::LocalCorrelationBSModel> {
	public:
		LocalCorrelationBSModel(
			const boost::shared_ptr<ObjectHandler::ValueObject>&                            properties,
			const QuantLib::Handle<QuantLib::YieldTermStructure>&							termStructure,
			const std::vector<std::string>&                                                 aliases,
			const std::vector<boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>>& processes,
			const boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>&				processToCal,
			const QuantLib::Handle<QuantLib::LocalCorrTermStructure>&						localCorrTermStructure,
			bool                                                                            permanent);
	};
	

}

#endif


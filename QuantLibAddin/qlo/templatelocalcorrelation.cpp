/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2010 Sebastian Schlenkrich

 */


#include <qlo/templatelocalcorrelation.hpp>

#include <boost/algorithm/string.hpp>


namespace QuantLibAddin {

	LocalCorrelationBSModel::LocalCorrelationBSModel(
		const boost::shared_ptr<ObjectHandler::ValueObject>&                            properties,
		const QuantLib::Handle<QuantLib::YieldTermStructure>&							termStructure,
		const std::vector<std::string>&                                                 aliases,
		const std::vector<boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>>& processes,
		const boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>&				processToCal,
		const QuantLib::Handle<QuantLib::LocalCorrTermStructure>&						localCorrTermStructure,
		bool                                                                            permanent)
		: ObjectHandler::LibraryObject<QuantLib::LocalCorrelationBSModel>(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::LocalCorrelationBSModel>(
			new QuantLib::LocalCorrelationBSModel(termStructure, aliases, processes, processToCal, localCorrTermStructure));
	}


}




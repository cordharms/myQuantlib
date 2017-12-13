/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2010 Sebastian Schlenkrich

 */


#include <qlo/vanillalocalvolmodel.hpp>

// #include <boost/algorithm/string.hpp>


namespace QuantLibAddin {

	VanillaLocalVolModel::VanillaLocalVolModel(
		const boost::shared_ptr<ObjectHandler::ValueObject>&  properties,
		const QuantLib::Time                                  T,
		const QuantLib::Real                                  S0,
		const QuantLib::Real                                  sigmaATM,
		const std::vector<QuantLib::Real>&                    Sp,
		const std::vector<QuantLib::Real>&                    Sm,
		const std::vector<QuantLib::Real>&                    Mp,
		const std::vector<QuantLib::Real>&                    Mm,
		const QuantLib::Size                                  maxCalibrationIters,
		const QuantLib::Size                                  onlyForwardCalibrationIters,
		const bool                                            adjustATMFlag,
		const bool                                            enableLogging,
		const bool                                            useInitialMu,
		const  QuantLib::Real                                 initialMu,
		bool                                                  permanent)
		: ObjectHandler::LibraryObject<QuantLib::VanillaLocalVolModel>(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::VanillaLocalVolModel>(
			new QuantLib::VanillaLocalVolModel(T,S0,sigmaATM,Sp,Sm,Mp,Mm,maxCalibrationIters,onlyForwardCalibrationIters,adjustATMFlag,enableLogging,useInitialMu,initialMu));
	}


}




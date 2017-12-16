/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2010 Sebastian Schlenkrich

 */

#ifndef qla_vanillalocalvolmodel_hpp
#define qla_vanillalocalvolmodel_hpp

#include <ql/types.hpp>

#include <qlo/baseinstruments.hpp>


#include <ql/experimental/templatemodels/vanillalocalvol/vanillalocalvolmodels.hpp>


namespace QuantLib {
    template <class T>
    class Handle;
	class StochasticProcess;
	class VanillaLocalVolModelSmileSection;
}


namespace QuantLibAddin {


	class VanillaLocalVolModel : public ObjectHandler::LibraryObject<QuantLib::VanillaLocalVolModel> {
	public:
		VanillaLocalVolModel(
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
			bool                                                  permanent);

		VanillaLocalVolModel(
			const boost::shared_ptr<ObjectHandler::ValueObject>&  properties,
			const boost::shared_ptr<QuantLib::VanillaLocalVolModelSmileSection> smileSection,
			bool                                                  permanent);
	};

}

#endif


/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2010 Sebastian Schlenkrich

 */

#ifndef qla_vanillalocalvolmodel_hpp
#define qla_vanillalocalvolmodel_hpp

#include <ql/types.hpp>

#include <qlo/baseinstruments.hpp>

 // #include <qlo/vanillaswap.hpp>
// #include <qlo/termstructures.hpp>
// #include <qlo/pricingengines.hpp>
// #include <qlo/indexes/iborindex.hpp>

// #include <ql/processes/hestonprocess.hpp>
// #include <ql/models/equity/hestonmodel.hpp>
// #include <ql/pricingengines/vanilla/analytichestonengine.hpp>
// #include <ql/pricingengines/vanilla/analytichestonengine.hpp>
// #include <ql/experimental/templatemodels/stochvol/stochvolmodels.hpp>
// #include <ql/experimental/templatemodels/stochvol/stochvolcalibrator.hpp>
// 
// #include <ql/experimental/models/hestonslvfdmmodel.hpp>

// #include <ql/models/equity/hestonmodelhelper.hpp>
// #include <ql/termstructures/volatility/equityfx/hestonblackvolsurface.hpp>
// 
// #include <ql/experimental/templatemodels/multiasset/multiassetbsmodel.hpp>

#include <ql/experimental/templatemodels/vanillalocalvol/vanillalocalvolmodels.hpp>


// #include <qlo/templatequasigaussian.hpp>


namespace QuantLib {
    template <class T>
    class Handle;
	class StochasticProcess;
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
	};

}

#endif


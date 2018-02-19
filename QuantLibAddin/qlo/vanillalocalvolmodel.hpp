/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2010 Sebastian Schlenkrich

 */

#ifndef qla_vanillalocalvolmodel_hpp
#define qla_vanillalocalvolmodel_hpp

#include <ql/types.hpp>

#include <qlo/baseinstruments.hpp>
#include <qlo/smilesection.hpp>

#include <ql/experimental/templatemodels/vanillalocalvol/vanillalocalvolmodels.hpp>
#include <ql/experimental/templatemodels/vanillalocalvol/vanillalocalvolsmilesection.hpp>

#include <qlo/templatestochasticprocess.hpp>


namespace QuantLib {
    template <class T>
    class Handle;
	class StochasticProcess;
	class VanillaLocalVolModelSmileSection;
}


namespace QuantLibAddin {


	class VanillaLocalVolModel : public RealStochasticProcess {
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

	class VanillaLocalVolModelSmileSection : public SmileSection {
	public:
		VanillaLocalVolModelSmileSection(
			const boost::shared_ptr<ObjectHandler::ValueObject>&        properties,
			const boost::shared_ptr<QuantLib::VanillaLocalVolModel>&    model,
			const QuantLib::DayCounter&                                 dc,
			const QuantLib::VolatilityType                              type,
			const QuantLib::Rate                                        shift,
			bool permanent);

		VanillaLocalVolModelSmileSection(
			const boost::shared_ptr<ObjectHandler::ValueObject>&      properties,
			const QuantLib::Date&                                     expiryDate,
			const QuantLib::Rate&                                     forward,
			const std::vector<QuantLib::Rate>&                        relativeStrikes,
			const std::vector<QuantLib::Volatility>&                  smileVolatilities,
			const QuantLib::Real                                      extrapolationRelativeStrike,
			const QuantLib::Real                                      extrapolationSlope,
			bool                                                      vegaWeighted,
			const boost::shared_ptr<QuantLib::EndCriteria>&           endCriteria,
			const boost::shared_ptr<QuantLib::OptimizationMethod>&    method,
			const QuantLib::DayCounter&                               dc,
			const QuantLib::Date&                                     referenceDate,
			const QuantLib::VolatilityType                            type,
			const QuantLib::Rate                                      shift,
			const boost::shared_ptr<QuantLib::VanillaLocalVolModel>&  model,
			const QuantLib::Real                                      minSlope,   //  lower boundary for m in calibration
			const QuantLib::Real                                      maxSlope,   //  upper boundary for m in calibration
			const QuantLib::Real                                      alpha,      //  Tikhonov alpha
			bool                                                      permanent);

		VanillaLocalVolModelSmileSection(
			const boost::shared_ptr<ObjectHandler::ValueObject>&      properties,
			const QuantLib::Date&                                     expiryDate,
			const QuantLib::Rate&                                     forward,
			const QuantLib::Volatility&                               atmVolatility,
			const boost::shared_ptr<QuantLib::VanillaLocalVolModelSmileSection>& smile1,
			const boost::shared_ptr<QuantLib::VanillaLocalVolModelSmileSection>& smile2,
			const QuantLib::Real&                                     rho,
			const bool                                                calcSimple,
			const QuantLib::DayCounter&                               dc,
			const QuantLib::Date&                                     referenceDate,
			const QuantLib::VolatilityType                            type,
			const QuantLib::Rate                                      shift,
			bool                                                      permanent);

	};  // class VanillaLocalVolModelSmileSection


}

#endif


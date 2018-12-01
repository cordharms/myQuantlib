/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2010 Sebastian Schlenkrich

 */

#ifndef qla_vanillalocalvolmodel_hpp
#define qla_vanillalocalvolmodel_hpp

#include <ql/types.hpp>

#include <qlo/baseinstruments.hpp>
#include <qlo/smilesection.hpp>
#include <qlo/termstructures.hpp>

// dev implementation based on template
#include <ql/experimental/templatemodels/vanillalocalvol/vanillalocalvolmodels.hpp>

// re-factored implementation
#include <ql/experimental/vanillalocalvolmodel/vanillalocalvolmodel.hpp>
#include <ql/experimental/vanillalocalvolmodel/vanillalocalvolsmilesection.hpp>
#include <ql/experimental/vanillalocalvolmodel/vanillalocalvoltermstructures.hpp>

#include <qlo/templatestochasticprocess.hpp>


namespace QuantLib {
    template <class T>
    class Handle;
	class StochasticProcess;
}


namespace QuantLibAddin {

	class VanillaLocalVolModelDev : public RealStochasticProcess {
	public:
		VanillaLocalVolModelDev(
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

	// this is an auxillary container for a column of smiles
	class VanillaLocalVolCMSTS : public ObjectHandler::LibraryObject< std::vector< boost::shared_ptr<QuantLib::VanillaLocalVolModelSmileSection> > >{
	private:
		const QuantLib::Period swapTerm_;
	public:
		VanillaLocalVolCMSTS(
			const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
			const QuantLib::Period&                                 swapTerm,
			const std::vector< boost::shared_ptr<QuantLib::VanillaLocalVolModelSmileSection> >&  smiles,
			bool                                                    permanent);
		const QuantLib::Period swapTerm() const { return swapTerm_; }
	};

	class VanillaLocalVolSwaptionVTS : public SwaptionVolatilityStructure {
	public:
		VanillaLocalVolSwaptionVTS(
			const boost::shared_ptr<ObjectHandler::ValueObject>&              properties,
			const boost::shared_ptr<QuantLib::SwaptionVolatilityStructure>&   atmVolTS,
			const std::vector< boost::shared_ptr<VanillaLocalVolCMSTS> >&     cmsTS,
			const boost::shared_ptr<QuantLib::SwapIndex>&                     index,
			bool                                                              permanent);
	};


}

#endif


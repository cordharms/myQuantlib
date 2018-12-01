/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2010 Sebastian Schlenkrich

 */


#include <qlo/vanillalocalvolmodel.hpp>


// #include <boost/algorithm/string.hpp>


namespace QuantLibAddin {

	VanillaLocalVolModelDev::VanillaLocalVolModelDev(
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
		: RealStochasticProcess(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::VanillaLocalVolModelDev>(
			new QuantLib::VanillaLocalVolModelDev(T, S0, sigmaATM, Sp, Sm, Mp, Mm, maxCalibrationIters, onlyForwardCalibrationIters, adjustATMFlag, enableLogging, useInitialMu, initialMu));
	}


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

	VanillaLocalVolModel::VanillaLocalVolModel(
		const boost::shared_ptr<ObjectHandler::ValueObject>&  properties,
		const boost::shared_ptr<QuantLib::VanillaLocalVolModelSmileSection> smileSection,
		bool                                                  permanent)
		: ObjectHandler::LibraryObject<QuantLib::VanillaLocalVolModel>(properties, permanent) {
		libraryObject_ = smileSection->model();
	}

	VanillaLocalVolModelSmileSection::VanillaLocalVolModelSmileSection(
		const boost::shared_ptr<ObjectHandler::ValueObject>&        properties,
		const boost::shared_ptr<QuantLib::VanillaLocalVolModel>&    model,
		const QuantLib::DayCounter&                                 dc,
		const QuantLib::VolatilityType                              type,
		const QuantLib::Rate                                        shift,
		bool permanent) : SmileSection(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::SmileSection>(
			new QuantLib::VanillaLocalVolModelSmileSection(model, dc, type, shift));
	}

	VanillaLocalVolModelSmileSection::VanillaLocalVolModelSmileSection(
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
		bool                                                      permanent)
		: SmileSection(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::SmileSection>(
			new QuantLib::VanillaLocalVolModelSmileSection(expiryDate, forward, relativeStrikes, smileVolatilities, extrapolationRelativeStrike, extrapolationSlope, vegaWeighted, endCriteria, method, dc, referenceDate, type, shift, model, minSlope, maxSlope, alpha));
	}

	VanillaLocalVolModelSmileSection::VanillaLocalVolModelSmileSection(
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
		bool                                                      permanent)
		: SmileSection(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::SmileSection>(
			new QuantLib::VanillaLocalVolModelSmileSection(expiryDate, forward, atmVolatility, smile1, smile2, rho, calcSimple, dc, referenceDate, type, shift));
	}

	VanillaLocalVolCMSTS::VanillaLocalVolCMSTS(
		const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
		const QuantLib::Period&                                 swapTerm,
		const std::vector< boost::shared_ptr<QuantLib::VanillaLocalVolModelSmileSection> >&  smiles,
		bool                                                    permanent)
		: ObjectHandler::LibraryObject< std::vector< boost::shared_ptr<QuantLib::VanillaLocalVolModelSmileSection> > >(properties, permanent),
	      swapTerm_(swapTerm) {
		libraryObject_ = boost::shared_ptr< std::vector< boost::shared_ptr<QuantLib::VanillaLocalVolModelSmileSection> > >(
			new std::vector< boost::shared_ptr<QuantLib::VanillaLocalVolModelSmileSection> >(smiles));
	}


	VanillaLocalVolSwaptionVTS::VanillaLocalVolSwaptionVTS(
		const boost::shared_ptr<ObjectHandler::ValueObject>&              properties,
		const boost::shared_ptr<QuantLib::SwaptionVolatilityStructure>&   atmVolTS,
		const std::vector< boost::shared_ptr<VanillaLocalVolCMSTS> >&     cmsTS,
		const boost::shared_ptr<QuantLib::SwapIndex>&                     index,
		bool                                                              permanent)
		: SwaptionVolatilityStructure(properties, permanent) {
		std::vector< std::vector< boost::shared_ptr<QuantLib::VanillaLocalVolModelSmileSection> > > smiles;
		std::vector<QuantLib::Period> swapTerms;
		for (size_t k = 0; k < cmsTS.size(); ++k) {
			boost::shared_ptr< std::vector< boost::shared_ptr<QuantLib::VanillaLocalVolModelSmileSection> > > obj;
			cmsTS[k]->getLibraryObject(obj);  // check if retrieval and cast was successfull
			if (obj->size() > 0) {
				smiles.push_back(*obj);
				swapTerms.push_back(cmsTS[k]->swapTerm());
			}
		}
		libraryObject_ = boost::shared_ptr<QuantLib::Extrapolator>(new QuantLib::VanillaLocalVolSwaptionVTS(atmVolTS, smiles, swapTerms, index));
	}


}




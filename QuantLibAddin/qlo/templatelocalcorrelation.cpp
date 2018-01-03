/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2010 Sebastian Schlenkrich

 */


#include <qlo/templatelocalcorrelation.hpp>


namespace QuantLibAddin {

	LocalCorrelationBSModel::LocalCorrelationBSModel(
		const boost::shared_ptr<ObjectHandler::ValueObject>&                            properties,
		const QuantLib::Handle<QuantLib::YieldTermStructure>&							termStructure,
		const std::vector<std::string>&                                                 aliases,
		const std::vector<boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>>& processes,
		const QuantLib::Handle<QuantLib::LocalCorrTermStructure>&						localCorrTermStructure,
		bool                                                                            permanent)
		: MultiAssetBSModel(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::RealStochasticProcess>(
			new QuantLib::LocalCorrelationBSModel(termStructure, aliases, processes, localCorrTermStructure));
	}

	//LocalCorrTermStructure::LocalCorrTermStructure(
	//	const boost::shared_ptr<ObjectHandler::ValueObject>&                            properties,
	//	const std::vector<boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>>& processes,
	//	const boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>&				processToCal,
	//	bool                                                                            permanent) 
	//	: CorrelationTermStructureStrike(properties, permanent) {
	//	libraryObject_ = boost::shared_ptr<QuantLib::LocalCorrTermStructure>(processes, processToCal);
	//}

	CTSlocalInCrossCorrelationFX::CTSlocalInCrossCorrelationFX(
		const boost::shared_ptr<ObjectHandler::ValueObject>&                            properties,
		const std::vector<boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>>& processes,
		const boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>&				processToCal,
		boost::shared_ptr<QuantLib::CalibratorLocalCorrInt>&								calibratorLocalCorr,
		bool                                                                            permanent)
		: LocalCorrSurfaceABFFX(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::LocalCorrTermStructure>(
			new QuantLib::CTSlocalInCrossCorrelationFX(processes, processToCal, calibratorLocalCorr));
	}

	ParticleMethodUtils::ParticleMethodUtils(
		const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
		const std::string&										kernel,
		unsigned int											numberOfPaths,
		QuantLib::Time											maxTime,
		QuantLib::Time											deltaT,
		QuantLib::Time											tMin,
		QuantLib::Real											kappa,
		QuantLib::Real											sigmaAVR,
		QuantLib::Real											exponentN,
		QuantLib::Real											gridMinQuantile,
		QuantLib::Real											gridMaxQuantile,
		bool                                                    permanent)
		: CalibratorLocalCorrInt(properties, permanent) {

		//libraryObject_ = boost::shared_ptr<QuantLib::CalibratorLocalCorrInt>(
		//	new QuantLib::ParticleMethodUtils(kernel,numberOfPaths,maxTime,deltaT,tMin,kappa,sigmaAVR,exponentN,gridMinQuantile,gridMaxQuantile));
		libraryObject_ = boost::shared_ptr<QuantLib::CalibratorLocalCorrInt>(
			new QuantLib::ParticleMethodUtils());
	}
}




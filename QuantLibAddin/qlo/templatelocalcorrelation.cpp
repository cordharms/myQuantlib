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
	

	LocalCorrelationSLVModel::LocalCorrelationSLVModel(
		const boost::shared_ptr<ObjectHandler::ValueObject>&                            properties,
		const QuantLib::Handle<QuantLib::YieldTermStructure>&							termStructure,
		const std::vector<std::string>&                                                 aliases,
		const std::vector<boost::shared_ptr<QuantLib::HestonSLVProcess>>&				processes,
		const QuantLib::Handle<QuantLib::LocalCorrTermStructure>&						localCorrTermStructure,
		bool                                                                            permanent)
		: MultiAssetSLVModel(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::RealStochasticProcess>(
			new QuantLib::LocalCorrelationSLVModel(termStructure, aliases, processes, localCorrTermStructure));
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
		const std::vector<boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>>& BSprocesses,
		const std::vector<boost::shared_ptr<QuantLib::HestonSLVProcess>>&				SLVprocesses,
		const boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>&				processToCal,
		const QuantLib::RealStochasticProcess::MatA										correlations,
		bool                                                                            permanent)
		: LocalCorrSurfaceABFFX(properties, permanent) {
		if (BSprocesses.size() > 0 && SLVprocesses.size() == 0) {
			libraryObject_ = boost::shared_ptr<QuantLib::LocalCorrTermStructure>(
				new QuantLib::CTSlocalInCrossCorrelationFX(BSprocesses, processToCal));
		}
		else if (BSprocesses.size() == 0 && SLVprocesses.size() > 0) {
			libraryObject_ = boost::shared_ptr<QuantLib::LocalCorrTermStructure>(
				new QuantLib::CTSlocalInCrossCorrelationFX(SLVprocesses, processToCal,correlations));
		}
		else {
			QL_FAIL("Either BSprocesses or SLVprocesses should be provided.");
		}
	}
	CTSlocalInCrossCovarianceFX::CTSlocalInCrossCovarianceFX(
		const boost::shared_ptr<ObjectHandler::ValueObject>&                            properties,
		const std::vector<boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>>& BSprocesses,
		const std::vector<boost::shared_ptr<QuantLib::HestonSLVProcess>>&				SLVprocesses,
		const boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>&				processToCal,
		const QuantLib::RealStochasticProcess::MatA										correlations,
		bool                                                                            permanent)
		: LocalCorrSurfaceABFFX(properties, permanent) {

		if (BSprocesses.size() > 0 && SLVprocesses.size() == 0) {
			libraryObject_ = boost::shared_ptr<QuantLib::LocalCorrTermStructure>(
				new QuantLib::CTSlocalInCrossCovarianceFX(BSprocesses, processToCal));
		}
		else if (BSprocesses.size() == 0 && SLVprocesses.size() > 0) {
			libraryObject_ = boost::shared_ptr<QuantLib::LocalCorrTermStructure>(
				new QuantLib::CTSlocalInCrossCovarianceFX(SLVprocesses, processToCal, correlations));
		}
		else {
			QL_FAIL("Either BSprocesses or SLVprocesses should be provided.");
		}
	}
	CTSlocalInCrossNegSkewFX::CTSlocalInCrossNegSkewFX(
		const boost::shared_ptr<ObjectHandler::ValueObject>&                            properties,
		const std::vector<boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>>& BSprocesses,
		const std::vector<boost::shared_ptr<QuantLib::HestonSLVProcess>>&				SLVprocesses,
		const boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>&				processToCal,
		double																			beta,
		const QuantLib::RealStochasticProcess::MatA										correlations,
		bool                                                                            permanent)
		: LocalCorrSurfaceABFFX(properties, permanent) {

		if (BSprocesses.size() > 0 && SLVprocesses.size() == 0) {
			libraryObject_ = boost::shared_ptr<QuantLib::LocalCorrTermStructure>(
				new QuantLib::CTSlocalInCrossNegSkewFX(BSprocesses, processToCal, beta));
		}
		else if (BSprocesses.size() == 0 && SLVprocesses.size() > 0) {
			libraryObject_ = boost::shared_ptr<QuantLib::LocalCorrTermStructure>(
				new QuantLib::CTSlocalInCrossNegSkewFX(SLVprocesses, processToCal, beta, correlations));
		}
		else {
			QL_FAIL("Either BSprocesses or SLVprocesses should be provided.");
		}
	}
	CTSlocalInCrossVolatilityFX::CTSlocalInCrossVolatilityFX(
		const boost::shared_ptr<ObjectHandler::ValueObject>&                            properties,
		const std::vector<boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>>& BSprocesses,
		const std::vector<boost::shared_ptr<QuantLib::HestonSLVProcess>>&				SLVprocesses,
		const boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>&				processToCal,
		const QuantLib::RealStochasticProcess::MatA										correlations,
		bool                                                                            permanent)
		: LocalCorrSurfaceABFFX(properties, permanent) {

		if (BSprocesses.size() > 0 && SLVprocesses.size() == 0) {
			libraryObject_ = boost::shared_ptr<QuantLib::LocalCorrTermStructure>(
				new QuantLib::CTSlocalInCrossVolatilityFX(BSprocesses, processToCal));
		}
		else if (BSprocesses.size() == 0 && SLVprocesses.size() > 0) {
			libraryObject_ = boost::shared_ptr<QuantLib::LocalCorrTermStructure>(
				new QuantLib::CTSlocalInCrossVolatilityFX(SLVprocesses, processToCal, correlations));
		}
		else {
			QL_FAIL("Either BSprocesses or SLVprocesses should be provided.");
		}
	}
}




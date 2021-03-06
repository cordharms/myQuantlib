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
#include <ql/experimental/templatemodels/multiasset/localcorrelationSLVmodel.hpp>
#include <ql/experimental/termstructures/localcorrtermstructure.hpp>
#include <ql/experimental/termstructures/localCorrFX/CTSlocalInCrossCorrelationFX.hpp>
#include <ql/experimental/termstructures/localCorrFX/CTSlocalInCrossCovarianceFX.hpp>
#include <ql/experimental/termstructures/localCorrFX/CTSlocalInCrossVolatilityFX.hpp>
#include <ql/experimental/termstructures/localCorrFX/CTSlocalInCrossNegSkewFX.hpp>
#include <ql/experimental/termstructures/localCorrFX/localcorrsurfaceabfFX.hpp>
#include <ql/experimental/termstructures/localCorrIndex/localcorrsurfaceabfIndex.hpp>
#include <ql/experimental/termstructures/localCorrIndex/CTSlocalInLambdaIndex.hpp>
#include <qlo\templatehestonmodel.hpp>


namespace QuantLib {
    template <class T>
    class Handle;
}


namespace QuantLibAddin {

	class LocalCorrelationBSModel : public MultiAssetBSModel {
	public:
		LocalCorrelationBSModel(
			const boost::shared_ptr<ObjectHandler::ValueObject>&                            properties,
			const QuantLib::Handle<QuantLib::YieldTermStructure>&							termStructure,
			const std::vector<std::string>&                                                 aliases,
			const std::vector<boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>>& processes,
			const QuantLib::Handle<QuantLib::LocalCorrTermStructure>&						localCorrTermStructure,
			bool                                                                            permanent);

	};
	class LocalCorrelationSLVModel : public MultiAssetSLVModel {
	public:
		LocalCorrelationSLVModel(
			const boost::shared_ptr<ObjectHandler::ValueObject>&                            properties,
			const QuantLib::Handle<QuantLib::YieldTermStructure>&							termStructure,
			const std::vector<std::string>&                                                 aliases,
			const std::vector<boost::shared_ptr<QuantLib::HestonSLVProcess>>&				processes,
			const QuantLib::Handle<QuantLib::LocalCorrTermStructure>&						localCorrTermStructure,
			bool                                                                            permanent);
	};

	OH_OBJ_CLASS(CorrelationTermStructureStrike, TermStructure);
	OH_OBJ_CLASS(LocalCorrTermStructure, CorrelationTermStructureStrike);
	OH_OBJ_CLASS(LocalCorrSurfaceABF, LocalCorrTermStructure);
	OH_OBJ_CLASS(LocalCorrSurfaceABFFX, LocalCorrSurfaceABF);
	OH_OBJ_CLASS(LocalCorrSurfaceABFIndex, LocalCorrSurfaceABF);

	/*class LocalCorrTermStructure : CorrelationTermStructureStrike {
	public:
		LocalCorrTermStructure(
			const boost::shared_ptr<ObjectHandler::ValueObject>&                            properties,
			const std::vector<boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>>& processes,
			const boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>&				processToCal,
			bool                                                                            permanent);
	};

	class LocalCorrSurfaceABF : LocalCorrTermStructure {
	public:
		LocalCorrSurfaceABF(
			const boost::shared_ptr<ObjectHandler::ValueObject>&                            properties,
			const std::vector<boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>>& processes,
			const boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>&				processToCal,
			bool                                                                            permanent);
	};

	class LocalCorrSurfaceABFFX : LocalCorrSurfaceABF {
	public:
		LocalCorrSurfaceABFFX(
			const boost::shared_ptr<ObjectHandler::ValueObject>&                            properties,
			const std::vector<boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>>& processes,
			const boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>&				processToCal,
			bool                                                                            permanent);
	};*/

	class CTSlocalInCrossCorrelationFX : public LocalCorrSurfaceABFFX {
	public:	
		CTSlocalInCrossCorrelationFX(
		const boost::shared_ptr<ObjectHandler::ValueObject>&                            properties,
		const std::vector<boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>>& BSprocesses,
		const std::vector<boost::shared_ptr<QuantLib::HestonSLVProcess>>&				SLVprocesses,
		const boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>&				processToCal,
		const QuantLib::RealStochasticProcess::MatA										correlations,
		bool                                                                            permanent);
	};
	class CTSlocalInCrossCovarianceFX : public LocalCorrSurfaceABFFX {
	public:
		CTSlocalInCrossCovarianceFX(
			const boost::shared_ptr<ObjectHandler::ValueObject>&                            properties,
			const std::vector<boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>>& BSprocesses,
			const std::vector<boost::shared_ptr<QuantLib::HestonSLVProcess>>&				SLVprocesses,
			const boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>&				processToCal,
			const QuantLib::RealStochasticProcess::MatA										correlations,
			bool                                                                            permanent);
	};
	class CTSlocalInCrossVolatilityFX : public LocalCorrSurfaceABFFX {
	public:
		CTSlocalInCrossVolatilityFX(
			const boost::shared_ptr<ObjectHandler::ValueObject>&                            properties,
			const std::vector<boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>>& BSprocesses,
			const std::vector<boost::shared_ptr<QuantLib::HestonSLVProcess>>&				SLVprocesses,
			const boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>&				processToCal,
			const QuantLib::RealStochasticProcess::MatA										correlations,
			bool                                                                            permanent);
	};
	class CTSlocalInCrossNegSkewFX : public LocalCorrSurfaceABFFX {
	public:
		CTSlocalInCrossNegSkewFX(
			const boost::shared_ptr<ObjectHandler::ValueObject>&                            properties,
			const std::vector<boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>>& BSprocesses,
			const std::vector<boost::shared_ptr<QuantLib::HestonSLVProcess>>&				SLVprocesses,
			const boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>&				processToCal,
			double																			beta,
			const QuantLib::RealStochasticProcess::MatA										correlations,
			bool                                                                            permanent);
	};

	class CTSlocalInLambdaIndex : public LocalCorrSurfaceABFIndex {
	public:
		CTSlocalInLambdaIndex(
			const boost::shared_ptr<ObjectHandler::ValueObject>&                            properties,
			const std::vector<boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>>& BSprocesses,
			const std::vector<boost::shared_ptr<QuantLib::HestonSLVProcess>>&				SLVprocesses,
			const boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>&				processToCal,
			const QuantLib::RealStochasticProcess::MatA&									corr0,
			const QuantLib::RealStochasticProcess::MatA&									corr1,
			const QuantLib::RealStochasticProcess::VecA&									weightsIndex,
			bool																			possibleNegativeIndex,
			double																			processToCalBlackVolShift,
			bool                                                                            permanent);
	};
}

#endif


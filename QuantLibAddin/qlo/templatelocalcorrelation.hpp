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
#include <ql/experimental/termstructures/localcorrtermstructure.hpp>
#include <ql/experimental/termstructures/localCorrFX/CTSlocalInCrossCorrelationFX.hpp>
#include <ql/experimental/termstructures/localCorrFX/localcorrsurfaceabfFX.hpp>
#include <ql/experimental/termstructures/Helper/CalibratorLocalCorrInt.hpp>
#include <ql/experimental/termstructures/Helper/ParticleMethodUtils.hpp>
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

	OH_OBJ_CLASS(CorrelationTermStructureStrike, TermStructure);
	OH_OBJ_CLASS(LocalCorrTermStructure, CorrelationTermStructureStrike);
	OH_OBJ_CLASS(LocalCorrSurfaceABF, LocalCorrTermStructure);
	OH_OBJ_CLASS(LocalCorrSurfaceABFFX, LocalCorrSurfaceABF);

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
		const std::vector<boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>>& processes,
		const boost::shared_ptr<QuantLib::GeneralizedBlackScholesProcess>&				processToCal,
		boost::shared_ptr<QuantLib::CalibratorLocalCorrInt>&								calibratorLocalCorr,
		bool                                                                            permanent);
	};

	OH_LIB_CLASS(CalibratorLocalCorrInt, QuantLib::CalibratorLocalCorrInt);

	class ParticleMethodUtils : public CalibratorLocalCorrInt {
	public:
		ParticleMethodUtils(
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
			unsigned int											ns1,
			unsigned int											ns2,
			bool                                                    permanent);
	};




}

#endif


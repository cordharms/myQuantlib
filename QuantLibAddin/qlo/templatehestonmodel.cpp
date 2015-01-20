/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2010 Sebastian Schlenkrich

 */


#include <qlo/templatehestonmodel.hpp>

namespace QuantLibAddin {

    HestonProcess::HestonProcess(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Handle<QuantLib::YieldTermStructure>& riskFreeRate,
            const QuantLib::Handle<QuantLib::YieldTermStructure>& dividendYield,
            const QuantLib::Handle<QuantLib::Quote>& s0,
            QuantLib::Real v0, 
            QuantLib::Real kappa,
            QuantLib::Real theta, 
            QuantLib::Real sigma, 
            QuantLib::Real rho,
            bool permanent) : StochasticProcess(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::HestonProcess>(
			new QuantLib::HestonProcess( riskFreeRate, dividendYield, s0, v0, kappa, theta, sigma, rho ));            
    }

    HestonModel::HestonModel(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const boost::shared_ptr<QuantLib::HestonProcess>& process,
            bool permanent) : CalibratedModel(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::HestonModel>(
			new QuantLib::HestonModel( process ));            
    }

    AnalyticHestonEngine::AnalyticHestonEngine(
                const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                const boost::shared_ptr<QuantLib::HestonModel>& model,
                QuantLib::Real relTolerance,
                QuantLib::Size maxEvaluations,
                bool permanent) : PricingEngine(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::AnalyticHestonEngine>(
			new QuantLib::AnalyticHestonEngine( model, relTolerance, maxEvaluations ));            
    }

    RealHestonModel::RealHestonModel(
                const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                QuantLib::Real                                       kappa,                             
                QuantLib::Real                                       theta,
                QuantLib::Real                                       sigma,
                QuantLib::Real                                       rho,
                QuantLib::Real                                       v0,
                bool                                                 permanent)
        : ObjectHandler::LibraryObject<QuantLib::RealHestonModel>(properties, permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealHestonModel>(
			new QuantLib::RealHestonModel( kappa, theta, sigma, rho, v0 ));            
    }

    ActiveHestonModel::ActiveHestonModel(
                const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                QuantLib::Real                                       kappa,                             
                QuantLib::Real                                       theta,
                QuantLib::Real                                       sigma,
                QuantLib::Real                                       rho,
                QuantLib::Real                                       v0,
                bool                                                 permanent)
        : ObjectHandler::LibraryObject<QuantLib::ActiveHestonModel>(properties, permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::ActiveHestonModel>(
			new QuantLib::ActiveHestonModel( kappa, theta, sigma, rho, v0 ));            
    }

	RealStochVolModel::RealStochVolModel(
                const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                QuantLib::Real  lambda,                             
                QuantLib::Real  b,
                QuantLib::Real  L,
                QuantLib::Real  theta,
                QuantLib::Real  m,
                QuantLib::Real  eta,
                QuantLib::Real  z0,
                QuantLib::Real  rho,
                bool            permanent)
        : ObjectHandler::LibraryObject<QuantLib::RealStochVolModel>(properties, permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealStochVolModel>(
			new QuantLib::RealStochVolModel( lambda, b, L, theta, m, eta, z0, rho ));
    }

	RealPWCNumericalStochVolModel::RealPWCNumericalStochVolModel(
                const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                const std::vector<QuantLib::Time>&                   times,
				const std::vector<QuantLib::Real>&                   lambda,
				const std::vector<QuantLib::Real>&                   b,
				const std::vector<QuantLib::Real>&                   eta,
				const QuantLib::Real                                 L,
				const QuantLib::Real                                 theta,
				const QuantLib::Real                                 m,
				const QuantLib::Real                                 z0,
				const QuantLib::Real                                 rho,
				const QuantLib::Real                                 S0,
                const QuantLib::Real                                 absAccuracy,
			    const QuantLib::Real                                 relAccuracy,
			    const size_t                                         maxEvaluations,
				const QuantLib::Time                                 dt,
  				bool                                                 permanent)
	: RealTDStochVolModel(properties, permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealPWCNumericalStochVolModel>(
			new QuantLib::RealPWCNumericalStochVolModel( times, lambda, b, eta, L, theta, m, z0, rho, S0, absAccuracy, relAccuracy, maxEvaluations, dt ) );
	}

	RealPWCStochVolModel::RealPWCStochVolModel(
                const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                const std::vector<QuantLib::Time>&                   times,
				const std::vector<QuantLib::Real>&                   lambda,
				const std::vector<QuantLib::Real>&                   b,
				const std::vector<QuantLib::Real>&                   eta,
				const QuantLib::Real                                 L,
				const QuantLib::Real                                 theta,
				const QuantLib::Real                                 m,
				const QuantLib::Real                                 z0,
				const QuantLib::Real                                 rho,
				const QuantLib::Real                                 S0,
  				bool                                                 permanent)
	: RealTDStochVolModel(properties, permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::RealPWCStochVolModel>(
			new QuantLib::RealPWCStochVolModel( times, lambda, b, eta, L, theta, m, z0, rho, S0 ) );
	}


}




/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2005, 2006 Eric Ehlers
 Copyright (C) 2005 Aurelien Chanudet

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifdef HAVE_CONFIG_H
#include <qlo/config.hpp>
#endif

#include <qlo/shortratemodels.hpp>

#include <ql/models/shortrate/onefactormodels/vasicek.hpp>
#include <ql/models/shortrate/onefactormodels/hullwhite.hpp>
#include <ql/models/shortrate/twofactormodels/g2.hpp>
#include <ql/models/shortrate/calibrationhelpers/swaptionhelper.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/pricingengines/swaption/g2swaptionengine.hpp>


namespace QuantLibAddin {

    Vasicek::Vasicek(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                     QuantLib::Real a,
                     QuantLib::Real b,
                     QuantLib::Real lambda,
                     QuantLib::Real sigma,
                     bool permanent) : AffineModel(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::AffineModel>(new
            QuantLib::Vasicek(a, b, lambda, sigma));
    }

    HullWhite::HullWhite(
                const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                const QuantLib::Handle<QuantLib::YieldTermStructure>& hYTS,
                QuantLib::Real a,
                QuantLib::Real sigma,
                bool permanent) : AffineModel(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::AffineModel>(new
            QuantLib::HullWhite(hYTS, a, sigma));
    }

    G2::G2(const boost::shared_ptr<ObjectHandler::ValueObject>&  properties,
		   const QuantLib::Handle<QuantLib::YieldTermStructure>& termStructure,
           QuantLib::Real                                        a,
           QuantLib::Real                                        sigma,
           QuantLib::Real                                        b,
           QuantLib::Real                                        eta,
           QuantLib::Real                                        rho,
		   bool                                                  permanent)
		   : AffineModel(properties, permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::AffineModel>(new
            QuantLib::G2(termStructure, a, sigma,b,eta,rho));
	}

    G2SwaptionEngine::G2SwaptionEngine(
		                 const boost::shared_ptr<ObjectHandler::ValueObject>&  properties,
			             const boost::shared_ptr<QuantLib::G2>&                model,
                         QuantLib::Real                                        range,
                         QuantLib::Size                                        intervals,
		                 bool                                                  permanent)
						 : PricingEngine(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::PricingEngine>(new
            QuantLib::G2SwaptionEngine(model,range,intervals));
	}

    SwaptionHelper::SwaptionHelper(
		               const boost::shared_ptr<ObjectHandler::ValueObject>&  properties,
			           const QuantLib::Period&                               maturity,
                       const QuantLib::Period&                               length,
                       const QuantLib::Handle<QuantLib::Quote>&              volatility,
                       const boost::shared_ptr<QuantLib::IborIndex>&         index,
                       const QuantLib::Period&                               fixedLegTenor,
                       const QuantLib::DayCounter&                           fixedLegDayCounter,
                       const QuantLib::DayCounter&                           floatingLegDayCounter,
                       const QuantLib::Handle<QuantLib::YieldTermStructure>&   termStructure,
                       const QuantLib::CalibrationHelper::CalibrationErrorType errorType,
                       const QuantLib::Real                                    strike,
                       const QuantLib::Real                                    nominal,
                       const QuantLib::Real                                    shift,
		               bool                                                    permanent)
					   : CalibrationHelper(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::CalibrationHelper>(new
            QuantLib::SwaptionHelper(maturity,length,volatility,index,fixedLegTenor,fixedLegDayCounter,floatingLegDayCounter,termStructure,errorType,strike,nominal,shift));
	}


}


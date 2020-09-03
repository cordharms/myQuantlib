/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2005 Eric Ehlers
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

#ifndef qla_shortratemodels_hpp
#define qla_shortratemodels_hpp

#include <qlo/termstructures.hpp>
#include <qlo/pricingengines.hpp>

#include <ql/types.hpp>

#include <ql/models/calibrationhelper.hpp>


namespace QuantLib {
    template <class T>
    class Handle;
    class AffineModel;
	class IborIndex;
	class G2;
	// class CalibrationHelper;
	class OptimizationMethod;
	class EndCriteria;
}

namespace QuantLibAddin {

    OH_LIB_CLASS(AffineModel, QuantLib::AffineModel);

    class Vasicek : public AffineModel {
      public:
          Vasicek(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                  QuantLib::Real a,
                  QuantLib::Real b,
                  QuantLib::Real lambda,
                  QuantLib::Real sigma,
                  bool permanent);
    };

    class HullWhite : public AffineModel {
      public:
        HullWhite(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                  const QuantLib::Handle<QuantLib::YieldTermStructure>& hYTS,
                  QuantLib::Real a,
                  QuantLib::Real sigma,
                  bool permanent);
    };

    class G2 : public AffineModel {
	public:
        G2(const boost::shared_ptr<ObjectHandler::ValueObject>&  properties,
		   const QuantLib::Handle<QuantLib::YieldTermStructure>& termStructure,
           QuantLib::Real                                        a,
           QuantLib::Real                                        sigma,
           QuantLib::Real                                        b,
           QuantLib::Real                                        eta,
           QuantLib::Real                                        rho,
		   bool                                                  permanent);
		void calibrate(const std::vector<boost::shared_ptr<QuantLib::BlackCalibrationHelper> >& instruments,
					   const boost::shared_ptr<QuantLib::OptimizationMethod>&              method,
					   const boost::shared_ptr<QuantLib::EndCriteria>&                     endCriteria,
                       const std::vector<QuantLib::Real>&                                  weights,
                       const std::vector<bool>&                                            fixParameters);
	};

    class G2SwaptionEngine : public PricingEngine {
	public:
        G2SwaptionEngine(const boost::shared_ptr<ObjectHandler::ValueObject>&  properties,
			             const boost::shared_ptr<QuantLib::G2>&                model,
                         QuantLib::Real                                        range,
                         QuantLib::Size                                        intervals,
		                 bool                                                  permanent);
	};

    class SwaptionHelper : public BlackCalibrationHelper {
    public:
        SwaptionHelper(const boost::shared_ptr<ObjectHandler::ValueObject>&  properties,
			           const QuantLib::Period&                               maturity,
                       const QuantLib::Period&                               length,
                       const QuantLib::Handle<QuantLib::Quote>&              volatility,
                       const boost::shared_ptr<QuantLib::IborIndex>&         index,
                       const QuantLib::Period&                               fixedLegTenor,
                       const QuantLib::DayCounter&                           fixedLegDayCounter,
                       const QuantLib::DayCounter&                           floatingLegDayCounter,
                       const QuantLib::Handle<QuantLib::YieldTermStructure>&   termStructure,
                       const QuantLib::BlackCalibrationHelper::CalibrationErrorType errorType,
                       const QuantLib::Real                                    strike,
                       const QuantLib::Real                                    nominal,
			           const QuantLib::VolatilityType                          type,
                       const QuantLib::Real                                    shift,
		               bool                                                    permanent);
	};


}

#endif


/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2006 Francois du Vignaud

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

#ifndef qla_smilesection_hpp
#define qla_smilesection_hpp

#include <oh/libraryobject.hpp>
#include <ql/types.hpp>

#include <ql/experimental/templatemodels/vanillalocalvol/vanillalocalvolsmilesection.hpp>

namespace QuantLib {
    class Date;
    class SmileSection;
    class DayCounter;
    class EndCriteria;
    class Quote;
    class OptimizationMethod;
    class SabrVolSurface;

    template <class T>
    class Handle;
}

namespace QuantLibAddin {
    
    OH_LIB_CLASS(SmileSection, QuantLib::SmileSection);

    class FlatSmileSection : public SmileSection {
      public:
        FlatSmileSection(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                         const QuantLib::Date& optionDate,
                         QuantLib::Volatility v,
                         const QuantLib::DayCounter& dc,
                         const QuantLib::Date& refDate,
                         QuantLib::Real atmValue,
                         bool permanent);
    };

    class InterpolatedSmileSection : public SmileSection {
      public:
        InterpolatedSmileSection(
              const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
              const QuantLib::Date& optionDate,
              const std::vector<QuantLib::Rate>& strikes,
              const std::vector<QuantLib::Handle<QuantLib::Quote> >& stdDevs,
              const QuantLib::Handle<QuantLib::Quote>& atmLevel,
              const QuantLib::DayCounter& dc,
              bool permanent);
    };

    class SabrSmileSection: public SmileSection{
      public:
        SabrSmileSection(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Time expiry,
            const std::vector<QuantLib::Rate>& strikes,
            const std::vector<QuantLib::Handle<QuantLib::Quote> >& stdDevs,
            const QuantLib::Handle<QuantLib::Quote>& forward,
            QuantLib::Real alpha, 
            QuantLib::Real beta,
            QuantLib::Real nu,
            QuantLib::Real rho,
            bool isAlphaFixed,
            bool isBetaFixed,
            bool isNuFixed,
            bool isRhoFixed,
            bool vegaWeighted = false,
            const boost::shared_ptr<QuantLib::EndCriteria> endCriteria
                = boost::shared_ptr<QuantLib::EndCriteria>(),
            const boost::shared_ptr<QuantLib::OptimizationMethod> method
                = boost::shared_ptr<QuantLib::OptimizationMethod>(),
            bool permanent = false);
        
    };

    class SabrInterpolatedSmileSection : public SmileSection {
      public:
        SabrInterpolatedSmileSection(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Date& optionDate,
            const QuantLib::Rate& forward,
            const std::vector<QuantLib::Rate>& strikes,
            bool hasFloatingStrikes,
            const QuantLib::Volatility& atmVolatility,
            const std::vector<QuantLib::Volatility>& vols,
            QuantLib::Real alpha,
            QuantLib::Real beta,
            QuantLib::Real nu,
            QuantLib::Real rho,
            bool isAlphaFixed,
            bool isBetaFixed,
            bool isNuFixed,
            bool isRhoFixed,
            bool vegaWeighted,
            const boost::shared_ptr<QuantLib::EndCriteria> endCriteria,
            const boost::shared_ptr<QuantLib::OptimizationMethod> method,
            const QuantLib::DayCounter& dc,
			const QuantLib::Real shift,
			const bool useNormlaVols,
            bool permanent);

        SabrInterpolatedSmileSection(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Date& optionDate,
            const QuantLib::Handle<QuantLib::Quote>& forward,
            const std::vector<QuantLib::Rate>& strikes,
            bool hasFloatingStrikes,
            const QuantLib::Handle<QuantLib::Quote>& atmVolatility,
            const std::vector<QuantLib::Handle<QuantLib::Quote> >& volHandles,
            QuantLib::Real alpha,
            QuantLib::Real beta,
            QuantLib::Real nu,
            QuantLib::Real rho,
            bool isAlphaFixed,
            bool isBetaFixed,
            bool isNuFixed,
            bool isRhoFixed,
            bool vegaWeighted,
            const boost::shared_ptr<QuantLib::EndCriteria> endCriteria,
            const boost::shared_ptr<QuantLib::OptimizationMethod> method,
            const QuantLib::DayCounter& dc,
			const QuantLib::Real shift,
			const bool useNormlaVols,
            bool permanent);
    };
    
    class SmileSectionFromSabrVolSurface : public SmileSection {
    public:
        SmileSectionFromSabrVolSurface(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::Handle<QuantLib::SabrVolSurface>& sabrVol,
            const QuantLib::Time& time,
            bool permanent);
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


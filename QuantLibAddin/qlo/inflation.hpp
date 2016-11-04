/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2016 Sebastian Schlenkrich

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

#ifndef qla_inflation_hpp
#define qla_inflation_hpp

#include <oh/ohdefines.hpp>

#include <qlo/termstructures.hpp>
#include <qlo/index.hpp>

#include <ql/indexes/inflationindex.hpp>
#include <ql/termstructures/inflation/inflationhelpers.hpp>

namespace QuantLib {
}


namespace QuantLibAddin {

	//OH_LIB_CLASS(InflationIndex, QuantLib::InflationIndex);

	class ZeroInflationIndex : public Index {
	public:
		ZeroInflationIndex(
			const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
			bool                                                    permanent);

		ZeroInflationIndex(
			const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
			const std::string&                                      familyName,
			const QuantLib::Region&                                 region,
			bool                                                    revised,
			bool                                                    interpolated,
			const QuantLib::Frequency                               frequency,
			const QuantLib::Period&                                 availabilityLag,
			const QuantLib::Currency&                               currency,
			const QuantLib::Handle<QuantLib::ZeroInflationTermStructure>& ts,
			bool                                                    permanent);
	};

	class EUHICP : public ZeroInflationIndex {
	public:
		EUHICP(
			const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
			bool                                                    interpolated,
			const QuantLib::Handle<QuantLib::ZeroInflationTermStructure>& ts,
			bool                                                    permanent);

	};

	class FRHICP : public ZeroInflationIndex {
	public:
		FRHICP(
			const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
			bool                                                    interpolated,
			const QuantLib::Handle<QuantLib::ZeroInflationTermStructure>& ts,
			bool                                                    permanent);

	};

	class ZeroCouponInflationSwapHelper : public ObjectHandler::LibraryObject<QuantLib::ZeroCouponInflationSwapHelper> {
	public:
		ZeroCouponInflationSwapHelper(
			const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
		    const QuantLib::Handle<QuantLib::Quote>&                quote,
			const QuantLib::Period&                                 swapObsLag,   // lag on swap observation of index
			const QuantLib::Date&                                   maturity,
			const QuantLib::Calendar&                               calendar,   // index may have null calendar as valid on every day
			const QuantLib::BusinessDayConvention                   paymentConvention,
			const QuantLib::DayCounter&                             dayCounter,
			const boost::shared_ptr<QuantLib::ZeroInflationIndex>&  zii,
			bool                                                    permanent);
	};

	OH_LIB_CLASS(ZeroInflationTermStructure, QuantLib::ZeroInflationTermStructure);

	class InterpolatedZeroInflationCurve : public ZeroInflationTermStructure {
	public:
		InterpolatedZeroInflationCurve(
			const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
			const QuantLib::Date&                                   referenceDate,
			const QuantLib::Calendar&                               calendar,
			const QuantLib::DayCounter&                             dayCounter,
			const QuantLib::Period&                                 lag,
			const QuantLib::Frequency                               frequency,
			bool                                                    indexIsInterpolated,
			const QuantLib::Handle<QuantLib::YieldTermStructure>&   yTS,
			const std::vector<QuantLib::Date>&                      dates,
			const std::vector<QuantLib::Rate>&                      rates,
			const std::string&                                      interpolatorString, // not used, default linear interpolation
			bool                                                    permanent);
	};

	class PiecewiseZeroInflationCurve : public ZeroInflationTermStructure {
	public:
		PiecewiseZeroInflationCurve(
			const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
			const QuantLib::Date&                                   referenceDate,
			const QuantLib::Calendar&                               calendar,
			const QuantLib::DayCounter&                             dayCounter,
			const QuantLib::Period&                                 lag,
			const QuantLib::Frequency                               frequency,
			bool                                                    indexIsInterpolated,
			const QuantLib::Rate                                    baseZeroRate,
			const QuantLib::Handle<QuantLib::YieldTermStructure>&   nominalTS,
			const std::vector<boost::shared_ptr<QuantLib::ZeroCouponInflationSwapHelper> >&  instruments,
			const QuantLib::Real                                    accuracy,
			const std::string&                                      interpolatorString, // not used, default linear interpolation
			bool                                                    permanent);
	};


}

#endif

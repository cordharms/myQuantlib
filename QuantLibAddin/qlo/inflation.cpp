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

#if defined(HAVE_CONFIG_H)
    #include <qlo/config.hpp>
#endif

#include <qlo/inflation.hpp>

#include <ql/indexes/inflation/euhicp.hpp>
#include <ql/indexes/inflation/frhicp.hpp>
#include <ql/termstructures/inflation/interpolatedzeroinflationcurve.hpp>
#include <ql/termstructures/inflation/piecewisezeroinflationcurve.hpp>
#include <ql/math/interpolations/linearinterpolation.hpp>

namespace QuantLibAddin {

	ZeroInflationIndex::ZeroInflationIndex(
		const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
		bool                                                    permanent)
		: Index(properties, permanent) {}

	ZeroInflationIndex::ZeroInflationIndex(
		const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
		const std::string&                                      familyName,
		const QuantLib::Region&                                 region,
		bool                                                    revised,
		bool                                                    interpolated,
		const QuantLib::Frequency                               frequency,
		const QuantLib::Period&                                 availabilityLag,
		const QuantLib::Currency&                               currency,
		const QuantLib::Handle<QuantLib::ZeroInflationTermStructure>& ts,
		bool                                                    permanent)
		: Index(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::ZeroInflationIndex>(new
			QuantLib::ZeroInflationIndex(familyName, region, revised, interpolated, frequency, availabilityLag, currency, ts));
	}

	EUHICP::EUHICP(
		const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
		bool                                                    interpolated,
		const QuantLib::Handle<QuantLib::ZeroInflationTermStructure>& ts,
		bool                                                    permanent)
		: ZeroInflationIndex(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::ZeroInflationIndex>(new QuantLib::EUHICP(interpolated, ts));
	}

	FRHICP::FRHICP(
		const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
		bool                                                    interpolated,
		const QuantLib::Handle<QuantLib::ZeroInflationTermStructure>& ts,
		bool                                                    permanent)
		: ZeroInflationIndex(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::ZeroInflationIndex>(new QuantLib::FRHICP(interpolated,ts));
	}

	ZeroCouponInflationSwapHelper::ZeroCouponInflationSwapHelper(
		const boost::shared_ptr<ObjectHandler::ValueObject>&    properties,
		const QuantLib::Handle<QuantLib::Quote>&                quote,
		const QuantLib::Period&                                 swapObsLag,   // lag on swap observation of index
		const QuantLib::Date&                                   maturity,
		const QuantLib::Calendar&                               calendar,   // index may have null calendar as valid on every day
		const QuantLib::BusinessDayConvention                   paymentConvention,
		const QuantLib::DayCounter&                             dayCounter,
		const boost::shared_ptr<QuantLib::ZeroInflationIndex>&  zii,
		bool                                                    permanent) 
	    : ObjectHandler::LibraryObject<QuantLib::ZeroCouponInflationSwapHelper>(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::ZeroCouponInflationSwapHelper>(
			new QuantLib::ZeroCouponInflationSwapHelper(quote, swapObsLag, maturity, calendar, paymentConvention, dayCounter, zii));
	}

	InterpolatedZeroInflationCurve::InterpolatedZeroInflationCurve(
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
		const std::string&                                      interpolatorString,
		bool                                                    permanent)
		: ZeroInflationTermStructure(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::ZeroInflationTermStructure>(
			new QuantLib::InterpolatedZeroInflationCurve<QuantLib::Linear>(referenceDate, calendar, dayCounter, lag, frequency, indexIsInterpolated, yTS, dates, rates));
	}

	PiecewiseZeroInflationCurve::PiecewiseZeroInflationCurve(
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
		bool                                                    permanent)
		: ZeroInflationTermStructure(properties, permanent) {

		std::vector < boost::shared_ptr<QuantLib::ZeroInflationTraits::helper>> helpers;
		for (QuantLib::Size k = 0; k < instruments.size(); ++k) helpers.push_back(boost::dynamic_pointer_cast<QuantLib::ZeroInflationTraits::helper>(instruments[k]));
		libraryObject_ = boost::shared_ptr<QuantLib::ZeroInflationTermStructure>(
			new QuantLib::PiecewiseZeroInflationCurve<QuantLib::Linear>(referenceDate, calendar, dayCounter, lag, frequency, indexIsInterpolated, baseZeroRate, nominalTS, helpers, accuracy));
	}

}

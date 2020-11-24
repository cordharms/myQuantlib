/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
  Copyright (C) 2006, 2007 Chiara Fornarola
  Copyright (C) 2006, 2007, 2008, 2009, 2010, 2011 Ferdinando Ametrano
  Copyright (C) 2005, 2006 Eric Ehlers
  Copyright (C) 2005 Plamen Neykov
  Copyright (C) 2005 Walter Penschke
  Copyright (C) 2009 Piter Dias
  Copyright (C) 2020 Peter Kreyssig
 
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
	
	#ifndef qla_convertiblebonds_hpp
	 #define qla_convertiblebonds_hpp
	
	#include <qlo/baseinstruments.hpp>
	 #include <qlo/bonds.hpp>
	#include <qlo/indexes/iborindex.hpp>
	
	#include <ql/currency.hpp>
	 #include <ql/handle.hpp>
	 #include <ql/instruments/bond.hpp>
	 #include <ql/instruments/callabilityschedule.hpp>
	 #include <ql/instruments/dividendschedule.hpp>
	#include <ql/indexes/iborindex.hpp>
	
	#include <oh/libraryobject.hpp>
	
	#include <string>
	
	namespace QuantLib {
	class Exercise;
	class Quote;
	class FixedDividend;
	class Callability;
	class Schedule;
	class Calendar;
	class Date;
	class DayCounter;
	class IborIndex;
	
}

using boost::shared_ptr;

namespace QuantLibAddin {
	
		OH_LIB_CLASS(Exercise, QuantLib::Exercise);
	OH_LIB_CLASS(Schedule, QuantLib::Schedule);
	
		class ConvertibleZeroCouponBond : public Bond {
		public:
			ConvertibleZeroCouponBond(
				const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
				const std::string& des,
				const QuantLib::Currency& cur,
				const boost::shared_ptr<QuantLib::Exercise>& exercise,
				QuantLib::Real conversionRatio,
				const QuantLib::Callability::Type conversionType,
				const std::vector<boost::shared_ptr<QuantLib::FixedDividend> > dividends,
				const std::vector<boost::shared_ptr<QuantLib::Callability> > callability,
				const QuantLib::Handle<QuantLib::Quote>& creditSpread,
				const QuantLib::Date& issueDate,
				QuantLib::Natural settlementDays,
				const QuantLib::DayCounter& dayCounter,
				const boost::shared_ptr<QuantLib::Schedule>& schedule,
				QuantLib::Real redemption,
				bool permanent);
			
	};
	
		class ConvertibleFixedCouponBond : public Bond {
		public:
			ConvertibleFixedCouponBond(
				const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
				const std::string& des,
				const QuantLib::Currency& cur,
				const boost::shared_ptr<QuantLib::Exercise>& exercise,
				QuantLib::Real conversionRatio,
				const QuantLib::Callability::Type conversionType,
				const std::vector<boost::shared_ptr<QuantLib::FixedDividend> > dividends,
				const std::vector<boost::shared_ptr<QuantLib::Callability> > callability,
				const QuantLib::Handle<QuantLib::Quote>& creditSpread,
				const QuantLib::Date& issueDate,
				QuantLib::Natural settlementDays,
				const std::vector<QuantLib::Rate>& coupons,
				const QuantLib::DayCounter& dayCounter,
				const boost::shared_ptr<QuantLib::Schedule>& schedule,
				QuantLib::Real redemption,
				bool permanent);
			
	};
	
		class FixedDividend : public ObjectHandler::LibraryObject<QuantLib::FixedDividend> {
		public:
			FixedDividend(
				const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
				QuantLib::Real amount,
				const QuantLib::Date& date,
				bool permanent);
			protected:
				OH_LIB_CTOR(FixedDividend, QuantLib::FixedDividend);
				boost::shared_ptr<QuantLib::FixedDividend> qlDivObject_;
				
	};
	
		class Callability : public ObjectHandler::LibraryObject<QuantLib::Callability> {
		public:
			Callability(
				const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
				QuantLib::Real price,
				QuantLib::Bond::Price::Type priceType,
				const QuantLib::Callability::Type callType,
				const QuantLib::Date& date,
				bool permanent);
			protected:
				OH_LIB_CTOR(Callability, QuantLib::Callability);
				boost::shared_ptr<QuantLib::Callability> qlCallObject_;
				
	};
	
		class CoCoFloatingRateBond : public Bond {
		public:
			CoCoFloatingRateBond(
				const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
				const std::string& des,
				const QuantLib::Currency& cur,
				QuantLib::Real conversionRatio,
				const std::vector<boost::shared_ptr<QuantLib::FixedDividend> > dividends,
				const std::vector<boost::shared_ptr<QuantLib::Callability> > callability,
				const QuantLib::Handle<QuantLib::Quote>& creditSpread,
				const QuantLib::Date& issueDate,
				QuantLib::Natural settlementDays,
				const boost::shared_ptr<QuantLib::IborIndex>& index,
				QuantLib::Natural fixingDays,
				const std::vector<QuantLib::Real>& gearings,
				const std::vector<QuantLib::Spread>& spreads,
				const QuantLib::DayCounter& dayCounter,
				const boost::shared_ptr<QuantLib::Schedule>& schedule,
				QuantLib::Real cocoTrigger,
				bool isWriteDown,
				QuantLib::Real cocoWriteDownRR,
				bool isRiskyDiscountingWD,
				QuantLib::Real redemption,
				bool permanent);

		};
		class CoCoGenericCouponBond : public Bond {
		public:
			CoCoGenericCouponBond(
				const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
				const std::string& des,
				const QuantLib::Currency& cur,
				QuantLib::Real conversionRatio,
				const std::vector<boost::shared_ptr<QuantLib::FixedDividend> > dividends,
				const std::vector<boost::shared_ptr<QuantLib::Callability> > callability,
				const QuantLib::Handle<QuantLib::Quote>& creditSpread,
				const QuantLib::Date& issueDate,
				QuantLib::Natural settlementDays,
				const std::vector<QuantLib::Rate>& coupons,
				const QuantLib::DayCounter& dayCounter,
				const boost::shared_ptr<QuantLib::Schedule>& schedule,
				QuantLib::Real cocoTrigger,
				bool isWriteDown,
				QuantLib::Real cocoWriteDownRR,
				bool isRiskyDiscountingWD,
				QuantLib::Real redemption,
				bool permanent);

		};
}

#endif
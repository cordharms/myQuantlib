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
	
	#if defined(HAVE_CONFIG_H)
	#include <qlo/config.hpp>
	 #endif
	
	#include <qlo/bonds.hpp>
	#include <qlo/convertiblebonds.hpp>
	
	#include <ql/experimental/convertiblebonds/convertiblebond.hpp>
	 #include <ql/utilities/dataformatters.hpp>
	 #include <ql/quote.hpp>
	
	#include <oh/repository.hpp>
	
	#include <ostream>
	
	using std::vector;
using std::string;
using boost::shared_ptr;
using ObjectHandler::property_t;
using ObjectHandler::convert2;
using QuantLib::Size;
using QuantLib::Date;
using boost::dynamic_pointer_cast;

namespace QuantLibAddin {
	
		ConvertibleZeroCouponBond::ConvertibleZeroCouponBond(
			const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const string& des,
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
			bool permanent)
		 : Bond(properties, des, cur, permanent)
		 {
		qlBondObject_ = shared_ptr<QuantLib::ConvertibleZeroCouponBond>(new
			 QuantLib::ConvertibleZeroCouponBond(exercise,
				conversionRatio,
				conversionType,
				std::vector<boost::shared_ptr<QuantLib::Dividend> >(dividends.begin(), dividends.end()),
				std::vector<boost::shared_ptr<QuantLib::Callability> >(callability.begin(), callability.end()),
				creditSpread,
				issueDate,
				settlementDays,
				dayCounter,
				*schedule,
				redemption));
		libraryObject_ = qlBondObject_;
		if (description_.empty()) {
			std::ostringstream temp;
			temp << "ConvertibleZeroCouponBond ";
			temp << QuantLib::io::iso_date(qlBondObject_->maturityDate());
			description_ = temp.str();
			
		}
		}
	
		ConvertibleFixedCouponBond::ConvertibleFixedCouponBond(
			const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const string& des,
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
			bool permanent)
		 : Bond(properties, des, cur, permanent)
		 {
		qlBondObject_ = shared_ptr<QuantLib::ConvertibleFixedCouponBond>(new
			 QuantLib::ConvertibleFixedCouponBond(exercise,
				conversionRatio,
				conversionType,
				std::vector<boost::shared_ptr<QuantLib::Dividend> >(dividends.begin(), dividends.end()),
				std::vector<boost::shared_ptr<QuantLib::Callability> >(callability.begin(), callability.end()),
				creditSpread,
				issueDate,
				settlementDays,
				coupons,
				dayCounter,
				*schedule,
				redemption));
		libraryObject_ = qlBondObject_;
		if (description_.empty()) {
			std::ostringstream temp;
			temp << "ConvertibleFixedCouponBond ";
			temp << QuantLib::io::iso_date(qlBondObject_->maturityDate());
			description_ = temp.str();
			
		}
		}
	
		Callability::Callability(
			const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			
			QuantLib::Real price,
			QuantLib::Bond::Price::Type priceType,
			const QuantLib::Callability::Type callType,
			const QuantLib::Date& date,
			
			bool permanent)
		 : Callability(properties, permanent)
		 {
		qlCallObject_ = shared_ptr<QuantLib::Callability>(new QuantLib::Callability(
			QuantLib::Bond::Price(price, priceType),
			callType,
			date
			 ));
		libraryObject_ = qlCallObject_;
		}
	
		FixedDividend::FixedDividend(
			const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			
			QuantLib::Real amount,
			const QuantLib::Date& date,
			
			bool permanent)
		 : FixedDividend(properties, permanent)
		 {
		qlDivObject_ = shared_ptr<QuantLib::FixedDividend>(new QuantLib::FixedDividend(
			amount,
			date
			 ));
		libraryObject_ = qlDivObject_;
		}
	
		CoCoFloatingRateBond::CoCoFloatingRateBond(
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
			bool permanent)
			: Bond(properties, des, cur, permanent)
		{
		
			qlBondObject_ = shared_ptr<QuantLib::CoCoFloatingRateBond>(new
				QuantLib::CoCoFloatingRateBond(conversionRatio,
					QuantLib::Callability::Type::Call,
					std::vector<boost::shared_ptr<QuantLib::Dividend> >(dividends.begin(), dividends.end()),
					std::vector<boost::shared_ptr<QuantLib::Callability> >(callability.begin(), callability.end()),
					creditSpread,
					issueDate,
					settlementDays,
					index, fixingDays,
					gearings, spreads,
					dayCounter,
					*schedule,
					cocoTrigger, true,isWriteDown,cocoWriteDownRR, isRiskyDiscountingWD,
					redemption));
			libraryObject_ = qlBondObject_;
			if (description_.empty()) {
				std::ostringstream temp;
				temp << "CoCoFloatingRateBond ";
				temp << QuantLib::io::iso_date(qlBondObject_->maturityDate());
				description_ = temp.str();

			}
		}

		CoCoGenericCouponBond::CoCoGenericCouponBond(
			const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const string& des,
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
			bool permanent)
			: Bond(properties, des, cur, permanent)
		{
			qlBondObject_ = shared_ptr<QuantLib::CoCoFixedCouponBond>(new
				QuantLib::CoCoFixedCouponBond(
					conversionRatio, QuantLib::Callability::Type::Call,
					std::vector<boost::shared_ptr<QuantLib::Dividend> >(dividends.begin(), dividends.end()),
					std::vector<boost::shared_ptr<QuantLib::Callability> >(callability.begin(), callability.end()),
					creditSpread,
					issueDate,
					settlementDays,
					coupons,
					dayCounter,
					*schedule,
					cocoTrigger,true, isWriteDown,cocoWriteDownRR,isRiskyDiscountingWD,
					redemption));
			libraryObject_ = qlBondObject_;
			if (description_.empty()) {
				std::ostringstream temp;
				temp << "ConvertibleFixedCouponBond ";
				temp << QuantLib::io::iso_date(qlBondObject_->maturityDate());
				description_ = temp.str();

			}
		}
		
}
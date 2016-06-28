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

#if defined(HAVE_CONFIG_H)     // Dynamically created by configure
    #include <qlo/config.hpp>
#endif

#include <qlo/coupons.hpp>

#include <ql/cashflows/cmscoupon.hpp>

//using ObjectHandler::LibraryObject;
//using ObjectHandler::Create;
//using ObjectHandler::ValueObject;
//using QuantLib::earlier_than;
//using QuantLib::CashFlow;
//using boost::shared_ptr;
//using std::vector;

namespace QuantLibAddin {

    CmsCoupon::CmsCoupon(
		          const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			      const QuantLib::Date&                                paymentDate,
                  const QuantLib::Real                                 nominal,
                  const QuantLib::Date&                                startDate,
                  const QuantLib::Date&                                endDate,
                  const QuantLib::Natural                              fixingDays,
                  const boost::shared_ptr<QuantLib::SwapIndex>&        index,
                  const QuantLib::DayCounter&                          dayCounter,
                  const bool                                           isInArrears,
				  bool permanent)
				  : CashFlow(properties, permanent) {
		libraryObject_ = boost::shared_ptr<QuantLib::CashFlow>(new
            QuantLib::CmsCoupon(paymentDate,nominal,startDate,endDate,fixingDays,index,1.0,0.0,QuantLib::Date(),QuantLib::Date(),dayCounter,isInArrears));
	}

}
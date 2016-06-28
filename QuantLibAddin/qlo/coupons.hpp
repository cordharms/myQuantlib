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

#ifndef qla_coupons_hpp
#define qla_coupons_hpp

#include <qlo/leg.hpp>

#include <ql/time/businessdayconvention.hpp>
#include <ql/cashflows/replication.hpp>
#include <ql/indexes/swapindex.hpp>


namespace QuantLib {
    class CmsCoupon;   

    template <class T>
    class Handle;
}

namespace QuantLibAddin {

	OH_LIB_CLASS(CashFlow, QuantLib::CashFlow);

	class CmsCoupon : public CashFlow{
	public:
        CmsCoupon(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			      const QuantLib::Date&                                paymentDate,
                  const QuantLib::Real                                 nominal,
                  const QuantLib::Date&                                startDate,
                  const QuantLib::Date&                                endDate,
                  const QuantLib::Natural                              fixingDays,
                  const boost::shared_ptr<QuantLib::SwapIndex>&        index,
                  const QuantLib::DayCounter&                          dayCounter,
                  const bool                                           isInArrears,
				  bool                                                 permanent) ;
	};



}

#endif

/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2015 Sebastian Schlenkrich

 */


#include <qlo/templatecommodity.hpp>

namespace QuantLibAddin {

    IndexTermStructure::IndexTermStructure(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			const QuantLib::Date&                                referenceDate,
			const QuantLib::Calendar&                            cal,
			const QuantLib::DayCounter&                          dc,
			const boost::shared_ptr<QuantLib::Interpolation>&    timeInterpol,
            bool permanent) : TermStructure(properties,permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::IndexTermStructure>(
			new QuantLib::IndexTermStructure( referenceDate, cal, dc, timeInterpol ));            
    }



}




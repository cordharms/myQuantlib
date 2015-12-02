/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2015 Sebastian Schlenkrich

 */

#ifndef qla_templatecommodity_hpp
#define qla_templatecommodity_hpp

#include <ql/types.hpp>

#include <qlo/termstructures.hpp>

#include <ql/experimental/template/commodity/indextermstructure.hpp>



namespace QuantLib {
    template <class T>
    class Handle;
	class StochasticProcess;
}


namespace QuantLibAddin {

    class IndexTermStructure : public TermStructure {
    public:
        //HestonProcess(const boost::shared_ptr<ObjectHandler::ValueObject>& properties, bool permanent) : StochasticProcess(properties,permanent) {}
        IndexTermStructure(
                      const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			          const QuantLib::Date&                                referenceDate,
			          const QuantLib::Calendar&                            cal,
			          const QuantLib::DayCounter&                          dc,
			          const boost::shared_ptr<QuantLib::Interpolation>&    timeInterpol,
                      bool permanent);
    };


}

#endif


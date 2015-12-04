/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2015 Sebastian Schlenkrich

 */

#ifndef qla_templatecommodity_hpp
#define qla_templatecommodity_hpp

#include <qlo/termstructures.hpp>
#include <qlo/templatehestonmodel.hpp>

#include <ql/types.hpp>
#include <ql/experimental/template/commodity/indextermstructure.hpp>
#include <ql/experimental/template/commodity/commoditymodels.hpp>


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

	OH_OBJ_CLASS(Real2FMeanReversionModel,    RealStochasticProcess);

	class Real2FNormalModel : public Real2FMeanReversionModel {
	public:
		Real2FNormalModel(
                const boost::shared_ptr<ObjectHandler::ValueObject>&   properties,
                const QuantLib::Handle<QuantLib::IndexTermStructure>&  phi,
                const std::vector<QuantLib::Time>&                     times,   // time-grid of left-constant model parameter values
		        // time-dependent parameters, left-piecewise constant on times_-grid
		        const std::vector< QuantLib::Real >&                   sigma,  // Y-volatility
		        const std::vector< QuantLib::Real >&                   eta,    // Z-volatility
				const QuantLib::Real                                   a,      // Y-mean reversion
				const QuantLib::Real                                   b,      // Z-mean reversion
				const QuantLib::Real                                   rho,    // Y vs Z correlation
				bool                                                   permanent);			   
	};

	class Real2FLognormalModel : public Real2FMeanReversionModel {
	public:
		Real2FLognormalModel(
                const boost::shared_ptr<ObjectHandler::ValueObject>&   properties,
                const QuantLib::Handle<QuantLib::IndexTermStructure>&  phi,
                const std::vector<QuantLib::Time>&                     times,   // time-grid of left-constant model parameter values
		        // time-dependent parameters, left-piecewise constant on times_-grid
		        const std::vector< QuantLib::Real >&                   sigma,  // Y-volatility
		        const std::vector< QuantLib::Real >&                   eta,    // Z-volatility
				const QuantLib::Real                                   a,      // Y-mean reversion
				const QuantLib::Real                                   b,      // Z-mean reversion
				const QuantLib::Real                                   rho,    // Y vs Z correlation
				bool                                                   permanent);			   
	};


}

#endif


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


	Real2FNormalModel::Real2FNormalModel(
                const boost::shared_ptr<ObjectHandler::ValueObject>&   properties,
                const QuantLib::Handle<QuantLib::IndexTermStructure>&  phi,
                const std::vector<QuantLib::Time>&                     times,   // time-grid of left-constant model parameter values
		        // time-dependent parameters, left-piecewise constant on times_-grid
		        const std::vector< QuantLib::Real >&                   sigma,  // Y-volatility
		        const std::vector< QuantLib::Real >&                   eta,    // Z-volatility
				const QuantLib::Real                                   a,      // Y-mean reversion
				const QuantLib::Real                                   b,      // Z-mean reversion
				const QuantLib::Real                                   rho,    // Y vs Z correlation
				bool                                                   permanent)
				: Real2FMeanReversionModel(properties,permanent) {
       libraryObject_ = boost::shared_ptr<QuantLib::Real2FNormalModel>(
			new QuantLib::Real2FNormalModel( phi, times, sigma, eta, a, b, rho ));            	    
	}

	Real2FLognormalModel::Real2FLognormalModel(
                const boost::shared_ptr<ObjectHandler::ValueObject>&   properties,
                const QuantLib::Handle<QuantLib::IndexTermStructure>&  phi,
                const std::vector<QuantLib::Time>&                     times,   // time-grid of left-constant model parameter values
		        // time-dependent parameters, left-piecewise constant on times_-grid
		        const std::vector< QuantLib::Real >&                   sigma,  // Y-volatility
		        const std::vector< QuantLib::Real >&                   eta,    // Z-volatility
				const QuantLib::Real                                   a,      // Y-mean reversion
				const QuantLib::Real                                   b,      // Z-mean reversion
				const QuantLib::Real                                   rho,    // Y vs Z correlation
				bool                                                   permanent)
				: Real2FMeanReversionModel(properties,permanent) {
       libraryObject_ = boost::shared_ptr<QuantLib::Real2FLognormalModel>(
			new QuantLib::Real2FLognormalModel( phi, times, sigma, eta, a, b, rho ));            	    
	}




}




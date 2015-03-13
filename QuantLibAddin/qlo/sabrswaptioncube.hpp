/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2010 Sebastian Schlenkrich

 */

#ifndef qla_sabrswaptioncube_hpp
#define qla_sabrswaptioncube_hpp

#include <ql/types.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/experimental/sabrswaptioncube/sabrswaptioncube.hpp>


#include <qlo/termstructures.hpp>
#include <qlo/indexes/iborindex.hpp>


namespace QuantLibAddin {

    class SabrSwaptionCube : public SwaptionVolatilityStructure {
    public:
        SabrSwaptionCube ( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                           const std::vector<QuantLib::Time>&                   optionTimes,
                           const std::vector<QuantLib::Time>&                   swapTimes,
                           const std::vector< std::vector< QuantLib::Real > >&  alpha,
                           const std::vector< std::vector< QuantLib::Real > >&  beta,
                           const std::vector< std::vector< QuantLib::Real > >&  rho,
                           const std::vector< std::vector< QuantLib::Real > >&  nu,
                           const std::vector< std::vector< QuantLib::Real > >&  fwd,
                           QuantLib::BusinessDayConvention                      bdc,
                           const QuantLib::DayCounter&                          dc,
						   const bool                                           useNormalVols,
                           bool permanent );

    };

	class SABRCapletSurface : public OptionletVolatilityStructure {
	public:
		SABRCapletSurface( const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			               const boost::shared_ptr<QuantLib::SwaptionVolatilityStructure> cube,
						   const QuantLib::Real                                           swapTerm,
                           bool permanent );
	};

}

#endif


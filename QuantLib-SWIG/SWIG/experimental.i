
/*
 Copyright (C) 2019, Cord Harms

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

#ifndef quantlib_experimental_i
#define quantlib_experimental_i

%include options.i
%include marketelements.i
%include types.i
%include termstructures.i


// actual market elements
%{
using QuantLib::DeltaVolQuote;
typedef boost::shared_ptr<Quote> DeltaVolQuotePtr;
%}

#if defined(SWIGJAVA) || defined(SWIGCSHARP)
%rename(_DeltaVolQuote) DeltaVolQuote;
#else
%ignore DeltaVolQuote;
#endif
class DeltaVolQuote {
  public:
    enum DeltaType {
            Spot = 0,        // Spot Delta, e.g. usual Black Scholes delta
            Fwd = 1,         // Forward Delta
            PaSpot = 2,      // Premium Adjusted Spot Delta
            PaFwd = 3        // Premium Adjusted Forward Delta
        };
    enum AtmType {
            AtmNull,         // Default, if not an atm quote
            AtmSpot,         // K=S_0
            AtmFwd,          // K=F
            AtmDeltaNeutral, // Call Delta = Put Delta
            AtmVegaMax,      // K such that Vega is Maximum
            AtmGammaMax,     // K such that Gamma is Maximum
            AtmPutCall50     // K such that Call Delta=0.50 (only for Fwd Delta)
        };
#if defined(SWIGJAVA) || defined(SWIGCSHARP)
  private:
    DeltaVolQuote();
#endif
};

%rename(DeltaVolQuote) DeltaVolQuotePtr;
class DeltaVolQuotePtr : public boost::shared_ptr<Quote> {
  public:
    %extend {
        DeltaVolQuotePtr(Real delta,
                      const Handle<Quote>& vol,
                      Time maturity,
                      DeltaVolQuote::DeltaType deltaType) {
            return new DeltaVolQuotePtr(new DeltaVolQuote(delta, vol, maturity, deltaType));
        };
        static const DeltaVolQuote::DeltaType Spot = DeltaVolQuote::Spot;
        static const DeltaVolQuote::DeltaType Fwd = DeltaVolQuote::Fwd;
        static const DeltaVolQuote::DeltaType PaSpot = DeltaVolQuote::PaSpot;
        static const DeltaVolQuote::DeltaType PaFwd = DeltaVolQuote::PaFwd;
        static const DeltaVolQuote::AtmType AtmNull = DeltaVolQuote::AtmNull;
        static const DeltaVolQuote::AtmType AtmSpot = DeltaVolQuote::AtmSpot;
        static const DeltaVolQuote::AtmType AtmFwd = DeltaVolQuote::AtmFwd;
        static const DeltaVolQuote::AtmType AtmDeltaNeutral = DeltaVolQuote::AtmDeltaNeutral;
        static const DeltaVolQuote::AtmType AtmVegaMax = DeltaVolQuote::AtmVegaMax;
        static const DeltaVolQuote::AtmType AtmGammaMax = DeltaVolQuote::AtmGammaMax;
        static const DeltaVolQuote::AtmType AtmPutCall50 = DeltaVolQuote::AtmPutCall50;
    }
};

%{
using QuantLib::BlackDeltaCalculator;
%}

class BlackDeltaCalculator {
  public:
    %extend {
        BlackDeltaCalculator(Option::Type ot,
                         DeltaVolQuote::DeltaType dt,
                         Real spot,
                         DiscountFactor dDiscount,
                         DiscountFactor fDiscount,
                         Real stdDev){
                            return new BlackDeltaCalculator(ot,dt,spot,dDiscount,fDiscount,stdDev);
                         };
        Real strikeFromDelta(Real delta) const {return (*self).strikeFromDelta(delta);};
        Real atmStrike(DeltaVolQuote::AtmType atmT) const {return (*self).atmStrike(atmT);};
    }
};

#endif


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
%include common.i
%include stochasticprocess.i
%include vectors.i


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

//RealStochasticProcesses:

%{
using QuantLib::StochasticProcessT;
using QuantLib::MultiAssetBSModel;
%}

%ignore StochasticProcessT;
template <class DateType, class PassiveType, class ActiveType> class StochasticProcessT  {
    public:
        StochasticProcessT();
};

%template(RealStochasticProcess) boost::shared_ptr<StochasticProcessT<Time,Real,Real>>;
typedef StochasticProcessT<Time,Real,Real> RealStochasticProcess;

%{
typedef StochasticProcessT<Time,Real,Real> RealStochasticProcess;
typedef boost::shared_ptr<RealStochasticProcess> MultiAssetBSModelPtr;
%}

%rename(MultiAssetBSModel) MultiAssetBSModelPtr;
class MultiAssetBSModelPtr : public boost::shared_ptr<RealStochasticProcess> {
  public:
    %extend {
        MultiAssetBSModelPtr(const Handle<YieldTermStructure>&                                            termStructure,
			              const std::vector<std::string>&                                                 aliases,
			              const std::vector<boost::shared_ptr<StochasticProcess> >&                       processes,
			              const std::vector< std::vector<Real> >&                                         correlations) {
            std::vector<boost::shared_ptr<GeneralizedBlackScholesProcess>> gbslist(processes.size());
            for(int i=0;i<gbslist.size();i++){
                gbslist[i] = boost::dynamic_pointer_cast<GeneralizedBlackScholesProcess>(processes[i]);
            }
            return new MultiAssetBSModelPtr(new MultiAssetBSModel(termStructure,aliases,gbslist,correlations));
        };
    }
};



//RealMonteCarlo:

%{
using QuantLib::MCSimulationT;
%}

template <class DateType, class PassiveType, class ActiveType> class MCSimulationT  {
    public:
        MCSimulationT( const boost::shared_ptr<RealStochasticProcess> process,
                       const std::vector<Real>&                       simTimes,
                       const std::vector<Real>&                       obsTimes,
                       size_t                               nPaths,
                       BigNatural                           seed = 1234,
                       bool                                 richardsonExtrapolation = true,
                       bool                                 timeInterpolation = false,
                       bool                                 storeBrownians = false );
        void simulate() {self->simulate()};
        void calculateAssetAdjuster( const std::vector<Real>&  assetObservTimes, const std::vector<std::string>& aliases ) {self->calculateAssetAdjuster()};
        std::vector<std::vector<ActiveType>> observedPath(const size_t idx){ return self->simulate(observedPath(idx))};
};
typedef MCSimulationT<Time,Real,Real> RealMCSimulation;
%template(RealMCSimulation) boost::shared_ptr<MCSimulationT<Time,Real,Real>>;

%{
using QuantLib::MCPayoffT;
using QuantLib::RealMCPayoffPricer;
typedef MCSimulationT<Time,Real,Real> RealMCSimulation;
typedef boost::shared_ptr<RealMCSimulation> RealMCSimulationPtr;
%}

class RealMCSimulationPtr : public boost::shared_ptr<RealMCSimulation> {
  public:
    %extend {
        RealMCSimulationPtr( const boost::shared_ptr<RealStochasticProcess> process,
                       const std::vector<Real>&                       simTimes,
                       const std::vector<Real>&                       obsTimes,
                       size_t                               nPaths,
                       BigNatural                           seed = 1234,
                       bool                                 richardsonExtrapolation = true,
                       bool                                 timeInterpolation = false,
                       bool                                 storeBrownians = false ) {
            return new RealMCSimulationPtr(new RealMCSimulation(process,simTimes,obsTimes,nPaths,seed,richardsonExtrapolation,timeInterpolation,storeBrownians));
        };
        void simulate() {boost::dynamic_pointer_cast<RealMCSimulation>(*self)->simulate();};
        void calculateAssetAdjuster( const std::vector<Real>&  assetObservTimes, const std::vector<std::string>& aliases ) {
            boost::dynamic_pointer_cast<RealMCSimulation>(*self)->calculateAssetAdjuster(assetObservTimes,aliases);
        };
        std::vector<std::vector<Real>> observedPath(const size_t idx){ return boost::dynamic_pointer_cast<RealMCSimulation>(*self)->observedPath(idx);};
    }
};


template <class DateType, class PassiveType, class ActiveType> class MCPayoffT  {
    public:
        MCPayoffT(){}
};
typedef MCPayoffT<Time,Real,Real> RealMCPayoff;

%template(RealMCPayoff) boost::shared_ptr<MCPayoffT<Time,Real,Real>>;

%{
typedef MCPayoffT<Time,Real,Real> RealMCPayoff;
typedef boost::shared_ptr<RealMCPayoff> RealMCAssetPtr;
typedef boost::shared_ptr<RealMCPayoff> RealMCVanillaOptionPtr;
typedef boost::shared_ptr<RealMCPayoff> RealMCPayoffPricerPtr;
%}

%rename(RealMCAsset) RealMCAssetPtr;
//nested classes currently not supported in SWIG, therefore declared outside class MCPayoffT for RealMCPayoff
class RealMCAssetPtr : public boost::shared_ptr<RealMCPayoff> {
  public:
    %extend {
        RealMCAssetPtr(Time obsTime, const std::string alias) {
            return new RealMCAssetPtr(new RealMCPayoff::Asset(obsTime,alias));
        };
    }
};

namespace std {
    %template(VectorOfRealMCPayoff) vector<boost::shared_ptr<RealMCPayoff>>;
}

%rename(RealMCVanillaOption) RealMCVanillaOptionPtr;
//nested classes currently not supported in SWIG, therefore declared outside class MCPayoffT for RealMCPayoff
class RealMCVanillaOptionPtr : public boost::shared_ptr<RealMCPayoff> {
  public:
    %extend {
        RealMCVanillaOptionPtr(const Time   expiry,
		              const std::string&    alias,
		              const Real            strike,
					  const Real            callOrPut) {
            return new RealMCVanillaOptionPtr(new RealMCPayoff::VanillaOption(expiry,alias,strike,callOrPut));
        };
    }
};

//nested classes currently not supported in SWIG, therefore declared outside class MCPayoffT for RealMCPayoff
class RealMCPayoffPricer {
  public:
    RealMCPayoffPricer(const std::vector< boost::shared_ptr<MCPayoffT<Time, Real, Real>> >&         payoffs,
                       const boost::shared_ptr<MCSimulationT<Time, Real, Real>>&  simulation){
        return new RealMCPayoffPricer(payoffs,simulation);
    };
    static std::vector<Real> NPVs(const std::vector< boost::shared_ptr<MCPayoffT<Time, Real, Real>> >&         payoffs,
                                  const boost::shared_ptr<RealMCSimulation>&  simulation){
        boost::shared_ptr<RealMCSimulation> simPtr = boost::dynamic_pointer_cast<RealMCSimulation>(simulation);
        return MCPayoffT<Time, Real, Real>::Pricer::NPVs(payoffs,simPtr);
    };
};

%{
using QuantLib::blackFormulaImpliedStdDev;
%}

    
%inline %{
    Real  get_blackFormulaImpliedStdDev(Option::Type optionType,
                                                Real strike,
                                                Real forward,
                                                Real blackPrice,
                                                Real discount,
                                                Real displacement=0,
                                                Real guess=0.1, Real accuracy=1.0e-6, Real maxIter=100) {
        return blackFormulaImpliedStdDev(optionType,strike,forward,blackPrice,discount,displacement,guess,accuracy,maxIter);
    }
%}

#endif

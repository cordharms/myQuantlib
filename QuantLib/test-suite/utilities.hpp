
/*
 Copyright (C) 2003, 2004 StatPro Italia srl

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it under the
 terms of the QuantLib license.  You should have received a copy of the
 license along with this program; if not, please email quantlib-dev@lists.sf.net
 The license is also available online at http://quantlib.org/html/license.html

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifndef quantlib_test_utilities_hpp
#define quantlib_test_utilities_hpp

#include <ql/Instruments/payoffs.hpp>
#include <ql/exercise.hpp>
#include <ql/termstructure.hpp>
#include <ql/voltermstructure.hpp>
#include <ql/DayCounters/simpledaycounter.hpp>
#include <ql/Patterns/observable.hpp>
#include <vector>
#include <string>
#include <numeric>

// This makes it easier to use array literals (alas, no std::vector literals)
#define LENGTH(a) (sizeof(a)/sizeof(a[0]))

namespace QuantLib {

    std::string payoffTypeToString(const Handle<Payoff>&);
    std::string exerciseTypeToString(const Handle<Exercise>&);


    Handle<TermStructure> 
    makeFlatCurve(const Handle<Quote>& forward,
                  DayCounter dc);

    Handle<BlackVolTermStructure> 
    makeFlatVolatility(const Handle<Quote>& volatility,
                       DayCounter dc);

    double relativeError(double x1, double x2, double reference);

    struct VanillaOptionData {
        Option::Type type;
        double strike;
        double s;      // spot
        double q;      // dividend
        double r;      // risk-free rate
        Time t;        // time to maturity
        double v;      // volatility
        double result; // expected result
        double tol;    // tolerance
    };

    void vanillaOptionTestFailed(std::string greekName,
                                 const Handle<StrikedTypePayoff>& payoff,
                                 const Handle<Exercise>& exercise,
                                 double s,
                                 double q,
                                 double r,
                                 Date today,
                                 DayCounter dc,
                                 double v,
                                 double expected,
                                 double calculated,
                                 double error,
                                 double tolerance);

}

class Flag : public QuantLib::Observer {
  private:
    bool up_;
  public:
    Flag() : up_(false) {}
    void raise() { up_ = true; }
    void lower() { up_ = false; }
    bool isUp() const { return up_; }
    void update() { raise(); }
};

template<class Iterator>
double norm(const Iterator& begin, const Iterator& end, double h) {
    // squared values
    std::vector<double> f2(end-begin);
    std::transform(begin,end,begin,f2.begin(),
                   std::multiplies<double>());
    // numeric integral of f^2
    double I = h * (std::accumulate(f2.begin(),f2.end(),0.0)
                    - 0.5*f2.front() - 0.5*f2.back());
    return QL_SQRT(I);
}

#endif

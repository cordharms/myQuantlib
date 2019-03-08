
# Copyright (C) 2019, Cord Harms
#
# This file is part of QuantLib, a free-software/open-source library
# for financial quantitative analysts and developers - http://quantlib.org/
#
# QuantLib is free software: you can redistribute it and/or modify it under the
# terms of the QuantLib license.  You should have received a copy of the
# license along with this program; if not, please email
# <quantlib-dev@lists.sf.net>. The license is also available online at
# <http://quantlib.org/license.shtml>.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the license for more details.

from QuantLib import *
import numpy as np
import math

def is_number(s):
    try:
        float(s)
        return True
    except ValueError:
        return False

class VolSurface:
    def __init__(self,todaysDate, spot, deltas, matAsDates, yieldCurve, divCurve):
        self.todaysDate = todaysDate
        self.spot = spot
        self.deltas = deltas
        self.matAsDates = matAsDates
        self.yieldCurve = yieldCurve
        self.divCurve = divCurve
        self.quotes = []
        self.strikes = []
    def __calcStrikesFromDeltas(self):
        self.strikes = np.zeros((len(self.matAsDates),len(self.deltas)))
        for i in range(0,len(self.deltas)):
            for j in range(0,len(self.matAsDates)):
                if is_number(self.deltas[i]):
                    if self.deltas[i]<0:
                        bdc = BlackDeltaCalculator(Option.Put,
                            DeltaVolQuote.Spot,
                            self.spot.value(),
                            self.yieldCurve.discount(self.matAsDates[j]),
                            self.divCurve.discount(self.matAsDates[j]),
                            self.quotes[j][i]*math.sqrt(Actual365Fixed().yearFraction(self.todaysDate, self.matAsDates[j]))*0.01)
                        self.strikes[j][i] = bdc.strikeFromDelta(self.deltas[i])
                    else:
                        bdc = BlackDeltaCalculator(Option.Call,
                            DeltaVolQuote.Spot,
                            self.spot.value(),
                            self.yieldCurve.discount(self.matAsDates[j]),
                            self.divCurve.discount(self.matAsDates[j]),
                            self.quotes[j][i]*math.sqrt(Actual365Fixed().yearFraction(self.todaysDate, self.matAsDates[j]))*0.01)
                        self.strikes[j][i] = bdc.strikeFromDelta(self.deltas[i])
                else:
                    bdc = BlackDeltaCalculator(Option.Put,
                        DeltaVolQuote.Spot,
                        self.spot.value(),
                        self.yieldCurve.discount(self.matAsDates[j]),
                        self.divCurve.discount(self.matAsDates[j]),
                        self.quotes[j][i]*math.sqrt(Actual365Fixed().yearFraction(self.todaysDate, self.matAsDates[j]))*0.01)
                    self.strikes[j][i] = bdc.atmStrike(DeltaVolQuote.AtmFwd)
                    self.atmIndex = i
    def calcSABRSmiledSurface(self):
        self.__calcStrikesFromDeltas()
        self.sabrSections = VectorOfSABRInterpolatedSmileSection()
        for i in range(0,len(self.matAsDates)):
            sabr = SabrInterpolatedSmileSection(
                           self.matAsDates[i], self.spot.value(),self.strikes[i,:].tolist(),
                           False, self.quotes[i][self.atmIndex]*0.01, self.quotes[i,:].tolist(),
                           0.08, 0.7, 1.0, 
                           0.1)
            self.sabrSections.append(sabr)
        self.smiledSurface = SmiledSurface(self.sabrSections,self.todaysDate)
        print(self.smiledSurface)

########################################################
# global data
########################################################

calendar = TARGET()
todaysDate = Date(10,October,2017);
Settings.instance().evaluationDate = todaysDate

########################################################
# market data
########################################################

underlying1 = SimpleQuote(1.0)
underlying2 = SimpleQuote(1.0)
underlyingCross = SimpleQuote(underlying1.value()/underlying2.value())

yieldDom = FlatForward(0,calendar,0.0,Actual365Fixed())
yield1 = FlatForward(0,calendar,0.0,Actual365Fixed())
yield2 = FlatForward(0,calendar,0.0,Actual365Fixed())

volDelta = [-0.05,-0.1,-0.15,-0.25,-0.35,"ATM",0.35,0.25,0.15,0.1,0.05]
volMat = ["1D","1W","2W","3W","1M","2M","3M","4M","5M","6M","9M","1Y","18M","2Y","3Y","4Y","5Y","6Y","7Y","10Y","15Y","20Y","25Y"]
#transform to dates
for i in range(0,len(volMat)): volMat[i] = calendar.advance(todaysDate,Period(volMat[i]))

vol1 = VolSurface(todaysDate, underlying1,volDelta, volMat,yieldDom,yield1)
vol2 = VolSurface(todaysDate, underlying2,volDelta, volMat,yieldDom,yield2)
volCross = VolSurface(todaysDate, underlyingCross,volDelta, volMat, yield2, yield1)

vol1.quotes = np.loadtxt("localCorrelation_vol1.txt", dtype='f', delimiter=',')
vol2.quotes = np.loadtxt("localCorrelation_vol2.txt", dtype='f', delimiter=',')
volCross.quotes = np.loadtxt("localCorrelation_volCross.txt", dtype='f', delimiter=',')

try:
    assert len(volDelta) == vol1.quotes.shape[1], "err: size of volDelta and columns of vol1 do not match"
    assert len(volDelta) == vol2.quotes.shape[1], "err: size of volDelta and columns of vol2 do not match"
    assert len(volDelta) == volCross.quotes.shape[1], "err: size of volDelta and columns of volCross do not match"
    assert len(volMat) == vol1.quotes.shape[0], "err: size of volMat and rows of vol1 do not match"
    assert len(volMat) == vol2.quotes.shape[0], "err: size of volMat and rows of vol2 do not match"
    assert len(volMat) == volCross.quotes.shape[0], "err: size of volMat and rows of volCross do not match"
except AssertionError as e:
    print(e)
    quit()

########################################################
# derive blackVolSurface
########################################################

vol1.calcSABRSmiledSurface()
vol2.calcSABRSmiledSurface()
volCross.calcSABRSmiledSurface()

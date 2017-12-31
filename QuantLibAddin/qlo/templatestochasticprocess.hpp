/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2010 Sebastian Schlenkrich

 */

#ifndef qla_stochasticprocess_hpp
#define qla_stochasticprocess_hpp


namespace QuantLib {
	template <class T>
	class Handle;
	class StochasticProcess;
	class CalibratedModel;
}

namespace QuantLibAddin {

	OH_LIB_CLASS(StochasticProcess, QuantLib::StochasticProcess);

	OH_LIB_CLASS(CalibratedModel, QuantLib::CalibratedModel);

	OH_LIB_CLASS(RealStochasticProcess, QuantLib::RealStochasticProcess);
	OH_OBJ_CLASS(RealTDStochVolModel, RealStochasticProcess);

}

#endif


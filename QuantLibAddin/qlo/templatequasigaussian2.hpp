/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2010 Sebastian Schlenkrich

 */

#ifndef qla_templatequasigaussian2_hpp
#define qla_templatequasigaussian2_hpp

#include <ql/types.hpp>
#include <ql/experimental/templatemodels/qgaussian2/quasigaussianmodel2T.hpp>
#include <ql/experimental/templatemodels/qgaussian2/qgswapratemodelT.hpp>
#include <ql/experimental/templatemodels/qgaussian2/qgaverageswapratemodelT.hpp>
#include <ql/experimental/templatemodels/qgaussian2/qgcalibrator.hpp>
#include <ql/experimental/templatemodels/qgaussian2/qglocalvolmodel.hpp>


#include <qlo/termstructures.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/templatestochasticprocess.hpp>

namespace QuantLib {
    template <class T>
    class Handle;
	class Swaption;
	class SwapIndex;

	typedef QuasiGaussianModel2T<QuantLib::Time, QuantLib::Real, QuantLib::Real> QuasiGaussianModel;
	typedef QGSwaprateModelT<QuantLib::Time, QuantLib::Real, QuantLib::Real> QGSwaprateModel;
	typedef QGAverageSwaprateModelT<QuantLib::Time, QuantLib::Real, QuantLib::Real> QGAverageSwaprateModel;
}

namespace QuantLibAddin {

    // OH_LIB_CLASS(RealStochasticProcess, QuantLib::RealStochasticProcess);

    class QuasiGaussianModel : public RealStochasticProcess {
      public:
		  // using piece-wise constant parameters
		  QuasiGaussianModel(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
							 const QuantLib::Handle<QuantLib::YieldTermStructure>& hYTS,
		                     // number of yield curve factors (excluding stoch. vol)
		                     size_t                                             d,       // (d+1)-dimensional Brownian motion for [x(t), z(t)]^T
		                     // unique grid for time-dependent parameters
		                     const std::vector<QuantLib::Time>&                 times,   // time-grid of left-constant model parameter values
		                     // time-dependent parameters, left-piecewise constant on times_-grid
		                     const std::vector< std::vector<QuantLib::Real> >&  sigma,   // volatility
		                     const std::vector< std::vector<QuantLib::Real> >&  slope,   // shift
		                     const std::vector< std::vector<QuantLib::Real> >&  curve,   // f-weighting
		                     const std::vector<QuantLib::Real>&                 eta,     // vol-of-vol
		                     // time-homogeneous parameters
		                     const std::vector<QuantLib::Real>&                 delta,   // maturity of benchmark rates f(t,t+delta_i) 		
		                     const std::vector<QuantLib::Real>&                 chi,     // mean reversions
		                     const std::vector< std::vector<QuantLib::Real> >&  Gamma,   // (benchmark rate) correlation matrix
		                     QuantLib::Real                                     theta,   // stoch vol mean reversion speed
							 bool permanent);

		  // calibrated model from calibrator
		  QuasiGaussianModel(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			                 const boost::shared_ptr<QuantLib::QGCalibrator>&     calibrator,
							 bool permanent);

		  // do nothing, only fascilitate inheritance
		  QuasiGaussianModel(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
			                 bool                                                 permanent);
	};

	class QGSwaprateModel : public RealStochasticProcess {
	public:
		// do nothing, only fascilitate inheritance
		QGSwaprateModel(const boost::shared_ptr<ObjectHandler::ValueObject>&         properties,
			            bool                                                         permanent);

		QGSwaprateModel(const boost::shared_ptr<ObjectHandler::ValueObject>&         properties,
			            const boost::shared_ptr<QuantLib::QuasiGaussianModel>&       model,
			            const std::vector<QuantLib::Time>&                           floatTimes,    // T[1], ..., T[M]
			            const std::vector<QuantLib::Real>&                           floatWeights,  // u[1], ..., u[M]
			            const std::vector<QuantLib::Time>&                           fixedTimes,    // T[1], ..., T[N]
			            const std::vector<QuantLib::Real>&                           fixedWeights,  // w[1], ..., w[N-1]
			            const std::vector<QuantLib::Time>&                           modelTimes,    // time grid for numerical integration
			            const bool                                                   useExpectedXY, // evaluate E^A [ x(t) ], E^A [ y(t) ] as expansion points
			            bool permanent);

		QGSwaprateModel(const boost::shared_ptr<ObjectHandler::ValueObject>&         properties,
			const boost::shared_ptr<QuantLib::QuasiGaussianModel>&                   model,
			const boost::shared_ptr<QuantLib::Swaption>&                             swaption,
			const QuantLib::Handle<QuantLib::YieldTermStructure>&                    discountCurve,
			const QuantLib::Size                                                     timePointsPerYear,    // time grid for numerical integration
			const bool                                                               useExpectedXY, // evaluate E^A [ x(t) ], E^A [ y(t) ] as expansion points
			bool permanent);

		QGSwaprateModel(const boost::shared_ptr<ObjectHandler::ValueObject>&         properties,
			const boost::shared_ptr<QuantLib::QuasiGaussianModel>&                   model,
			const QuantLib::Time                                                     fixingTime,
			const boost::shared_ptr<QuantLib::SwapIndex>&                            swapIndex,
			const QuantLib::Handle<QuantLib::YieldTermStructure>&                    discountCurve,
			const QuantLib::Size                                                     timePointsPerYear,    // time grid for numerical integration
			const bool                                                               useExpectedXY, // evaluate E^A [ x(t) ], E^A [ y(t) ] as expansion points
			bool permanent);
	};

	class QGAverageSwaprateModel : public QGSwaprateModel {
	public:
		QGAverageSwaprateModel(const boost::shared_ptr<ObjectHandler::ValueObject>&         properties,
			const boost::shared_ptr<QuantLib::QGSwaprateModel>&                             model,
			bool                                                                            permanent);
	};

	class QGCalibrator : public ObjectHandler::LibraryObject<QuantLib::QGCalibrator> {
	public:
		QGCalibrator(const boost::shared_ptr<ObjectHandler::ValueObject>&            properties,
			         const boost::shared_ptr<QuantLib::QuasiGaussianModel>&          model,
			         const boost::shared_ptr<QuantLib::SwaptionVolatilityStructure>& volTS,
			         const std::vector< boost::shared_ptr<QuantLib::SwapIndex> >&    swapIndices,
			         const QuantLib::Real                                            modelTimesStepSize,
			         const bool                                                      useExpectedXY,
                     const QuantLib::Real                                            sigmaMax,
                     const QuantLib::Real                                            slopeMax,
                     const QuantLib::Real                                            etaMax,
                     const QuantLib::Real                                            sigmaWeight,
                     const QuantLib::Real                                            slopeWeight,
                     const QuantLib::Real                                            etaWeight,
			         const QuantLib::Real                                            penaltySigma,
			         const QuantLib::Real                                            penaltySlope,
			         const boost::shared_ptr<QuantLib::EndCriteria>&                 endCriteria,
			         bool                                                            permanent);
	};

	class QGLocalvolModel : public QuasiGaussianModel {
	public:
		QGLocalvolModel(
			const boost::shared_ptr<ObjectHandler::ValueObject>&            properties,
			const QuantLib::Handle<QuantLib::YieldTermStructure>&           hYTS,
			const boost::shared_ptr<QuantLib::SwaptionVolatilityStructure>& volTS,
			const QuantLib::Real                                            chi,
			const boost::shared_ptr<QuantLib::SwapIndex>&                   swapIndex,
			const std::vector<QuantLib::Time>&                              times,      // time-grid of left-constant model parameter values
			const std::vector<QuantLib::Real>&                              stdDevGrid,  // S-grid in terms of normal ATM vol stdDev's
			const QuantLib::Size                                            nPaths,
			const QuantLib::BigNatural                                      seed,
			bool                                                            permanent);

	};

	class QGLocalvolModelSimulation : public ObjectHandler::LibraryObject<QuantLib::QGLocalvolModel::MCSimulation> {
	public:
		QGLocalvolModelSimulation(
			const boost::shared_ptr<ObjectHandler::ValueObject>&         properties,
			const boost::shared_ptr<QuantLib::QGLocalvolModel>&          model,
			bool                                                         permanent);
	};

}  // namespace QuantLibAddin

#endif  // quasigaussianmodels


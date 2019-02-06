#include <cmath>

#include "hough.h"

HoughTransformer::HoughTransformer(const double thetaStep,
                                   const double thetaStart,
                                   const double thetaStop,
                                   const bool endpoint)
    : thetaSize {static_cast<std::size_t>(round((thetaStop-thetaStart)/thetaStep))}
{
    // if endpoint was requested, we need one more theta value
    if (endpoint)
        thetaSize++;

    // make lookup tables for sin and cos
    sinLT = new double[thetaSize];
    cosLT = new double[thetaSize];

    // fill lookup tables
    double theta = thetaStart;
    for (std::size_t i{0}; i<thetaSize; i++) {
        sinLT[i] = sin(theta);
        cosLT[i] = cos(theta);
        theta += thetaStep;
    }
}

HoughTransformer::~HoughTransformer()
{
}

void HoughTransformer::transform(double* inputSignal, std::size_t x_size,
                                 std::size_t y_size=1)
{

}

int HoughTransformer::getRhoLine(std::size_t x, std::size_t y,
                                 std::size_t theta)
{
    double rho = x
}

void HoughTransformer::quantize(std::size_t max, std::size_t steps)
{
}

void HoughTransformer::edges()
{

}

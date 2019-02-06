#include <cmath>

#include "hough.h"

HoughTransformer::HoughTransformer(const double thetaStep,
                                   const double thetaStart,
                                   const double thetaStop,
                                   const bool endpoint)
{
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

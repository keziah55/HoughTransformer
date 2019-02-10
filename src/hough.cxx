#include <cmath>
#include <vector>
#include <stdexcept>
#include <fstream>

#include "hough.h"

HoughTransformer::HoughTransformer(const double thetaStep,
                                   const double thetaStart,
                                   const double thetaStop,
                                   const bool endpoint)
: thetaSize {static_cast<std::size_t>(round((thetaStop-thetaStart)/thetaStep))}
// , x_values {nullptr}
// , y_values {nullptr}
{
    // if endpoint was requested, we need one more theta value
    if (endpoint)
        thetaSize++;

    // fill sin and cos lookup tables
    double theta = thetaStart;
    for (std::size_t i{0}; i<thetaSize; i++) {
        sinLT.push_back(sin(theta));
        cosLT.push_back(cos(theta));
        theta += thetaStep;
    }
}

HoughTransformer::~HoughTransformer()
{
}

void HoughTransformer::transform(const double* inputSignal,
                                 const std::size_t x_size,
                                 const std::size_t y_size, const double sig_max)
{
    if (y_size == 1)
        quantize(sig_max, x_size);
    else if (y_size > 1)
        edges();
    else
        throw std::invalid_argument("Input signal must be 1D or 2D.");

    // for 1D signal, y_values.size()=x_size, but for 2D signal, they may differ
    std::size_t r_max = round(sqrt(pow(x_size,2) + pow(y_values.size(),2)));

    // accumulator width
    std::size_t acc_width {2*r_max};

    // reserve all the space we need for the accumulator
    // access elements: acc[rho][theta]
    std::vector<std::vector<int>> acc;
    acc.resize(thetaSize);
    for (std::size_t i {0}; i<acc.size(); i++)
        acc[i].resize(acc_width);

    // x may be read from x_values or inferred from inputSignal indices
    std::size_t x;
    std::size_t x_idx {0};
    std::size_t y;
    std::size_t rho;

    for (std::size_t i {0}; i<x_size; i++) {
        // get appropriate value of x
        if (x_values.empty())
            x++;
        else {
            x = x_values[x_idx];
            x_idx++;
        }
        // get y
        y = y_values[i];

        // for all angles, get rho and increment accumulator
        for (std::size_t t {0}; t<thetaSize; t++) {
            rho = static_cast<std::size_t>(getRhoLine(x, y, t) + r_max);
            acc[rho][t]++;
        }
    }
    write(acc);
}

void HoughTransformer::write(std::vector<std::vector<int>> acc)
{
    write accumulator to file
    std::ofstream file;
    file.open("hough.csv");

    for each row in acc, write every value to file
    for (std::vector<int> v : acc) {
        for (int i{0}; i<v.size(); i++) {
            file << v[i];
            in order to be read be numpy, commas should separate values,
            but not appear at the end of a line
            if (i < v.size()-1)
                file << ",";
            }
        file << "\n";
    }
}

int HoughTransformer::getRhoLine(std::size_t x, std::size_t y,
                                 std::size_t theta)
{
    double rho = x * cosLT[theta] + y * sinLT[theta];
    return round(rho);
}

void HoughTransformer::quantize(double maximum, std::size_t steps)
{
    // quanization factor
    double q_factor {steps/maximum};

    // populate y_values vector
    for (std::size_t i {0}; i<steps; i++) {
        std::size_t q {size_round(inputSignal[i]*q_factor)};
        y_values.push_back(q);
    }
}

void HoughTransformer::edges()
{
    // fill x_values and y_values with coordinates of valid data in input
}

std::size_t HoughTransformer::size_round(double value)
{
    return static_cast<std::size_t>(round(value));
}

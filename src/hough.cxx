#include <cmath>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <utility>
#include <string>

#include <iostream>

#include "hough.h"

HoughTransformer::HoughTransformer(const double thetaStep,
                                   const double thetaStart,
                                   const double thetaStop,
                                   const bool endpoint)
: thetaSize {static_cast<std::size_t>(round((thetaStop-thetaStart)/thetaStep))}
, q_factor {1.}
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
                                 const std::size_t q_steps)
{
    // set quantization factor for this data
    set_q_factor(inputSignal, x_size, q_steps);
    // make accumulator for this data
    std::size_t r_max {make_accumulator(x_size, q_steps)};

    int rho; // for getRhoLine return value
    std::size_t rho_idx; // value to index accumulator

    for (std::size_t x {0}; x<x_size; x++) {
        // quantize y value
        std::size_t y = quantize(inputSignal[x]);
        for (std::size_t t{0}; t<thetaSize; t++) {
            rho = getRhoLine(x, y, t);
            rho_idx = static_cast<std::size_t>(rho + r_max);
            acc[t][rho_idx]++;
        }
    }
}

void HoughTransformer::write(const std::string ofile)
{
    // write accumulator to file
    std::ofstream file;
    file.open(ofile);

    // for each row in acc, write every value to file
    for (std::vector<int> v : acc) {
        for (std::size_t i{0}; i<v.size(); i++) {
            file << v[i];
            // in order to be read be numpy, commas should separate values,
            // but not appear at the end of a line
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

void HoughTransformer::set_q_factor(const double* inputSignal,
                                    const std::size_t x_size,
                                    const std::size_t q_steps)
{
    // find largest number in input
    double sig_max {0};
    for (std::size_t i {0}; i<x_size; i++) {
        double value = std::abs(inputSignal[i]);
        if (value > sig_max)
            sig_max = value;
    }
    // set quantisation factor
    q_factor = static_cast<double>(q_steps/sig_max);
}

std::size_t HoughTransformer::make_accumulator(const std::size_t x_size,
                                               const std::size_t q_steps)
{
    std::size_t r_max {size_round(sqrt(pow(x_size,2) + pow(q_steps,2)))};

    // accumulator width
    std::size_t acc_width {2*r_max};

    // reserve all the space we need for the accumulator
    // access elements: acc[theta][rho]
    acc.resize(thetaSize);
    for (std::size_t i {0}; i<acc.size(); i++)
        acc[i].resize(acc_width);

    // std::cout << "Accumulator size: " << thetaSize << " x " << acc_width << "\n";
    std::cout << "Made accumulator of size: " << acc.size() << " x ";
    std::cout << acc[0].size() << "\n";

    return r_max;
}

std::size_t HoughTransformer::quantize(const double value)
{
    return size_round(value*q_factor);
}

std::pair<double, double> HoughTransformer::unquantize(const double theta,
                                                       const double rho)
{
    // calculate original y-intercept and gradient
    double c0 {rho / (q_factor*sin(theta))};
    double m0 {1. / (q_factor*tan(theta))};
    // therefore, get original theta and rho
    double theta0 {atan(1./m0)};
    double rho0 {c0 * sin(theta0)};

    // return theta and rho as a tuple
    std::pair<double, double> result {std::make_pair(theta0, rho0)};
    return result;
}

std::size_t HoughTransformer::size_round(double value)
{
    return static_cast<std::size_t>(round(value));
}

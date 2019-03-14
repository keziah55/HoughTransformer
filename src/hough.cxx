#include <cmath>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <utility>

#include <iostream>

#include "hough.h"

HoughTransformer::HoughTransformer(const double thetaStep,
                                   const double thetaStart,
                                   const double thetaStop,
                                   const bool endpoint)
: thetaSize {static_cast<std::size_t>(round((thetaStop-thetaStart)/thetaStep))}
, q_steps {1000}
, q_factor {1.}
, quantized {false}
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
                                 const double sig_max)
{
    // set quantisation factor (with default q_steps=1000)
    set_q_factor(sig_max);
    quantized = true;

    // TODO put make accumulator in separate function, so it can be changed
    // according to q_steps

    std::size_t r_max {size_round(sqrt(pow(x_size,2) + pow(q_steps,2)))};

    // accumulator width
    std::size_t acc_width {2*r_max};

    // reserve all the space we need for the accumulator
    // access elements: acc[theta][rho]
    acc.resize(thetaSize);
    for (std::size_t i {0}; i<acc.size(); i++)
        acc[i].resize(acc_width);

    std::cout << "Accumulator size: " << thetaSize << " x " << acc_width << "\n";
    std::cout << "Accumulator size: " << acc.size() << " x " << acc[0].size() << "\n";

    int rho;

    for (std::size_t x {0}; x<x_size; x++) {
        // quantize y value
        std::size_t y = quantize(inputSignal[x]);
        for (std::size_t t{0}; t<thetaSize; t++) {
            rho = static_cast<std::size_t>(getRhoLine(x, y, t) + r_max);
            acc[t][rho]++;
        }
    }
    write();
}

void HoughTransformer::write()
{
    // write accumulator to file
    std::ofstream file;
    file.open("hough.csv");

    // for each row in acc, write every value to file
    for (std::vector<int> v : acc) {
        for (int i{0}; i<v.size(); i++) {
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

void HoughTransformer::set_q_steps(const std::size_t steps)
{
    q_steps = steps;
}

void HoughTransformer::set_q_factor(const double maximum)
{
    q_factor = q_steps/maximum;
}

std::size_t HoughTransformer::quantize(const double value)
{
    return size_round(value*q_factor);
}

std::pair<double, double> HoughTransformer::unquantize(const double theta,
                                                       const double rho,
                                                       const double q)
{
    // calculate original y-intercept and gradient
    double c0 {rho / (q*sin(theta))};
    double m0 {1. / (q*tan(theta))};
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

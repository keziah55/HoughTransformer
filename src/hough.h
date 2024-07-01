#ifndef _HOUGH_H_
#define _HOUGH_H_

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
#include <cmath>
#include <vector>
#include <utility>
#include <string>

typedef std::vector<std::pair<double, double>>  theta_rho_t;

class HoughTransformer {
public:
    /*! Make a HoughTransformer
     *  \param thetaStep Size of angle to step through (radians). Default is
     *  pi/180 (i.e. 1 degree).
     *  \param thetaStart Angle at which to start. Default is zero.
     *  \param thetaStop Angle at which to end. Default is pi.
     *  \param endpoint If true, thetaStop will be included. If false, angles
     *   will go up to, but not include, thetaStop. Default is false.
     */
    HoughTransformer(const double thetaStep=M_PI/180.,
                     const double thetaStart=0.,
                     const double thetaStop=M_PI, const bool endpoint=false);

    /*! Get the Hough transform of a signal
     *  \param inputSignal Input array
     *  \param x_size Array length
     *  \param q_steps Number of quantization steps. Default is 1000.
     */
    void transform(const double* inputSignal, const std::size_t x_size,
                   const std::size_t q_steps=1000);

    ~HoughTransformer();

    /*! Get correct theta and rho values by reversing quantization process */
    std::pair<double, double> unquantize(const double theta, const double rho);

    /*! Write accumulator to csv file */
    void write(const std::string ofile);

protected:
    /*! Number of angle in look-up tables */
    std::size_t thetaSize;
    /*! Sine look-up table */
    std::vector<double> sinLT;
    /*! Cosine look-up table */
    std::vector<double> cosLT;
    /*! Accumulator */
    std::vector<std::vector<int>> acc;
    /*! Quantization factor */
    double q_factor;
    /*! Calculate rho from equation of straight line */
    int getRhoLine(std::size_t x, std::size_t y, std::size_t theta);
    /*! Set quantization factor */
    void set_q_factor(const double* inputSignal,
                      const std::size_t x_size,
                      const std::size_t q_steps);
    /*! Make accumulator and return r_max */
    std::size_t make_accumulator(const std::size_t x_size,
                                 const std::size_t q_steps);
    /*! Using q_factor, get quantized value */
    std::size_t quantize(const double value);
    /*! Round a double to a size_t */
    std::size_t size_round(double value);
};

#endif

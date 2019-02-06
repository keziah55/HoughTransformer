#ifndef _HOUGH_H_
#define _HOUGH_H_

#include <cmath>

class HoughTransformer {
public:
    /*! Make a HoughTransformer
    *   \param thetaStep Size of angle to step through (radians). Default is
    *   pi/180 (i.e. 1 degree).
    *   \param thetaStart Angle at which to start. Default is zero.
    *   \param thetaStop Angle at which to end. Default is pi.
    *   \param endpoint If true, thetaStop will be included. If false, angles
    *    will go up to, but not include, thetaStop. Default is false.
    */
    HoughTransformer(const double thetaStep=M_PI/180.,
                     const double thetaStart=0.,
                     const double thetaStop=M_PI, const bool endpoint=false);

    /*! Get the Hough transform of a signal
    *   \param inputSignal Input array
    *   \param x_size Array length
    *   \param y_size Array height. Default is 1.
    */
    void transform(double* inputSignal, const std::size_t x_size,
                   const std::size_t y_size=1);

    ~HoughTransformer();

protected:
    /*! Number of angle in look-up tables */
    std::size_t thetaSize;
    /*! Sine look-up table */
    double* sinLT;
    /*! Cosine look-up table */
    double* cosLT;
    /*! Array of x values */
    std::size_t* x_values;
    /*! Array of y values */
    std::size_t* y_values;
    /*! Calculate rho from equation of straight line */
    int getRhoLine(std::size_t x, std::size_t y, std::size_t theta);
    /*! Quantize values */
    void quantize(std::size_t max, std::size_t steps); // take input and fill y values
    /*! High pass filter (edge detector) */
    void edges();
}

#endif

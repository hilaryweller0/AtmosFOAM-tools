/*
Creates a scalar field which is a cosine in each Cartesian direction. Intended
to force specific Fourier modes of a problem to become excited. Returns:

    f(x,y,z) = mag * (a_x + b_x*cos(2pi*k_x*x/L_x - phi_x))
                   * (a_y + b_y*cos(2pi*k_y*y/L_y - phi_y))
                   * (a_z + b_z*cos(2pi*k_z*z/L_z - phi_z))
*/

#ifndef SINUSOIDAL_3D_TRACER_FIELD_H
#define SINUSOIDAL_3D_TRACER_FIELD_H

#include "advectable.H"
#include "tracerField.H"

class sinusoidalTracerField final : public tracerField
{
    public:
    TypeName("sinusoidal");
    sinusoidalTracerField(const dictionary& dict, const advectable& velocityField);

    private:
    scalar tracerAt(const point& p, const Time& t) const;
    // The coeffiecients for different terms
    const scalar mag, 
                 a_x, a_y, a_z,
                 b_x, b_y, b_z,
                 k_x, k_y, k_z,
                 L_x, L_y, L_z,
                 phi_x, phi_y, phi_z;
    // The maximum and minimum possible values of the function
    const scalar funcMax, funcMin;
};

#endif



#include "fitCoefficients.H"

Foam::fitCoefficients::fitCoefficients
(
    const fitCoefficients& c
)
:
    coefficients(0),
    linearCorrection(c.linearCorrection),
    wLin(c.wLin)
{
    coefficients.append(c.coefficients);
}

Foam::fitCoefficients::fitCoefficients
(
    const label stencilSize,
    const bool linearCorrection,
    const scalar wLin
)
:
    coefficients(stencilSize, scalar(0)),
    linearCorrection(linearCorrection),
    wLin(wLin)
{}

void Foam::fitCoefficients::copyFrom(const scalarList& source)
{
    forAll(source, i)
    {
        coefficients[i] = source[i];
    }
}

void Foam::fitCoefficients::copyInto(scalarList& target)
{
    target.append(coefficients);
}

scalar& Foam::fitCoefficients::operator[](int i)
{
    return coefficients[i];
}

scalar Foam::fitCoefficients::operator[](int i) const
{
    return coefficients[i];
}

label Foam::fitCoefficients::size() const
{
    return coefficients.size();
}

void Foam::fitCoefficients::applyCorrection(const bool goodFit)
{
    if (goodFit)
    {
        if (linearCorrection)
        {
            // Remove the uncorrected linear coefficients
            coefficients[0] -= wLin;
            coefficients[1] -= 1 - wLin;
        }
        else
        {
            // Remove the uncorrected upwind coefficients
            coefficients[0] -= 1.0;
        }
    }
    else
    {
        coefficients = 0;
        
        if (linearCorrection)
        {
            coefficients[0] = 1-wLin;
            coefficients[1] = -(1-wLin);
        }
    }
}

Foam::Ostream& Foam::operator<<
(
    Ostream& stream,
    const fitCoefficients& c
)
{
    stream << c.coefficients;
    return stream;
}

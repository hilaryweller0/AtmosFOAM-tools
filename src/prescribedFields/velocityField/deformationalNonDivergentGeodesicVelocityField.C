#include "deformationalNonDivergentGeodesicVelocityField.H"
#include "addToRunTimeSelectionTable.H"

#include "polarPoint.H"

defineTypeNameAndDebug(deformationalNonDivergentGeodesicVelocityField, 0);
addToRunTimeSelectionTable
(
    velocityField,
    deformationalNonDivergentGeodesicVelocityField,
    dict
);

deformationalNonDivergentGeodesicVelocityField::
deformationalNonDivergentGeodesicVelocityField(const dictionary& dict)
:
    radius("radius", dimLength, readScalar(dict.lookup("radius"))),
    deformationScale(readScalar(dict.lookup("deformationScale"))),
    endTime(dict.lookup("endTime"))
{};

vector deformationalNonDivergentGeodesicVelocityField::streamfunctionAt
(
        const point& p,
        const Time& t
) const
{
    const dimensionedScalar& T = endTime;

    const polarPoint& polarp = convertToPolar(p);
    const scalar lat = polarp.lat();
    const scalar lon = polarp.lon();

    // section 2.3 doi:10.5194/gmd-5-887-2012
    const dimensionedScalar lonPrime = lon - 2 * M_PI * t / T;

    const dimensionedScalar psi = deformationScale * radius / T * 
            sqr(Foam::sin(lonPrime)) * sqr(Foam::cos(lat)) * Foam::cos(M_PI*t/T)
          - 2*M_PI*radius/T * Foam::sin(lat);
    return p/mag(p) * psi.value() * radius.value();
}

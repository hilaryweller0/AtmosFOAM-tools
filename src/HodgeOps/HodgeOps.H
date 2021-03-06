/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2013 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::HodgeOps

Description
    Non-orthogoanl H operators for transforming from d direction (cell centre
    to cell centre) to flux

SourceFiles
    HodgeOpsI.H
    HodgeOps.C

\*---------------------------------------------------------------------------*/

#ifndef HodgeOps_H
#define HodgeOps_H

#include "fvc.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                         Class HodgeOps Declaration
\*---------------------------------------------------------------------------*/

class HodgeOps
{
    // Private data

        //- Reference to the mesh
        const fvMesh& mesh_;

        //- cell centre to cell centre vector
        const surfaceVectorField delta_;
        
        //- cell centre to cell centre distance
        const surfaceScalarField magd_;

        //- Diagonal component of H operator (Sf() & delta/sqr(magd))
        const surfaceScalarField Hdiag_;

    // Private Member Functions

        //- Disallow default bitwise copy construct
        HodgeOps(const HodgeOps&);

        //- Disallow default bitwise assignment
        void operator=(const HodgeOps&);


public:

    // Constructors

        //- Construct from mesh
        HodgeOps(const fvMesh& mesh__);


    // Member Functions

        // Access
        
            //- Reference to the mesh
            const fvMesh& mesh() const { return mesh_; }

            //- cell centre to cell centre vector
            const surfaceVectorField& delta() const { return delta_;}
            
            //- cell centre to cell centre distance
            const surfaceScalarField& magd() const { return magd_;}
     
            //- Diagonal component of H operator
            const surfaceScalarField& Hdiag() const { return Hdiag_;}


         // Non-orthogonal corrections

            //- Make the boundary faces orthogonal (done on construction)
            const fvMesh&  orthogonalBoundaries(const fvMesh& mesh);

            //- transform from a field integrated along d to a flux
            inline tmp<surfaceScalarField> ddirToFlux
            (
                const surfaceScalarField& V
            ) const;
            
            //- off diagonal component of transformation from a field
            //- integrated along d to a flux
            inline tmp<surfaceScalarField> ddirToFluxOffDiag
            (
                const surfaceScalarField& V
            ) const;
            
            //- correction terms of H
            inline tmp<surfaceScalarField> ddirToFluxCorr
            (
                const surfaceScalarField& V
            ) const;
            
            inline tmp<volVectorField> reconstructd
            (
                const surfaceScalarField& V
            ) const;
            
            //- cell centre reconstruction from fluxes
            inline tmp<volVectorField> reconstruct
            (
                const surfaceScalarField& phi
            ) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "HodgeOpsI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //

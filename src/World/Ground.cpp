/*
   This file is part of The Lost Souls Downfall prototype.

    The Lost Souls Downfall prototype is free software: you can
    redistribute it and/or modify it under the terms of the GNU
    General Public License as published by the Free Software
    Foundation, either version 3 of the License, or (at your option)
    any later version.

    The Lost Souls Downfall prototype is distributed in the hope that
    it will be useful, but WITHOUT ANY WARRANTY; without even the
    implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
    PURPOSE.  See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with The Lost Souls Downfall prototype.  If not, see
    <http://www.gnu.org/licenses/>.
*/

#include <math.h>

#include "Ground.h"
#include "../Geometry/Vec3D.h"
#include "../Graphics/Render/Face.h"
#include "../Graphics/Render/Model3D.h"
#include "../Graphics/Color.h"
#include "Chunk.h"

namespace World
{

    Graphics::Render::Model3D computeGroundModel(World& world, int x, int y)
    {
        float chunkSize = World::ChunkSize;

        Chunk chunk;
        if (!world.getChunk(x, y, chunk))
        {
            throw NotGeneratedChunkException();
        }

        if (chunk.getState() != Chunk::GeneratedState)
        {
            throw NotGeneratedChunkException();
        }
        // Creating the heightmap of the ground
        float period = 1.0/Resolution;
        float groundTable[static_cast<int>(chunkSize*period)+1][static_cast<int>(chunkSize*period)+1];

        for (float i = 0; i<=chunkSize; i += Resolution)
        {
            for (float j = 0; j<=chunkSize; j += Resolution)
            {
                groundTable[static_cast<int>(i*period)][static_cast<int>(j*period)] = computeHeight(world, x*chunkSize+i, y*chunkSize+j);
            }
        }
        int baseIndex = 0;

        std::vector<Geometry::Vec3Df> vertices;
        std::vector<Graphics::Render::Face> faces;
        // Creating the 3D model from the heightmap
        for (float i = 0; i<chunkSize*period; i++)
        {
            for (float j = 0; j<chunkSize*period; j++)
            {
                vertices.push_back(Geometry::Vec3Df(i/period,j/period,groundTable[static_cast<int>(i)][static_cast<int>(j)]));
                vertices.push_back(Geometry::Vec3Df((i+1)/period,j/period,groundTable[static_cast<int>(i+1)][static_cast<int>(j)]));
                vertices.push_back(Geometry::Vec3Df(i/period,(j+1)/period,groundTable[static_cast<int>(i)][static_cast<int>(j+1)]));
                vertices.push_back(Geometry::Vec3Df((i+1)/period,(j+1)/period,groundTable[static_cast<int>(i+1)][static_cast<int>(j+1)]));
                Graphics::Color color = world.getBiome(x*chunkSize+i/period,y*chunkSize+j/period).getColor();
                faces.push_back(Graphics::Render::Face(baseIndex, baseIndex+2, baseIndex+1, color));
                color = world.getBiome(x*chunkSize+(i+1)/period,y*chunkSize+(j+1)/period).getColor();
                faces.push_back(Graphics::Render::Face(baseIndex+3, baseIndex+1, baseIndex+2, color));

                baseIndex +=4;

            }
        }

        return Graphics::Render::Model3D(vertices, faces);

    }

    float computeEllipse(float x, float y, float squareChunk)
    {
        return 1 - (x + y) * (x + y) * 2.0 / (2.0 * 3.0 * squareChunk) - (x - y) * (x - y) * 2.0 / (2.0 * squareChunk);
    }


    float computeHeight(World& world, float x, float y)
    {
        float chunkSize = World::ChunkSize;

        int i0 = floor(x/chunkSize);
        int j0 = floor(y/chunkSize);

        Chunk actualChunk;
        if (!world.getChunk(i0,j0,actualChunk))
        {
            throw NotGeneratedChunkException();
        }
        if (i0!=x/chunkSize && j0!=y/chunkSize && actualChunk.getState() != Chunk::GeneratedState)
        {
            throw NotGeneratedChunkException();
        }

        const GroundCoefficients& actualChunkGroundCoefficients = actualChunk.getCoefficients();

        float xChunk = x-static_cast<float>(i0)*chunkSize;
        float yChunk = y-static_cast<float>(j0)*chunkSize;

        float i1, j1;
        if (xChunk>yChunk)
        {
            i1 = 1;
            j1 = 0;
        }
        else
        {
            i1 = 0;
            j1 = 1;
        }

        float x1 = xChunk-i1*chunkSize;
        float y1 = yChunk-j1*chunkSize;
        float x2 = xChunk-chunkSize;
        float y2 = yChunk-chunkSize;
        float squareChunk = powf(chunkSize, 2);

        float ellipse0 = computeEllipse(xChunk, yChunk, squareChunk);
        float ellipse1 = computeEllipse(x1, y1, squareChunk);
        float ellipse2 = computeEllipse(x2, y2, squareChunk);
        float n0,n1,n2;

        Chunk sideChunk, diagonalChunk;

        if (ellipse0 <= 0)
        {
            n0 = 0;
        }
        else
        {
            n0 = powf(ellipse0,4)*world.getBiome(i0*chunkSize,j0*chunkSize).transformCoefficient(actualChunkGroundCoefficients.getCoefficient(1,0,0));
        }
        if (ellipse1 <= 0)
        {
            n1 = 0;
        }
        else
        {
            if (!world.getChunk(i0+i1,j0+j1,sideChunk))
            {
                throw NotPreparatedChunkException();
            }
            n1 = powf(ellipse1,4)*world.getBiome((i0+i1)*chunkSize,(j0+j1)*chunkSize).transformCoefficient(sideChunk.getCoefficients().getCoefficient(1,0,0));
        }
        if (ellipse2 <= 0)
        {
            n2 = 0;
        }
        else
        {
            if (!world.getChunk(i0+1,j0+1,diagonalChunk))
            {
                throw NotPreparatedChunkException();
            }
            n2 = powf(ellipse2,4)*world.getBiome((i0+1)*chunkSize,(j0+1)*chunkSize).transformCoefficient(diagonalChunk.getCoefficients().getCoefficient(1,0,0));
        }

        float firstOctaveContribution = n0 + n1 + n2;





        // Computing the second octave contribution
        chunkSize = chunkSize/2;

        int i = floor(xChunk/chunkSize);
        int j = floor(yChunk/chunkSize);

        float x0 = xChunk-static_cast<float>(i)*chunkSize;
        float y0 = yChunk-static_cast<float>(j)*chunkSize;

        float i2, j2;
        if (x0>y0)
        {
            i2 = 1;
            j2 = 0;
        }
        else
        {
            i2 = 0;
            j2 = 1;
        }

        x1 = x0-i2*chunkSize;
        y1 = y0-j2*chunkSize;
        x2 = x0-chunkSize;
        y2 = y0-chunkSize;
        squareChunk = powf(chunkSize, 2);

        ellipse0 = computeEllipse(x0, y0, squareChunk);
        ellipse1 = computeEllipse(x1, y1, squareChunk);
        ellipse2 = computeEllipse(x2, y2, squareChunk);


        if (ellipse0 <= 0)
        {
            n0 = 0;
        }
        else
        {
            n0 = powf(ellipse0,4)*world.getBiome(floor(x/chunkSize)*chunkSize,floor(y/chunkSize)*chunkSize).transformCoefficient(actualChunkGroundCoefficients.getCoefficient(2,i,j));
        }

        if (ellipse2 <= 0)
        {
            n2 = 0;
        }
        else
        {
            BiomeInterface& diagonalBiome = world.getBiome((floor(x/chunkSize)+1)*chunkSize,(floor(y/chunkSize)+1)*chunkSize);
            if (j==1 && i==0)
            {
                if (!world.getChunk(i0+i1,j0+j1,sideChunk))
                {
                 throw NotPreparatedChunkException();
                }
                n2 = powf(ellipse2,4)*diagonalBiome.transformCoefficient(sideChunk.getCoefficients().getCoefficient(2,1,0));
            }
            else if (i==1 && j==1)
            {
                if (!world.getChunk(i0+1,j0+1,diagonalChunk))
                {
                    throw NotPreparatedChunkException();
                }
                n2 = powf(ellipse2,4)*diagonalBiome.transformCoefficient(diagonalChunk.getCoefficients().getCoefficient(2,0,0));
            }
            else if (i==1 && j==0)
            {
                if (!world.getChunk(i0+i1,j0+j1,sideChunk))
                {
                 throw NotPreparatedChunkException();
                }
                n2 = powf(ellipse2,4)*diagonalBiome.transformCoefficient(sideChunk.getCoefficients().getCoefficient(2,0,1));
            }
            else
            {
                n2 = powf(ellipse2,4)*diagonalBiome.transformCoefficient(actualChunkGroundCoefficients.getCoefficient(2,i+1,j+1));
            }
        }

        if (ellipse1 <= 0)
        {
            n1 = 0;
        }
        else
        {
            BiomeInterface& sideBiome = world.getBiome((floor(x/chunkSize)+i2)*chunkSize,(floor(y/chunkSize)+j2)*chunkSize);
            if (i==0 && j==0)
            {
                n1 = powf(ellipse1,4)*sideBiome.transformCoefficient(actualChunkGroundCoefficients.getCoefficient(2,i2,j2));
            }
            else if (i==0 && j==1)
            {
                if (i2==0)
                {
                    if (!world.getChunk(i0+i1,j0+j1,sideChunk))
                    {
                     throw NotPreparatedChunkException();
                    }
                    n1 = powf(ellipse1,4)*sideBiome.transformCoefficient(sideChunk.getCoefficients().getCoefficient(2,0,0));
                }
                else
                {
                    n1 = powf(ellipse1,4)*sideBiome.transformCoefficient(actualChunkGroundCoefficients.getCoefficient(2,1,1));
                }
            }
            else if (i==1 && j==0)
            {
                if (i2==0)
                {
                    n1 = powf(ellipse1,4)*sideBiome.transformCoefficient(actualChunkGroundCoefficients.getCoefficient(2,1,1));
                }
                else
                {
                    if (!world.getChunk(i0+i1,j0+j1,sideChunk))
                    {
                     throw NotPreparatedChunkException();
                    }
                    n1 = powf(ellipse1,4)*sideBiome.transformCoefficient(sideChunk.getCoefficients().getCoefficient(2,0,0));
                }
            }
            else
            {
                if (!world.getChunk(i0+i1,j0+j1,sideChunk))
                {
                 throw NotPreparatedChunkException();
                }
                if (i2==0)
                {
                    n1 = powf(ellipse1,4)*sideBiome.transformCoefficient(sideChunk.getCoefficients().getCoefficient(2,1,0));
                }
                else
                {
                    n1 = powf(ellipse1,4)*sideBiome.transformCoefficient(sideChunk.getCoefficients().getCoefficient(2,0,1));
                }
            }
        }

        float secondOctaveContribution = n0 + n1 + n2;





        // Computing the third octave contribution
        chunkSize = chunkSize/2;

        i = floor(xChunk/chunkSize);
        j = floor(yChunk/chunkSize);

        x0 = xChunk-static_cast<float>(i)*chunkSize;
        y0 = yChunk-static_cast<float>(j)*chunkSize;

        if (x0>y0)
        {
            i2 = 1;
            j2 = 0;
        }
        else
        {
            i2 = 0;
            j2 = 1;
        }

        x1 = x0-i2*chunkSize;
        y1 = y0-j2*chunkSize;
        x2 = x0-chunkSize;
        y2 = y0-chunkSize;
        squareChunk = powf(chunkSize, 2);

        ellipse0 = computeEllipse(x0,y0,squareChunk);
        ellipse1 = computeEllipse(x1,y1,squareChunk);
        ellipse2 = computeEllipse(x2,y2,squareChunk);


        if (ellipse0 <= 0)
        {
            n0 = 0;
        }
        else
        {
            n0 = powf(ellipse0,4)*world.getBiome(floor(x/chunkSize)*chunkSize,floor(y/chunkSize)*chunkSize).transformCoefficient(actualChunkGroundCoefficients.getCoefficient(3,i,j));
        }

        if (ellipse2 <= 0)
        {
            n2 = 0;
        }
        else
        {
            BiomeInterface& diagonalBiome = world.getBiome((floor(x/chunkSize)+1)*chunkSize,(floor(y/chunkSize)+1)*chunkSize);
            if (j==3 && i<3)
            {
                if (!world.getChunk(i0+i1,j0+j1,sideChunk))
                {
                 throw NotPreparatedChunkException();
                }
                n2 = powf(ellipse2,4)*diagonalBiome.transformCoefficient(sideChunk.getCoefficients().getCoefficient(3,i+1,0));
            }
            else if (i==3 && j<3)
            {
                if (!world.getChunk(i0+i1,j0+j1,sideChunk))
                {
                 throw NotPreparatedChunkException();
                }
                n2 = powf(ellipse2,4)*diagonalBiome.transformCoefficient(sideChunk.getCoefficients().getCoefficient(3,0,j+1));
            }
            else if (i==3 && j==3)
            {
                if (!world.getChunk(i0+1,j0+1,diagonalChunk))
                {
                    throw NotPreparatedChunkException();
                }
                n2 = powf(ellipse2,4)*diagonalBiome.transformCoefficient(diagonalChunk.getCoefficients().getCoefficient(3,0,0));
            }
            else
            {
                n2 = powf(ellipse2,4)*diagonalBiome.transformCoefficient(actualChunkGroundCoefficients.getCoefficient(3,i+1,j+1));
            }
        }

        if (ellipse1 <= 0)
        {
            n1 = 0;
        }
        else
        {
            BiomeInterface& sideBiome = world.getBiome((floor(x/chunkSize)+i2)*chunkSize,(floor(y/chunkSize)+j2)*chunkSize);
            if (j==3 && i<3)
            {
                if (i2==0)
                {
                    if (!world.getChunk(i0+i1,j0+j1,sideChunk))
                    {
                     throw NotPreparatedChunkException();
                    }
                    n1 = powf(ellipse1,4)*sideBiome.transformCoefficient(sideChunk.getCoefficients().getCoefficient(3,i,0));
                }
                else
                {
                    n1 = powf(ellipse1,4)*sideBiome.transformCoefficient(actualChunkGroundCoefficients.getCoefficient(3,i+1,3));
                }
            }
            else if (i==3 && j<3)
            {
                if (i2==0)
                {
                    n1 = powf(ellipse1,4)*sideBiome.transformCoefficient(actualChunkGroundCoefficients.getCoefficient(3,3,j+1));
                }
                else
                {
                    if (!world.getChunk(i0+i1,j0+j1,sideChunk))
                    {
                     throw NotPreparatedChunkException();
                    }
                    n1 = powf(ellipse1,4)*sideBiome.transformCoefficient(sideChunk.getCoefficients().getCoefficient(3,0,j));
                }
            }
            else if (i==3 && j==3)
            {
                if (i2==0)
                {
                    if (!world.getChunk(i0+i1,j0+j1,sideChunk))
                    {
                     throw NotPreparatedChunkException();
                    }
                    n1 = powf(ellipse1,4)*sideBiome.transformCoefficient(sideChunk.getCoefficients().getCoefficient(3,3,0));
                }
                else
                {
                    if (!world.getChunk(i0+i1,j0+j1,sideChunk))
                    {
                     throw NotPreparatedChunkException();
                    }
                    n1 = powf(ellipse1,4)*sideBiome.transformCoefficient(sideChunk.getCoefficients().getCoefficient(3,0,3));
                }
            }
            else
            {
                n1 = powf(ellipse1,4)*sideBiome.transformCoefficient(actualChunkGroundCoefficients.getCoefficient(3,i+i2,j+j2));
            }
        }

        float thirdOctaveContribution = n0 + n1 + n2;



        return firstOctaveContribution + 1.0/2.0*secondOctaveContribution + 1.0/4.0*thirdOctaveContribution;

    }
}

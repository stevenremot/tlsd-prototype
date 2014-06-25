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

    void computeGroundModel(
        World& world,
        int x,
        int y,
        Graphics::Render::Model3D& model,
        Physics::GroundCollisionBody& collBody
    )
    {
        float chunkSize = World::ChunkSize;
        float maxHeight = World::MaximalHeight;

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
        float period = 1.0 / Resolution;


        int size = static_cast<int>(chunkSize * period) + 1;
        Physics::Heightmap groundTable;
        for (int i = 0; i < size; i++)
        {
            groundTable.push_back(std::vector<float>(size));
        }

        for (float i = 0; i<=chunkSize; i += Resolution)
        {
            for (float j = 0; j<=chunkSize; j += Resolution)
            {
                groundTable[static_cast<int>(i * period)][static_cast<int>(j * period)] = computeHeight(world, x * chunkSize + i, y * chunkSize + j);
            }
        }

        collBody.setChunkSize(chunkSize);
        collBody.setResolution(Resolution);
        collBody.setHeightmap(groundTable);

        // Creating the 3D model from the heightmap
        int baseIndex = 0;
        std::vector<Geometry::Vec3Df> vertices;
        std::vector<Graphics::Render::Face> faces;
        float chunkX = static_cast<float>(x) * chunkSize;
        float chunkY = static_cast<float>(y) * chunkSize;

        for (float i = 0; i<chunkSize*period; i++)
        {
            for (float j = 0; j<chunkSize*period; j++)
            {
                float ground00 = groundTable[static_cast<int>(i)][static_cast<int>(j)];
                float ground10 = groundTable[static_cast<int>(i + 1)][static_cast<int>(j)];
                float ground01 = groundTable[static_cast<int>(i)][static_cast<int>(j + 1)];
                float ground11 = groundTable[static_cast<int>(i + 1)][static_cast<int>(j + 1)];
                float x0 = i / period;
                float x1 = (i + 1) / period;
                float y0 = j / period;
                float y1 = (j + 1) / period;

                vertices.push_back(Geometry::Vec3Df(x0, y0, ground00));
                vertices.push_back(Geometry::Vec3Df(x1, y0, ground10));
                vertices.push_back(Geometry::Vec3Df(x0, y1, ground01));
                vertices.push_back(Geometry::Vec3Df(x1, y1, ground11));

                Graphics::Color color00 = (world.getBiome(chunkX + x0, chunkY + y0).getColor() + Geometry::Vec3Df(1, 1, 1) * ground00 * 1.0 / maxHeight) / 2;
                Graphics::Color color10 = (world.getBiome(chunkX + x1, chunkY + y0).getColor() + Geometry::Vec3Df(1, 1, 1) * ground10 * 1.0 / maxHeight) / 2;
                Graphics::Color color01 = (world.getBiome(chunkX + x0, chunkY + y1).getColor() + Geometry::Vec3Df(1, 1, 1) * ground01 * 1.0 / maxHeight) / 2;
                Graphics::Color color11 = (world.getBiome(chunkX + x1, chunkY + y1).getColor() + Geometry::Vec3Df(1, 1, 1) * ground11 * 1.0 / maxHeight) / 2;
                Graphics::Color color = (color00 + color10 + color01)/3.0;
                faces.push_back(
                    Graphics::Render::Face(
                        baseIndex,
                        baseIndex + 1,
                        baseIndex + 2,
                        color
                    )
                );
                color = (color11 + color10 + color01)/3.0;
                faces.push_back(
                    Graphics::Render::Face(
                        baseIndex + 3,
                        baseIndex + 2,
                        baseIndex + 1,
                        color
                    )
                );

                baseIndex += 4;

            }
        }
        model.setVertices(vertices);
        model.setFaces(faces);
    }

    float computeEllipse(float x, float y, float squareChunk)
    {
        return 1 - (x + y) * (x + y) * 2.0 / (2.0 * 3.0 * squareChunk) - (x - y) * (x - y) * 2.0 / (2.0 * squareChunk);
    }

    /**
     * @param[in] xChunk
     * @param[in] yChunk
     * @param[out] i
     * @param[out] j
     */
    void computeOffsets(float x, float y, float& i, float& j)
    {
        if (x > y)
        {
            i = 1;
            j = 0;
        }
        else
        {
            i = 0;
            j = 1;
        }
    }

    /**
     * @param[in] x
     * @param[in] y
     * @param[in] i
     * @param[in] j
     * @param[in] chunkSize
     * @param[out] x1
     * @param[out] y1
     * @param[out] x2
     * @param[out] y2
     */
    void computeInTriangleCoordinates(float x, float y, float i, float j, float chunkSize,
                                      float& x1, float& y1, float& x2, float& y2)
    {
        x1 = x - i*chunkSize;
        y1 = y - j*chunkSize;
        x2 = x - chunkSize;
        y2 = y - chunkSize;
    }

    float computeFirstOctaveContribution(World& world, float ellipse0, float ellipse1, float ellipse2,
                                         float i0, float j0, float i1, float j1, float chunkSize)
    {
        float n0,n1,n2;

        Chunk sideChunk, diagonalChunk;
        Chunk actualChunk;

        // Does not break because this have been checked before
        world.getChunk(i0, j0, actualChunk);

        if (ellipse0 <= 0)
        {
            n0 = 0;
        }
        else
        {
            n0 = powf(ellipse0, 4) * world.getBiome(i0 * chunkSize, j0 * chunkSize).transformCoefficient(actualChunk.getCoefficients().getCoefficient(1, 0, 0));
        }
        if (ellipse1 <= 0)
        {
            n1 = 0;
        }
        else
        {
            if (!world.getChunk(i0 + i1, j0 + j1, sideChunk))
            {
                throw NotPreparatedChunkException();
            }
            n1 = powf(ellipse1, 4) * world.getBiome((i0 + i1) * chunkSize, (j0 + j1) * chunkSize).transformCoefficient(sideChunk.getCoefficients().getCoefficient(1, 0, 0));
        }
        if (ellipse2 <= 0)
        {
            n2 = 0;
        }
        else
        {
            if (!world.getChunk(i0 + 1, j0 + 1, diagonalChunk))
            {
                throw NotPreparatedChunkException();
            }
            n2 = powf(ellipse2, 4) * world.getBiome((i0 + 1) * chunkSize, (j0 + 1) * chunkSize).transformCoefficient(diagonalChunk.getCoefficients().getCoefficient(1, 0, 0));
        }

        return n0 + n1 + n2;
    }

    float computeSecondOctaveContribution(World& world, float ellipse0, float ellipse1, float ellipse2,
                                          float i0, float j0, float i1, float j1,
                                          float i2, float j2, float i, float j,
                                          float x, float y, float chunkSize)
    {
        float n0, n1, n2;

        Chunk sideChunk, diagonalChunk;
        Chunk actualChunk;

        // Does not break because this have been checked before
        world.getChunk(i0, j0, actualChunk);

        if (ellipse0 <= 0)
        {
            n0 = 0;
        }
        else
        {
            n0 = powf(ellipse0, 4) * world.getBiome(floor(x / chunkSize) * chunkSize, floor(y / chunkSize) * chunkSize).transformCoefficient(actualChunk.getCoefficients().getCoefficient(2, i, j));
        }

        if (ellipse2 <= 0)
        {
            n2 = 0;
        }
        else
        {
            BiomeInterface& diagonalBiome = world.getBiome((floor(x / chunkSize) + 1) * chunkSize, (floor(y / chunkSize) + 1) * chunkSize);
            if (j == 1 && i == 0)
            {
                if (!world.getChunk(i0 + i1, j0 + j1, sideChunk))
                {
                    throw NotPreparatedChunkException();
                }
                n2 = powf(ellipse2, 4) * diagonalBiome.transformCoefficient(sideChunk.getCoefficients().getCoefficient(2, 1, 0));
            }
            else if (i == 1 && j == 1)
            {
                if (!world.getChunk(i0 + 1, j0 + 1,diagonalChunk))
                {
                    throw NotPreparatedChunkException();
                }
                n2 = powf(ellipse2, 4) * diagonalBiome.transformCoefficient(diagonalChunk.getCoefficients().getCoefficient(2, 0, 0));
            }
            else if (i == 1 && j == 0)
            {
                if (!world.getChunk(i0 + i1, j0 + j1, sideChunk))
                {
                    throw NotPreparatedChunkException();
                }
                n2 = powf(ellipse2, 4) * diagonalBiome.transformCoefficient(sideChunk.getCoefficients().getCoefficient(2, 0, 1));
            }
            else
            {
                n2 = powf(ellipse2, 4) * diagonalBiome.transformCoefficient(actualChunk.getCoefficients().getCoefficient(2, i + 1, j + 1));
            }
        }

        if (ellipse1 <= 0)
        {
            n1 = 0;
        }
        else
        {
            BiomeInterface& sideBiome = world.getBiome((floor(x / chunkSize) + i2) * chunkSize, (floor(y / chunkSize) + j2) * chunkSize);
            if (i == 0 && j == 0)
            {
                n1 = powf(ellipse1, 4) * sideBiome.transformCoefficient(actualChunk.getCoefficients().getCoefficient(2, i2, j2));
            }
            else if (i == 0 && j == 1)
            {
                if (i2 == 0)
                {
                    if (!world.getChunk(i0 + i1, j0 + j1, sideChunk))
                    {
                        throw NotPreparatedChunkException();
                    }
                    n1 = powf(ellipse1, 4) * sideBiome.transformCoefficient(sideChunk.getCoefficients().getCoefficient(2, 0, 0));
                }
                else
                {
                    n1 = powf(ellipse1, 4) * sideBiome.transformCoefficient(actualChunk.getCoefficients().getCoefficient(2, 1, 1));
                }
            }
            else if (i == 1 && j == 0)
            {
                if (i2 == 0)
                {
                    n1 = powf(ellipse1, 4) * sideBiome.transformCoefficient(actualChunk.getCoefficients().getCoefficient(2, 1, 1));
                }
                else
                {
                    if (!world.getChunk(i0 + i1, j0 + j1, sideChunk))
                    {
                        throw NotPreparatedChunkException();
                    }
                    n1 = powf(ellipse1, 4) * sideBiome.transformCoefficient(sideChunk.getCoefficients().getCoefficient(2, 0, 0));
                }
            }
            else
            {
                if (!world.getChunk(i0 + i1, j0 + j1, sideChunk))
                {
                    throw NotPreparatedChunkException();
                }
                if (i2 == 0)
                {
                    n1 = powf(ellipse1, 4) * sideBiome.transformCoefficient(sideChunk.getCoefficients().getCoefficient(2, 1, 0));
                }
                else
                {
                    n1 = powf(ellipse1, 4) * sideBiome.transformCoefficient(sideChunk.getCoefficients().getCoefficient(2, 0, 1));
                }
            }
        }

        return n0 + n1 + n2;
    }

    float computeThirdOctaveContribution(World& world, float ellipse0, float ellipse1, float ellipse2,
                                         float i0, float j0, float i1, float j1,
                                         float i2, float j2, float i, float j,
                                         float x, float y, float chunkSize)
    {
        float n0, n1, n2;

        Chunk sideChunk, diagonalChunk;
        Chunk actualChunk;

        // Does not break because this have been checked before
        world.getChunk(i0, j0, actualChunk);

        if (ellipse0 <= 0)
        {
            n0 = 0;
        }
        else
        {
            n0 = powf(ellipse0, 4) * world.getBiome(floor(x / chunkSize) * chunkSize, floor(y / chunkSize) * chunkSize).transformCoefficient(actualChunk.getCoefficients().getCoefficient(3, i, j));
        }

        if (ellipse2 <= 0)
        {
            n2 = 0;
        }
        else
        {
            BiomeInterface& diagonalBiome = world.getBiome((floor(x / chunkSize) + 1) * chunkSize, (floor(y / chunkSize) + 1) * chunkSize);
            if (j == 3 && i < 3)
            {
                if (!world.getChunk(i0 + i1, j0 + j1, sideChunk))
                {
                    throw NotPreparatedChunkException();
                }
                n2 = powf(ellipse2, 4) * diagonalBiome.transformCoefficient(sideChunk.getCoefficients().getCoefficient(3, i + 1, 0));
            }
            else if (i == 3 && j < 3)
            {
                if (!world.getChunk(i0 + i1, j0 + j1, sideChunk))
                {
                    throw NotPreparatedChunkException();
                }
                n2 = powf(ellipse2, 4) * diagonalBiome.transformCoefficient(sideChunk.getCoefficients().getCoefficient(3, 0, j + 1));
            }
            else if (i == 3 && j == 3)
            {
                if (!world.getChunk(i0 + 1, j0 + 1, diagonalChunk))
                {
                    throw NotPreparatedChunkException();
                }
                n2 = powf(ellipse2, 4) * diagonalBiome.transformCoefficient(diagonalChunk.getCoefficients().getCoefficient(3, 0, 0));
            }
            else
            {
                n2 = powf(ellipse2, 4) * diagonalBiome.transformCoefficient(actualChunk.getCoefficients().getCoefficient(3, i + 1, j + 1));
            }
        }

        if (ellipse1 <= 0)
        {
            n1 = 0;
        }
        else
        {
            BiomeInterface& sideBiome = world.getBiome((floor(x / chunkSize) + i2) * chunkSize, (floor(y / chunkSize) + j2) * chunkSize);
            if (j == 3 && i < 3)
            {
                if (i2 == 0)
                {
                    if (!world.getChunk(i0 + i1, j0 + j1, sideChunk))
                    {
                        throw NotPreparatedChunkException();
                    }
                    n1 = powf(ellipse1, 4) * sideBiome.transformCoefficient(sideChunk.getCoefficients().getCoefficient(3, i, 0));
                }
                else
                {
                    n1 = powf(ellipse1, 4) * sideBiome.transformCoefficient(actualChunk.getCoefficients().getCoefficient(3, i + 1, 3));
                }
            }
            else if (i == 3 && j < 3)
            {
                if (i2 == 0)
                {
                    n1 = powf(ellipse1, 4) * sideBiome.transformCoefficient(actualChunk.getCoefficients().getCoefficient(3, 3, j + 1));
                }
                else
                {
                    if (!world.getChunk(i0 + i1, j0 + j1, sideChunk))
                    {
                        throw NotPreparatedChunkException();
                    }
                    n1 = powf(ellipse1, 4) * sideBiome.transformCoefficient(sideChunk.getCoefficients().getCoefficient(3, 0, j));
                }
            }
            else if (i == 3 && j == 3)
            {
                if (i2 == 0)
                {
                    if (!world.getChunk(i0 + i1, j0 + j1, sideChunk))
                    {
                        throw NotPreparatedChunkException();
                    }
                    n1 = powf(ellipse1, 4) * sideBiome.transformCoefficient(sideChunk.getCoefficients().getCoefficient(3, 3, 0));
                }
                else
                {
                    if (!world.getChunk(i0 + i1, j0 + j1, sideChunk))
                    {
                        throw NotPreparatedChunkException();
                    }
                    n1 = powf(ellipse1, 4) * sideBiome.transformCoefficient(sideChunk.getCoefficients().getCoefficient(3, 0, 3));
                }
            }
            else
            {
                n1 = powf(ellipse1, 4) * sideBiome.transformCoefficient(actualChunk.getCoefficients().getCoefficient(3, i + i2, j + j2));
            }
        }

        return n0 + n1 + n2;
    }

    float computeHeight(World& world, float x, float y)
    {
        float chunkSize = World::ChunkSize;

        int i0 = floor(x / chunkSize);
        int j0 = floor(y / chunkSize);

        Chunk actualChunk;
        if (!world.getChunk(i0, j0, actualChunk))
        {
            throw NotGeneratedChunkException();
        }
        if (i0!=x/chunkSize && j0!=y/chunkSize && actualChunk.getState() != Chunk::GeneratedState)
        {
            throw NotGeneratedChunkException();
        }

        float xChunk = x - static_cast<float>(i0) * chunkSize;
        float yChunk = y - static_cast<float>(j0) * chunkSize;

        float i1, j1;
        computeOffsets(xChunk, yChunk, i1, j1);

        float x1, y1, x2, y2;
        computeInTriangleCoordinates(
            xChunk, yChunk, i1, j1, chunkSize,
            x1, y1, x2, y2
        );

        float squareChunk = powf(chunkSize, 2);

        float ellipse0 = computeEllipse(xChunk, yChunk, squareChunk);
        float ellipse1 = computeEllipse(x1, y1, squareChunk);
        float ellipse2 = computeEllipse(x2, y2, squareChunk);

        float firstOctaveContribution = computeFirstOctaveContribution(
                                            world, ellipse0, ellipse1, ellipse2,
                                            i0, j0, i1, j1, chunkSize
                                        );

        // Computing the second octave contribution
        chunkSize = chunkSize/2;

        int i = floor(xChunk / chunkSize);
        int j = floor(yChunk / chunkSize);

        float x0 = xChunk - static_cast<float>(i) * chunkSize;
        float y0 = yChunk - static_cast<float>(j) * chunkSize;

        float i2, j2;
        computeOffsets(x0, y0, i2, j2);

        computeInTriangleCoordinates(
            x0, y0, i2, j2, chunkSize,
            x1, y1, x2, y2
        );
        squareChunk = powf(chunkSize, 2);

        ellipse0 = computeEllipse(x0, y0, squareChunk);
        ellipse1 = computeEllipse(x1, y1, squareChunk);
        ellipse2 = computeEllipse(x2, y2, squareChunk);

        float secondOctaveContribution = computeSecondOctaveContribution(
                                             world, ellipse0, ellipse1, ellipse2,
                                             i0, j0, i1, j1,
                                             i2, j2, i, j,
                                             x, y, chunkSize
                                         );

        // Computing the third octave contribution
        chunkSize = chunkSize/2;

        i = floor(xChunk / chunkSize);
        j = floor(yChunk / chunkSize);

        x0 = xChunk - static_cast<float>(i) * chunkSize;
        y0 = yChunk - static_cast<float>(j) * chunkSize;

        computeOffsets(x0, y0, i2, j2);

        computeInTriangleCoordinates(
            x0, y0, i2, j2, chunkSize,
            x1, y1, x2, y2
        );
        squareChunk = powf(chunkSize, 2);

        ellipse0 = computeEllipse(x0, y0, squareChunk);
        ellipse1 = computeEllipse(x1, y1, squareChunk);
        ellipse2 = computeEllipse(x2, y2, squareChunk);

        float thirdOctaveContribution = computeThirdOctaveContribution(
                                            world, ellipse0, ellipse1, ellipse2,
                                            i0, j0, i1, j1,
                                            i2, j2, i, j,
                                            x, y, chunkSize
                                        );

        return firstOctaveContribution + 1.0/2.0*secondOctaveContribution + 1.0/4.0*thirdOctaveContribution;

    }
}

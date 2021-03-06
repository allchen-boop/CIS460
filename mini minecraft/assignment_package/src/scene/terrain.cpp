#include "terrain.h"
#include "cube.h"
#include <stdexcept>
#include <iostream>
#include <scene/procgen.h>

Terrain::Terrain(OpenGLContext *context)
    : m_chunks(), m_generatedTerrain(), m_geomCube(context), mp_context(context)
{}

Terrain::~Terrain() {
    m_geomCube.destroy();
}

// Combine two 32-bit ints into one 64-bit int
// where the upper 32 bits are X and the lower 32 bits are Z
int64_t toKey(int x, int z) {
    int64_t xz = 0xffffffffffffffff;
    int64_t x64 = x;
    int64_t z64 = z;

    // Set all lower 32 bits to 1 so we can & with Z later
    xz = (xz & (x64 << 32)) | 0x00000000ffffffff;

    // Set all upper 32 bits to 1 so we can & with XZ
    z64 = z64 | 0xffffffff00000000;

    // Combine
    xz = xz & z64;
    return xz;
}

glm::ivec2 toCoords(int64_t k) {
    // Z is lower 32 bits
    int64_t z = k & 0x00000000ffffffff;
    // If the most significant bit of Z is 1, then it's a negative number
    // so we have to set all the upper 32 bits to 1.
    // Note the 8    V
    if(z & 0x0000000080000000) {
        z = z | 0xffffffff00000000;
    }
    int64_t x = (k >> 32);

    return glm::ivec2(x, z);
}

// Surround calls to this with try-catch if you don't know whether
// the coordinates at x, y, z have a corresponding Chunk
BlockType Terrain::getBlockAt(int x, int y, int z) const
{
    if(hasChunkAt(x, z)) {
        // Just disallow action below or above min/max height,
        // but don't crash the game over it.
        if(y < 0 || y >= 256) {
            return EMPTY;
        }
        const uPtr<Chunk> &c = getChunkAt(x, z);
        glm::vec2 chunkOrigin = glm::vec2(floor(x / 16.f) * 16, floor(z / 16.f) * 16);
        return c->getBlockAt(static_cast<unsigned int>(x - chunkOrigin.x),
                             static_cast<unsigned int>(y),
                             static_cast<unsigned int>(z - chunkOrigin.y));
    }
    else {
        throw std::out_of_range("Coordinates " + std::to_string(x) +
                                " " + std::to_string(y) + " " +
                                std::to_string(z) + " have no Chunk!");
    }
}

BlockType Terrain::getBlockAt(glm::vec3 p) const {
    return getBlockAt(p.x, p.y, p.z);
}

bool Terrain::hasChunkAt(int x, int z) const {
    // Map x and z to their nearest Chunk corner
    // By flooring x and z, then multiplying by 16,
    // we clamp (x, z) to its nearest Chunk-space corner,
    // then scale back to a world-space location.
    // Note that floor() lets us handle negative numbers
    // correctly, as floor(-1 / 16.f) gives us -1, as
    // opposed to (int)(-1 / 16.f) giving us 0 (incorrect!).
    int xFloor = static_cast<int>(glm::floor(x / 16.f));
    int zFloor = static_cast<int>(glm::floor(z / 16.f));
    return m_chunks.find(toKey(16 * xFloor, 16 * zFloor)) != m_chunks.end();
}


uPtr<Chunk>& Terrain::getChunkAt(int x, int z) {
    int xFloor = static_cast<int>(glm::floor(x / 16.f));
    int zFloor = static_cast<int>(glm::floor(z / 16.f));
    return m_chunks[toKey(16 * xFloor, 16 * zFloor)];
}


const uPtr<Chunk>& Terrain::getChunkAt(int x, int z) const {
    int xFloor = static_cast<int>(glm::floor(x / 16.f));
    int zFloor = static_cast<int>(glm::floor(z / 16.f));
    return m_chunks.at(toKey(16 * xFloor, 16 * zFloor));
}


void Terrain::setBlockAt(int x, int y, int z, BlockType t) {
    if(hasChunkAt(x, z)) {
        uPtr<Chunk> &c = getChunkAt(x, z);
        glm::vec2 chunkOrigin = glm::vec2(floor(x / 16.f) * 16, floor(z / 16.f) * 16);
        c->setBlockAt(static_cast<unsigned int>(x - chunkOrigin.x),
                      static_cast<unsigned int>(y),
                      static_cast<unsigned int>(z - chunkOrigin.y),
                      t);
    }
    else {
        throw std::out_of_range("Coordinates " + std::to_string(x) +
                                " " + std::to_string(y) + " " +
                                std::to_string(z) + " have no Chunk!");
    }
}


Chunk* Terrain::instantiateChunkAt(int x, int z) {
    uPtr<Chunk> chunk = mkU<Chunk>(mp_context);
    Chunk *cPtr = chunk.get();
    m_chunks[toKey(x, z)] = move(chunk);

    if (hasChunkAt(x, z + 16)) {
        auto &chunkNorth = m_chunks[toKey(x, z + 16)];
        cPtr->linkNeighbor(chunkNorth, ZPOS);
    }
    if (hasChunkAt(x, z - 16)) {
        auto &chunkSouth = m_chunks[toKey(x, z - 16)];
        cPtr->linkNeighbor(chunkSouth, ZNEG);
    }
    if (hasChunkAt(x + 16, z)) {
        auto &chunkEast = m_chunks[toKey(x + 16, z)];
        cPtr->linkNeighbor(chunkEast, XPOS);
    }
    if (hasChunkAt(x - 16, z)) {
        auto &chunkWest = m_chunks[toKey(x - 16, z)];
        cPtr->linkNeighbor(chunkWest, XNEG);
    }

    for (int i = x; i < x + 16; i++) {
        for (int j = z; j < z + 16; j++) {
            fillColumn(i, j);
        }
    }

    cPtr->setWorldPos(x, z);
    cPtr->destroy();
    cPtr->create();

    return cPtr;
}

void Terrain::fillColumn(int x, int z) {
    int height = ProcGen::getHeight(x, z);

    for (int k = height-2; k < height; k++) {
        setBlockAt(x, k, z, 150 < height ? STONE : GRASS);
    }
}

void Terrain::updateScene(glm::vec3 pos) {
    int xFloor = static_cast<int>(glm::floor(pos.x / 16.f));
    int zFloor = static_cast<int>(glm::floor(pos.z / 16.f));
    int x = 16 * xFloor;
    int z = 16 * zFloor;

    // when the player is 16 blocks of an edge of a Chunk
    // that does not connect to an existing Chunk
    // the Terrain should insert a new Chunk into its map
    // and set up its VBOs for rendering
    if (!hasChunkAt(x, z + 16)) {
        instantiateChunkAt(x, z + 16);
    }

    if (!hasChunkAt(x + 16, z)) {
        instantiateChunkAt(x + 16, z);
    }

    if (!hasChunkAt(x, z - 16)) {
        instantiateChunkAt(x, z - 16);
    }

    if (!hasChunkAt(x - 16, z)) {
        instantiateChunkAt(x - 16, z);
    }

    // right back diag
    if (!hasChunkAt(x + 16, z - 16)) {
        instantiateChunkAt(x + 16, z - 16);
    }

    // right front diagonal
    if (!hasChunkAt(x + 16, z + 16)) {
        instantiateChunkAt(x + 16, z + 16);
    }

    // left back diag
    if (!hasChunkAt(x - 16, z - 16)) {
        instantiateChunkAt(x - 16, z - 16);
    }

    // left front diag
    if (!hasChunkAt(x - 16, z + 16)) {
        instantiateChunkAt(x - 16, z + 16);
    }
}


// TODO: When you make Chunk inherit from Drawable, change this code so
// it draws each Chunk with the given ShaderProgram, remembering to set the
// model matrix to the proper X and Z translation
void Terrain::draw(int minX, int maxX, int minZ, int maxZ, ShaderProgram *shaderProgram) {
    for(int x = minX; x < maxX; x += 16) {
        for(int z = minZ; z < maxZ; z += 16) {
            if (hasChunkAt(x, z)) {
                const uPtr<Chunk> &chunk = getChunkAt(x, z);

                chunk->setWorldPos(x, z);
                shaderProgram->setModelMatrix(glm::translate(glm::mat4(), glm::vec3(x, 0, z)));
                shaderProgram->drawOpq(*chunk);
            }
        }
    }

    for(int x = minX; x < maxX; x += 16) {
        for(int z = minZ; z < maxZ; z += 16) {
            if (hasChunkAt(x, z)) {
                const uPtr<Chunk> &chunk = getChunkAt(x, z);

                chunk->setWorldPos(x, z);
                shaderProgram->setModelMatrix(glm::translate(glm::mat4(), glm::vec3(x, 0, z)));
                shaderProgram->drawTrans(*chunk);
            }
        }
    }
}


void Terrain::CreateTestScene()
{

    // Create the Chunks that will
    // store the blocks for our
    // initial world space
    for(int x = 0; x < 64; x += 16) {
        for(int z = 0; z < 64; z += 16) {
            instantiateChunkAt(x, z);
        }
    }

    // Tell our existing terrain set that
    // the "generated terrain zone" at (0,0)
    // now exists.
    m_generatedTerrain.insert(toKey(0, 0));

    for (int x = 0; x < 64; ++x) {
        for (int z = 0; z < 64; ++z) {
            setBlockAt(x, ProcGen::getHeight(x, z), z, STONE);
        }
    }

    // Add "walls" for collision testing
    for(int x = 0; x < 64; ++x) {
        setBlockAt(x, 129, 0, GRASS);
        setBlockAt(x, 130, 0, GRASS);
        setBlockAt(x, 129, 63, GRASS);
        setBlockAt(0, 130, x, GRASS);
    }

    // Add a central column
    for(int y = 129; y < 140; ++y) {
        setBlockAt(32, y, 32, WATER);
    }

    // create chunk vbo data
    for (int x = 0; x < 64; x += 16) {
        for (int z = 0; z < 64; z += 16) {
            const uPtr<Chunk> &chunk = getChunkAt(x, z);
            chunk->setWorldPos(x, z);
            chunk->destroy();
            chunk->create();
        }
    }
}

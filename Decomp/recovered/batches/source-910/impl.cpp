#include "impl.hpp"

// Direct disassembly agrees with accepted simplex_solver_reduce_vertices.S.
// Calls at 0x5465af and 0x5467d2 come from the closest-point update; its
// count dispatch accepts 0..4. The mask is the low byte of its used-vertex
// record (at solver+0x14c). Names for vector roles reflect the surrounding
// support-point arithmetic; this recovery does not implement that caller.
//
// Remove highest indices first: replacement by the current last entry is
// deliberately unstable. Vacated entries are never cleared. Do not cache
// the byte: the original rereads it after each removal (including aliases).
void RIFF_THISCALL SimplexSolverVertices::reduceVertices(const uint8_t* usedVertices) {
    if (vertexCount >= 4 && !(*usedVertices & 8)) removeVertex(3);
    if (vertexCount >= 3 && !(*usedVertices & 4)) removeVertex(2);
    if (vertexCount >= 2 && !(*usedVertices & 2)) removeVertex(1);
    if (vertexCount >= 1 && !(*usedVertices & 1)) removeVertex(0);
}

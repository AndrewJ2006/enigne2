#include "Plane.h"
#include "Objects.hpp"

Mesh* Plane::Create() {
    return new Mesh(Hardcoded::GetPlaneVertices(), Hardcoded::GetPlaneIndices());
}
#include "DimensionContainer.hpp"
#include "DimensionContainer.cpp"

#include <iostream>
#include <vector>

using namespace std;

int main() {
    DimensionContainer<int> tensor3d = DimensionContainer<int>(multidimensional_vertex_definitions_t({3, 3, 3})); // Cube 3 x 3 x 3
}
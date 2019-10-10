#pragma once

#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int dimension_size_t;
typedef vector<dimension_size_t> multidimensional_vertex_definitions_t;

template<typename T>
using multidimensional_iterator_lambda_ptr_t = void (*)(&T, &multidimensional_vertex_definitions_t); // (currentvalue, currentmultidimensionalindex)

template<typename T>
class DimensionContainer {
    private:

    dimension_size_t dimension_depth;

    multidimensional_vertex_definitions_t& dimensional_shape;

    vector<DimensionContainer<T>> nested_dimensions;

    vector<T> values;

    void _iterate(multidimensional_iterator_lambda_ptr_t<T> _iterator_lambda, multidimensional_vertex_definitions_t& _iterator_range);

    public:
    DimensionContainer(multidimensional_vertex_definitions_t& _multidimensional_shape_vertex_locations, dimension_size_t _dimension_count = 1);

    DimensionContainer<T> &operator[] (const dimension_size_t _index_of_dimension);

    T& index(const dimension_size_t _index_of_value);

    void iterate(multidimensional_iterator_lambda_ptr_t<T> _iterator_lambda);

    T& retrieve(multidimensional_vertex_definitions_t& _multidimensional_location_of_value);

};

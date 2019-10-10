#include "DimensionContainer.hpp"

#include <iostream>
#include <vector>

using namespace std;

template<class T>
DimensionContainer<T>::DimensionContainer(multidimensional_vertex_definitions_t& _multidimensional_shape_vertex_locations, dimension_size_t _dimension_count = 1) {
    dimension_depth = _dimension_count;
    const dimension_size_t dimension_max_bounds = _multidimensional_shape_vertex_locations[dimension_depth - 1];

    if (dimension_depth < _multidimensional_shape_vertex_locations.size()) {
        
        nested_dimensions = vector<DimensionContainer<T>>(dimension_max_bounds);

        for (dimension_size_t i = 0; i < dimension_max_bounds; i++) {
            nested_dimensions[i] = DimensionContainer<T>(_multidimensional_shape_vertex_locations, _dimension_count + 1);
        }

        values = nullptr;

    } else {

        nested_dimensions = nullptr;

        values = vector<T>(dimension_max_bounds);

    }

}

template<class T>
DimensionContainer<T> &DimensionContainer<T>::operator[](const dimension_size_t _index_of_dimension) {

    if (nested_dimensions == nullptr) {
        cout << "Error: Accessing the last nested dimension is not allowed with the [] operator. Use the '.index(const dimension_size_t)' method to access the value instead." << endl;
        return this;
    }

    if (_index_of_dimension >= nested_dimensions.size()) {
        cout << "Error: The dimensional vertex accessed '" << _index_of_dimension <<"', is out of bounds." << endl;
        return nullptr;
    }

    return nested_dimensions[_index_of_dimension];
}

template<class T>
T& DimensionContainer<T>::index(const dimension_size_t _index_of_value) {

    if (nested_dimensions != nullptr) {
        cout << "Error: Accessing an intermediate dimension is only allowed with the [] operator." << endl;
        return nullptr;
    }

    if (_index_of_value >= values.size()) {
        cout << "Error: The dimensional value accessed '" << _index_of_dimension <<"', is out of bounds." << endl;
        return nullptr;
    }

    return values[_index_of_value];
}

template<class T>
void DimensionContainer<T>::iterate(multidimensional_iterator_lambda_ptr_t<T> _iterator_lambda) {
    if (dimension_depth > 1) {
        return;
    }

    multidimensional_vertex_definitions_t iterator_range = multidimensional_vertex_definitions_t(dimensional_shape.size() - (dimension_depth - 1));
    for (dimension_size_t i = 0; i < iterator_range.size(); i++) {
        iterator_range[i] = 0;
    }

    _iterate(_iterator_lambda, iterator_range);
}

template<class T>
void DimensionContainer<T>::_iterate(multidimensional_iterator_lambda_ptr_t<T> _iterator_lambda, multidimensional_vertex_definitions_t& _iterator_range) {
    _iterator_lambda(, _iterator_range);
}

template<class T>
T& DimensionContainer<T>::retrieve(multidimensional_vertex_definitions_t& _multidimensional_location_of_value) {
    if (values != nullptr) {
        return index(_multidimensional_location_of_value.back());
    }

    return nested_dimensions[_multidimensional_location_of_value[dimension_depth - 1]].retrieve(_multidimensional_location_of_value);
}
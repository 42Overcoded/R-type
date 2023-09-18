#include "sparse_array.hpp"

template <typename Component>
typename sparse_array<Component>::reference_type sparse_array<Component>::insert_at(size_type pos, Component const &entity)
{
    _data[pos] = entity;
}
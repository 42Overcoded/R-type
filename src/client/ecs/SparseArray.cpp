#include "SparseArray.hpp"

template <typename Component>
typename SparseArray<Component>::reference_type SparseArray<Component>::insert_at(size_type pos, const Component &entity)
{
    if (pos >= _data.size()) {
        return;
    } else {
        _data[pos] = entity;
        return _data[pos];
    }
}

template <typename Component>
typename SparseArray<Component>::reference_type SparseArray<Component>::insert_at(size_type pos, Component &&entity)
{
    if (pos >= _data.size()) {
        return;
    } else {
        _data[pos] = entity;
        return _data[pos];
    }
}

template <typename Component>
void SparseArray<Component>::erase(size_type pos)
{
    if (pos >= _data.size()) {
        return;
    } else {
        _data[pos] = nullptr;
    }
}

template <typename Component>
typename SparseArray<Component>::size_type SparseArray<Component>::get_index(const value_type &entity) const
{
    for (size_type i = 0; i < _data.size(); i++) {
        if (_data[i] == entity) {
            return i;
        }
    }
    return -1;
}

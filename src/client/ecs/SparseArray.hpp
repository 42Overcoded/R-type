/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** SparseArray
*/

#ifndef SPARSEARRAY_HPP
#define SPARSEARRAY_HPP

#include <optional>
#include <vector>
#include <iostream>
#include <any>

template <typename Component>
class SparseArray {
    public:
        using value_type = Component;
        using reference_type = value_type &;
        using const_reference_type = const value_type &;
        using container_t = std::vector<std::optional<value_type>>;
        using size_type = typename container_t::size_type;
        using iterator = typename container_t::iterator;
        using const_iterator = typename container_t::const_iterator;
    public:
        SparseArray() = default; // You can add more constructors.
        SparseArray(const SparseArray &) = default;
        SparseArray(SparseArray &&) noexcept = default;
        ~SparseArray() = default;

        SparseArray &operator=(const SparseArray &)
        {
            return *this;
        };
        SparseArray &operator=(SparseArray &&) noexcept
        {
            return *this;
        };
        reference_type operator[](size_t idx) {
            return _data[idx];
        };
        const_reference_type operator[](size_t idx) const
        {
            return *_data[idx];
        };

        iterator begin() {
            return _data.begin();
        };
        const_iterator begin() const {
            return _data.begin();
        };
        const_iterator cbegin() const {
            return _data.cbegin();
        };
        iterator end() {
            return _data.end();
        };
        const_iterator end() const {
            return _data.end();
        };
        const_iterator cend() const {
            return _data.cend();
        };
        size_type size() const {
            return _data.size();
        };

        void insert_at(size_type pos, const Component &) {
            if (pos >= _data.size())
                _data.resize(pos + 1);
            else {
                _data[pos] = Component();
            }
        };

        void insert_at(size_type pos, Component &&) {
            if (pos >= _data.size()) {
                _data.resize(pos + 1);
            }
            _data[pos] = Component();
        };
        
        template <class... Params>
        void emplace_at(size_type pos, Params &&...); // Optional
        
        void erase(size_type pos)
        {
            if (pos >= _data.size())
                _data.resize(pos + 1);
            _data[pos] = std::nullopt;
        };

        size_type get_index(const value_type &type) const
        {
            for (size_t i = 0; i < _data.size(); i++) {
                if (_data[i] == type)
                    return i;
            }
            return -1;
        };

    private:
        container_t _data;
};

#endif //SPARSEARRAY_HPP
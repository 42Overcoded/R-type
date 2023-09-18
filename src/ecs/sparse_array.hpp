/*
** EPITECH PROJECT, 2023
** B-CPP-500-TLS-5-1-bsrtype-florian.azema
** File description:
** sparse_array
*/

#include <cstddef>
#include <iostream>
#include <vector>

class Entity {
private:
public:
    std::size_t size;
    operator std::size_t() const {
        return this->size;
    }
};

template <typename Component>
class sparse_array {
public:
    using value_type = Component;
    using reference_type = value_type &;
    using const_reference_type = value_type const &;
    using container_t = std::vector<value_type>; // Vous pouvez ajouter votre allocateurr ici.
    using size_type = typename container_t::size_type;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

public:
    sparse_array();                         // Vous pouvez ajouter plus de constructeurs.
    sparse_array(sparse_array const &);     // Constructeur de copie
    sparse_array(sparse_array &&) noexcept; // Constructeur de déplacement
    ~sparse_array();
    sparse_array &operator=(sparse_array const &);     // Opérateur d'assignation par copie
    sparse_array &operator=(sparse_array &&) noexcept; // Opérateur d'assignation par déplacement
    reference_type operator[](size_t idx);
    const_reference_type operator[](size_t idx) const;
    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;
    size_type size() const;
    reference_type insert_at(size_type pos, Component const &);
    reference_type insert_at(size_type pos, Component &&);
    template <class... Params>
    reference_type emplace_at(size_type pos, Params &&...); // Facultatif
    void erase(size_type pos);
    size_type get_index(value_type const &) const;

private:
    container_t _data;
};

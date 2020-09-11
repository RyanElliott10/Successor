//
// Created by Ryan Elliott on 9/10/20.
//

#ifndef SUCCESSOR_SIMPLE_MOVING_AVERAGE_HPP
#define SUCCESSOR_SIMPLE_MOVING_AVERAGE_HPP


#include <array>

template<typename Type, size_t Window>
struct simple_moving_average
{
    simple_moving_average() = default;

    // Re-implementation of std::vector interface
    __attribute__((always_inline))
    void push_back(const Type &value)
    { underlying_vector.push_back(value); }

    __attribute__((always_inline))
    Type &at(const size_t pos) const
    { return underlying_vector.at(pos); }

    __attribute__((always_inline))
    Type &operator[](const size_t pos) const
    { return underlying_vector[pos]; }

    [[nodiscard]] __attribute__((always_inline))
    size_t size() const noexcept
    { return underlying_vector.size(); }

    __attribute__((always_inline))
    constexpr typename std::vector<Type>::iterator &begin() const noexcept
    { return underlying_vector.begin(); }

    __attribute__((always_inline))
    constexpr typename std::vector<Type>::iterator &end() const noexcept
    { return underlying_vector.end(); }

    __attribute__((always_inline))
    constexpr typename std::vector<Type>::iterator &cbegin() const noexcept
    { return underlying_vector.cbegin(); }

    __attribute__((always_inline))
    constexpr typename std::vector<Type>::iterator &cend() const noexcept
    { return underlying_vector.cend(); }

    __attribute__((always_inline))
    constexpr typename std::vector<Type>::iterator &rbegin() const noexcept
    { return underlying_vector.rbegin(); }

    __attribute__((always_inline))
    constexpr typename std::vector<Type>::iterator &rend() const noexcept
    { return underlying_vector.rend(); }

    __attribute__((always_inline))
    constexpr typename std::vector<Type>::iterator &crbegin() const noexcept
    { return underlying_vector.crbegin(); }

    __attribute__((always_inline))
    constexpr typename std::vector<Type>::iterator &crend() const noexcept
    { return underlying_vector.crend(); }

private:
    typename std::array<Type, Window> underlying_vector{};
};


#endif //SUCCESSOR_SIMPLE_MOVING_AVERAGE_HPP

#pragma once

namespace std {
    template <class T>
    constexpr const T& min (const T& a, const T& b) {
        return !(b<a)?a:b;
    }

    template <class T, class Compare>
    constexpr const T& min (const T& a, const T& b, Compare comp) {
        return !comp(b,a)?a:b;
    }

    /*
    template <class T>
    constexpr T min (initializer_list<T> il) {

    }

    template <class T, class Compare>
    constexpr T min (initializer_list<T> il, Compare comp);
    */
}
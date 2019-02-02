/****************************************************************************************
** Copyright (C) 2016-2019 Simone Angeloni
** This file is part of Tic Tac Toe.
**
** Tic Tac Toe is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Tic Tac Toe is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Tic Tac Toe. If not, see <http://www.gnu.org/licenses/>
**
****************************************************************************************/

#pragma once

namespace utils {

    template<typename T>
    class point final
    {
      public:
        point() = default;
        point(T x, T y) : m_x(x), m_y(y) {}

        inline T x() const noexcept { return m_x; }
        inline T y() const noexcept { return m_y; }
        inline void set_x(T x) noexcept { m_x = x; }
        inline void set_y(T y) noexcept { m_y = y; }

        inline T & rx() noexcept { return m_x; }
        inline T & ry() noexcept { return m_y; }

        inline point<T> & operator+=(const point<T> & p);
        inline point<T> & operator-=(const point<T> & p);
        inline point<T> & operator*=(T c);
        inline point<T> & operator/=(T c);

        template<class Y>
        friend inline bool operator==(const point<T> & p1, const point<T> & p2);

        template<class Y>
        friend inline bool operator!=(const point<T> & p1, const point<T> & p2);

        template<class Y>
        friend inline const point<T> operator+(const point<T> & p1, const point<T> & p2);

        template<class Y>
        friend inline const point<T> operator-(const point<T> & p1, const point<T> & p2);

        template<class Y>
        friend inline const point<T> operator*(T c, const point<T> & p);

        template<class Y>
        friend inline const point<T> operator*(const point<T> &, T c);

        template<class Y>
        friend inline const point<T> operator+(const point<T> & p);

        template<class Y>
        friend inline const point<T> operator-(const point<T> &);

        template<class Y>
        friend inline const point<T> operator/(const point<T> & p, T divisor);

      private:
        T m_x{0};
        T m_y{0};
    };

    // -------------------------------------------------------------

    using point_uint = point<unsigned int>;
    using point_int = point<int>;
    using point_float = point<float>;
    using point_double = point<double>;

    // -------------------------------------------------------------

    template<typename T>
    point<T> & point<T>::operator+=(const point & p)
    {
        m_x += p.m_x;
        m_y += p.m_y;
        return *this;
    }

    template<typename T>
    point<T> & point<T>::operator-=(const point & p)
    {
        m_x -= p.m_x;
        m_y -= p.m_y;
        return *this;
    }

    template<typename T>
    point<T> & point<T>::operator*=(T c)
    {
        m_x *= c;
        m_y *= c;
        return *this;
    }

    template<typename T>
    point<T> & point<T>::operator/=(T divisor)
    {
        m_x /= divisor;
        m_y /= divisor;
        return *this;
    }

    template<typename T>
    bool operator==(const point<T> & p1, const point<T> & p2)
    {
        return p1.m_x == p2.m_x && p1.m_y == p2.m_y;
    }

    template<typename T>
    bool operator!=(const point<T> & p1, const point<T> & p2)
    {
        return p1.m_x != p2.m_x || p1.m_y != p2.m_y;
    }

    template<typename T>
    const point<T> operator+(const point<T> & p1, const point<T> & p2)
    {
        return point<T>(p1.m_x + p2.m_x, p1.m_y + p2.m_y);
    }

    template<typename T>
    const point<T> operator-(const point<T> & p1, const point<T> & p2)
    {
        return point<T>(p1.m_x - p2.m_x, p1.m_y - p2.m_y);
    }

    template<typename T>
    const point<T> operator*(T c, const point<T> & p)
    {
        return point<T>(p.m_x * c, p.m_y * c);
    }

    template<typename T>
    const point<T> operator*(const point<T> & p, T c)
    {
        return point<T>(p.m_x * c, p.m_y * c);
    }

    template<typename T>
    const point<T> operator+(const point<T> & p)
    {
        return p;
    }

    template<typename T>
    const point<T> operator-(const point<T> & p)
    {
        return point<T>(-p.m_x, -p.m_x);
    }

    template<typename T>
    const point<T> operator/(const point<T> & p, T divisor)
    {
        return point<T>(p.m_x / divisor, p.m_y / divisor);
    }

} // namespace utils

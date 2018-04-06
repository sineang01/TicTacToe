/****************************************************************************************
** Copyright (C) 2016-2018 Simone Angeloni
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

namespace Utils {

	template <typename T>
	class Point final
	{
	public:
		Point() :mX(0), mY(0) {}
		Point(T x, T y) :mX(x), mY(y) {}
		~Point() {}

		inline T x() const { return mX; }
		inline T y() const { return mY; }
		inline void setX(T x) { mX = x; }
		inline void setY(T y) { mY = y; }

		inline T & rx() { return mX; }
		inline T & ry() { return mY; }

		inline Point<T> &operator+=(const Point<T> & p);
		inline Point<T> &operator-=(const Point<T> & p);
		inline Point<T> &operator*=(T c);
		inline Point<T> &operator/=(T c);

		friend inline bool operator==(const Point<T> & p1, const Point<T> & p2);
		friend inline bool operator!=(const Point<T> & p1, const Point<T> & p2);
		friend inline const Point<T> operator+(const Point<T> & p1, const Point<T> & p2);
		friend inline const Point<T> operator-(const Point<T> & p1, const Point<T> & p2);
		friend inline const Point<T> operator*(T, const Point<T> & p);
		friend inline const Point<T> operator*(const Point<T> &, T c);
		friend inline const Point<T> operator+(const Point<T> & p);
		friend inline const Point<T> operator-(const Point<T> &);
		friend inline const Point<T> operator/(const Point<T> & p, T divisor);

	private:
		T mX;
		T mY;
	};

	// -------------------------------------------------------------

	using PointUInt = Point<unsigned int>;
	using PointInt = Point<int>;
	using PointFloat = Point<float>;
	using PointDouble = Point<double>;

	// -------------------------------------------------------------

	template <typename T>
	Point<T> & Point<T>::operator+=(const Point & p)
	{
		mX += p.mX;
		mY += p.mY;
		return *this;
	}

	template <typename T>
	Point<T> &Point<T>::operator-=(const Point & p)
	{
		mX -= p.mX;
		mY -= p.mY;
		return *this;
	}

	template <typename T>
	Point<T> &Point<T>::operator*=(T c)
	{
		mX *= c;
		mY *= c;
		return *this;
	}

	template <typename T>
	bool operator==(const Point<T> & p1, const Point<T> & p2)
	{
		return p1.mX == p2.mX && p1.mY == p2.mY;
	}

	template <typename T>
	bool operator!=(const Point<T> & p1, const Point<T> & p2)
	{
		return p1.mX != p2.mX || p1.mY != p2.mY;
	}

	template <typename T>
	bool operator+(const Point<T> & p1, const Point<T> & p2)
	{
		return Point<T>(p1.mX + p2.mX, p1.mY + p2.mY);
	}

	template <typename T>
	bool operator-(const Point<T> & p1, const Point<T> & p2)
	{
		return Point<T>(p1.mX - p2.mX, p1.mY - p2.mY);
	}

	template <typename T>
	bool operator*(const Point<T> & p, T c)
	{
		return Point<T>(p.mX * c, p.mY * c);
	}

	template <typename T>
	const Point<T> operator+(const Point<T> & p)
	{
		return p;
	}

	template <typename T>
	Point<T> & Point<T>::operator/=(T divisor)
	{
		mX /= divisor;
		mY /= divisor;
		return *this;
	}

	template <typename T>
	const Point<T> operator-(const Point<T> & p)
	{
		return Point<T>(-p.mX, -p.mX);
	}

	template <typename T>
	const Point<T> operator/(const Point<T> & p, T divisor)
	{
		return Point<T>(p.mX / divisor, p.mY / divisor);
	}

} // namespace Utils

/*
   This file is part of The Lost Souls Downfall prototype.

    The Lost Souls Downfall prototype is free software: you can
    redistribute it and/or modify it under the terms of the GNU
    General Public License as published by the Free Software
    Foundation, either version 3 of the License, or (at your option)
    any later version.

    The Lost Souls Downfall prototype is distributed in the hope that
    it will be useful, but WITHOUT ANY WARRANTY; without even the
    implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
    PURPOSE.  See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with The Lost Souls Downfall prototype.  If not, see
    <http://www.gnu.org/licenses/>.
*/

#ifndef GEOMETRY_VEC2D_H
#define GEOMETRY_VEC2D_H

#include <cmath>
#include <ostream>

namespace Geometry
{
    /**
     * Vector in two-dimensional space.
     */
    template<typename T>
    class Vec2D
    {
    public:
        Vec2D(): x_(0), y_(0)
        {}

        Vec2D(T x, T y): x_(x), y_(y)
        {}

        // Copy operators

        Vec2D(const Vec2D& vec): x_(vec.x_), y_(vec.y_)
        {}

        inline Vec2D& operator=(const Vec2D& vec)
        {
            x_ = vec.x_;
            y_ = vec.y_;
            return *this;
        }

        // Getters, setters

        inline T& getX() { return x_; }
        inline T getX() const { return x_; }
        inline void setX(T x) { x_ = x; }

        inline T& getY() { return y_; }
        inline T getY() const { return y_; }
        inline void setY(T y) { y_ = y; }

        // Vector operations
        inline bool operator==(const Vec2D& vec) const
        {
            return x_ == vec.x_ && y_ == vec.y_;
        }

        inline bool operator!=(const Vec2D& vec) const
        {
            return x_ != vec.x_ || y_ != vec.y_;
        }

        inline Vec2D operator+(const Vec2D& vec) const
        {
            return Vec2D(x_ + vec.x_,
                         y_ + vec.y_);
        }

        inline Vec2D& operator+=(const Vec2D& vec)
        {
            x_ += vec.x_;
            y_ += vec.y_;
            return *this;
        }

        inline Vec2D operator-(const Vec2D& vec) const
        {
            return Vec2D(x_ - vec.x_,
                         y_ - vec.y_);
        }

        inline Vec2D& operator-=(const Vec2D& vec)
        {
            x_ -= vec.x_;
            y_ -= vec.y_;
            return *this;
        }

        inline Vec2D operator*(const Vec2D& vec) const
        {
            return Vec2D(x_ * vec.x_,
                         y_ * vec.y_);
        }

        inline Vec2D& operator*=(const Vec2D& vec)
        {
            x_ *= vec.x_;
            y_ *= vec.y_;
            return *this;
        }

        inline Vec2D operator*(T t) const
        {
            return Vec2D(t * x_,
                         t * y_);
        }

        inline Vec2D& operator *=(T t)
        {
            x_ *= t;
            y_ *= t;
            return *this;
        }

        inline Vec2D operator-() const
        {
            return Vec2D(-x_, -y_);
        }

        inline bool operator<(const Vec2D& vec) const
        {
            return x_ < vec.x_ || (x_ == vec.x_ && y_ < vec.y_);
        }

        inline T dot(const Vec2D& vec) const
        {
            return x_ * vec.x_ + y_ * vec.y_;
        }

        // Vector function
        inline T getSquaredLength() const
        {
            return x_ * x_ + y_ * y_;
        }

        inline T getLength() const
        {
            return std::sqrt(getSquaredLength());
        }

    private:
        T x_;
        T y_;
    };

    template<typename T>
    inline Vec2D<T>& operator*(T t, const Vec2D<T>& vec)
    {
        return vec * t;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& out, const Vec2D<T>& vec)
    {
        return out << "Vec2D(" << vec.getX() << ", " << vec.getY() << ")";
    }

    typedef Vec2D<int> Vec2Di;
    typedef Vec2D<float> Vec2Df;
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:

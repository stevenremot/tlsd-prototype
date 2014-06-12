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

#ifndef GEOMETRY_VEC3D_H
#define GEOMETRY_VEC3D_H

#include <ostream>
#include <cmath>

namespace Geometry
{
    /**
     * Vector in two-dimensional space.
     */
    template<typename T>
    class Vec3D
    {
    public:
        Vec3D(): x_(0), y_(0), z_(0)
        {}

        Vec3D(T x, T y, T z): x_(x), y_(y), z_(z)
        {}

        // Copy operators

        Vec3D(const Vec3D& vec): x_(vec.x_), y_(vec.y_), z_(vec.z_)
        {}

        inline Vec3D& operator=(const Vec3D& vec)
        {
            x_ = vec.x_;
            y_ = vec.y_;
            z_ = vec.z_;
            return *this;
        }

        // Getters, setters

        inline T& getX() { return x_; }
        inline T getX() const { return x_; }
        inline void setX(T x) { x_ = x; }

        inline T& getY() { return y_; }
        inline T getY() const { return y_; }
        inline void setY(T y) { y_ = y; }

        inline T& getZ() { return z_; }
        inline T getZ() const { return z_; }
        inline void setZ(T z) { z_ = z; }

        // Vector operations
        inline bool operator==(const Vec3D& vec) const
        {
            return x_ == vec.x_ && y_ == vec.y_ && z_ == vec.z_;
        }

        inline bool operator!=(const Vec3D& vec) const
        {
            return x_ != vec.x_ || y_ != vec.y_ || z_ != vec.z_;
        }

        inline Vec3D operator+(const Vec3D& vec) const
        {
            return Vec3D(x_ + vec.x_,
                         y_ + vec.y_,
                         z_ + vec.z_);
        }

        inline Vec3D& operator+=(const Vec3D& vec)
        {
            x_ += vec.x_;
            y_ += vec.y_;
            z_ += vec.z_;
            return *this;
        }

        inline Vec3D operator-(const Vec3D& vec) const
        {
            return Vec3D(x_ - vec.x_,
                         y_ - vec.y_,
                         z_ - vec.z_);
        }

        inline Vec3D& operator-=(const Vec3D& vec)
        {
            x_ -= vec.x_;
            y_ -= vec.y_;
            z_ -= vec.z_;
            return *this;
        }

        inline Vec3D operator*(const Vec3D& vec) const
        {
            return Vec3D(x_ * vec.x_,
                         y_ * vec.y_,
                         z_ * vec.z_);
        }

        inline Vec3D& operator*=(const Vec3D& vec)
        {
            x_ *= vec.x_;
            y_ *= vec.y_;
            z_ *= vec.z_;
            return *this;
        }

        inline Vec3D operator*(T t) const
        {
            return Vec3D(t * x_,
                         t * y_,
                         t * z_);
        }

        inline Vec3D& operator *=(T t)
        {
            x_ *= t;
            y_ *= t;
            z_ *= t;
            return *this;
        }

        inline Vec3D operator/(T t) const
        {
            return Vec3D(x_ / t,
                         y_ / t,
                         z_ / t);
        }

        inline Vec3D& operator /=(T t)
        {
            x_ /= t;
            y_ /= t;
            z_ /= t;
            return *this;
        }

        inline Vec3D operator-() const
        {
            return Vec3D(-x_, -y_, -z_);
        }

        inline T dot(const Vec3D& vec) const
        {
            return x_ * vec.x_ + y_ * vec.y_ + z_ * vec.z_;
        }

        inline Vec3D cross(const Vec3D& vec) const
        {
            return Vec3D(y_*vec.z_ - z_* vec.y_, z_*vec.x_ - x_*vec.z_, x_*vec.y_ - y_*vec.x_);
        }

        // Vector function
        inline T getSquaredLength() const
        {
            return x_ * x_ + y_ * y_ + z_ * z_;
        }

        inline T getLength() const
        {
            return std::sqrt(getSquaredLength());
        }

        inline void normalize()
        {
            T length = this->getLength();

            x_ /= length;
            y_ /= length;
            z_ /= length;
        }

    private:
        T x_;
        T y_;
        T z_;
    };

    template<typename T>
    inline Vec3D<T>& operator*(T t, const Vec3D<T>& vec)
    {
        return vec * t;
    }


    template<typename T>
    std::ostream& operator<<(std::ostream& out, const Vec3D<T>& vec)
    {
        return out << "Vec3D(" <<
            vec.getX() << ", " <<
            vec.getY() << ", " <<
            vec.getZ() << ")";
    }

    typedef Vec3D<int> Vec3Di;
    typedef Vec3D<float> Vec3Df;
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:

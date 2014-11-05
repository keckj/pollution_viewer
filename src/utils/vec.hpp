
#ifndef VEC_H
#define VEC_H

#include <iostream>
#include <limits>

//3D vector structure

template <typename T>
struct Vec {
    T x;
    T y;
    T z;

    Vec<T>();
    Vec<T>(const Vec<T> &v);
    Vec<T>(T x, T y, T z);
    ~Vec<T>();

    Vec<T>& operator= (const Vec<T> &v);
    void setValue(T x, T y, T z);

    Vec<T> & operator+= (const Vec<T> &a);
    Vec<T> & operator-= (const Vec<T> &a);
    Vec<T> & operator*= (const Vec<T> &a);
    Vec<T> & operator/= (const Vec<T> &a);
    Vec<T> & operator^= (const Vec<T> &a);

    Vec<T> & operator+= (T k);
    Vec<T> & operator-= (T k);
    Vec<T> & operator*= (T k);
    Vec<T> & operator/= (T k);

    T normalize ();

    T norm () const;
    T squaredNorm () const;

    Vec<T> unit () const;
    Vec<T> orthogonalVec () const;
};

template <typename T>
Vec<T>::Vec() : x(0), y(0), z(0) {}

template <typename T>
Vec<T>::Vec(const Vec<T> &v) : x(v.x), y(v.y), z(v.z) {}

template <typename T>
Vec<T>::Vec(T x, T y, T z) : x(x), y(y), z(z) {}

template <typename T>
Vec<T>::~Vec() {}

template <typename T>
Vec<T>& Vec<T>::operator= (const Vec<T> &v) {
    Vec<T> V(v);
    return *this;
}

template <typename T>
void Vec<T>::setValue(T x, T y, T z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

template <typename T>
Vec<T> & Vec<T>::operator+= (const Vec<T> &a) {
    x += a.x;
    y += a.y;
    z += a.z;
    return *this;
}

template <typename T>
Vec<T> & Vec<T>::operator-= (const Vec<T> &a) {
    x -= a.x;
    y -= a.y;
    z -= a.z;
    return *this;
}

template <typename T>
Vec<T> & Vec<T>::operator*= (const Vec<T> &a) {
    x *= a.x;
    y *= a.y;
    z *= a.z;
    return *this;
}

template <typename T>
Vec<T> & Vec<T>::operator/= (const Vec<T> &a) {
    x /= a.x;
    y /= a.y;
    z /= a.z;
    return *this;
}

template <typename T>
Vec<T> & Vec<T>::operator^= (const Vec<T> &a) {
    Vec<T> b(*this);
    x = b.y*a.z - b.z*a.y;
    y = b.z*a.x - b.x*a.z;
    z = b.x*a.y - b.y*a.x;
    return *this;
}

template <typename T>
Vec<T> & Vec<T>::operator+= (T k) {
    x += k;
    y += k;
    z += k;
    return *this;
}

template <typename T>
Vec<T> & Vec<T>::operator-= (T k) {
    x -= k;
    y -= k;
    z -= k;
    return *this;
}

template <typename T>
Vec<T> & Vec<T>::operator*= (T k) {
    x *= k;
    y *= k;
    z *= k;
    return *this;
}

template <typename T>
Vec<T> & Vec<T>::operator/= (T k) {
    x /= k;
    y /= k;
    z /= k;
    return *this;
}

template <typename T>
Vec<T> operator+ (const Vec<T> &a, const Vec<T> &b) {
    return Vec<T>(a.x+b.x, a.y+b.y, a.z+b.z);
}

template <typename T>
Vec<T> operator- (const Vec<T> &a, const Vec<T> &b) {
    return Vec<T>(a.x-b.x, a.y-b.y, a.z-b.z);
}

template <typename T>
Vec<T> operator* (const Vec<T> &a, const Vec<T> &b) {
    return Vec<T>(a.x*b.x, a.y*b.y, a.z*b.z);
}

template <typename T>
Vec<T> operator/ (const Vec<T> &a, const Vec<T> &b) {
    return Vec<T>(a.x/b.x, a.y/b.y, a.z/b.z);
}

template <typename T>
Vec<T> operator^ (const Vec<T> &a, const Vec<T> &b) {
    return Vec<T>(
            a.y*b.z - a.z*b.y,
            a.z*b.x - a.x*b.z,
            a.x*b.y - a.y*b.x
            );
}

template <typename T>
T operator| (const Vec<T> &a, const Vec<T> &b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

template <typename T>
Vec<T> operator* (const Vec<T> &a, T k) {
    return Vec<T>(a.x * k, a.y * k, a.z * k);
}

template <typename T>
Vec<T> operator/ (const Vec<T> &a, T k) {
    return Vec<T>(a.x / k, a.y / k, a.z / k);
}

template <typename T>
Vec<T> operator* (T k, const Vec<T> &b) {
    return Vec<T>(b.x * k, b.y * k, b.z * k);
}

template <typename T>
Vec<T> operator/ (T k, const Vec<T> &b) {
    return Vec<T>(b.x / k, b.y / k, b.z / k);
}


template <typename T>
bool operator!= (const Vec<T> &a, const Vec<T> &b) {
    return !(a == b);
}

template <typename T>
bool operator== (const Vec<T> &a, const Vec<T> &b) {
    Vec<T> dv = b - a;
    T epsilon = std::numeric_limits<T>::epsilon();
    return (abs(dv.x) < epsilon && abs(dv.y) < epsilon && abs(dv.z) < epsilon);
}

template <typename T>
T Vec<T>::normalize () {
    T norm = this->norm();
    x /= norm;
    y /= norm;
    z /= norm;
    return norm;
}

template <typename T>
Vec<T> Vec<T>::orthogonalVec () const {
    return Vec<T>(z,z,-x-y);
}

template <typename T>
Vec<T> Vec<T>::unit () const {
    Vec<T> v(*this);
    v.normalize();
    return v;
}

template <typename T>
T Vec<T>::squaredNorm () const {
    return x*x + y*y + z*z;
}

template <typename T>
T Vec<T>::norm () const {
    return sqrt(x*x + y*y + z*z);
}

template <typename T>
std::ostream & operator << (std::ostream &os, Vec<T> &v) {
    os << "(" << v.x << "," << v.y << "," << v.z << ")";
    return os;
}

#endif /* end of include guard: VEC_H */

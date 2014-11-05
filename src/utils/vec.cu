
#include <cfloat> 
#include "vec.hpp"

__host__ __device__ Vec::Vec() : x(0.0f), y(0.0f), z(0.0f) {}
__host__ __device__ Vec::Vec(const Vec &v) : x(v.x), y(v.y), z(v.z) {}
__host__ __device__ Vec::Vec(float x, float y, float z) : x(x), y(y), z(z) {}
__host__ __device__ Vec::~Vec() {}

__host__ __device__ Vec& Vec::operator= (const Vec &v) {
    Vec V(v);
    return *this;
}


__host__ __device__ void Vec::setValue(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

__host__ __device__ Vec & Vec::operator+= (const Vec &a) {
    x += a.x;
    y += a.y;
    z += a.z;
    return *this;
}

__host__ __device__ Vec & Vec::operator-= (const Vec &a) {
    x -= a.x;
    y -= a.y;
    z -= a.z;
    return *this;
}

__host__ __device__ Vec & Vec::operator*= (const Vec &a) {
    x *= a.x;
    y *= a.y;
    z *= a.z;
    return *this;
}

__host__ __device__ Vec & Vec::operator/= (const Vec &a) {
    x /= a.x;
    y /= a.y;
    z /= a.z;
    return *this;
}

__host__ __device__ Vec & Vec::operator^= (const Vec &a) {
    Vec b(*this);
    x = b.y*a.z - b.z*a.y;
    y = b.z*a.x - b.x*a.z;
    z = b.x*a.y - b.y*a.x;
    return *this;
}

__host__ __device__ Vec & Vec::operator+= (float k) {
    x += k;
    y += k;
    z += k;
    return *this;
}

__host__ __device__ Vec & Vec::operator-= (float k) {
    x -= k;
    y -= k;
    z -= k;
    return *this;
}

__host__ __device__ Vec & Vec::operator*= (float k) {
    x *= k;
    y *= k;
    z *= k;
    return *this;
}

__host__ __device__ Vec & Vec::operator/= (float k) {
    x /= k;
    y /= k;
    z /= k;
    return *this;
}

__host__ __device__ Vec operator+ (const Vec &a, const Vec &b) {
    return Vec(a.x+b.x, a.y+b.y, a.z+b.z);
}

__host__ __device__ Vec operator- (const Vec &a, const Vec &b) {
    return Vec(a.x-b.x, a.y-b.y, a.z-b.z);
}

__host__ __device__ Vec operator* (const Vec &a, const Vec &b) {
    return Vec(a.x*b.x, a.y*b.y, a.z*b.z);
}

__host__ __device__ Vec operator/ (const Vec &a, const Vec &b) {
    return Vec(a.x/b.x, a.y/b.y, a.z/b.z);
}

__host__ __device__ Vec operator^ (const Vec &a, const Vec &b) {
    return Vec(
            a.y*b.z - a.z*b.y,
            a.z*b.x - a.x*b.z,
            a.x*b.y - a.y*b.x
            );
}

__host__ __device__ float operator| (const Vec &a, const Vec &b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

__host__ __device__ Vec operator* (const Vec &a, float k) {
    return Vec(a.x * k, a.y * k, a.z * k);
}

__host__ __device__ Vec operator/ (const Vec &a, float k) {
    return Vec(a.x / k, a.y / k, a.z / k);
}

__host__ __device__ Vec operator* (float k, const Vec &b) {
    return Vec(b.x * k, b.y * k, b.z * k);
}

__host__ __device__ Vec operator/ (float k, const Vec &b) {
    return Vec(b.x / k, b.y / k, b.z / k);
}


__host__ __device__ bool operator!= (const Vec &a, const Vec &b) {
    return !(a == b);
}
__host__ __device__ bool operator== (const Vec &a, const Vec &b) {
    Vec dv = b - a;
    return (abs(dv.x) < FLT_EPSILON && abs(dv.y) < FLT_EPSILON && abs(dv.z) < FLT_EPSILON);
}

__host__ __device__ float Vec::normalize () {
    float norm = this->norm();
    x /= norm;
    y /= norm;
    z /= norm;
    return norm;
}

__host__ __device__ Vec Vec::orthogonalVec () const {
    return Vec(z,z,-x-y);
}

__host__ __device__ Vec Vec::unit () const {
    Vec v(*this);
    v.normalize();
    return v;
}

__host__ __device__ float Vec::squaredNorm () const {
    return x*x + y*y + z*z;
}

__host__ __device__ float Vec::norm () const {
    return sqrt(x*x + y*y + z*z);
}

__host__ std::ostream & operator << (std::ostream &os, Vec &v) {
    os << "(" << v.x << "," << v.y << "," << v.z << ")";
    return os;
}

#include "vec4.h"
#include <iomanip>

///----------------------------------------------------------------------
/// Constructors
///----------------------------------------------------------------------

vec4::vec4() : data {0, 0, 0, 0}
{}

vec4::vec4(float x, float y, float z, float w) : data {x, y, z, w}
{}

vec4::vec4(const vec4 &v2) : data{v2.data[0], v2.data[1], v2.data[2], v2.data[3]}
{}

///----------------------------------------------------------------------
/// Getters/Setters
///----------------------------------------------------------------------
///

/// Returns the value at index
float vec4::operator[](unsigned int index) const {
    if (index > 3) {
        throw std::out_of_range ("input index is out of bounds");
    }

    if (index < 0) {
        throw std::out_of_range ("input index is out of bounds");
    }

    return data[index];
}

/// Returns a reference to the value at index
float& vec4::operator[](unsigned int index) {
    if (index > 3) {
        throw std::out_of_range ("input index is out of bounds");
    }

    if (index < 0) {
        throw std::out_of_range ("input index is out of bounds");
    }

    return data[index];
}

///----------------------------------------------------------------------
/// Operator Functions
///----------------------------------------------------------------------

/// Sets each element of this->data to v2's corresponding data, then returns this
vec4 &vec4::operator=(const vec4 &v2) {
    for (int i = 0; i < 4; i++) {
        this->data[i] = v2.data[i];
    }

    return *this;
}

/// Test for equality
bool vec4::operator==(const vec4 &v2) const {
    const float epsilon = 0.0000001f;

    for (int i = 0; i < 4; i++) {
        float diff = std::abs(this->data[i] - v2.data[i]);
            if (diff > epsilon) {
                return false;
            }
    }

    return true;
}

/// Test for inequality
bool vec4::operator!=(const vec4 &v2) const {
    return !this->operator==(v2);
}

/// Arithmetic:
/// e.g. += adds v2 to this and return this (like regular +=)
///      +  returns a new vector that is sum of this and v2
vec4 &vec4::operator+=(const vec4 &v2) {
    for (int i = 0; i < 4; i++) {
        this->data[i] += v2.data[i];
    }

    return *this;
}

vec4 &vec4::operator-=(const vec4 &v2) {
    for (int i = 0; i < 4; i++) {
        this->data[i] -= v2.data[i];
    }

    return *this;
}

vec4 &vec4::operator*=(float c) {
    for (int i = 0; i < 4; i++) {
        this->data[i] *= c;
    }

    return *this;
}

vec4 &vec4::operator/=(float c) {
    for (int i = 0; i < 4; i++) {
        this->data[i] /= c;
    }

    return *this;
}

vec4 vec4::operator+(const vec4 &v2) const {
    vec4 sum;

    for (int i = 0; i < 4; i++) {
            sum.data[i] = this->data[i] + v2.data[i];
    }

    return sum;
}

vec4 vec4::operator-(const vec4 &v2) const {
    vec4 diff;

    for (int i = 0; i < 4; i++) {
        diff.data[i] = this->data[i] - v2.data[i];
    }

    return diff;
}

vec4 vec4::operator*(float c) const {
    vec4 product;

    for (int i = 0; i < 4; i++) {
        product.data[i] = this->data[i] * c;
    }

    return product;
}

vec4 vec4::operator/(float c) const {
    vec4 quotient;

    for (int i = 0; i < 4; i++) {
        quotient.data[i] = this->data[i] / c;
    }

    if (c == 0) {
        quotient = vec4(std::numeric_limits<double>::quiet_NaN(),
                        std::numeric_limits<double>::quiet_NaN(),
                        std::numeric_limits<double>::quiet_NaN(),
                        std::numeric_limits<double>::quiet_NaN());
    }

    return quotient;
}

/// Dot Product
float dot(const vec4 &v1, const vec4 &v2) {
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3] * v2[3];
}

/// Cross Product
vec4 cross(const vec4 &v1, const vec4 &v2) {
    vec4 cross = vec4(v1[1] * v2[2] - v1[2] * v2[1],
                      v1[2] * v2[0] - v1[0] * v2[2],
                      v1[0] * v2[1] - v1[1] * v2[0],
                      0);
    return cross;
}

/// Returns the geometric length of the input vector
float length(const vec4 &v) {
    return sqrt(dot(v, v));
}

/// Scalar Multiplication (c * v)
vec4 operator*(float c, const vec4 &v) {
    vec4 vec;

    for (int i = 0; i < 4; i++) {
        vec[i] = c * v[i];
    }

    return vec;
}

vec4 normalize(const vec4& v) {
    return v / length(v);
}

/// Prints the vector to a stream in a nice format
std::ostream &operator<<(std::ostream &o, const vec4 &v) {
    std::cout << std::fixed << std::showpoint;
    std::cout << std::setprecision(1);
    o << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3];
    return o;
}

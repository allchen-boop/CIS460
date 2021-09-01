#include "mat4.h"

///----------------------------------------------------------------------
/// Constructors
///----------------------------------------------------------------------

/// Default Constructor.  Initialize to identity matrix.
mat4::mat4() : data {vec4(), vec4(), vec4(), vec4()}
{}

/// Initializes the diagonal values of the matrix to diag. All other values are 0.
mat4::mat4(float diag) : data {vec4(diag, 0, 0, 0),
                               vec4(0, diag, 0, 0),
                               vec4(0, 0, diag, 0),
                               vec4(0, 0, 0, diag)}
{}

/// Initializes matrix with each vector representing a column in the matrix
mat4::mat4(const vec4 &col0, const vec4 &col1, const vec4 &col2, const vec4& col3)
    : data {vec4(col0), vec4(col1), vec4(col2), vec4(col3)}
{}

// copy constructor
mat4::mat4(const mat4 &m2) : data {m2.data[0], m2.data[1], m2.data[2], m2.data[3]}
{}

///----------------------------------------------------------------------
/// Getters
///----------------------------------------------------------------------

/// Returns the values of the column at the index
vec4 mat4::operator[](unsigned int index) const {
    if (index > 3) {
        throw std::out_of_range ("input index is out of bounds");
    }

    if (index < 0) {
        throw std::out_of_range ("input index is out of bounds");
    }

    return data[index];

}

/// Returns a reference to the column at the index
vec4 &mat4::operator[](unsigned int index) {
    if (index > 3) {
        throw std::out_of_range ("input index is out of bounds");
    }

    if (index < 0) {
        throw std::out_of_range ("input index is out of bounds");
    }

    return data[index];
}

///----------------------------------------------------------------------
/// Static Initializers
///----------------------------------------------------------------------

/// Creates a 3-D rotation matrix.
/// Takes an angle in degrees and an axis represented by its xyz components, and outputs a 4x4 rotation matrix
/// Use Rodrigues' formula to implement this method
mat4 mat4 :: rotate(float angle, float x, float y, float z) {

    //deg to rad
    angle = angle * (M_PI / 180.f);

    //normalize
    vec4 norm = normalize(vec4(x, y, z, 0));

    x = norm[0];
    y = norm[1];
    z = norm[2];

    //Rodrigues' formula
    vec4 v0 = vec4(cos(angle) + pow(x, 2) * (1.f - cos(angle)),
                   z * sin(angle) + x * y * (1.f - cos(angle)),
                   -y * sin(angle) + x * z * (1.f - cos(angle)), 0.f);

    vec4 v1 = vec4(-z * sin(angle) + x * y * (1.f - cos(angle)),
                   cos(angle) + pow(y, 2) * (1.f - cos(angle)),
                   x * sin(angle) + y * z * (1.f - cos(angle)), 0.f);

    vec4 v2 = vec4(y * sin(angle) + x * z * (1.f - cos(angle)),
                   -x * sin(angle) + y * z * (1.f - cos(angle)),
                   cos(angle) + pow(z, 2) * (1.f - cos(angle)), 0.f);

    vec4 v3 = vec4(0, 0, 0, 1);

    return mat4(v0, v1, v2, v3);
}

/// Takes an xyz displacement and outputs a 4x4 translation matrix
mat4 mat4 :: translate(float x, float y, float z) {
    return mat4(vec4(1, 0, 0, x),
                vec4(0, 1, 0, y),
                vec4(0, 0, 1, z),
                vec4(0, 0, 0, 1));
}

/// Takes an xyz scale and outputs a 4x4 scale matrix
mat4 mat4 :: scale(float x, float y, float z) {
    return mat4(vec4(x, 0, 0, 0),
                vec4(0, y, 0, 0),
                vec4(0, 0, z, 0),
                vec4(0, 0, 0, 1));
}

/// Generates a 4x4 identity matrix
mat4 mat4 :: identity() {
    return mat4(1);
}

///----------------------------------------------------------------------
/// Operator Functions
///----------------------------------------------------------------------

/// Assign m2's data to this's data and return this
mat4 &mat4::operator=(const mat4 &m2) {
    for (int i = 0; i < 4; i++) {
        this->data[i] = m2.data[i];
    }

    return *this;
}

/// Test for equality
bool mat4::operator==(const mat4 &m2) const {
    for (int i = 0; i < 4; i++) {
        if (this->data[i] != m2.data[i]) {
            return false;
        }
    }

    return true;
}

/// Test for inequality
bool mat4::operator!=(const mat4 &m2) const {
    return !this->operator==(m2);
}

/// Element-wise arithmetic
/// e.g. += adds the elements of m2 to this and returns this (like regular +=)
///      +  returns a new matrix whose elements are the sums of this and v2

mat4 &mat4::operator+=(const mat4 &m2) {
    for (int i = 0; i < 4; i++) {
        this->data[i] += m2.data[i];
    }

    return *this;
}

mat4 &mat4::operator-=(const mat4 &m2) {
    for (int i = 0; i < 4; i++) {
        this->data[i] -= m2.data[i];
    }

    return *this;
}

// multiplication by a scalar
mat4 &mat4::operator*=(float c) {
    for (int i = 0; i < 4; i++) {
        this->data[i] *= c;
    }

    return *this;
}

// division by a scalar
mat4 &mat4::operator/=(float c) {
    for (int i = 0; i < 4; i++) {
        this->data[i] /= c;
    }

    return *this;
}

mat4 mat4::operator+(const mat4 &m2) const {
    mat4 sum;

    for (int i = 0; i < 4; i++) {
        sum.data[i] = this->data[i] + m2.data[i];
    }

    return sum;
}

mat4 mat4::operator-(const mat4 &m2) const {
     mat4 diff;

     for (int i = 0; i < 4; i++) {
         diff.data[i] = this->data[i] - m2.data[i];
     }

     return diff;
}

// multiplication by a scalar
mat4 mat4::operator*(float c) const {
    mat4 product;

    for (int i = 0; i < 4; i++) {
        product.data[i] = this->data[i] * c;
    }

    return product;
}

// division by a scalar
mat4 mat4::operator/(float c) const {
    mat4 quotient;

    for (int i = 0; i < 4; i++) {
        quotient.data[i] = this->data[i] / c;
    }

    return quotient;
}

/// Matrix multiplication (m1 * m2)
mat4 mat4::operator*(const mat4 &m2) const {
    mat4 mat;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mat[i][j] = dot(row(*this, i), m2.data[j]);
        }
    }

    return mat;
}

/// Matrix/vector multiplication (m * v)
/// Assume v is a column vector (ie. a 4x1 matrix)
vec4 mat4::operator*(const vec4 &v) const {
    return vec4(dot(row(*this, 0), v),
                dot(row(*this, 1), v),
                dot(row(*this, 2), v),
                dot(row(*this, 3), v));
    };


///----------------------------------------------------------------------
/// Matrix Operations
///----------------------------------------------------------------------
/// Returns the transpose of the input matrix (v_ij == v_ji)
mat4 transpose(const mat4 &m) {
    return mat4(row(m, 0), row(m, 1), row(m, 2), row(m, 3));
}

/// Returns a row of the input matrix
vec4 row(const mat4 &m, unsigned int index) {
    if (index < 0) {
        throw std::out_of_range ("input index is out of bounds");
    }

    if (index > 3) {
        throw std::out_of_range ("input index is out of bounds");
    }

    return vec4(m[0][index], m[1][index], m[2][index], m[3][index]);
}

/// Scalar multiplication (c * m)
mat4 operator*(float c, const mat4 &m) {
    mat4 mat;

    for (int i = 0; i < 4; i++) {
        mat[i] = c * m[i];
    }

    return mat;
}

/// Vector/matrix multiplication (v * m)
/// Assume v is a row vector (ie. a 1x4 matrix)
vec4 operator*(const vec4 &v, const mat4 &m) {
    vec4 mat;

    for (int i = 0; i < 4; i++) {
        mat[i] = dot(v, m[i]);
    }

    return mat;
}

/// Prints the matrix to a stream in a nice format
std::ostream &operator<<(std::ostream &o, const mat4 &m) {
    o << std::endl << m[0] << std::endl << m[1] << std::endl << m[2] << std::endl << m[3] << std::endl;
    return o;
}

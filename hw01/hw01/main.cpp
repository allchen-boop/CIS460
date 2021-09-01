// Base code written by Jan Allbeck, Chris Czyzewicz, Cory Boatright, Tiantian Liu, Benedict Brown, and Adam Mally
// University of Pennsylvania

// At least some C++ compilers do funny things
// to C's math.h header if you don't define this
#define _USE_MATH_DEFINES

#include "vec4.h"
#include "mat4.h"
#include <iostream>
#include <math.h>
using namespace std;


///----------------------------------------------------------------------
/// VEC4 TESTS
///----------------------------------------------------------------------


void vec4AddTest() {
    vec4 a = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 b = vec4(2.f, 4.f, 6.f, 8.f);

    std::cout << "\nVEC4 ADD" << std::endl;
    std::cout << "vec4 + vec4 expected value: (3.0, 6.0, 9.0, 12.0)" << std::endl;
    std::cout << "vec4 + vec4 actual value: " << (a + b) << std::endl;
}

void vec4PrintTest() {
    vec4 a = vec4(3.f, 6.f, 9.f, 12.f);

    std::cout << "\nVEC4 PRINT" << std::endl;
    std::cout << "vec4 + vec4 expected value: (3.0, 6.0, 9.0, 12.0)" << std::endl;
    std::cout << "vec4 + vec4 actual value: " << a << std::endl;
}

void vec4ValAtIndexTest() {
    vec4 a = vec4(1.f, 2.f, 3.f, 4.f);

    std::cout << " \nVEC4 GETTER" << std::endl;
    std::cout << "vec4[1] expected value: 2.0" << std::endl;
    std::cout << "vec4[1] actual value: " << a[1] << std::endl;
}

void vec4VOutOfBoundsIndexTest() {
    vec4 a = vec4(1.f, 2.f, 3.f, 4.f);

    std::cout << " \nVEC4 GETTER OUT OF BOUNDS" << std::endl;
    std::cout << "vec4[5] expected value: out of bounds" << std::endl;
    std::cout << "vec4[5] actual value: " << a[5] << std::endl;
}

void vec4VOutOfBoundsIndexTes2t() {
    vec4 a = vec4(1.f, 2.f, 3.f, 4.f);

    std::cout << " \nVEC4 GETTER OUT OF BOUNDS" << std::endl;
    std::cout << "vec4[-1] expected value: out of bounds" << std::endl;
    std::cout << "vec4[-1] actual value: " << a[-1] << std::endl;
}

void vec4DefaultConstructor() {
    std::cout << " \nVEC4 DEFAULT CONSTRUCTOR" << std::endl;
    std::cout << "vec4() expected value: (0.0, 0.0, 0.0, 0.0)" << std::endl;
    std::cout << "vec4() actual value: " << vec4() << std::endl;
}

void vec4Constructor() {
    std::cout << " \nVEC4 CONSTRUCTOR" << std::endl;
    std::cout << "vec4(1.0, 2.0, 3.0, 4.0) expected value: (1.0, 2.0, 3.0, 4.0)" << std::endl;
    std::cout << "vec4(1.0, 2.0, 3.0, 4.0) actual value: " << vec4(1.f, 2.f, 3.f, 4.f) << std::endl;
}

void vec4CopyConstructor() {
    vec4 a = vec4(1.f, 2.f, 3.f, 4.f);

    std::cout << " \nVEC4 COPY CONSTRUCTOR" << std::endl;
    std::cout << "vec4(vec4) expected value: (1.0, 2.0, 3.0, 4.0)" << std::endl;
    std::cout << "vec4(vec4) actual value: " << vec4(a) << std::endl;
}

void vec4Set() {
    vec4 a = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 b = vec4(2.f, 4.f, 6.f, 8.f);

    a = b;

    std::cout << " \nVEC4 SETTER" << std::endl;
    std::cout << "vec4 = vec4 expected value: (2.0, 4.0, 6.0, 8.0)" << std::endl;
    std::cout << "vec4 = vec4 actual value: " << a << std::endl;
}

void vec4EqualityTrue() {
    vec4 a = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 b = vec4(1.f, 2.f, 3.f, 4.f);

    std::cout << "\nVEC4 EQUALITY TRUE" << std::endl;
    std::cout << "vec4 == vec4 expected value: true" << std::endl;
    std::cout << "vec4 == vec4 actual value: " << (a == b) << std::endl;
}

void vec4EqualityFalse() {
    vec4 a = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 b = vec4(1.f, 2.f, 3.f, 1.f);

    std::cout << "\nVEC4 EQUALITY FALSE" << std::endl;
    std::cout << "vec4 == vec4 expected value: false" << std::endl;
    std::cout << "vec4 == vec4 actual value: " << (a == b) << std::endl;
}

void vec4InequalityTrue() {
    vec4 a = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 b = vec4(2.f, 4.f, 6.f, 8.f);

    std::cout << " \nVEC4 INEQUALITY TRUE" << std::endl;
    std::cout << "vec4 != vec4 expected value: true" << std::endl;
    std::cout << "vec4 != vec4 actual value: " << (a != b) << std::endl;
}

void vec4InequalityFalse() {
    vec4 a = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 b = vec4(1.f, 2.f, 3.f, 4.f);

    std::cout << " \nVEC4 INEQUALITY FALSE" << std::endl;
    std::cout << "vec4 != vec4 expected value: false" << std::endl;
    std::cout << "vec4 != vec4 actual value: " << (a != b) << std::endl;
}

void vec4Sum() {
    vec4 a = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 b = vec4(2.f, 4.f, 6.f, 8.f);

    a += b;

    std::cout << "\nVEC4 SUM" << std::endl;
    std::cout << "vec4 += vec4 expected value: (3.0, 6.0, 9.0, 12.0)" << std::endl;
    std::cout << "vec4 += vec4 actual value: " << a << std::endl;
}

void vec4Diff() {
    vec4 b = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 a = vec4(2.f, 4.f, 6.f, 8.f);

    a -= b;

    std::cout << "\nVEC4 DIFF" << std::endl;
    std::cout << "vec4 -= vec4 expected value: (1.0, 2.0, 3.0, 4.0)" << std::endl;
    std::cout << "vec4 -= vec4 actual value: " << a << std::endl;
}

void vec4Product() {
    vec4 a = vec4(1.f, 2.f, 3.f, 4.f);

    a *= 2;

    std::cout << "\nVEC4 PRODUCT" << std::endl;
    std::cout << "vec4 *= vec4 expected value: (2.0, 4.0, 6.0, 8.0)" << std::endl;
    std::cout << "vec4 *= vec4 actual value: " << a << std::endl;
}

void vec4Quotient() {
    vec4 a = vec4(2.f, 4.f, 6.f, 8.f);

    a /= 2;

    std::cout << "\nVEC4 QUOTIENT" << std::endl;
    std::cout << "vec4 /= vec4 expected value: (1.0, 2.0, 3.0, 4.0)" << std::endl;
    std::cout << "vec4 /= vec4 actual value: " << a << std::endl;
}

void vec4Sub() {
    vec4 b = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 a = vec4(2.f, 4.f, 6.f, 8.f);

    std::cout << "\nVEC4 SUB" << std::endl;
    std::cout << "vec4 - vec4 expected value: (1.0, 2.0, 3.0, 4.0)" << std::endl;
    std::cout << "vec4 - vec4 actual value: " << (a - b) << std::endl;
}

void vec4Mult() {
    vec4 a = vec4(1.f, 2.f, 3.f, 4.f);

    std::cout << "\nVEC4 MULT" << std::endl;
    std::cout << "vec4 * vec4 expected value: (2.0, 4.0, 6.0, 8.0)" << std::endl;
    std::cout << "vec4 * vec4 actual value: " << (a * 2) << std::endl;
}

void vec4Div() {
    vec4 a = vec4(2.f, 4.f, 6.f, 8.f);

    std::cout << "\nVEC4 DIV" << std::endl;
    std::cout << "vec4 / vec4 expected value: (1.0, 2.0, 3.0, 4.0)" << std::endl;
    std::cout << "vec4 / vec4 actual value: " << (a / 2) << std::endl;
}

void vec4DivZero() {
    vec4 a = vec4(2.f, 4.f, 6.f, 8.f);

    std::cout << "\nVEC4 DIV ZERO" << std::endl;
    std::cout << "vec4 / vec4 expected value: (NaN, NaN, NaN, NaN)" << std::endl;
    std::cout << "vec4 / vec4 actual value: " << (a / 0) << std::endl;
}

void vec4DivZeroZero() {
    vec4 a = vec4();

    std::cout << "\nVEC4 DIV ZERO / ZERO" << std::endl;
    std::cout << "vec4 / vec4 expected value: (NaN, NaN, NaN, NaN)" << std::endl;
    std::cout << "vec4 / vec4 actual value: " << (a / 0) << std::endl;
}


void vec4Dot() {
    vec4 a = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 b = vec4(5.f, 6.f, 7.f, 8.f);

    std::cout << "\nVEC4 DOT" << std::endl;
    std::cout << "dot(vec4, vec4) expected value: 70.0" << std::endl;
    std::cout << "dot(vec4, vec4) actual value: " << dot(a, b) << std::endl;
}

void vec4Cross() {
    vec4 a = vec4(1.f, 2.f, 3.f, 0.f);
    vec4 b = vec4(4.f, 5.f, 6.f, 0.f);

    std::cout << "\nVEC4 CROSS" << std::endl;
    std::cout << "cross(vec4, vec4) expected value: (-3.0, 6.0, -3.0, 0.0)" << std::endl;
    std::cout << "cross(vec4, vec4) actual value: " << cross(a, b) << std::endl;
}

void vec4CrossNotZero() {
    vec4 a = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 b = vec4(4.f, 5.f, 6.f, 7.f);

    std::cout << "\nVEC4 CROSS 4D NOT ZERO" << std::endl;
    std::cout << "cross(vec4, vec4) expected value: (-3.0, 6.0, -3.0, 0.0)" << std::endl;
    std::cout << "cross(vec4, vec4) actual value: " << cross(a, b) << std::endl;
}

void vec4Length() {
    vec4 a = vec4(1.f, 2.f, 3.f, 4.f);

    std::cout << "\nVEC4 LENGTH" << std::endl;
    std::cout << "length(vec4) expected value: 5.5" << std::endl;
    std::cout << "length(vec4) actual value: " << length(a) << std::endl;
}

void vec4Scalar() {
    vec4 a = vec4(1.f, 2.f, 3.f, 4.f);

    std::cout << "\nVEC4 SCALAR" << std::endl;
    std::cout << "2 * vec4 expected value:  (2.0, 4.0, 6.0, 8.0)" << std::endl;
    std::cout << "2 * vec4 actual value: " << (a * 2) << std::endl;
}

void vec4Normalize() {
    vec4 a = vec4(1.f, 2.f, 3.f, 4.f);

    std::cout << "\nVEC4 NORMALIZE" << std::endl;
    std::cout << "normalize(vec4) expected value:  (0.2, 0.4, 0.5, 0.7)" << std::endl;
    std::cout << "normalize(vec4) actual value: " << normalize(a) << std::endl;
}

void vec4NormalizeZero() {
    vec4 a = vec4();

    std::cout << "\nVEC4 NORMALIZE ZER0" << std::endl;
    std::cout << "normalize(vec4) expected value:  (NaN, NaN, NaN, NaN)" << std::endl;
    std::cout << "normalize(vec4) actual value: " << normalize(a) << std::endl;
}

///----------------------------------------------------------------------
/// MAT4 TESTS
///----------------------------------------------------------------------

void mat4DefaultConstructor() {
    std::cout << "\nMAT4 DEFAULT CONSTRUCTOR" << std::endl;
    std::cout << "mat4() expected value: \n (0.0, 0.0, 0.0, 0.0)"
                                        "\n (0.0, 0.0, 0.0, 0.0)"
                                        "\n (0.0, 0.0, 0.0, 0.0)"
                                        "\n (0.0, 0.0, 0.0, 0.0) \n" << std::endl;
    std::cout << "mat4() actual value: " << mat4() << std::endl;
}

void mat4DiagConstructor() {
    std::cout << "MAT4 DIAG CONSTRUCTOR" << std::endl;
    std::cout << "mat4(diag) expected value: \n (1.0, 0.0, 0.0, 0.0)"
                                           "\n (0.0, 1.0, 0.0, 0.0)"
                                           "\n (0.0, 0.0, 1.0, 0.0)"
                                           "\n (0.0, 0.0, 0.0, 1.0) \n" << std::endl;
    std::cout << "mat4(diag) actual value: " << mat4(1) << std::endl;
}

void mat4ColConstructor() {
    vec4 col0 = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 col1 = vec4(5.f, 6.f, 7.f, 8.f);
    vec4 col2 = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 col3 = vec4(5.f, 6.f, 7.f, 8.f);

    std::cout << "MAT4 COL CONSTRUCTOR" << std::endl;
    std::cout << "mat4(vec4, vec4, vec4, vec4) expected value: \n (1.0, 2.0, 3.0, 4.0)"
                                                              "\n (5.0, 6.0, 7.0, 8.0)"
                                                              "\n (1.0, 2.0, 3.0, 4.0)"
                                                              "\n (5.0, 6.0, 7.0, 8.0) \n" << std::endl;
    std::cout << "mat4(vec4, vec4, vec4, vec4) actual value: " << mat4(col0, col1, col2, col3) << std::endl;
}

void mat4CopyConstructor() {
    mat4 a = mat4(1.f);

    std::cout << "MAT4 COPY CONSTRUCTOR" << std::endl;
    std::cout << "mat4(mat4) expected value: \n (1.0, 0.0, 0.0, 0.0)"
                                            "\n (0.0, 1.0, 0.0, 0.0)"
                                            "\n (0.0, 0.0, 1.0, 0.0)"
                                            "\n (0.0, 0.0, 0.0, 1.0) \n" << std::endl;
    std::cout << "mat4(mat4) actual value: " << mat4(a) << std::endl;
}

void mat4Print() {
    vec4 col0 = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 col1 = vec4(5.f, 6.f, 7.f, 8.f);
    vec4 col2 = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 col3 = vec4(5.f, 6.f, 7.f, 8.f);

    std::cout << "MAT4 PRINT" << std::endl;
    std::cout << "mat4 << expected value: \n (1.0, 2.0, 3.0, 4.0)"
                                         "\n (5.0, 6.0, 7.0, 8.0)"
                                         "\n (1.0, 2.0, 3.0, 4.0)"
                                         "\n (5.0, 6.0, 7.0, 8.0) \n" << std::endl;
    std::cout << "mat4 << actual value: " << mat4(col0, col1, col2, col3) << std::endl;
}

void mat4Getter() {
    vec4 col0 = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 col1 = vec4(5.f, 6.f, 7.f, 8.f);
    vec4 col2 = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 col3 = vec4(5.f, 6.f, 7.f, 8.f);

    mat4 a = mat4(col0, col1, col2, col3);

    std::cout << "MAT4 GETTER" << std::endl;
    std::cout << "mat4[index] expected value: (1.0, 2.0, 3.0, 4.0) \n";
    std::cout << "mat4[index] actual value: " << a[2] << std::endl;
}

void mat4Rotate1() {

    std::cout << "\nMAT4 ROTATE1" << std::endl;
    std::cout << "rotate(angle, x, y , z) expected value: \n (1.0, 0.0, -0.0, 0.0)"
                                                         "\n (-0.0, 1.0, 0.0, 0.0)"
                                                         "\n (0.0, -0.0, 1.0, 0.0)"
                                                         "\n (0.0, 0.0, 0.0, 1.0) \n" << std::endl;
    std::cout << "rotate(angle, x, y , z) actual value: " << mat4 :: rotate(1, 1, 2, 3) << std::endl;
}

void mat4Rotate2() {

    std::cout << "MAT4 ROTATE2" << std::endl;
    std::cout << "rotate(angle, x, y , z) expected value: \n (0.1, 0.9, -0.3, 0.0)"
                                                         "\n (-0.7, 0.3, 0.7, 0.0)"
                                                         "\n (0.7, 0.2, 0.6, 0.0)"
                                                         "\n (0.0, 0.0, 0.0, 1.0) \n" << std::endl;
    std::cout << "rotate(angle, x, y , z) actual value: " << mat4 :: rotate(90, 1, 2, 3) << std::endl;
}


void mat4Rotate3() {

    std::cout << "MAT4 ROTATE3" << std::endl;
    std::cout << "rotate(angle, x, y , z) expected value: \n (0.7, 0.6, -0.3, 0.0)"
                                                         "\n (-0.5, 0.8, 0.3, 0.0)"
                                                         "\n (0.4, -0.1, 0.9, 0.0)"
                                                         "\n (0.0, 0.0, 0.0, 1.0) \n" << std::endl;
    std::cout << "rotate(angle, x, y , z) actual value: " << mat4 :: rotate(45, 5, 10, 15) << std::endl;
}

void mat4Setter() {
    vec4 col0 = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 col1 = vec4(5.f, 6.f, 7.f, 8.f);
    vec4 col2 = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 col3 = vec4(5.f, 6.f, 7.f, 8.f);

    mat4 a = mat4(col0, col1, col2, col3);
    mat4 b = mat4(1.0);

    a = b;

    std::cout << "\nMAT4 SETTER" << std::endl;
    std::cout << "mat4 = mat4 expected value: \n (1.0, 0.0, 0.0, 0.0)"
                                             "\n (0.0, 1.0, 0.0, 0.0)"
                                             "\n (0.0, 0.0, 1.0, 0.0)"
                                             "\n (0.0, 0.0, 0.0, 1.0) \n" << std::endl;
    std::cout << "mat4 = mat4 actual value: " << a << std::endl;
}

void mat4EqualityFalse() {
    vec4 col0 = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 col1 = vec4(5.f, 6.f, 7.f, 8.f);
    vec4 col2 = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 col3 = vec4(5.f, 6.f, 7.f, 8.f);

    mat4 a = mat4(col0, col1, col2, col3);
    mat4 b = mat4(1.0);

    std::cout << "MAT4 EQUALITY FALSE" << std::endl;
    std::cout << "mat4 == mat4 expected value: false" << std::endl;
    std::cout << "mat4 == mat4 actual value: " << (a == b) << std::endl;
}

void mat4EqualityTrue() {
    mat4 a = mat4(1.0);
    mat4 b = mat4(1.0);

    std::cout << "\nMAT4 EQUALITY TRUE" << std::endl;
    std::cout << "mat4 == mat4 expected value: true" << std::endl;
    std::cout << "mat4 == mat4 actual value: " << (a == b) << std::endl;
}

void mat4InequalityTrue() {
    vec4 col0 = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 col1 = vec4(5.f, 6.f, 7.f, 8.f);
    vec4 col2 = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 col3 = vec4(5.f, 6.f, 7.f, 8.f);

    mat4 a = mat4(col0, col1, col2, col3);
    mat4 b = mat4(1.0);

    std::cout << "\nMAT4 INEQUALITY TRUE" << std::endl;
    std::cout << "mat4 != mat4 expected value: true" << std::endl;
    std::cout << "mat4 != mat4 actual value: " << (a != b) << std::endl;
}

void mat4InequalityFalse() {
    mat4 a = mat4(1.0);
    mat4 b = mat4(1.0);

    std::cout << "\nMAT4 INEQUALITY FALSE" << std::endl;
    std::cout << "mat4 != mat4 expected value: false" << std::endl;
    std::cout << "mat4 != mat4 actual value: " << (a != b) << std::endl;
}

void mat4MatMatMult() {
    vec4 col0a = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 col1a = vec4(5.f, 6.f, 7.f, 8.f);
    vec4 col2a = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 col3a = vec4(5.f, 6.f, 7.f, 8.f);

    vec4 col0b = vec4(1.f, 0.f, 0.f, 0.f);
    vec4 col1b = vec4(0.f, 2.f, 0.f, 0.f);
    vec4 col2b = vec4(0.f, 0.f, 3.f, 0.f);
    vec4 col3b = vec4(0.f, 0.f, 0.f, 4.f);

    mat4 a = mat4(col0a, col1a, col2a, col3a);
    mat4 b = mat4(col0b, col1b, col2b, col3b);

    std::cout << "\nMAT4 MATRIX MATRIX MULT" << std::endl;
    std::cout << "mat4 * mat4 expected value:  \n (1.0, 10.0, 3.0, 20.0)"
                                              "\n (2.0, 12.0, 6.0, 24.0)"
                                              "\n (3.0, 14.0, 9.0, 28.0)"
                                              "\n (4.0, 16.0, 12.0, 32.0) \n" << std::endl;
    std::cout << "mat4 * mat4 actual value: " << (a * b) << std::endl;
}

void mat4MatVecMult() {
    vec4 col0 = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 col1 = vec4(0.f, 1.f, 0.f, 0.f);
    vec4 col2 = vec4(0.f, 0.f, 1.f, 0.f);
    vec4 col3 = vec4(0.f, 0.f, 0.f, 1.f);

    vec4 vec = vec4(1.f, 2.f, 3.f, 4.f);

    mat4 a = mat4(col0, col1, col2, col3);

    std::cout << "MAT4 MATRIX VEC MULT" << std::endl;
    std::cout << "mat4 * vec4 expected value:  (1.0, 4.0, 6.0, 8.0)" << std::endl;
    std::cout << "mat4 * vec4 actual value: " << (a * vec) << std::endl;
}

void mat4VecMatMult() {
    vec4 col0 = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 col1 = vec4(0.f, 1.f, 0.f, 0.f);
    vec4 col2 = vec4(0.f, 0.f, 1.f, 0.f);
    vec4 col3 = vec4(0.f, 0.f, 0.f, 1.f);

    mat4 a = mat4(col0, col1, col2, col3);
    vec4 b = vec4(1, 2, 3, 4);

    std::cout << "\nMAT4 VEC MATRIX MULT" << std::endl;
    std::cout << "vec4 * mat4 expected value:  (30.0, 2.0, 3.0, 4.0)" << std::endl;
    std::cout << "vec4 * mat4 actual value: " << (b * a) << std::endl;
}

void mat4Scalar() {
    vec4 col0 = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 col1 = vec4(5.f, 6.f, 7.f, 8.f);
    vec4 col2 = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 col3 = vec4(5.f, 6.f, 7.f, 8.f);

    mat4 a = mat4(col0, col1, col2, col3);

    std::cout << "\nMAT4 SCALAR" << std::endl;
    std::cout << "c * mat4 expected value:  \n (2.0, 4.0, 6.0, 8.0)"
                                           "\n (10.0, 12.0, 14.0, 16.0)"
                                           "\n (2.0, 4.0, 6.0, 8.0)"
                                           "\n (10.0, 12.0, 14.0, 16.0) \n" << std::endl;
    std::cout << "c * mat4 actual value: " << a * 2 << std::endl;
}

void mat4Row() {
    vec4 col0 = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 col1 = vec4(5.f, 6.f, 7.f, 8.f);
    vec4 col2 = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 col3 = vec4(5.f, 6.f, 7.f, 8.f);

    mat4 a = mat4(col0, col1, col2, col3);

    std::cout << "MAT4 ROW" << std::endl;
    std::cout << "row (mat4, index) expected value:  (2.0, 6.0, 2.0, 6.0)" << std::endl;
    std::cout << "row (mat4, index) actual value: " << row(a, 1) << std::endl;
}

void mat4Transpose() {
    vec4 col0 = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 col1 = vec4(5.f, 6.f, 7.f, 8.f);
    vec4 col2 = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 col3 = vec4(5.f, 6.f, 7.f, 8.f);

    mat4 a = mat4(col0, col1, col2, col3);

    std::cout << "\nMAT4 TRANSPOSE" << std::endl;
    std::cout << "transpose (mat4) expected value:  \n (1.0, 5.0, 1.0, 5.0)"
                                                   "\n (2.0, 6.0, 2.0, 6.0)"
                                                   "\n (3.0, 7.0, 3.0, 7.0)"
                                                   "\n (4.0, 8.0, 4.0, 8.0) \n" << std::endl;
    std::cout << "transpose (mat4) actual value: " << transpose(a) << std::endl;
}

void mat4Add() {
    vec4 col0a = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 col1a = vec4(5.f, 6.f, 7.f, 8.f);
    vec4 col2a = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 col3a = vec4(5.f, 6.f, 7.f, 8.f);

    vec4 col0b = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 col1b = vec4(5.f, 6.f, 7.f, 8.f);
    vec4 col2b = vec4(1.f, 2.f, 3.f, 4.f);
    vec4 col3b = vec4(5.f, 6.f, 7.f, 8.f);

    mat4 a = mat4(col0a, col1a, col2a, col3a);
    mat4 b = mat4(col0b, col1b, col2b, col3b);

    std::cout << "\nMAT4 ADD" << std::endl;
    std::cout << "mat4 + mat4 expected value:  \n (2.0, 4.0, 6.0, 8.0)"
                                              "\n (10.0, 12.0, 14.0, 16.0)"
                                              "\n (2.0, 4.0, 6.0, 8.0)"
                                              "\n (10.0, 12.0, 14.0, 16.0) \n" << std::endl;
    std::cout << "mat4 + mat4 actual value: " << a + b << std::endl;
}

void mat4Divide() {
    vec4 col0 = vec4(2.f, 2.f, 2.f, 4.f);
    vec4 col1 = vec4(2.f, 2.f, 2.f, 4.f);
    vec4 col2 = vec4(2.f, 2.f, 2.f, 4.f);
    vec4 col3 = vec4(2.f, 2.f, 2.f, 4.f);

    mat4 a = mat4(col0, col1, col2, col3);

    std::cout << "\nMAT4 DIVIDE" << std::endl;
    std::cout << "mat4 + mat4 expected value:  \n (1.0, 1.0, 1.0, 2.0)"
                                              "\n (1.0, 1.0, 1.0, 2.0)"
                                              "\n (1.0, 1.0, 1.0, 2.0)"
                                              "\n (1.0, 1.0, 1.0, 2.0) \n" << std::endl;
    std::cout << "mat4 + mat4 actual value: " << (a / 2) << std::endl;
}

void mat4DivideZero() {
    vec4 col0 = vec4(2.f, 2.f, 2.f, 4.f);
    vec4 col1 = vec4(2.f, 2.f, 2.f, 4.f);
    vec4 col2 = vec4(2.f, 2.f, 2.f, 4.f);
    vec4 col3 = vec4(2.f, 2.f, 2.f, 4.f);

    mat4 a = mat4(col0, col1, col2, col3);

    std::cout << "\nMAT4 DIVIDE ZERO" << std::endl;
    std::cout << "mat4 + mat4 expected value:  \n (NaN, NaN, NaN, NaN)"
                                              "\n (NaN, NaN, NaN, NaN)"
                                              "\n (NaN, NaN, NaN, NaN)"
                                              "\n (NaN, NaN, NaN, NaN) \n" << std::endl;
    std::cout << "mat4 + mat4 actual value: " << (a / 0) << std::endl;
}


void mat4Translate() {
    std::cout << "\nMAT4 TRANSLATE" << std::endl;
    std::cout << "translate(x, y, z) expected value:  \n (1.0, 0.0, 0.0, 2.0)"
                                                     "\n (1.0, 1.0, 0.0, 3.0)"
                                                     "\n (0.0, 0.0, 1.0, 4.0)"
                                                     "\n (0.0, 0.0, 0.0, 1.0) \n" << std::endl;
    std::cout << "translate(x, y, z) actual value: " << mat4::translate(2, 3, 4) << std::endl;
}


void mat4Scale() {
    std::cout << "\nMAT4 SCALE" << std::endl;
    std::cout << "scale(x, y, z) expected value:  \n (1.0, 0.0, 0.0, 0.0)"
                                                 "\n (0.0, 2.0, 0.0, 0.0)"
                                                 "\n (0.0, 0.0, 3.0, 0.0)"
                                                 "\n (0.0, 0.0, 0.0, 1.0) \n" << std::endl;
    std::cout << "scale(x, y, z) actual value: " << mat4::scale(1, 2, 3) << std::endl;
}

void mat4Identity() {
    std::cout << "\nMAT4 IDENTITY" << std::endl;
    std::cout << "identity() expected value:  \n (1.0, 0.0, 0.0, 0.0)"
                                             "\n (0.0, 1.0, 0.0, 0.0)"
                                             "\n (0.0, 0.0, 1.0, 0.0)"
                                             "\n (0.0, 0.0, 0.0, 1.0) \n" << std::endl;
    std::cout << "identity() actual value: " << mat4::identity() << std::endl;
}


int main() {

    ///----------------------------------------------------------------------
    /// VEC4 TESTS
    ///----------------------------------------------------------------------


    // Example test (won't work until you implement vec4's operator+ and operator<<)
    vec4AddTest();
    // Add your own tests here
    vec4ValAtIndexTest();

    vec4PrintTest();

    // Constructors
    vec4DefaultConstructor();
    vec4Constructor();
    vec4CopyConstructor();

    vec4Set(); // =
    vec4EqualityTrue();
    vec4EqualityFalse();
    vec4InequalityTrue();
    vec4InequalityFalse();
    vec4Sum(); // +=
    vec4Diff(); // -=
    vec4Product(); // *=
    vec4Quotient(); // /=
    vec4Sub();
    vec4Mult();
    vec4Div();
    vec4DivZero();
    vec4DivZeroZero();

    vec4Dot();
    vec4Cross();
    vec4CrossNotZero();

    vec4Length();
    vec4Scalar();
    vec4Normalize();
    vec4NormalizeZero();

    ///----------------------------------------------------------------------
    /// MAT4 TESTS
    ///----------------------------------------------------------------------

    mat4DefaultConstructor();
    mat4DiagConstructor();
    mat4ColConstructor();
    mat4CopyConstructor();

    mat4Print();

    mat4Getter();
    mat4Setter();

    mat4Rotate1();
    mat4Rotate2();
    mat4Rotate3();

    mat4EqualityFalse();
    mat4EqualityTrue();
    mat4InequalityTrue();
    mat4InequalityFalse();

    mat4MatMatMult();
    mat4MatVecMult();
    mat4VecMatMult();

    mat4Scalar();
    mat4Row();
    mat4Transpose();

    mat4Add();
    mat4Divide();
    mat4DivideZero();

    mat4Translate();
    mat4Scale();
    mat4Identity();
}

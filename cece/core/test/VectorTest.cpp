/* ************************************************************************ */
/* Georgiev Lab (c) 2015-2016                                               */
/* ************************************************************************ */
/* Department of Cybernetics                                                */
/* Faculty of Applied Sciences                                              */
/* University of West Bohemia in Pilsen                                     */
/* ************************************************************************ */
/*                                                                          */
/* This file is part of CeCe.                                               */
/*                                                                          */
/* CeCe is free software: you can redistribute it and/or modify             */
/* it under the terms of the GNU General Public License as published by     */
/* the Free Software Foundation, either version 3 of the License, or        */
/* (at your option) any later version.                                      */
/*                                                                          */
/* CeCe is distributed in the hope that it will be useful,                  */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of           */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            */
/* GNU General Public License for more details.                             */
/*                                                                          */
/* You should have received a copy of the GNU General Public License        */
/* along with CeCe.  If not, see <http://www.gnu.org/licenses/>.            */
/*                                                                          */
/* ************************************************************************ */

// GTest
#include <gtest/gtest.h>

// C++
#include <sstream>
#include <complex>

// CeCe
#include "cece/core/Vector.hpp"

/* ************************************************************************ */

using namespace cece;

/* ************************************************************************ */

TEST(VectorTest, zero)
{
    const Vector<float> vec{Zero};

    EXPECT_FLOAT_EQ(0.f, vec.getX());
    EXPECT_FLOAT_EQ(0.f, vec.getY());
}

/* ************************************************************************ */

TEST(VectorTest, accessors)
{
    const Vector<float> vec{2.f, 3.f};

    EXPECT_FLOAT_EQ(2.f, vec.getX());
    EXPECT_FLOAT_EQ(3.f, vec.getY());
}

/* ************************************************************************ */

TEST(VectorTest, comparisonOperators)
{
    const Vector<float> v1{10.f, 50.f};
    const Vector<float> v2{60.f, 30.f};
    const Vector<float> v3{10.f, 50.f};
    const Vector<float> v4{10.f, 80.f};
    const Vector<float> v5{10.f, 10.f};

    // Same vectors
    EXPECT_TRUE(v1 == v1);
    EXPECT_TRUE(v2 == v2);
    EXPECT_TRUE(v3 == v3);
    EXPECT_TRUE(v4 == v4);
    EXPECT_TRUE(v5 == v5);

    // Same vector values
    EXPECT_TRUE(v1 == v3);
    EXPECT_TRUE(v3 == v1);

    // Different vectors
    EXPECT_TRUE(v1 != v2);
    EXPECT_TRUE(v2 != v1);
    EXPECT_TRUE(v2 != v3);
    EXPECT_TRUE(v3 != v2);
    EXPECT_TRUE(v4 != v1);
    EXPECT_TRUE(v4 != v2);
    EXPECT_TRUE(v4 != v3);
    EXPECT_TRUE(v4 != v5);
}

/* ************************************************************************ */

TEST(VectorTest, addition)
{
    const Vector<float> v1{6.2f, 3.3f};
    const Vector<float> v2{1.4f, 0.9f};

    const auto vRes0 = v1 + v2;

    EXPECT_FLOAT_EQ(7.6f, vRes0.getX());
    EXPECT_FLOAT_EQ(4.2f, vRes0.getY());

    const auto vRes1 = v2 + v1;

    EXPECT_FLOAT_EQ(7.6f, vRes1.getX());
    EXPECT_FLOAT_EQ(4.2f, vRes1.getY());
}

/* ************************************************************************ */

TEST(VectorTest, substraction)
{
    const Vector<float> v1{6.2f, 3.3f};
    const Vector<float> v2{1.4f, 0.9f};

    const auto vRes0 = v1 - v2;

    EXPECT_FLOAT_EQ(4.8f, vRes0.getX());
    EXPECT_FLOAT_EQ(2.4f, vRes0.getY());

    const auto vRes1 = v2 - v1;

    EXPECT_FLOAT_EQ(-4.8f, vRes1.getX());
    EXPECT_FLOAT_EQ(-2.4f, vRes1.getY());
}

/* ************************************************************************ */

TEST(VectorTest, multiplication)
{
    const Vector<float> v1{6.2f, 3.3f};
    const Vector<float> v2{1.4f, 0.9f};

    const auto vRes0 = v1 * v2;

    EXPECT_FLOAT_EQ( 8.68f, vRes0.getX());
    EXPECT_FLOAT_EQ( 2.97f, vRes0.getY());

    const auto vRes1 = v1 * 2.2f;

    EXPECT_FLOAT_EQ(13.64f, vRes1.getX());
    EXPECT_FLOAT_EQ( 7.26f, vRes1.getY());

    const auto vRes2 = 5.1f * v2;

    EXPECT_FLOAT_EQ( 7.14f, vRes2.getX());
    EXPECT_FLOAT_EQ( 4.59f, vRes2.getY());
}

/* ************************************************************************ */

TEST(VectorTest, division)
{
    const Vector<float> v1{6.2f, 3.3f};
    const Vector<float> v2{1.4f, 0.9f};

    const auto vRes0 = v1 / v2;

    EXPECT_FLOAT_EQ(4.428571429f, vRes0.getX());
    EXPECT_FLOAT_EQ(3.666666667f, vRes0.getY());
}

/* ************************************************************************ */

TEST(VectorTest, dot)
{
    const Vector<float> v1{ 0.f,  5.f};
    const Vector<float> v2{10.f,  0.f};
    const Vector<float> v3{ 5.f,  5.f};
    const Vector<float> v4{ 1.f,  1.f};
    const Vector<float> v5{ 2.f, -2.f};

    EXPECT_FLOAT_EQ( 0.f, v1.dot(v2));
    EXPECT_FLOAT_EQ(50.f, v2.dot(v3));
    EXPECT_FLOAT_EQ( 0.f, v4.dot(v5));
}

/* ************************************************************************ */

TEST(VectorTest, lengthSquared)
{
    const Vector<float> v1{Zero};
    const Vector<float> v2{1.f, 1.f};
    const Vector<float> v3{2.f, 4.f};
    const Vector<float> v4{3.f, 8.f};

    EXPECT_FLOAT_EQ(0.f, v1.getLengthSquared());
    EXPECT_FLOAT_EQ(2.f, v2.getLengthSquared());
    EXPECT_FLOAT_EQ(20.f, v3.getLengthSquared());
    EXPECT_FLOAT_EQ(73.f, v4.getLengthSquared());
}

/* ************************************************************************ */

TEST(VectorTest, length)
{
    const Vector<float> v1{Zero};
    const Vector<float> v2{1.f, 1.f};
    const Vector<float> v3{2.f, 4.f};
    const Vector<float> v4{3.f, 8.f};

    EXPECT_FLOAT_EQ(0.f, v1.getLength());
    EXPECT_FLOAT_EQ(1.414213562f, v2.getLength());
    EXPECT_FLOAT_EQ(4.472135955f, v3.getLength());
    EXPECT_FLOAT_EQ(8.544003745f, v4.getLength());
}

/* ************************************************************************ */

TEST(VectorTest, istream)
{
    {
        std::istringstream is("10 20");

        Vector<int> vec;
        is >> vec;

        EXPECT_EQ(10.f, vec.getX());
        EXPECT_EQ(20.f, vec.getY());
    }

    {
        std::istringstream is("0.3 1.1");

        Vector<float> vec;
        is >> vec;

        EXPECT_FLOAT_EQ(0.3f, vec.getX());
        EXPECT_FLOAT_EQ(1.1f, vec.getY());
    }

    {
        std::istringstream is("(10,15) (90)");

        Vector<std::complex<float>> vec;
        is >> vec;

        EXPECT_EQ(std::complex<float>(10.f, 15.f), vec.getX());
        EXPECT_EQ(std::complex<float>(90.f), vec.getY());
    }

    {
        std::istringstream is("10");

        Vector<int> vec;
        is >> vec;

        EXPECT_EQ(10.f, vec.getX());
        EXPECT_EQ(10.f, vec.getY());
    }

    {
        std::istringstream is("0.5");

        Vector<float> vec;
        is >> vec;

        EXPECT_FLOAT_EQ(0.5f, vec.getX());
        EXPECT_FLOAT_EQ(0.5f, vec.getY());
    }

}

/* ************************************************************************ */

TEST(VectorTest, ostream)
{
    //Vector
}

/* ************************************************************************ */

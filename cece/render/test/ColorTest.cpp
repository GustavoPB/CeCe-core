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

// CeCe
#include "cece/core/StringStream.hpp"
#include "cece/render/Color.hpp"

/* ************************************************************************ */

using namespace cece;
using namespace cece::render;

/* ************************************************************************ */

TEST(ColorTest, parse)
{
    {
        InStringStream iss("#FFFFFF");
        Color color;
        iss >> color;

        EXPECT_FLOAT_EQ(1.f, color.getRed());
        EXPECT_FLOAT_EQ(1.f, color.getGreen());
        EXPECT_FLOAT_EQ(1.f, color.getBlue());
        EXPECT_FLOAT_EQ(1.f, color.getAlpha());
    }

    {
        InStringStream iss("#000000");
        Color color;
        iss >> color;

        EXPECT_FLOAT_EQ(0.f, color.getRed());
        EXPECT_FLOAT_EQ(0.f, color.getGreen());
        EXPECT_FLOAT_EQ(0.f, color.getBlue());
        EXPECT_FLOAT_EQ(1.f, color.getAlpha());
    }


    {
        InStringStream iss("#FF0000");
        Color color;
        iss >> color;

        EXPECT_FLOAT_EQ(1.f, color.getRed());
        EXPECT_FLOAT_EQ(0.f, color.getGreen());
        EXPECT_FLOAT_EQ(0.f, color.getBlue());
        EXPECT_FLOAT_EQ(1.f, color.getAlpha());
    }


    {
        InStringStream iss("#00FF00");
        Color color;
        iss >> color;

        EXPECT_FLOAT_EQ(0.f, color.getRed());
        EXPECT_FLOAT_EQ(1.f, color.getGreen());
        EXPECT_FLOAT_EQ(0.f, color.getBlue());
        EXPECT_FLOAT_EQ(1.f, color.getAlpha());
    }


    {
        InStringStream iss("#0000FF");
        Color color;
        iss >> color;

        EXPECT_FLOAT_EQ(0.f, color.getRed());
        EXPECT_FLOAT_EQ(0.f, color.getGreen());
        EXPECT_FLOAT_EQ(1.f, color.getBlue());
        EXPECT_FLOAT_EQ(1.f, color.getAlpha());
    }


    {
        InStringStream iss("#00000000");
        Color color;
        iss >> color;

        EXPECT_FLOAT_EQ(0.f, color.getRed());
        EXPECT_FLOAT_EQ(0.f, color.getGreen());
        EXPECT_FLOAT_EQ(0.f, color.getBlue());
        EXPECT_FLOAT_EQ(0.f, color.getAlpha());
    }


    {
        InStringStream iss("#FFFFFF00");
        Color color;
        iss >> color;

        EXPECT_FLOAT_EQ(1.f, color.getRed());
        EXPECT_FLOAT_EQ(1.f, color.getGreen());
        EXPECT_FLOAT_EQ(1.f, color.getBlue());
        EXPECT_FLOAT_EQ(0.f, color.getAlpha());
    }
}

/* ************************************************************************ */

TEST(ColorTest, parseNamed)
{
    {
        InStringStream iss("white");
        Color color;
        iss >> color;

        EXPECT_FLOAT_EQ(1.f, color.getRed());
        EXPECT_FLOAT_EQ(1.f, color.getGreen());
        EXPECT_FLOAT_EQ(1.f, color.getBlue());
        EXPECT_FLOAT_EQ(1.f, color.getAlpha());
    }

    {
        InStringStream iss("black");
        Color color;
        iss >> color;

        EXPECT_FLOAT_EQ(0.f, color.getRed());
        EXPECT_FLOAT_EQ(0.f, color.getGreen());
        EXPECT_FLOAT_EQ(0.f, color.getBlue());
        EXPECT_FLOAT_EQ(1.f, color.getAlpha());
    }

    {
        InStringStream iss("red");
        Color color;
        iss >> color;

        EXPECT_FLOAT_EQ(1.f, color.getRed());
        EXPECT_FLOAT_EQ(0.f, color.getGreen());
        EXPECT_FLOAT_EQ(0.f, color.getBlue());
        EXPECT_FLOAT_EQ(1.f, color.getAlpha());
    }

    {
        InStringStream iss("green");
        Color color;
        iss >> color;

        EXPECT_FLOAT_EQ(0.f, color.getRed());
        EXPECT_FLOAT_EQ(1.f, color.getGreen());
        EXPECT_FLOAT_EQ(0.f, color.getBlue());
        EXPECT_FLOAT_EQ(1.f, color.getAlpha());
    }

    {
        InStringStream iss("blue");
        Color color;
        iss >> color;

        EXPECT_FLOAT_EQ(0.f, color.getRed());
        EXPECT_FLOAT_EQ(0.f, color.getGreen());
        EXPECT_FLOAT_EQ(1.f, color.getBlue());
        EXPECT_FLOAT_EQ(1.f, color.getAlpha());
    }

    {
        InStringStream iss("yellow");
        Color color;
        iss >> color;

        EXPECT_FLOAT_EQ(1.f, color.getRed());
        EXPECT_FLOAT_EQ(1.f, color.getGreen());
        EXPECT_FLOAT_EQ(0.f, color.getBlue());
        EXPECT_FLOAT_EQ(1.f, color.getAlpha());
    }

    {
        InStringStream iss("cyan");
        Color color;
        iss >> color;

        EXPECT_FLOAT_EQ(0.f, color.getRed());
        EXPECT_FLOAT_EQ(1.f, color.getGreen());
        EXPECT_FLOAT_EQ(1.f, color.getBlue());
        EXPECT_FLOAT_EQ(1.f, color.getAlpha());
    }

    {
        InStringStream iss("magenta");
        Color color;
        iss >> color;

        EXPECT_FLOAT_EQ(1.f, color.getRed());
        EXPECT_FLOAT_EQ(0.f, color.getGreen());
        EXPECT_FLOAT_EQ(1.f, color.getBlue());
        EXPECT_FLOAT_EQ(1.f, color.getAlpha());
    }
}

/* ************************************************************************ */

TEST(ColorTest, printHex)
{
    {
        OutStringStream oss;
        Color color = Color::fromUchar(0xFF, 0xFF, 0xF0);
        oss << color;

        EXPECT_EQ("#FFFFF0FF", oss.str());
    }


    {
        OutStringStream oss;
        Color color = Color::fromUchar(0xA0, 0x08, 0xFB, 0x38);
        oss << color;

        EXPECT_EQ("#A008FB38", oss.str());
    }
}

/* ************************************************************************ */

TEST(ColorTest, printNamed)
{
    {
        OutStringStream oss;
        Color color = colors::WHITE;
        oss << color;

        EXPECT_EQ("white", oss.str());
    }

    {
        OutStringStream oss;
        Color color = colors::BLACK;
        oss << color;

        EXPECT_EQ("black", oss.str());
    }

    {
        OutStringStream oss;
        Color color = colors::RED;
        oss << color;

        EXPECT_EQ("red", oss.str());
    }

    {
        OutStringStream oss;
        Color color = colors::GREEN;
        oss << color;

        EXPECT_EQ("green", oss.str());
    }

    {
        OutStringStream oss;
        Color color = colors::BLUE;
        oss << color;

        EXPECT_EQ("blue", oss.str());
    }

    {
        OutStringStream oss;
        Color color = colors::YELLOW;
        oss << color;

        EXPECT_EQ("yellow", oss.str());
    }

    {
        OutStringStream oss;
        Color color = colors::CYAN;
        oss << color;

        EXPECT_EQ("cyan", oss.str());
    }

    {
        OutStringStream oss;
        Color color = colors::MAGENTA;
        oss << color;

        EXPECT_EQ("magenta", oss.str());
    }
}

/* ************************************************************************ */

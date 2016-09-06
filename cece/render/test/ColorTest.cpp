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

        EXPECT_EQ(1.f, color.getRed());
        EXPECT_EQ(1.f, color.getGreen());
        EXPECT_EQ(1.f, color.getBlue());
        EXPECT_EQ(1.f, color.getAlpha());
    }

    {
        InStringStream iss("#000000");
        Color color;
        iss >> color;

        EXPECT_EQ(0.f, color.getRed());
        EXPECT_EQ(0.f, color.getGreen());
        EXPECT_EQ(0.f, color.getBlue());
        EXPECT_EQ(0.f, color.getAlpha());
    }
}

/* ************************************************************************ */

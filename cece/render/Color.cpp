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

// Declaration
#include "cece/render/Color.hpp"

// CeCe
#include "cece/core/Assert.hpp"
#include "cece/core/String.hpp"
#include "cece/core/Map.hpp"
#include "cece/core/Exception.hpp"

/* ************************************************************************ */

namespace cece {
namespace render {

/* ************************************************************************ */

namespace {

/* ************************************************************************ */

// Predefined colors
const Map<String, render::Color> g_colors{{
    {"transparent", render::colors::TRANSPARENT},
    {"black", render::colors::BLACK},
    {"white", render::colors::WHITE},
    {"red", render::colors::RED},
    {"green", render::colors::GREEN},
    {"blue", render::colors::BLUE},
    {"yellow", render::colors::YELLOW},
    {"cyan", render::colors::CYAN},
    {"magenta", render::colors::MAGENTA}
}};

/* ************************************************************************ */

/**
 * Convert hex character to number.
 * @param  c Hex character.
 * @return Hex number.
 */
int convertHex(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';

    if (c >= 'A' && c <= 'F')
        return 10 + c - 'A';

    if (c >= 'a' && c <= 'f')
        return 10 + c - 'a';

    throw InvalidArgumentException("Invalid HEX character");
}

/* ************************************************************************ */

/**
 * Parse 2 first characters from string.
 * @param  str Source string.
 * @return Parsed number.
 */
int parseHex(const char* str)
{
    CECE_ASSERT(str);
    CECE_ASSERT(*str);
    CECE_ASSERT(*(str + 1));

    return
        16 * convertHex(*str) +
        convertHex(*(str + 1));
    ;
}

/* ************************************************************************ */

}

/* ************************************************************************ */

InStream& operator>>(InStream& is, Color& color)
{
    String str;
    is >> str;

    if (str.empty())
        throw InvalidArgumentException("Empty color value");

    // Find color by name
    auto it = g_colors.find(str);
    if (it != g_colors.end())
    {
        color = it->second;
        return is;
    }

    if (str[0] != '#')
        throw InvalidArgumentException("Invalid color value");

    // Extract components
    const int red   = parseHex(str.c_str() + 1);
    const int green = parseHex(str.c_str() + 3);
    const int blue  = parseHex(str.c_str() + 5);
    int alpha = 255;

    if (str.size() >= 9)
        alpha = parseHex(str.c_str() + 7);

    // Create color
    color = Color::fromUchar(red, green, blue, alpha);

    return is;
}

/* ************************************************************************ */

OutStream& operator<<(OutStream& os, const Color& color) noexcept
{
    // Store predefined color
    for (const auto& p : g_colors)
    {
        if (p.second == color)
            return os << p.first;
    }

    static constexpr char HEX[] = "0123456789ABCDEF";

    const int red   = color.getRed()   * 255;
    const int green = color.getGreen() * 255;
    const int blue  = color.getBlue()  * 255;
    const int alpha = color.getAlpha() * 255;

    os << '#';
    os << HEX[(red   >> 4) & 0x0F] << HEX[red   & 0x0F];
    os << HEX[(green >> 4) & 0x0F] << HEX[green & 0x0F];
    os << HEX[(blue  >> 4) & 0x0F] << HEX[blue  & 0x0F];
    os << HEX[(alpha >> 4) & 0x0F] << HEX[alpha & 0x0F];

    return os;
}

/* ************************************************************************ */

}
}

/* ************************************************************************ */

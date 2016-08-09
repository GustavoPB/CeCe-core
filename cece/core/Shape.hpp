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

#pragma once

/* ************************************************************************ */

// CeCe
#include "cece/core/Units.hpp"
#include "cece/core/VectorUnits.hpp"
#include "cece/core/DynamicArray.hpp"

/* ************************************************************************ */

namespace cece {
inline namespace core {

/* ************************************************************************ */

/**
 * @brief Shape types.
 */
enum class ShapeType
{
    Undefined   = 0,
    Circle      = 1,
    Rectangle   = 2,
    Edges       = 3
};

/* ************************************************************************ */

/**
 * @brief Structure for circle shape.
 */
struct ShapeUndefined {};

/* ************************************************************************ */

/**
 * @brief Structure for circle shape.
 */
struct ShapeCircle
{
    /// Shape center.
    units::PositionVector center;

    /// Circle radius.
    units::Length radius;
};

/* ************************************************************************ */

/**
 * @brief Structure for rectangle shape.
 */
struct ShapeRectangle
{
    /// Shape center.
    units::PositionVector center;

    /// Rectangle size.
    units::SizeVector size;
};

/* ************************************************************************ */

/**
 * @brief Structure for edge chain shape.
 */
struct ShapeEdges
{
    /// Shape center.
    units::PositionVector center;

    /// List of edges.
    DynamicArray<units::PositionVector> edges;
};

/* ************************************************************************ */

/**
 * @brief Structure for storing shape.
 */
class Shape
{

// Public Ctors & Dtors
public:


    /**
     * @brief Default constructor.
     */
    Shape()
    {
        // Nothing to do
    }


    /**
     * @brief Constructor.
     *
     * @param circle
     */
    Shape(ShapeCircle circle)
        : m_type(ShapeType::Circle)
        , m_circle(std::move(circle))
    {
        // Nothing to do
    }


    /**
     * @brief Constructor.
     *
     * @param rectangle
     */
    Shape(ShapeRectangle rectangle)
        : m_type(ShapeType::Rectangle)
        , m_rectangle(std::move(rectangle))
    {
        // Nothing to do
    }


    /**
     * @brief Constructor.
     *
     * @param edges
     */
    Shape(ShapeEdges edges)
        : m_type(ShapeType::Edges)
        , m_edges(std::move(edges))
    {
        // Nothing to do
    }


// Public Accessors
public:


    /**
     * @brief Get shape type.
     *
     * @return
     */
    ShapeType getType() const noexcept
    {
        return m_type;
    }


    /**
     * @brief Get circle shape.
     *
     * @return
     */
    ShapeCircle& getCircle() noexcept
    {
        return m_circle;
    }


    /**
     * @brief Get circle shape.
     *
     * @return
     */
    const ShapeCircle& getCircle() const noexcept
    {
        return m_circle;
    }


    /**
     * @brief Get rectangle shape.
     *
     * @return
     */
    ShapeRectangle& getRectangle() noexcept
    {
        return m_rectangle;
    }


    /**
     * @brief Get rectangle shape.
     *
     * @return
     */
    const ShapeRectangle& getRectangle() const noexcept
    {
        return m_rectangle;
    }


    /**
     * @brief Get edges shape.
     *
     * @return
     */
    ShapeEdges& getEdges() noexcept
    {
        return m_edges;
    }


    /**
     * @brief Get edges shape.
     *
     * @return
     */
    const ShapeEdges& getEdges() const noexcept
    {
        return m_edges;
    }


// Public Operations
public:


    /**
     * @brief Create undefined shape.
     *
     * @return
     */
    static Shape makeUndefined() noexcept
    {
        return Shape{};
    }


    /**
     * @brief Create circle shape.
     *
     * @param radius Circle radius.
     * @param center Circle center (position offset).
     *
     * @return
     */
    static Shape makeCircle(units::Length radius, units::PositionVector center = Zero) noexcept
    {
        return Shape{ShapeCircle{center, radius}};
    }


    /**
     * @brief Create rectangle shape.
     *
     * @param size   Rectangle size.
     * @param center Rectangle center (position offset).
     *
     * @return
     */
    static Shape makeRectangle(units::SizeVector size, units::PositionVector center = Zero) noexcept
    {
        return Shape{ShapeRectangle{center, size}};
    }


    /**
     * @brief Create edges shape.
     *
     * @param edges  List of edges.
     * @param center Shape center (position offset).
     *
     * @return
     */
    static Shape makeEdges(DynamicArray<units::PositionVector> edges, units::PositionVector center = Zero) noexcept
    {
        return Shape{ShapeEdges{center, std::move(edges)}};
    }


/// Private Data Types
private:

    /// Stored shape type.
    ShapeType m_type = ShapeType::Undefined;
    ShapeCircle m_circle;
    ShapeRectangle m_rectangle;
    ShapeEdges m_edges;
};

/* ************************************************************************ */

}
}

/* ************************************************************************ */

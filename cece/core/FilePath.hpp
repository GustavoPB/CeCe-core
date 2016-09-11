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

// C++
#include <cstring>
#include <utility>
#include <iterator>

#ifdef _WIN32
#  include <cwchar>
#endif

// CeCe
#include "cece/core/String.hpp"
#include "cece/core/DynamicArray.hpp"
#include "cece/core/InStream.hpp"
#include "cece/core/OutStream.hpp"

/* ************************************************************************ */

namespace cece {
inline namespace core {

/* ************************************************************************ */

/**
 * @brief File path type.
 */
class FilePath
{

// Public Constants
public:


    /// Path separator.
    static constexpr char SEPARATOR = '/';


// Public Ctors & Dtors
public:


    /**
     * @brief Default constructor.
     */
    FilePath() = default;


    /**
     * @brief Constructor.
     *
     * @param source
     */
    FilePath(String source)
        : m_path(std::move(source))
    {
        // Nothing to do
    }


    /**
     * @brief Constructor.
     *
     * @param source
     */
    FilePath(const char* source)
        : m_path(source)
    {
        // Nothing to do
    }


// Public Operators
public:


    /**
     * @brief Append path.
     *
     * @param path
     *
     * @return this
     */
    FilePath& operator/=(const FilePath& path)
    {
        m_path += SEPARATOR;
        m_path.append(path.m_path);
        return *this;
    }


    /**
     * @brief Append source.
     *
     * @param source
     *
     * @return this
     */
    FilePath& operator/=(const String& source)
    {
        m_path += SEPARATOR;
        m_path.append(source);
        return *this;
    }


    /**
     * @brief Append source.
     *
     * @param source
     *
     * @return this
     */
    FilePath& operator/=(const char* source)
    {
        m_path += SEPARATOR;
        m_path.append(source);
        return *this;
    }


    /**
     * @brief Append path.
     *
     * @param path
     *
     * @return
     */
    FilePath operator/(const FilePath& path) const
    {
        return FilePath(*this) /= path;
    }


    /**
     * @brief Append source.
     *
     * @param source
     *
     * @return
     */
    FilePath operator/(const String& source) const
    {
        return FilePath(*this) /= source;
    }


    /**
     * @brief Append source.
     *
     * @param source
     *
     * @return
     */
    FilePath operator/(const char* source) const
    {
        return FilePath(*this) /= source;
    }


// Public Accessors & Mutators
public:


    /**
     * @brief Check if path is empty.
     *
     * @return
     */
    bool isEmpty() const noexcept
    {
        return m_path.empty();
    }


    /**
     * @brief Check if path is empty.
     *
     * @return
     *
     * @deprecated
     */
    bool empty() const noexcept
    {
        return isEmpty();
    }


    /**
     * @brief Returns path file name.
     *
     * @return
     */
    String getFilename() const noexcept;


    /**
     * @brief Returns path extension.
     *
     * @return
     */
    String getExtension() const noexcept;


    /**
     * @brief Returns parent path.
     *
     * @return
     */
    FilePath getParentPath() const noexcept;


    /**
     * @brief Returns path stem.
     *
     * @return
     */
    FilePath getStem() const noexcept;


    /**
     * @brief Convert path to string.
     *
     * @return
     */
    const char* c_str() const noexcept
    {
        return m_path.c_str();
    }


    /**
     * @brief Returns path length.
     *
     * @return
     */
    String::size_type getSize() const noexcept
    {
        return m_path.size();
    }


    /**
     * @brief Convert path to string.
     *
     * @return
     */
    String toString() const noexcept
    {
        return m_path;
    }


    /**
     * @brief Convert path to string.
     *
     * @return
     *
     * @deprecated
     */
    String string() const noexcept
    {
        return toString();
    }


    /**
     * @brief Append string to the path.
     *
     * @param  str String to append.
     *
     * @return this
     */
    FilePath& append(const String& str)
    {
        m_path.append(str);
        return *this;
    }


    /**
     * @brief Replace path extension.
     *
     * @param  ext New extension.
     *
     * @return this
     */
    FilePath& replaceExtension(const String& ext);


// Public Operations
public:


    /**
     * @brief Clear path.
     */
    void clear() noexcept
    {
        m_path.clear();
    }


    /**
     * @brief Input stream operator.
     *
     * @param is
     * @param path
     *
     * @return is
     */
    friend InStream& operator>>(InStream& is, FilePath& path)
    {
        return is >> path.m_path;
    }


    /**
     * @brief Output stream operator.
     *
     * @param os
     * @param path
     *
     * @return os
     */
    friend OutStream& operator<<(OutStream& os, const FilePath& path)
    {
        return os << path.m_path;
    }


// Private Data Members
private:

    /// Path value.
    String m_path;

};

/* ************************************************************************ */

/**
 * @brief Tests if path is a file.
 *
 * @param path
 *
 * @return
 */
bool isFile(const FilePath& path) noexcept;

/* ************************************************************************ */

/**
 * @brief Tests if path is a directory.
 *
 * @param path
 *
 * @return
 */
bool isDirectory(const FilePath& path) noexcept;

/* ************************************************************************ */

/**
 * @brief Tests if file path exists.
 *
 * @param path
 *
 * @return
 */
bool pathExists(const FilePath& path) noexcept;

/* ************************************************************************ */

/**
 * @brief Returns temporary directory.
 *
 * @return
 */
FilePath tempDirectory();

/* ************************************************************************ */

/**
 * @brief Get all entries in given directory.
 *
 * @param dir
 *
 * @return
 */
DynamicArray<FilePath> openDirectory(const FilePath& dir);

/* ************************************************************************ */

}
}

/* ************************************************************************ */

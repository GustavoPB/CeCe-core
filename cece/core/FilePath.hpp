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

// Public Types
public:


    /// Type for storing path.
    using StringType = String;


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
    FilePath(StringType source)
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
        : m_path(source, std::strlen(source))
    {
        // Nothing to do
    }


#ifdef _WIN32

    /**
     * @brief Constructor.
     *
     * @param source
     */
    FilePath(const wchar_t* source)
        : m_path(source, std::wstrlen(source))
    {
        // Nothing to do
    }

#endif


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
        m_path += path.m_path;
        return *this;
    }


    /**
     * @brief Append source.
     *
     * @param source
     *
     * @return this
     */
    FilePath& operator/=(const StringType& source)
    {
        m_path += SEPARATOR;
        m_path += source;
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
        m_path += source;
        return *this;
    }


#ifdef _WIN32

    /**
     * @brief Append source.
     *
     * @param source
     *
     * @return this
     */
    FilePath& operator/=(const wchar_t* source)
    {
        m_path += SEPARATOR;
        m_path += source;
        return *this;
    }

#endif


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
    FilePath operator/(const StringType& source) const
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


#ifdef _WIN32

    /**
     * @brief Append source.
     *
     * @param source
     *
     * @return
     */
    FilePath operator/(const wchar_t* source)
    {
        return FilePath(*this) /= source;
    }

#endif


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
     * @brief Returns path file name.
     *
     * @return
     */
    StringType getFilename() const noexcept;


    /**
     * @brief Returns path extension.
     *
     * @return
     */
    StringType getExtension() const noexcept;


    /**
     * @brief Returns parent path.
     *
     * @return
     */
    FilePath getParentPath() const noexcept;


    /**
     * @brief Convert path to string.
     *
     * @return
     */
    StringType toString() const noexcept
    {
        return m_path;
    }


    /**
     * @brief Convert path to string.
     *
     * @return
     */
    const StringType::value_type* c_str() const noexcept
    {
        return m_path.c_str();
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
    StringType m_path;

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
bool fileExists(const FilePath& path) noexcept;

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

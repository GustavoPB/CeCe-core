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
#include "cece/core/String.hpp"
#include "cece/core/FilePath.hpp"

/* ************************************************************************ */

using namespace cece;

/* ************************************************************************ */

TEST(FilePath, construct)
{
    {
        auto path = FilePath();
        EXPECT_TRUE(path.isEmpty());
    }

    {
        const char* str = "filename1";
        auto path = FilePath(str);
        EXPECT_FALSE(path.isEmpty());
        EXPECT_EQ(str, path.toString());
    }

    {
        String str = "dirname/filename";
        auto path = FilePath(str);
        EXPECT_FALSE(path.isEmpty());
        EXPECT_EQ(str, path.toString());
    }
}

/* ************************************************************************ */

TEST(FilePath, append)
{
    {
        auto path = FilePath("dir");
        path /= "filename";
        EXPECT_EQ("dir/filename", path.toString());
    }

    {
        auto path = FilePath("dir");
        auto file = FilePath("filename");

        auto p = path / file;
        EXPECT_EQ("dir/filename", p.toString());
    }
}

/* ************************************************************************ */

TEST(FilePath, operations)
{
    FilePath path("dir1/dir2/dir3/file.txt");

    EXPECT_FALSE(path.isEmpty());
    EXPECT_EQ("dir1/dir2/dir3/file.txt", path.toString());
    EXPECT_EQ("file.txt", path.getFilename());
    EXPECT_EQ(".txt", path.getExtension());
    EXPECT_EQ("dir1/dir2/dir3", path.getParentPath().toString());
    EXPECT_EQ("dir1/dir2/dir3/file", path.getStem().toString());

    path.replaceExtension(".img");
    EXPECT_EQ("dir1/dir2/dir3/file.img", path.toString());
}

/* ************************************************************************ */

TEST(FilePath, functions)
{
    // TODO: test
    // bool isFile(const FilePath& path) noexcept;
    // bool isDirectory(const FilePath& path) noexcept;
    // bool pathExists(const FilePath& path) noexcept;
    // FilePath tempDirectory();
    // DynamicArray<FilePath> openDirectory(const FilePath& dir);
}

/* ************************************************************************ */

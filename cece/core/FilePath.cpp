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
#include "cece/core/FilePath.hpp"

// C++
#include <cstdlib>
#include <utility>

// Unix
#ifdef __unix__
#  include <unistd.h>
#  include <dirent.h>
#  include <sys/stat.h>
#  include <sys/types.h>
#endif

// Win32
#ifdef _WIN32
#  include <Windows.h>
#endif

// CeCe
#include "cece/core/Exception.hpp"

/* ************************************************************************ */

namespace cece {
inline namespace core {

/* ************************************************************************ */

FilePath::StringType FilePath::getFilename() const noexcept
{
    if (isEmpty())
        return {};

    auto pos = m_path.find_last_of(SEPARATOR);

    if (pos == StringType::npos)
        return m_path;

    return m_path.substr(pos + 1);
}

/* ************************************************************************ */

FilePath::StringType FilePath::getExtension() const noexcept
{
    const StringType& name = getFilename();
    auto pos = name.find_last_of('.');
    if (pos == StringType::npos)
        return {};

    return name.substr(pos + 1);
}

/* ************************************************************************ */

FilePath FilePath::getParentPath() const noexcept
{
    auto pos = m_path.find_last_of(SEPARATOR);
    return pos == StringType::npos
        ? FilePath{}
        : FilePath{m_path.substr(0, pos)}
    ;
}

/* ************************************************************************ */

FilePath FilePath::getStem() const noexcept
{
    if (m_path == "." || m_path == "..")
        return m_path;

    auto pos = m_path.find_last_of('.');
    return pos == StringType::npos
        ? FilePath{}
        : FilePath{m_path.substr(0, pos)}
    ;
}

/* ************************************************************************ */

FilePath& FilePath::replaceExtension(const String& ext)
{
    // erase existing extension, including the dot, if any
    m_path.erase(m_path.size() - getExtension().size());

    if (!ext.empty())
    {
        // append new_extension, adding the dot if necessary
        if (ext.front() != '.')
            m_path.push_back('.');

        m_path.append(ext);
    }

    return *this;
}

/* ************************************************************************ */

bool isFile(const FilePath& path) noexcept
{
    auto str = path.toString();
#if defined(_WIN32)
    DWORD attr = GetFileAttributesW(str.c_str());
    return (attr != INVALID_FILE_ATTRIBUTES && (attr & FILE_ATTRIBUTE_DIRECTORY) == 0);
#else
    struct stat sb;
    if (stat(str.c_str(), &sb))
        return false;
    return S_ISREG(sb.st_mode);
#endif
}

/* ************************************************************************ */

bool isDirectory(const FilePath& path) noexcept
{
    auto str = path.toString();
#if defined(_WIN32)
    DWORD result = GetFileAttributesW(str.c_str());
    if (result == INVALID_FILE_ATTRIBUTES)
        return false;
    return (result & FILE_ATTRIBUTE_DIRECTORY) != 0;
#else
    struct stat sb;
    if (stat(str.c_str(), &sb))
        return false;
    return S_ISDIR(sb.st_mode);
#endif
}

/* ************************************************************************ */

bool fileExists(const FilePath& path) noexcept
{
    auto str = path.toString();
#ifdef __unix__
    return access(str.c_str(), F_OK) != -1;
#elif defined(_WIN32)
    DWORD dwAttrib = GetFileAttributes(str.c_str());
    return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
#endif
}

/* ************************************************************************ */

FilePath tempDirectory()
{
    // Based on boost implementation

#ifdef __unix__
    const char* val = nullptr;

    // Check env variables
    (val = std::getenv("TMPDIR" )) ||
    (val = std::getenv("TMP"    )) ||
    (val = std::getenv("TEMP"   )) ||
    (val = std::getenv("TEMPDIR"));

    // Env variable not set, use /tmp
    FilePath p((val != nullptr) ? val : "/tmp");

    if (p.isEmpty() || !isDirectory(p))
        throw RuntimeException("Unable to find TEMP directory");

    return p;
#else  // Windows

    const wchar_t* envList[] = {
        L"TMP",
        L"TEMP",
        L"LOCALAPPDATA",
        L"USERPROFILE"
    };

    FilePath p;
    for (int i = 0; i < 4; ++i)
    {
        wchar_t* env = wgetenv(envList[i]);

        if (env)
        {
            p = env;
            if (i >= 2)
                p /= L"Temp";

            if (fileExists(p) && isDirectory(p))
                break;

            p.clear();
        }
    }

    if (p.isEmpty())
    {
        StringType buf(::GetWindowsDirectoryW(NULL, 0));

        if (buf.empty() || ::GetWindowsDirectoryW(&buf[0], static_cast<UINT>(buf.size())) == 0)
            throw RuntimeException("Unable to obtain windows directory for TEMP directory");

        p = buf;
        p /= L"Temp";
    }

    return p;

#endif
}

/* ************************************************************************ */

DynamicArray<FilePath> openDirectory(const FilePath& dir)
{

#ifdef __unix__
    DIR* d;

    if ((d = opendir(dir.c_str())) == nullptr)
        return {};

    DynamicArray<FilePath> entries;

    struct dirent* de;
    while ((de = readdir(d)) != NULL)
        entries.push_back(dir / de->d_name);

    closedir(d);

    return entries;
#else
    WIN32_FIND_DATA ffd;
    HANDLE hFind = FindFirstFile(dir.c_str(), &ffd);
    if (hFind == INVALID_HANDLE_VALUE)
        return {};

    DynamicArray<FilePath> entries;

    do
    {
        entries.push_back(dir / fdd.cFileName);
    }
    while (FindNextFile(hFind, &ffd) != 0);

    if (GetLastError() != ERROR_NO_MORE_FILES) {
        FindClose(hFind);
        return false;
    }

    FindClose(hFind);

    return entries;
#endif
}

/* ************************************************************************ */

}
}

/* ************************************************************************ */

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

#ifdef _WIN32
#  include <windows.h>
#else
#  include <unistd.h>
#  include <dirent.h>
#  include <sys/stat.h>
#  include <sys/types.h>
#endif

// CeCe
#include "cece/core/Exception.hpp"

/* ************************************************************************ */

namespace cece {
inline namespace core {

/* ************************************************************************ */

namespace {

/* ************************************************************************ */

#ifdef _WIN32
std::wstring toWide(const String& str)
{
    if (str.empty())
        return {};

    int size = MultiByteToWideChar(CP_UTF8, 0, str.data(), (int) str.size(), NULL, 0);
    std::wstring result(size, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, str.data(), (int) str.size(), &result.front(), size);
    return result;
}
#endif

/* ************************************************************************ */

#ifdef _WIN32
String fromWide(const std::wstring& str)
{
    int size = WideCharToMultiByte(CP_UTF8, 0, str.data(), (int) str.size(), NULL, 0, NULL, NULL);
    String result(size, '\0');
    WideCharToMultiByte(CP_UTF8, 0, str.data(), (int) str.size(), &result.front(), size, NULL, NULL);
    return result;
}
#endif

/* ************************************************************************ */

}

/* ************************************************************************ */

String FilePath::getFilename() const noexcept
{
    if (isEmpty())
        return {};

    auto pos = m_path.find_last_of(SEPARATOR);

#ifdef _WIN32
    if (pos == String::npos)
        pos = m_path.find_last_of('\\');
#endif

    if (pos == String::npos)
        return m_path;

    return m_path.substr(pos + 1);
}

/* ************************************************************************ */

String FilePath::getExtension() const noexcept
{
    const String& name = getFilename();
    auto pos = name.find_last_of('.');
    if (pos == String::npos)
        return {};

    return name.substr(pos);
}

/* ************************************************************************ */

FilePath FilePath::getParentPath() const noexcept
{
    auto pos = m_path.find_last_of(SEPARATOR);

#ifdef _WIN32
    if (pos == String::npos)
        pos = m_path.find_last_of('\\');
#endif

    return pos == String::npos
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
    return pos == String::npos
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

        m_path.append(ext.begin(), ext.end());
    }

    return *this;
}

/* ************************************************************************ */

bool isFile(const FilePath& path) noexcept
{
#ifdef _WIN32
    auto str = toWide(path.toString());
    DWORD attr = GetFileAttributesW(str.c_str());
    return (attr != INVALID_FILE_ATTRIBUTES && (attr & FILE_ATTRIBUTE_DIRECTORY) == 0);
#else
    struct stat sb;
    if (stat(path.c_str(), &sb))
        return false;
    return S_ISREG(sb.st_mode);
#endif
}

/* ************************************************************************ */

bool isDirectory(const FilePath& path) noexcept
{
#ifdef _WIN32
    auto str = toWide(path.toString());
    DWORD result = GetFileAttributesW(str.c_str());
    if (result == INVALID_FILE_ATTRIBUTES)
        return false;
    return (result & FILE_ATTRIBUTE_DIRECTORY) != 0;
#else
    struct stat sb;
    if (stat(path.c_str(), &sb))
        return false;
    return S_ISDIR(sb.st_mode);
#endif
}

/* ************************************************************************ */

bool pathExists(const FilePath& path) noexcept
{
#ifdef _WIN32
    auto str = toWide(path.toString());
    DWORD dwAttrib = GetFileAttributesW(str.c_str());
    return dwAttrib != INVALID_FILE_ATTRIBUTES;
#else
    return access(path.c_str(), F_OK) != -1;
#endif
}

/* ************************************************************************ */

FilePath tempDirectory()
{
    // Based on boost implementation

#ifdef _WIN32
    const wchar_t* envList[] = {
        L"TMP",
        L"TEMP",
        L"LOCALAPPDATA",
        L"USERPROFILE"
    };

    FilePath p;
    for (int i = 0; i < 4; ++i)
    {
        wchar_t* buffer;
        size_t size;

#ifdef __MINGW32__
        if (_wgetenv_s(&size, nullptr, 0, envList[i]) != 0)
            continue;

        DynamicArray<wchar_t> buf(size);
        buffer = buf.data();
        _wgetenv_s(&size, buffer, size, envList[i]);
#else
        if (_wdupenv_s(&buffer, &size, envList[i]) != 0)
            continue;
#endif

        p = fromWide(buffer);
        if (i >= 2)
            p /= "Temp";

        if (pathExists(p) && isDirectory(p))
            break;

        p.clear();
    }

    if (p.isEmpty())
    {
        std::wstring buf(::GetWindowsDirectoryW(NULL, 0), '\0');

        if (buf.empty() || ::GetWindowsDirectoryW(&buf[0], static_cast<UINT>(buf.size())) == 0)
            throw RuntimeException("Unable to obtain windows directory for TEMP directory");

        p = fromWide(buf);
        p /= "Temp";
    }

    return p;
#else
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
#endif
}

/* ************************************************************************ */

DynamicArray<FilePath> openDirectory(const FilePath& dir)
{

#ifdef _WIN32
    WIN32_FIND_DATAW ffd;
    auto str = toWide(dir.c_str());
    str.append(L"\\*");
    HANDLE hFind = FindFirstFileW(str.c_str(), &ffd);
    if (hFind == INVALID_HANDLE_VALUE)
        return {};

    DynamicArray<FilePath> entries;

    do
    {
        entries.push_back(dir / fromWide(ffd.cFileName));
    }
    while (FindNextFileW(hFind, &ffd) != 0);

    FindClose(hFind);

    return entries;
#else
    DIR* d;

    if ((d = opendir(dir.c_str())) == nullptr)
        return {};

    DynamicArray<FilePath> entries;

    struct dirent* de;
    while ((de = readdir(d)) != NULL)
        entries.push_back(dir / de->d_name);

    closedir(d);

    return entries;
#endif
}

/* ************************************************************************ */

}
}

/* ************************************************************************ */

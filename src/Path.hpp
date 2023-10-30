/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Path
*/

#ifndef PATH_HPP_
#define PATH_HPP_

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#elif defined(__linux__)
    #include <libgen.h>
    #include <unistd.h>
    #include <limits.h>
#else
    #error Unsupported platform
#endif
#include <string>

#define TRUE 1
#define FALSE 0
#define PATH_ASSETS std::string("/usr/games/rtype/assets/")
#define PATH_JSON std::string("/usr/games/rtype/json/")
#define GLOBAL_INSTALL TRUE


inline std::string GetExecutableParentDirectory()
{
    #if GLOBAL_INSTALL == FALSE
        #if defined(_WIN32) || defined(_WIN64)
            char buffer[MAX_PATH];
            GetModuleFileName(NULL, buffer, MAX_PATH);
            std::string path(buffer);
            size_t lastSlash = path.find_last_of("\\/");
            if (lastSlash != std::string::npos)
                return path.substr(0, lastSlash);
            else
                return path;
        #elif defined(__linux__)
            char buffer[1000];
            ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
            if (len != -1)
            {
                buffer[len] = '\0';
                return std::string(dirname(buffer));
            }
            else
            {
                return "";
            }
        #endif
    #else
        return "";
    #endif
}

#endif /* !PATH_HPP_ */

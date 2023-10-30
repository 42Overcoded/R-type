message("Config via package.txt")
set(GLOBAL_INSTALL FALSE)
set(PATH_ASSETS "/usr/games/rtype/assets/")
set(PATH_JSON "/usr/games/rtype/json/")

IF(CPACK_GENERATOR MATCHES "DEB" OR CPACK_GENERATOR MATCHES "RPM")
    set(GLOBAL_INSTALL TRUE)
    set(PATH_ASSETS "/usr/games/rtype/assets/")
    set(PATH_JSON "/usr/games/rtype/json/")
ELSE()
    set(PATH_ASSETS "../games/rtype/assets/")
    set(PATH_JSON "../games/rtype/json/")
    set(CPACK_PACKAGING_INSTALL_PREFIX "")
ENDIF()

IF(CPACK_SYSTEM_NAME MATCHES "WIN32" OR CPACK_SYSTEM_NAME MATCHES "WIN64")
    set(PATH_ASSETS "..\\games\\rtype\\assets\\")
    set(PATH_JSON "..\\games\\rtype\\json\\")
ENDIF()

configure_file(/home/viveli/Epitech/Delivery/Tek3/CPP/R-type/src/Path.hpp.in /home/viveli/Epitech/Delivery/Tek3/CPP/R-type/src/Path.hpp @ONLY)
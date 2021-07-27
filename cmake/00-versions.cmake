macro(set_version major minor patch)
    set(VERSION_MAJOR ${major})
    set(VERSION_MINOR ${minor})
    set(VERSION_PATCH ${patch})
    set(VERSION "${major}.${minor}.${patch}")
    add_definitions("-DVERSION_MAJOR=\"${major}\"")
    add_definitions("-DVERSION_MINOR=\"${minor}\"")
    add_definitions("-DVERSION_PATCH=\"${patch}\"")
    add_definitions("-DVERSION=\"${VERSION}\"")
    set(CPACK_PACKAGE_VERSION_MAJOR ${major})
    set(CPACK_PACKAGE_VERSION_MINOR ${minor})
    set(CPACK_PACKAGE_VERSION_PATCH ${patch})
    set(CPACK_DEBIAN_PACKAGE_VERSION ${version})
endmacro(set_version)

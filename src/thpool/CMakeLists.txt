set(
    thpool_SOURCES
    thpool.c
)

if(BUILD_SHARED_LIBS)
    add_library(thpool_shared SHARED ${thpool_SOURCES})
    set_target_properties(
        thpool_shared
        PROPERTIES OUTPUT_NAME thpool
                   SOVERSION "${VERSION_MAJOR}"
                   VERSION "${VERSION}")
endif()
add_library(thpool STATIC ${thpool_SOURCES})
set_target_properties(thpool PROPERTIES OUTPUT_NAME thpool)

include(GNUInstallDirs)
install(TARGETS thpool
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
# Install headers
install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/thpool"
        DESTINATION "include"
)

configure_file(${PROJECT_SOURCE_DIR}/libthpool.pc.in ${CMAKE_BINARY_DIR}/libthpool.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/libthpool.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

if (BUILD_TEST)
   add_subdirectory(test)
endif() # END TEST

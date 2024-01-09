cmake_minimum_required(VERSION 3.20)

project(relix C)
set(VERSION 0.1.1)
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 1)
set(COPYRIGHT "Copyright (C) 2024 Chase Zehl O'Byrne")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -fPIC -g3 -O0 -ggdb -Wall -Wno-unused-function")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_BUILD_RPATH "${LIBRARY_OUTPUT_PATH}/relix")
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib/relix")

##### CPack
set(CPACK_PACKAGE_VERSION ${VERSION})
set(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})

set(CPACK_RESOURCE_FILE_README.md "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_STRIP_FILES TRUE)
set(CPACK_GENERATOR "STGZ;TGZ;DEB;RPM")
set(CPACK_SYSTEM_NAME "${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "relix Maintainers")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libreadline6")

if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
   set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE amd64)
endif()

include(CPack)

###### GIT VERSION
execute_process(COMMAND git describe
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                OUTPUT_VARIABLE GIT_VERSION
                RESULT_VARIABLE GIT_RETURN_VALUE
                OUTPUT_STRIP_TRAILING_WHITESPACE
                ERROR_QUIET)

if(NOT GIT_RETURN_VALUE EQUAL 0)
  unset(GIT_VERSION)
endif(NOT GIT_RETURN_VALUE EQUAL 0)

###### CONFIG HEADER
set(PREFIX ${CMAKE_INSTALL_PREFIX})
set(BUILD_TYPE ${CMAKE_BUILD_TYPE})
set(SHARED_LIB_PREFIX ${CMAKE_SHARED_LIBRARY_PREFIX})
set(SHARED_LIB_SUFFIX ${CMAKE_SHARED_LIBRARY_SUFFIX})
set(PLATFORM "${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")
configure_file("${CMAKE_SOURCE_DIR}/src/config.h.in"
               "${CMAKE_BINARY_DIR}/config.h")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -include ${CMAKE_BINARY_DIR}/config.h")

###### SUBDIRECTORIES
include_directories(${CMAKE_BINARY_DIR}/src/)
include_directories(${CMAKE_SOURCE_DIR}/src/)
include_directories(${CMAKE_SOURCE_DIR}/lib/)

add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(tools)

###### TESTS
add_custom_target(test
  COMMAND ${CMAKE_SOURCE_DIR}/test/test
          ${CMAKE_BINARY_DIR}/relix
          ${CMAKE_SOURCE_DIR}/test
          ${CMAKE_BINARY_DIR}/testresults.xml)

###### DOCUMENTATION
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/doc)
add_custom_target(doc)

###### DOXYGEN
find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_SOURCE_DIR}/etc/Doxyfile.in ${CMAKE_BINARY_DIR}/Doxyfile)
    add_custom_target(doxygen ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile)
endif(DOXYGEN_FOUND)

###### SPHINX
find_program(SPHINX_EXECUTABLE NAMES sphinx-build)

###### HTML DOCUMENTATION
add_custom_target(html-doc ${SPHINX_EXECUTABLE} -c ${CMAKE_SOURCE_DIR}/doc/
                           ${CMAKE_SOURCE_DIR}/doc/
                           ${CMAKE_BINARY_DIR}/doc/)
add_dependencies(doc html-doc)

###### PDF DOCUMENTATION
add_custom_target(latex-doc ${SPHINX_EXECUTABLE} -b latex
                            -c ${CMAKE_SOURCE_DIR}/doc/
                            ${CMAKE_SOURCE_DIR}/doc/
                            ${CMAKE_BINARY_DIR}/pdf-doc/)
add_custom_target(relix.pdf make -C ${CMAKE_BINARY_DIR}/pdf-doc/)
add_custom_target(pdf-doc ${CMAKE_COMMAND} -E copy
                          ${CMAKE_BINARY_DIR}/pdf-doc/relix.pdf
                          ${CMAKE_BINARY_DIR}/doc/relix.pdf)
add_dependencies(relix.pdf latex-doc)
add_dependencies(pdf-doc relix.pdf)
add_dependencies(doc pdf-doc)

###### MANPAGE
install(FILES ${CMAKE_SOURCE_DIR}/etc/man/relix.1 DESTINATION share/man/man1/)

###### SOURCE DIST
set(ARCHIVE_NAME relix-${VERSION})
add_custom_target(dist
    COMMAND git archive --prefix=${ARCHIVE_NAME}/ HEAD
        | gzip > ${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}.tar.gz
        && gpg --armor --sign --detach-sign -o ${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}.tar.gz.sig
           ${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}.tar.gz
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

#
# RELIX ReScript, Copyright (C) 2024 Chase Zehl O'Byrne
#  <mail: zehl@live.com> http://zehlchen.com/
#
# This file is part of RELIX.
#
# RELIX is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# RELIX is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with RELIX; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#
#

execute_process(
  COMMAND git rev-list --count HEAD
  OUTPUT_VARIABLE GIT_BUILD
  OUTPUT_STRIP_TRAILING_WHITESPACE
  ERROR_QUIET
)

execute_process(
  COMMAND git log -1 --format=%h
  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
  OUTPUT_VARIABLE GIT_COMMIT
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
  COMMAND git rev-parse --abbrev-ref HEAD
  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
  OUTPUT_VARIABLE GIT_BRANCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
  COMMAND git describe --tags --abbrev=0
  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
  OUTPUT_VARIABLE GIT_TAG
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

add_compile_definitions(
  RELIX_GIT_BUILD="${GIT_BUILD}"
  RELIX_GIT_COMMIT="${GIT_COMMIT}"
  RELIX_GIT_BRANCH="${GIT_BRANCH}"
  RELIX_GIT_TAG="${GIT_TAG}"
  RELIX_VERSION_STRING="${VERSION}:${GIT_BUILD}"
  RELIX_COMPILE_FLAGS="${CMAKE_C_FLAGS}"
)

#
# relix executable
#

add_executable(rlxc rlxc/rlxc.c)
target_link_libraries(rlxc rescript)
set_target_properties(rlxc PROPERTIES LINK_FLAGS "-Wl,-rpath,${CMAKE_BUILD_RPATH}")
install(TARGETS rlxc RUNTIME DESTINATION bin)

#
# ipr executable
#

add_executable(irlx irlx/irlx.c)
target_link_libraries(irlx rescript readline relix-io)
set_target_properties(irlx PROPERTIES LINK_FLAGS "-Wl,-rpath,${CMAKE_BUILD_RPATH}")
install(TARGETS irlx RUNTIME DESTINATION bin)

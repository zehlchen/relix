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

include_directories(${CMAKE_SOURCE_DIR}/lib)
include_directories(${CMAKE_SOURCE_DIR}/src)

macro(relix_lib name)
  add_library(relix-${name} SHARED ${ARGN})
  set_target_properties(relix-${name} PROPERTIES
                                      RUNTIME_OUTPUT_DIRECTORY "relix"
                                      LIBRARY_OUTPUT_DIRECTORY "relix")
  target_link_libraries(relix-${name} librelix)
  install(TARGETS relix-${name} DESTINATION lib/relix)
endmacro(relix_lib)

relix_lib(io io/io.c io/file.c)
relix_lib(net net/net.c net/socket.c)
relix_lib(os os/os.c)
relix_lib(time time/time.c)

relix_lib(test test/test.c)
target_link_libraries(relix-test relix-io)

relix_lib(math math/math.c)
target_link_libraries(relix-math m)

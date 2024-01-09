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

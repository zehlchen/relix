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

find_package(BISON)
find_package(FLEX)

#
# librelix
#

add_library(librelix SHARED
  version.c
  memory.c
  vm/block.c
  vm/const.c
  vm/eval.c
  vm/load.c
  vm/module.c
  vm/state.c
  vm/opcodes.c
  runtime/runtime.c
  runtime/object.c
  runtime/cfunction.c
  runtime/function.c
  runtime/hash.c
  runtime/list.c
  runtime/symbol.c
  runtime/integer.c
  runtime/float.c
  runtime/string.c
  runtime/nil.c
  runtime/bool.c
  runtime/exception.c
)
set_target_properties(librelix PROPERTIES OUTPUT_NAME "relix")
target_link_libraries(librelix dl)
install(TARGETS librelix LIBRARY DESTINATION lib)
install(DIRECTORY vm DESTINATION include/relix FILES_MATCHING PATTERN "*.h")
install(DIRECTORY runtime DESTINATION include/relix FILES_MATCHING PATTERN "*.h")
install(DIRECTORY . DESTINATION include/relix FILES_MATCHING PATTERN "*.h")

#
# librelixc
#

bison_target(Parser compiler/parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.c)
flex_target(Lexer compiler/lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.c
            COMPILE_FLAGS --header-file=${CMAKE_CURRENT_BINARY_DIR}/lexer.h)
add_flex_bison_dependency(Lexer Parser)

add_library(rescript SHARED
  ${FLEX_Lexer_OUTPUTS}
  ${BISON_Parser_OUTPUTS}
  compiler/node.c
  compiler/compiler.c
  compiler/symtab.c
)
target_link_libraries(rescript librelix)
install(TARGETS rescript LIBRARY DESTINATION lib)
install(DIRECTORY compiler DESTINATION include/relix FILES_MATCHING PATTERN "*.h")

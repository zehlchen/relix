/*
 * RELIX ReScript, Copyright (C) 2024 Chase Zehl O'Byrne
 *  <mail: zehl@live.com> http://zehlchen.com/
 *
 * This file is part of RELIX.
 *
 * RELIX is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * RELIX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with RELIX; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <stdio.h>

#include "version.h"

const int relix_version[3] = {VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH};

const char* relix_version_string = VERSION;
const char* relix_platform       = PLATFORM;
const char* relix_prefix         = PREFIX;
const char* relix_build_type     = BUILD_TYPE;
const char* relix_copyright      = COPYRIGHT;

void relix_print_version()
{
  fprintf(stderr, "%s on %s-%s\n", RELIX_VERSION_STRING_LONG, relix_platform, relix_build_type);
}

void relix_print_copyright()
{
  fprintf(stderr, "%s\n", relix_copyright);
}

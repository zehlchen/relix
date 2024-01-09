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

#ifndef RELIX_VERSION_H
#define RELIX_VERSION_H

extern const int   relix_version[3];
extern const char* relix_version_string;
extern const char* relix_platform;
extern const char* relix_prefix;
extern const char* relix_build_type;
extern const char* relix_copyright;

#ifndef RELIX_GIT_BUILD
#define RELIX_GIT_BUILD "unknown"
#endif

#ifndef RELIX_GIT_COMMIT
#define RELIX_GIT_COMMIT "unknown"
#endif

#ifndef RELIX_GIT_BRANCH
#define RELIX_GIT_BRANCH "unknown"
#endif

#ifndef RELIX_GIT_TAG
#define RELIX_GIT_TAG "unknown"
#endif

#ifndef RELIX_VERSION_STRING
#define RELIX_VERSION_STRING "unknown"
#endif

#define RELIX_VERSION_STRING_LONG \
  "RELIX-" RELIX_VERSION_STRING "-" RELIX_GIT_COMMIT "-" RELIX_GIT_BRANCH "-" RELIX_GIT_TAG

#define RELIX_VERSION_STRING_SHORT "RELIX-" RELIX_VERSION_STRING

void relix_print_version();
void relix_print_copyright();

#endif

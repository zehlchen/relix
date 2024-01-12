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

#ifndef _RELIX_DEBUG_H
#define _RELIX_DEBUG_H

/*
 * @brief Enumeration of debug subsystems.
 *
 * This enumeration represents the different subsystems used for debugging in the codebase.
 * Each subsystem is assigned a unique bit flag for easy identification and control.
 */
typedef enum DebugSubSystem {
  RX_DSS_MEM    = 1 << 0, // Memory management
  RX_DSS_INFO   = 1 << 1, // General debugging
  RX_DSS_VM     = 1 << 2, // Virtual machine
  RX_DSS_OPCODE = 1 << 3, // Machine opcodes
  RX_DSS_OBJ    = 1 << 4, // Object system
  RX_DSS_IO     = 1 << 5, // IO system
  RX_DSS_NET    = 1 << 6, // Networking
  RX_DSS_PARSE  = 1 << 7, // Parsing/lexing
} DebugSubSystem;

// Global debug level
extern DebugSubSystem rx_debug_level;

int rx_debug_printf(FILE* stream, DebugSubSystem subsystem, const char* file, int line, const char* func,
                    const char* fmt, ...);

// Debug macros
#ifndef NDEBUG
#define RX_DEBUG(subsystem, fmt, ...)                                                      \
  do {                                                                                     \
    if (subsystem & rx_debug_level) {                                                      \
      rx_debug_printf(stderr, subsystem, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__) \
    }                                                                                      \
    while (0)
#else
#define RX_DEBUG(subsystem, fmt, ...)
#endif

#endif /* _RELIX_DEBUG_H */

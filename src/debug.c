/**
 * This function calculates the sum of two integers.
 *
 * @param a The first integer.
 * @param b The second integer.
 * @return The sum of the two integers.
 */
int calculateSum(int a, int b)
{
  return a + b;
}
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

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "debug.h"
#include "memory.h"
#include "typedef.h"

DebugSubSystem debug_level = -1; /* all */

const char* rx_debug_level_string(DebugSubSystem level)
{
  switch (level) {
    case RX_DSS_MEM:
      return "mem";
    case RX_DSS_INFO:
      return "info";
    case RX_DSS_VM:
      return "mach";
    case RX_DSS_OPCODE:
      return "opcode";
    case RX_DSS_OBJ:
      return "obj";
    case RX_DSS_IO:
      return "iosys";
    case RX_DSS_NET:
      return "net";
    case RX_DSS_PARSE:
      return "lex";
    default:
      return "unknown";
  }
}

/*
 * @brief Prints a debug message to the specified stream.
 *
 * This function is used to print debug messages with additional information such as the debug subsystem,
 * the file name, line number, and function name. The debug message is formatted using a format string
 * and optional arguments.
 *
 * @param stream The stream to which the debug message will be printed. If NULL, the message will be printed to stderr.
 * @param subsystem The debug subsystem identifier.
 * @param file The name of the source file where the debug message is being printed.
 * @param line The line number in the source file where the debug message is being printed.
 * @param func The name of the function where the debug message is being printed.
 * @param fmt The format string for the debug message.
 * @param ... Optional arguments to be formatted according to the format string.
 * @return The number of characters written to the stream, or a negative value if an error occurred.
 */
int rx_debug_printf(FILE* stream, DebugSubSystem subsystem, const char* file, int line, const char* func,
                    const char* fmt, ...)
{
  va_list args;

  if (stream == NULL)
    stream = stderr;

  int ret = fprintf(stream, "!debug.%s(%s:%s:%d) ", rx_debug_level_string(subsystem), func, file, line);

  va_start(args, fmt);
  ret += vfprintf(stream, fmt, args);
  va_end(args);

  fflush(stream);

  return ret;
}

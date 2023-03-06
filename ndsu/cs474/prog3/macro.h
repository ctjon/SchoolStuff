/*
 * +------------------------------------------------------------------------+
 * | LIMP - Language Independent Macro Processor                            |
 * | HEADER FILE 				                            |
 * |                                                                        |
 * | Written by: Christopher C. Tjon                                        |
 * | For: CS474                                                             |
 * | 30 Septemper 1992                                                      |
 * |                                                                        |
 * | Capabilities of Macroprocessor:                                        |
 * |               1) Nested Macros                                         |
 * |               2) Macro substitution                                    |
 * |               3) Include files can be loaded to a maximum depth of 4   |
 * |               4) Special Flag characters may be redefined through      |
 * |                      command line arguments                            |
 * |               5) Additional features may be added with minimal changes |
 * |                                                                        |
 * +------------------------------------------------------------------------+
 */
#include <stdio.h>
extern memset();

extern FILE *FileIn;
#define nxtchar(x) (((x)!=NULL) ? (*((x)++)) : (fgetc(FileIn)))
/*
 * conditional define-returns next character in macro string or next
 * character in current input file if x = null
 */

/* PROTOTYPES */
void ProcessChar();
void ProcessFile();

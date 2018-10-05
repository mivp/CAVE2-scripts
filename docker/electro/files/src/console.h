/*    Copyright (C) 2005 Robert Kooima                                       */
/*                                                                           */
/*    ELECTRO is free software;  you can redistribute it and/or modify it    */
/*    under the terms of the  GNU General Public License  as published by    */
/*    the  Free Software Foundation;  either version 2 of the License, or    */
/*    (at your option) any later version.                                    */
/*                                                                           */
/*    This program is distributed in the hope that it will be useful, but    */
/*    WITHOUT  ANY  WARRANTY;  without   even  the  implied  warranty  of    */
/*    MERCHANTABILITY or  FITNESS FOR A PARTICULAR PURPOSE.   See the GNU    */
/*    General Public License for more details.                               */

#ifndef CONSOLE_H
#define CONSOLE_H

/*---------------------------------------------------------------------------*/

#define CONSOLE_X    10
#define CONSOLE_Y    10
#define CONSOLE_COLS 80
#define CONSOLE_ROWS 24

int startup_console(const char *, int, int);

void draw_console(void);
void fini_console(void);

int  set_console_enable(int);
int  console_is_enabled(void);

int  input_console(int, int);
void clear_console(void);
void color_console(float, float, float);
void print_console(const char *);
void debug_console(const char *);
void error_console(const char *);

/*---------------------------------------------------------------------------*/

#endif

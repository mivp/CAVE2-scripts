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

#ifndef SCRIPT_H
#define SCRIPT_H

/*---------------------------------------------------------------------------*/

int  init_script(void);
void free_script(void);
void load_script(const char *);

void add_argument(int, const char *);

int  do_click_script(int, int);
int  do_point_script(int, int);
int  do_timer_script(float);
int  do_frame_script(void);
int  do_keyboard_script(int, int);
int  do_joystick_script(int, int, int);
int  do_contact_script(int, int, const float[3], const float[3], float);

void do_command(const char *);

/*---------------------------------------------------------------------------*/

#endif

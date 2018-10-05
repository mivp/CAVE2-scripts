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

#ifndef VIDEO_H
#define VIDEO_H

/*---------------------------------------------------------------------------*/

#define CLEAR_R 0.0
#define CLEAR_G 0.0
#define CLEAR_B 0.0
#define CLEAR_A 0.0

int init_video(int, int, int, int, int);

int quad_stereo_status(void);

/*---------------------------------------------------------------------------*/

#endif

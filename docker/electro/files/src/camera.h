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

#ifndef CAMERA_H
#define CAMERA_H

#include "entity.h"

/*---------------------------------------------------------------------------*/

#define CAMERA_ORTHO 1
#define CAMERA_PERSP 2

/*---------------------------------------------------------------------------*/

struct entity_func *startup_camera(void);

/*---------------------------------------------------------------------------*/

int  camera_onscreen(int);

int  get_camera_eye(void);
void get_camera_pos(float[3]);
void get_camera_rot(float[16]);

void get_camera_vector(int, int, float[3], int, int);

/*---------------------------------------------------------------------------*/

int  send_create_camera(int);
void recv_create_camera(void);

void send_set_camera_offset(int, const float[3], const float[16]);
void recv_set_camera_offset(void);

void send_set_camera_stereo(int, const float[3], const float[3], int);
void recv_set_camera_stereo(void);

void send_set_camera_range(int, float, float);
void recv_set_camera_range(void);

void send_set_camera_image(int, int, float, float, float, float);
void recv_set_camera_image(void);

/*---------------------------------------------------------------------------*/

#endif

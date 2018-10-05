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

#ifndef BRUSH_H
#define BRUSH_H

/*---------------------------------------------------------------------------*/

/* Default material properties */

#define BRUSH_DIFFUSE_R  0.8f
#define BRUSH_DIFFUSE_G  0.8f
#define BRUSH_DIFFUSE_B  0.8f
#define BRUSH_DIFFUSE_A  1.0f

#define BRUSH_SPECULAR_R 0.0f
#define BRUSH_SPECULAR_G 0.0f
#define BRUSH_SPECULAR_B 0.0f
#define BRUSH_SPECULAR_A 1.0f

#define BRUSH_AMBIENT_R  0.2f
#define BRUSH_AMBIENT_G  0.2f
#define BRUSH_AMBIENT_B  0.2f
#define BRUSH_AMBIENT_A  1.0f

#define BRUSH_SHININESS  0.0f

/*---------------------------------------------------------------------------*/

/* Brush flags */

#define BRUSH_DIFFUSE     0x0001
#define BRUSH_SPECULAR    0x0002
#define BRUSH_AMBIENT     0x0004
#define BRUSH_SHINY       0x0008
#define BRUSH_TRANSPARENT 0x0010
#define BRUSH_ENV_MAP_0   0x0020
#define BRUSH_ENV_MAP_1   0x0040
#define BRUSH_ENV_MAP_2   0x0080
#define BRUSH_ENV_MAP_3   0x0100
#define BRUSH_SKY_MAP_0   0x0200
#define BRUSH_SKY_MAP_1   0x0400
#define BRUSH_SKY_MAP_2   0x0800
#define BRUSH_SKY_MAP_3   0x1000
#define BRUSH_UNLIT       0x2000

/*---------------------------------------------------------------------------*/

int startup_brush(void);

/*---------------------------------------------------------------------------*/

int  dupe_create_brush(int);
int  send_create_brush(const char *, const char *);
void recv_create_brush(void);

void send_delete_brush(int);
void recv_delete_brush(void);

void send_set_brush_flags(int, int, int);
void recv_set_brush_flags(void);

void send_set_brush_image(int, int, int);
void recv_set_brush_image(void);

void send_set_brush_rotation(int, float);
void recv_set_brush_rotation(void);

void send_set_brush_position(int, const float[2]);
void recv_set_brush_position(void);

void send_set_brush_scale(int, const float[2]);
void revc_set_brush_scale(void);

void send_set_brush_color(int, const float[4],
                               const float[4],
                               const float[4],
                               const float[1], int);
void recv_set_brush_color(void);

void send_set_brush_frag_shader(int, const char *);
void recv_set_brush_frag_shader(void);

void send_set_brush_vert_shader(int, const char *);
void recv_set_brush_vert_shader(void);

void send_set_brush_uniform(int, const char *, int, int, int, const float *);
void recv_set_brush_uniform(void);

void send_set_brush_frag_prog(int, const char *);
void recv_set_brush_frag_prog(void);

void send_set_brush_vert_prog(int, const char *);
void recv_set_brush_vert_prog(void);

void send_set_brush_frag_param(int, int, const float[4]);
void recv_set_brush_frag_param(void);

void send_set_brush_vert_param(int, int, const float[4]);
void recv_set_brush_vert_param(void);

void send_set_brush_line_width(int, float);
void recv_set_brush_line_width(void);

/*---------------------------------------------------------------------------*/

void init_brush(int);
void fini_brush(int);
int  draw_brush(int, float);

void nuke_brushes(void);
void init_brushes(void);
void fini_brushes(void);

/*---------------------------------------------------------------------------*/

int get_brush_w(int);
int get_brush_h(int);
int get_brush_t(int);

/*---------------------------------------------------------------------------*/

#endif

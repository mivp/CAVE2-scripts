INSTALL_PREFIX = $(HOME)

#------------------------------------------------------------------------------

# To build in cluster mode: "make MPI=1".

ifdef MPI
	CC     = mpicc
	TARG   = electro-mpi
	CFLAGS = -O3 -Wall -DNDEBUG -DCONF_MPI
#	CFLAGS = -g -Wall -DNDEBUG -DCONF_MPI -I${HOME}/local/include/
#	CFLAGS = -g -Wall  -DdSINGLE -DCONF_MPI -I${HOME}/local/include/
else
	CC     = cc
	TARG   = electro
#	CFLAGS = -O2 -Wall
#	CFLAGS = -O3 -ffast-math -Wall
	CFLAGS = -g -Wall
endif

#------------------------------------------------------------------------------

ifeq ($(shell uname), Darwin)
	INCDIR = -I/opt/local/include
	LIBDIR = -L/opt/local/lib
	OGLLIB = -framework OpenGL
	SDL_CONFIG = /opt/local/bin/sdl-config
	FT2_CONFIG = /opt/local/bin/freetype-config
else
	OGLLIB = -lGL -lGLU
	SDL_CONFIG = /usr/bin/sdl-config
	FT2_CONFIG = /usr/bin/freetype-config
endif

# Include Lua, if it exists.

ifneq ($(wildcard /usr/include/lua5.1),)
	INCDIR += -I/usr/include/lua5.1
endif

#glext.h
INCDIR += -I/usr/include/GL


#------------------------------------------------------------------------------

CFLAGS += $(shell $(SDL_CONFIG) --cflags) $(shell $(FT2_CONFIG) --cflags) -Iode-0.12/include

SDLLIB = $(shell $(SDL_CONFIG) --libs) -lSDLmain
FT2LIB = $(shell $(FT2_CONFIG) --libs)
LUALIB = -llua5.1
IMGLIB = -ljpeg -lpng -lz -lm
OGGLIB = -lvorbisfile
ODELIB = -lode -lstdc++
#ODELIB = ./ode-0.12/ode/src/.libs/libode.a -lstdc++

#------------------------------------------------------------------------------

LIBS += $(LUALIB) $(ODELIB) $(SDLLIB) $(FT2LIB) $(IMGLIB) $(OGGLIB) $(OGLLIB)

OBJS =	src/opengl.o   \
	src/video.o    \
	src/glyph.o    \
	src/matrix.o   \
	src/vector.o   \
	src/utility.o  \
	src/tracker.o  \
	src/joystick.o \
	src/frustum.o  \
	src/display.o  \
	src/console.o  \
	src/physics.o  \
	src/buffer.o   \
	src/server.o   \
	src/client.o   \
	src/entity.o   \
	src/camera.o   \
	src/stereo.o   \
	src/galaxy.o   \
	src/terrain.o  \
	src/sprite.o   \
	src/object.o   \
	src/string.o   \
	src/light.o    \
	src/pivot.o    \
	src/script.o   \
	src/image.o    \
	src/brush.o    \
	src/sound.o    \
	src/font.o     \
	src/node.o     \
	src/star.o     \
	src/net.o      \
	src/vec.o      \
	src/main.o

SRCS= $(OBJS:.o=.c)
DEPS= $(OBJS:.o=.d)

#------------------------------------------------------------------------------

%.d : %.c
	$(CC) $(CFLAGS) $(INCDIR) -MM -MF $@ -MT $*.o $< > /dev/null

%.o : %.c Makefile
	$(CC) $(CFLAGS) $(INCDIR) -c -o $@ $<

$(TARG) : $(OBJS) Makefile
	$(CC) $(CFLAGS) -o $(TARG) $(OBJS) $(LIBDIR) $(LIBS)

clean :
	rm -f $(TARG) $(OBJS)

distclean:
	find . -name .svn | xargs rm -rf
	rm -f $(DEPS)

install : $(TARG)
	mkdir -p $(INSTALL_PREFIX)/bin
	mkdir -p $(INSTALL_PREFIX)/config
	cp $(TARG) $(INSTALL_PREFIX)/bin
	cp config/* $(INSTALL_PREFIX)/config

#------------------------------------------------------------------------------

CH= install_name_tool -change

osxdist : $(TARG)
	mkdir -p lib

	cp    /opt/local/lib/libSDL-1.2.0.dylib    lib
	cp    /opt/local/lib/libfreetype.6.dylib   lib
	cp    /opt/local/lib/libjpeg.62.dylib      lib
	cp    /opt/local/lib/libpng.3.dylib        lib
	cp    /opt/local/lib/libvorbisfile.3.dylib lib
	cp    /opt/local/lib/libvorbis.0.dylib     lib
	cp    /opt/local/lib/libogg.0.dylib        lib

	$(CH) /opt/local/lib/libSDL-1.2.0.dylib    \
          @executable_path/lib/libSDL-1.2.0.dylib    $(TARG)
	$(CH) /opt/local/lib/libfreetype.6.dylib   \
          @executable_path/lib/libfreetype.6.dylib   $(TARG)
	$(CH) /opt/local/lib/libjpeg.62.dylib      \
          @executable_path/lib/libjpeg.62.dylib      $(TARG)
	$(CH) /opt/local/lib/libpng.3.dylib        \
          @executable_path/lib/libpng.3.dylib        $(TARG)
	$(CH) /opt/local/lib/libvorbisfile.3.dylib \
          @executable_path/lib/libvorbisfile.3.dylib $(TARG)
	$(CH) /opt/local/lib/libvorbis.0.dylib     \
          @executable_path/lib/libvorbis.0.dylib     lib/libvorbisfile.3.dylib
	$(CH) /opt/local/lib/libogg.0.dylib        \
          @executable_path/lib/libogg.0.dylib        lib/libvorbisfile.3.dylib
	$(CH) /opt/local/lib/libogg.0.dylib        \
          @executable_path/lib/libogg.0.dylib        lib/libvorbis.0.dylib

#------------------------------------------------------------------------------

-include $(DEPS)

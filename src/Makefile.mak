CPP    = g++
WINDRES= windres
RM     = rm -f
OBJS   = classes/display.o \
         classes/glwindow.o \
         main.o \
         texture.o \
         skybox.o \
         texturemanager.o \
         objloader.o \
         sound.o \
         camera.o \
         player.o \
         vertex.o \
         object.o \
         model.o \
         terrain.o \
         house.o \
         scenemanager.o \
         util.o \
         tiny_obj_loader.o \
         AppResource.res

LIBS   = -mwindows -static -lmingw32 -lSOIL -lSDLmain -lSDL -lOpenGL32 -lglu32 -lwinmm -ldxguid -lfmod
CFLAGS =

.PHONY: ../bin/Environment.exe clean

all: ../bin/Environment.exe

clean:
	$(RM) $(OBJS) ../bin/Environment.exe

../bin/Environment.exe: $(OBJS)
	$(CPP) -Wall -s -O2 -o $@ $(OBJS) $(LIBS)

classes/display.o: classes/display.cpp classes/display.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

classes/glwindow.o: classes/glwindow.cpp classes/glwindow.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

main.o: main.cpp classes/glwindow.h util.h keyaction.h player.h skybox.h texturemanager.h scenemanager.h terrain.h sound.h house.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

texture.o: texture.cpp texture.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

skybox.o: skybox.cpp skybox.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

texturemanager.o: texturemanager.cpp texturemanager.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

objloader.o: objloader.cpp objloader.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

sound.o: sound.cpp sound.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

camera.o: camera.cpp camera.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

player.o: player.cpp player.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

vertex.o: vertex.cpp vertex.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

object.o: object.cpp object.h util.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

model.o: model.cpp model.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

terrain.o: terrain.cpp terrain.h util.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

house.o: house.cpp house.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

scenemanager.o: scenemanager.cpp scenemanager.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

util.o: util.cpp util.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

tiny_obj_loader.o: tiny_obj_loader.cc tiny_obj_loader.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

AppResource.res: AppResource.rc
	$(WINDRES) -i AppResource.rc -J rc -o AppResource.res -O coff


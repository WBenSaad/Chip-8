user_inc = include
SRCS = $(wildcard src/*.c)
CFLAGS = -w -Wl,-subsystem,windows
LDFLAGS = -LC:\MinGW\SDL2\i686-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2 -g
INCLUDES = -IC:\MinGW\SDL2\i686-w64-mingw32\include\SDL2 -I$(user_inc)
VARIANT =


.PHONY:all

all :
		gcc $(SRCS) $(CFLAGS) $(VARIANT) $(INCLUDES) $(LDFLAGS) -o main.exe

.PHONY:clean
clean :
	rm -rf build/*
	rm main.exe
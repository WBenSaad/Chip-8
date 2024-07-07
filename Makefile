user_inc = include
SRCS = $(wildcard src/*.c)
.PHONY:all
all :
	gcc $(SRCS) -IC:\MinGW\SDL2\i686-w64-mingw32\include\SDL2 -I$(user_inc) -LC:\MinGW\SDL2\i686-w64-mingw32\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -o main

.PHONY:clean
clean :
	rm -rf build/*
	rm main.exe
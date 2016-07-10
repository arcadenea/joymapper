TARGET=server
CC = g++
DEBUG =
SDL_CFLAGS := $(shell sdl-config --cflags)
SDL_LDFLAGS := $(shell sdl-config --libs)
CFLAGS = -DUSEGL -g -Wall $(SDL_CFLAGS) -I./  -fno-omit-frame-pointer
LFLAGS = -Wall $(DEBUG)
LIBS = $(SDL_LDFLAGS) -lm -lSDL -L/usr/lib/gcc/i486-linux-gnu/4.7 -L/usr/lib 

OBJS = server.o uinput.o

all: $(TARGET)

rm-elf:
	-rm -f $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -r $(OBJS) $(TARGET)

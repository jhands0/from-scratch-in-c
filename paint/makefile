CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c99 -Iinclude -D_GNU_SOURCE
LDFLAGS = -lm
SDL2 = `sdl2-config --cflags --libs`
SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES: .c=.o)
TARGET = out

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(TARGET) $(SDL2)

release: CFLAGS += -O3 -flto -march=native
release: LDFLAGS += -flto
release: clean $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< .o $@

clean:
	rm -f $(SRCDIR)/*.o $(TARGET)

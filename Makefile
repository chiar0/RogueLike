CC = g++
CFLAGS = -lncurses -lm -I./include/
SOURCES = ./sources/*.cpp

ifeq ($(OS),Windows_NT)
    detected_OS := Windows
else
    detected_OS := $(shell uname)
endif

all: game run clean

game:
  $(CC) $(SOURCES) $(CFLAGS) -o game

run:
  ./game

clean:
ifeq ($(detected_OS), Windows)
  del game.exe
else
  rm game
endif
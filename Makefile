# Flags
CFLAGS += -std=c99 -Wall -Wextra -pedantic -Wno-misleading-indentation -Wno-shift-negative-value -O2
LIBS :=

ifeq ($(OS),Windows_NT)
	DEL_BIN = IF EXIST bin DEL /F /Q bin\*
	BIN := $(BIN).exe
	LIBS := -lglfw3 -lopengl32 -lm -lGLU32 -lGLEW32 -lgdi32 -lhpdf		# use -mwindows to hide cmd window when running executable
	CC := gcc
else
	DEL_BIN = rm -rf bin
	UNAME_S := $(shell uname -s)
	GLFW3 := $(shell pkg-config --libs glfw3)
	ifeq ($(UNAME_S),Darwin)
		LIBS := $(GLFW3) -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -lm -lGLEW -L/usr/local/lib
		CFLAGS += -I/usr/local/include
	else
		LIBS := $(GLFW3) -lGL -lm -lGLU -lGLEW -lhpdf
	endif
endif

all: generate main

generate: clean
ifeq ($(OS),Windows_NT)
	@mkdir bin 2> nul || exit 0
else
	@mkdir -p bin	
endif

clean:
	$(DEL_BIN)

main: generate
	$(CC) $(CFLAGS) -o bin/BillHub source/main.c $(LIBS)

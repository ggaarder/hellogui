LIBS = `pkg-config --libs gtk+-3.0`

CFLAGS = `pkg-config --cflags gtk+-3.0`

all: hellogui.c
	gcc $^ $(LIBS) $(CFLAGS)

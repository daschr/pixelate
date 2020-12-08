FLAGS=-O3 -pedantic -Wall $(shell pkg-config --cflags glib-2.0)
LIBS=$(shell pkg-config vips --cflags --libs)
LIBS+=$(shell pkg-config --libs imagequant)

all:
	$(CC) $(FLAGS) -o pixelate pixelate.c $(LIBS)

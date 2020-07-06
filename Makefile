FLAGS=-pedantic -Wall
LIBS=$(shell pkg-config vips --cflags --libs)
LIBS+=$(shell pkg-config --libs imagequant)

all:
	$(CC) $(FLAGS) -o pixelate pixelate.c $(LIBS)

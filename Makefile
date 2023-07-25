
CC=gcc
CFLAGS_LANG=-std=c11 -Wall -Werror -Wextra
CFLAGS_CONF_DEBUG=-O0 -g
CFLAGS_CONF_OPT=-O2
CFLAGS_CONF=$(CFLAGS_CONF_DEBUG)
CFLAGS_LIBS=$(shell sdl2-config --cflags)
CFLAGS=$(CFLAGS_LANG) $(CFLAGS_CONF) $(CFLAGS_LIBS)
LDLIBS=$(shell sdl2-config --libs)
EXE=sdl_renderers

all: debug

$(EXE): main.o
	gcc $^ $(LDLIBS) -o $@

debug: CFLAGS_CONF=$(CFLAGS_CONF_DEBUG)
debug: $(EXE)

opt: CFLAGS_CONF+=$(CFLAGS_CONF_OPT)
opt: $(EXE)

main.o: main.c

%.o: %.c
	gcc -c $(CFLAGS) $< -o $@

clean:
	rm -f *.o
	rm -f $(EXE)


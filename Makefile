CC=gcc
CFLAGS=-O2 -Isrc -Wall -Wextra -DNDEBUG $(OPTFLAGS)
LDLIBS=
LDFLAGS=$(OPTLIBS)

PROJ=build/dcp_log

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

all: $(OBJECTS) $(PROJ)

$(PROJ): build $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(CFLAGS) $(LDLIBS) $(LDFLAGS)

build:
	@mkdir -p build

dev: CFLAGS=-g -O2 -Isrc -Wall -Wextra -Werror $(OPTFLAGS)
dev: all

.PHONY: clean
clean:
	rm -fr build
	rm -f $(OBJECTS)

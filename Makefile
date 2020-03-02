CC=gcc
CFLAGS=-O2 -Isrc -DNDEBUG $(OPTFLAGS)
LDLIBS=
LDFLAGS=$(OPTLIBS)

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TARGET=build/libdcplog.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

all: $(TARGET) $(SO_TARGET)

$(TARGET): CFLAGS+=-fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

build:
	@mkdir -p build

dev: CFLAGS=-g -O2 -Isrc -Wall -Wextra -Werror $(OPTFLAGS)
dev: all

.PHONY: clean
clean:
	rm -fr build $(OBJECTS)

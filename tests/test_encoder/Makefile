INCLUDE_DIRS:=include ../../include
COMPILE_DIRS:=source ../../source
LIB_DIRS:=

TEST_FILES:= $(notdir $(wildcard ./source/*.c ))

EXEC_TARGET:=$(shell basename $(CURDIR))

##FILES THAT NEED TO BE COMPILED
CFILES:= $(TEST_FILES) 
##EXISTING LIBNAMES THAT NEED TO BE LINKED lib<name>
LIBS_TO_LINK:=
##PACKAGE CONFIG LIBS
PKG_CONFIG_LIBS:=cunit
PKG_CONF_LIBFLAGS:=$(shell pkg-config --libs $(PKG_CONFIG_LIBS))
PKG_CONF_CFLAGS:=$(shell pkg-config --cflags $(PKG_CONFIG_LIBS))


LIBNAMES:=$(patsubst lib%.a,%,$(LIBFILES)) $(patsubst lib%,%,$(LIBS_TO_LINK)) 
LIBFLAGS:=$(patsubst %,-L%,$(LIB_DIRS)) $(patsubst %,-l%,$(LIBNAMES)) $(PKG_CONF_LIBFLAGS)

DIRS:=objects
VPATH:=$(INCLUDE_DIRS) $(COMPILE_DIRS) $(LIB_DIRS) $(DIRS)

INCLUDEFLAGS:=$(patsubst %,-I%,$(INCLUDE_DIRS)) $(PKG_CONF_CFLAGS)
CPPFLAGS:=$(INCLUDEFLAGS)
CFLAGS:=-g -Wall -std=c99
CFILENAMES:=$(notdir $(CFILES))
COBJECTS:=$(patsubst %.c,%.o,$(CFILENAMES))
CC:=gcc

.PHONY: clean run

all: $(EXEC_TARGET) 

$(EXEC_TARGET): $(DIRS) $(COBJECTS) $(LIBFILES)
	gcc $(CFLAGS) $(patsubst %,objects/%,$(COBJECTS)) $(LIBFLAGS) -o $@
$(COBJECTS): %.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o objects/$@

$(DIRS): %:
	mkdir -p $@

clean:
	rm -fr $(DIRS)
	rm -f $(EXEC_TARGET)
test:$(EXEC_TARGET) 
	./$(EXEC_TARGET)

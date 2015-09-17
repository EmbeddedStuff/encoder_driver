INCLUDE_DIRS:=include 
COMPILE_DIRS:=source
LIB_DIRS:= 

LIBTARGET:= encoder.a

##FILES THAT NEED TO BE COMPILED
CFILES:= encoder.c
##LIBRARIES THAT NEED TO BE CREATED
LIBFILES:=
##EXISTING LIBNAMES THAT NEED TO BE LINKED lib<name>
LIBS_TO_LINK:=

LIBNAMES:= $(patsubst lib%.a,%,$(LIBFILES)) $(patsubst lib%,%,$(LIBS_TO_LINK)) 
#LIBFLAGS:= -static $(patsubst %,-L%,$(LIB_DIRS)) $(patsubst %,-l%,$(LIBNAMES))

DIRS:= objects bin
VPATH:= $(INCLUDE_DIRS) $(COMPILE_DIRS) $(LIB_DIRS) $(DIRS)

INCLUDEFLAGS:=$(patsubst %,-I%,$(INCLUDE_DIRS))
CPPFLAGS:= $(INCLUDEFLAGS)
CFLAGS:= -g -Wall -std=c99
CFILENAMES:=$(notdir $(CFILES))
COBJECTS:=$(patsubst %.c,%.o,$(CFILENAMES))
CC:=gcc

.PHONY: clean run

all: $(LIBTARGET) 

$(LIBTARGET): $(DIRS) $(COBJECTS) $(LIBFILES)
	ar rcs ./bin/$@ objects/*.o
$(COBJECTS): %.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o objects/$@

$(DIRS): %:
	mkdir -p $@

clean:
	rm -fr $(DIRS)
	make -s --directory=tests clean
run: $(EXEC_TARGET)
	./$(EXEC_TARGET)
buildTest:
	make -s --directory=tests
test:
	make -s --directory=tests test

BINARY=hotloader
CODEDIRS=./src/hotloader ./src/common
INCDIRS=$(CODEDIRS) $(HOME)/source/lib/raylib/include/
LIBDIRS=. $(HOME)/source/lib/raylib/lib/
BUILDDIR=.#/build

CC=g++
OPT=-O3

# generate files that encode make rules for the .h dependencies
DEPFLAGS=-MP -MD

# automatically add the -I onto each include directory
CFLAGS=-Wall -Wextra -Wno-missing-field-initializers -ggdb $(foreach D,$(INCDIRS),-I$(D)) $(OPT) $(DEPFLAGS) -fPIC
LDFLAGS=$(foreach D,$(LIBDIRS),-L$(D)) $(foreach D,$(LIBDIRS),-Wl,-rpath,"$(D)") -lraylib -lm -ldl

# for-style iteration (foreach) and regular expression completions (wildcard)
CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.cpp))

# regular expression replacement
OBJECTS=$(patsubst %.cpp,%.o,$(CFILES))
DEPFILES=$(patsubst %.cpp,%.d,$(CFILES))

all: $(BINARY)

module:
	make -C ./src/module/

$(BINARY): $(OBJECTS)
	$(CC) -o $(BUILDDIR)/$@ $^ $(LDFLAGS)

# only want the .cpp file dependency here, thus $< instead of $^.
#
%.o:%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES)
	rm module.so
	make clean -C ./src/module/

# include the dependencies
-include $(DEPFILES)

# add .PHONY so that the non-targetfile - rules work even if a file with the same name exists.
.PHONY: all clean

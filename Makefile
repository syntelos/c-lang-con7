#
# COMPILER
#
CC := clang
#
# REPRESENTATION [600] SUSv3 / UNIX 03 / POSIX.1-2001
#
PORTABILITY := -D_XOPEN_SOURCE=600
#
# CONSISTENCY
#
WARNINGS := #-Wno-long-long -Wall -pedantic -Werror
#
# INSPECTION
#
DEBUG := -g -ggdb
#
# STRUCTURE
#
CCFLAGS := $(PORTABILITY) -Iinc -Ic-lang-bix/c-endian-bint/inc -Ic-lang-bix/inc $(WARNINGS) $(DEBUG)

LDFLAGS := -lm #-lpthread
#
# DEPENDENCIES
#
HEADERS := inc/*.h

SOURCES := src/*.c
#
# SUBMODULES
#
BIX_HEADERS := c-lang-bix/c-endian-bint/inc/*.h c-lang-bix/inc/*.h

BIX_SOURCES := c-lang-bix/c-endian-bint/src/*.c c-lang-bix/src/*.c

BINT_CCFLAGS := $(PORTABILITY) -Ic-lang-bix/c-endian-bint/inc -Ic-lang-bix/inc $(WARNINGS) $(DEBUG)

con7: $(HEADERS) $(BIX_HEADERS) $(SOURCES) $(BIX_SOURCES) main/con7.c
	$(CC) $(shell c-lang-bix/c-endian-bint/prep/bint) $(CCFLAGS) -o $@ $(SOURCES) $(BIX_SOURCES) main/con7.c $(LDFLAGS)

c-lang-bix/c-endian-bint/bint: c-lang-bix/c-endian-bint/prep/bint $(BIX_HEADERS) $(BIX_SOURCES) c-lang-bix/c-endian-bint/bint.c
	$(CC) $(shell c-lang-bix/c-endian-bint/prep/bint) $(BINT_CCFLAGS) -o $@ $(BIX_SOURCES) c-lang-bix/c-endian-bint/bint.c

c-lang-bix/c-endian-bint/prep/bint: c-lang-bix/c-endian-bint/prep/bint.c
	$(CC) -o c-lang-bix/c-endian-bint/prep/bint c-lang-bix/c-endian-bint/prep/bint.c

clean:
	rm -f c-lang-bix/c-endian-bint/bint c-lang-bix/c-endian-bint/prep/bint con7 core

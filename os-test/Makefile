CC=cc
RM=rm -rf
AR=ar
CLFAGS=-Wall -Werror -Wno-unused-result -Iinclude
LDFLAGS=
LDLIBS=

DEBUG ?= 1
ifeq ($(DEBUG), 1)
CFLAGS = $(CLFAGS) -g3 -Og -DDEBUG
BUILDDIR = build/debug/
else
CFLAGS = $(CLFAGS) -Os
BUILDDIR = build/release/
endif

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRCS=$(call rwildcard,src,*.c)
OBJS=$(patsubst src/%.c,$(BUILDDIR)obj/%.o,$(SRCS))

OUTPUT=blackbox_test
OUTPUTPATH=$(BUILDDIR)bin/$(OUTPUT)

.PHONY: clean distclean

all: $(OUTPUTPATH)

$(OUTPUTPATH): $(OBJS)
	@mkdir -p $$(dirname $@)
	@# generate compile commands
	@cc -E -x c++ - -v < /dev/null 2>&1 | awk '/End of search list./ { show=0 } { if (show) printf "-I%s\n",$$1 }; /#include <...> search starts here:/ { show=1; }' | tr '\n' ' ' > system_headers.txt
	@echo -n "[{\"directory\":\"$(shell pwd)\",\"command\":\"clang $(CFLAGS) " > compile_commands.json
	@cat system_headers.txt | tr '\n' ' ' >> compile_commands.json
	@echo "\",\"file\":\"src/*.c\"}]" >> compile_commands.json
	$(CC) $(CFLAGS) -o $(OUTPUTPATH) $(OBJS) $(LDFLAGS) $(LDLIBS)

$(OBJS): $(BUILDDIR)obj/%.o: src/%.c
	@mkdir -p $$(dirname $@)
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	$(RM) $(BUILDDIR)obj/*

distclean: clean
	$(RM) $(OUTPUTPATH)

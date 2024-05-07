# Makefile for parse-rss example

APP := parse-rss

# you are free to override CFLAGS and LDFLAGS  (passed unmodified)
CFLAGS := -Wall -g
LDFLAGS := -g

# these are mandatory and should not be overriden (unless you are cross-building)
MY_CFLAGS := $(shell pkg-config --cflags libxml-2.0)
MY_LDFLAGS := $(shell pkg-config --libs-only-other libxml-2.0)
# LDLIBS should NOT be overriden)
LDLIBS := $(shell pkg-config --libs-only-l libxml-2.0)

# added $(MY_CFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(MY_CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
# added $(MY_LDFLAGS)
LINK.o = $(CC) $(LDFLAGS) $(MY_LDFLAGS) $(TARGET_ARCH)

all: $(APP)

$(APP) : $(APP).o
$(APP).o : $(APP).c

run: $(APP) dsa.xml
	./$(APP) dsa.xml

valgrind: $(APP) dsa.xml
	valgrind ./$(APP) dsa.xml

clean:
	rm -f -- $(APP) $(APP).o
.PHONY: clean run valgrind


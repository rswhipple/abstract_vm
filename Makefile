CC := gcc
CXX := g++
CXXFLAGS := -Wall -Wextra -Werror -fsanitize=address -g3

# Using CURDIR to set the directories
SRCDIR = $(CURDIR)/src
INCDIR = $(CURDIR)/../inc
BUILDDIR = $(CURDIR)/../build
LIBDIR = $(BUILDDIR)/lib
LIBRARY = $(LIBDIR)/libmyabstractvm.a

# Recursively gather all source files
SOURCES = $(shell find $(SRCDIR) -name '*.cpp')
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))
INCLUDES = -I$(INCDIR)

all: $(LIBRARY)

$(LIBRARY): $(OBJECTS)
	@mkdir -p $(LIBDIR)
	ar rcs $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	rm -f $(OBJECTS) $(LIBRARY)

# Phony targets
.PHONY: all clean
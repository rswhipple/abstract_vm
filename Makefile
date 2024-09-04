# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Werror -Iinc

# Directories
SRCDIR := src
INCDIR := inc
BUILDDIR := build
TARGET := abstract_vm

# Source and object files
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

# Default target
all: $(TARGET)

# Linking the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compiling source files to object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Create build directory if it doesn't exist
$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

# Clean target to remove built files
clean:
	rm -rf $(BUILDDIR) $(TARGET)

# Phony targets
.PHONY: all clean

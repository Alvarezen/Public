CXX := g++
TARGET := linux_esat_rpg

SRCDIR = ../src
OBJDIR = ../build
BINDIR = ../bin

CXXFLAGS := -std=c++11 -g -O2 -Wall -Wno-reorder
CPPFLAGS := -I../deps/sfml_linux/include -I../include -I../include/sql -I../include/utils -I../include/imgui -I../include/scenes
LDFLAGS := -L../deps/sfml_linux/lib
LIBS := -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lGL -lsqlite3
FLAGS := $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)

SOURCES := $(shell find $(SRCDIR)/ -name "*.cc" -type f)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cc=$(OBJDIR)/%.o)

.PHONY: all clean

all:	$(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(OBJECTS)
	@echo "Linking..."
	$(CXX) $(OBJECTS) $(FLAGS) $(LIBS) -o $@
	@echo "End Linged!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cc
	@echo "Compiling $<..."
	$(CXX) $(FLAGS) -c $< -o $@

clean:
	-rm -rf $(OBJECTS) $(BINDIR)/$(TARGET)

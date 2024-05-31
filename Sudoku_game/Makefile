CXX = gcc
CXXFLAGS = -Wall -g
SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,%.o,$(SOURCES))
EXECUTABLE = Sudoku

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -fopenmp -o $@

%.o: $(SRCDIR)/%.c
	$(CXX) $(CXXFLAGS) -c  $< -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)

.PHONY: all clean
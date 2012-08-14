CC := gcc
CCFLAGS := -pedantic -Wall -Werror -g -lmingw32 -lSDLmain -lSDL -lm -lglu32 -lopengl32

SRCDIRS := ../src
SOURCES := $(foreach DIR, $(SRCDIRS), $(wildcard $(DIR)/*.c))
TARGET := ../bin/FreeEvolution.exe

.PHONY: all
.PHONY: clean
.PHONY: Debug
.PHONY: Release

all: $(TARGET)
	cp SDL.dll ../bin/
	
clean:
	rm -f $(TARGET)

Debug: all

Release: all
	
$(TARGET): $(SOURCES)
	mkdir -p $(@D)
	$(CC) -o $(TARGET) $(SOURCES) $(CCFLAGS)

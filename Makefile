TARGET := Mario.exe

SRC := src
BUILD := build
INCLUDE := include
LIB := lib

SRCS := $(shell find $(SRC) -type f -name '*.cpp')
OBJS := $(subst $(SRC)/,$(BUILD)/,$(addsuffix .o,$(basename $(SRCS))))

# Precompiled header
PCH := $(BUILD)/pch.h.gch

# Compiler flags for debug and release
DEBUG_FLAGS := -std=c++17 -I$(INCLUDE) -g -O0 -Wall -DDebug 
RELEASE_FLAGS := -std=c++17 -I$(INCLUDE) -O3 

# Libraries for Windows and Linux
ifeq ($(OS),Windows_NT)
    LIBS := -L$(LIB) -lraylib -lopengl32 -lgdi32 -lwinmm -lcomdlg32 -lole32
else
    LIBS := -L$(LIB) -lraylib 
endif



$(TARGET): $(OBJS)
	mkdir -p $(dir $@)
	g++ $(OBJS) -o $@ $(LIBS)

# Rule to compile the precompiled header
$(PCH): include/pch.h
	mkdir -p $(BUILD)
	g++ $(RELEASE_FLAGS) -x c++-header $< -o $@

$(BUILD)/%.o: $(SRC)/%.cpp $(PCH)
	mkdir -p $(dir $@)
	g++ $(FLAGS) -c $< -o $@ 

.PHONY: all clean debug release

all: release

release: FLAGS := $(RELEASE_FLAGS)
release: $(TARGET)

debug: FLAGS := $(DEBUG_FLAGS)
debug: $(TARGET)

clean:
	rm -rf $(BUILD)
	rm -f $(TARGET)

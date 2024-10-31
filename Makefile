TARGET := Mario.exe

SRC := src
BUILD := build
INCLUDE := include
LIB := lib

all: debug

SRCS := $(shell find $(SRC) -type f -name '*.cpp')
OBJS := $(subst $(SRC)/,$(BUILD)/,$(addsuffix .o,$(basename $(SRCS))))

# Precompiled header
PCH_H := $(INCLUDE)/pch.h 
PCH_GCH := $(BUILD)/pch.h.gch  # Change the output path to BUILD

# Compiler flags for debug and release
DEBUG_FLAGS := -std=c++17 -I$(INCLUDE) -g -O0 -D_DEBUG -include $(PCH_H) -H
RELEASE_FLAGS := -std=c++17 -I$(INCLUDE) -O3 -Wall -include $(PCH_H) -H
PCH_FLAGS := -std=c++17 -O3 -x c++-header
FLAGS := $(DEBUG_FLAGS)

# Libraries for Windows and Linux
ifeq ($(OS),Windows_NT)
    LIBS := -L$(LIB) -lraylib -lopengl32 -lgdi32 -lwinmm -lcomdlg32 -lole32
else
    LIBS := -L$(LIB) -lraylib 
endif

$(TARGET): $(OBJS) $(PCH_GCH)
	mkdir -p $(dir $@)
	g++ $(OBJS) -o $@ $(LIBS)

# Rule to compile the precompiled header
$(PCH_GCH): $(PCH_H)
	mkdir -p $(BUILD)
	g++ $(PCH_FLAGS) $(PCH_H) -o $@

$(BUILD)/%.o: $(SRC)/%.cpp $(PCH_GCH)
	mkdir -p $(dir $@)
	g++ $(FLAGS) -c $< -o $@ 

.PHONY: all clean debug release

release: FLAGS := $(RELEASE_FLAGS)
release: $(TARGET)

debug: FLAGS := $(DEBUG_FLAGS)
debug: $(TARGET)

clean:
	rm -rf $(BUILD)
	rm -f $(TARGET)

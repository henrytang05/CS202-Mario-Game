TARGET := Mario

SRC := src
BUILD := build
INCLUDE := include
LIB := lib

SRCS := $(shell find $(SRC) -type f -name '*.cpp')
OBJS := $(subst $(SRC)/,$(BUILD)/,$(addsuffix .o,$(basename $(SRCS))))

# Precompiled header
PCH := $(BUILD)/pch.h.gch

FLAGS := -std=c++17 -I$(INCLUDE) -g

all: $(TARGET)

$(TARGET): $(OBJS)
ifeq ($(OS),Windows_NT)
	mkdir -p $(dir $@)
	g++ $(OBJS) -o $@ -L$(LIB) -lraylib -lopengl32 -lgdi32 -lwinmm -lcomdlg32 -lole32
else
	mkdir -p $(dir $@)
	g++ $(OBJS) -o $@ -lGL -lGLU -lglut -L$(LIB) -lraylib
endif

# Rule to compile the precompiled header
$(PCH): include/pch.h
	mkdir -p $(BUILD)
	g++ $(FLAGS) -x c++-header $< -o $@

$(BUILD)/%.o: $(SRC)/%.cpp $(PCH)
	mkdir -p $(dir $@)
	g++ $(FLAGS) -c $< -o $@ 

.PHONY: all clean
clean:
	rm -rf $(BUILD)

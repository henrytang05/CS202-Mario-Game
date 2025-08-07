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
DEBUG_FLAGS := -std=c++17 -I$(INCLUDE) -g -O0 -D_DEBUG -include $(PCH_H)
RELEASE_FLAGS := -std=c++17 -I$(INCLUDE) -O3 -Wall -include $(PCH_H)
PCH_FLAGS := -std=c++17 -O0 -x c++-header
FLAGS := $(DEBUG_FLAGS)

UNAME_S := $(shell uname -s)
ifeq ($(OS),Windows_NT)
    LIBS := -L$(LIB) -lraylib -lopengl32 -lgdi32 -lwinmm -lcomdlg32 -lole32
else ifeq ($(UNAME_S), Darwin)
	RAYLIB_DIR := /opt/homebrew/opt/raylib
	LIBS := -L$(RAYLIB_DIR)/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
else
    LIBS := -L$(LIB) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
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



TEST_TARGET := MarioTest.exe
TESTS := tests
BUILD := build
TEST_BUILD := $(BUILD)/tests
TEST_FLAGS := -std=c++17 -I$(INCLUDE) -g -O0 -include $(PCH_H) -lgtest -lgtest_main -pthread
TEST_SRCS := $(shell find $(TESTS) -type f -name '*.cpp')
TEST_OBJS := $(subst $(TESTS)/,$(TEST_BUILD)/,$(addsuffix .o,$(basename $(TEST_SRCS))))


$(TEST_BUILD)/%.o: $(TESTS)/%.cpp
	@mkdir -p $(dir $@)
	g++ $(TEST_FLAGS) -c $< -o $@

test: FLAGS := $(TEST_FLAGS)
test: $(TEST_OBJS) $(PCH_GCH)
	g++ $(TEST_OBJS) -o $(TEST_TARGET) $(TEST_FLAGS)
	./$(TEST_TARGET)

clean_test: 
	rm -rf $(TEST_BUILD)
	rm -f $(TEST_TARGET)

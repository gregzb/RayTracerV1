TARGET_EXEC ?= program

BUILD_DIR ?= ./out
SRC_DIRS ?= ./src

SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d) ./include
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -std=c++17
#$(pkg-config --cflags --libs sdl2)
#-Wall
LDFLAGS ?= -lm -std=c++17 -O3
CFLAGS = -Wall
#CXXFLAGS = -Wall -Wextra -Werror
CXXFLAGS = -Wall -std=c++17 -O3
CC = g++
CXX = g++

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
	./$(BUILD_DIR)/$(TARGET_EXEC)

# assembly
$(BUILD_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	#$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean run auto $(BUILD_DIR)/$(TARGET_EXEC)

clean:
	-$(RM) -r $(BUILD_DIR)
	-$(RM) -r .vscode

run:
	./$(BUILD_DIR)/$(TARGET_EXEC)

-include $(DEPS)

MKDIR_P ?= mkdir -p

BUILD = vm

CC = gcc

CPPFLAGS = $(CPP_DIRS)
# CFLAGS =
# LDFLAGS = $(LD_DIRS)
# LDLIBS = -l

CPP_DIRS = -I$(INC_DIR)
# LD_DIRS = -L

# ----------------------------------------------------------------------------------------------------

SRC_DIR = ./src
INC_DIR = ./inc
# INC_SUBDIRS = $(shell find $(INC_DIR) -mindepth 1 \! -empty -type d)
# CONF_DIR = ./conf
# STRUCT_DIR = ./struct
BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj

# ----------------------------------------------------------------------------------------------------

_SRC = $(wildcard $(SRC_DIR)/*.c)
# _INC = $(wildcard $(INCLUDES)/*.h)
# _OBJ = $(wildcard $(OBJ_DIR)/*.o)

# ----------------------------------------------------------------------------------------------------

# first rule to build the program
.PHONY: all
all: dir build

# ----------------------------------------------------------------------------------------------------

INCLUDES = $(INC_DIR)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(_SRC))

# compiling the program
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# linking the program
$(BUILD_DIR)/$(BUILD): $(OBJS)
	$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@

# ----------------------------------------------------------------------------------------------------

.PHONY: dir
dir:
	@mkdir -p -v $(BUILD_DIR)
	@mkdir -p -v $(OBJ_DIR)

.PHONY: build
build: $(BUILD_DIR)/$(BUILD)

.PHONY: run
#run: build
run: all
# load from file
#	@$(BUILD_DIR)/$(BUILD) hello.vm
# load from stdin
	@$(BUILD_DIR)/$(BUILD) < hello.vm
#	@$(BUILD_DIR)/$(BUILD)

.PHONY: clean
clean:
	@rm -f -r -v $(BUILD_DIR)

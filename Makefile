CC = gcc

CFLAGS = $(INC)
LDFLAGS =

BUILD = vm

SRC_DIR = ./source
INC_DIR = ./include
BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/object

_SRC = $(wildcard $(SRC_DIR)/*.c)
_INC = $(wildcard $(INC_DIR)/*)
_OBJ = $(wildcard $(OBJ_DIR)/*.o)

INC = $(patsubst %,-I%,$(_INC))
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(_SRC))

.PHONY: all
all: dir build

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(_INC)
	$(CC) -c $< -o $@ $(CFLAGS) 

$(BUILD_DIR)/$(BUILD): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS) 

.PHONY: dir
dir:
	@mkdir -p -v $(OBJ_DIR)
	@mkdir -p -v $(BUILD_DIR)

.PHONY: build
build: $(BUILD_DIR)/$(BUILD)

.PHONY: run
run: build
	@$(BUILD_DIR)/$(BUILD) hello_world.vm

.PHONY: clean
clean:
	@rm -f -v $(_OBJ)
	@rm -f -v -d $(OBJ_DIR)
	@rm -f -v $(BUILD_DIR)/$(BUILD)
	@rm -f -v -d $(BUILD_DIR)

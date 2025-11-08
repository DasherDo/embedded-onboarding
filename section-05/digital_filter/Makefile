CFLAGS = -I./inc -Wall -g

# Directories
SRC_DIR = ./Src
INC_DIR = ./Inc
BUILD_DIR = ./build

# Files
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/filter.c
HEADERS = $(INC_DIR)/main.h $(INC_DIR)/filter.h

EXE = $(BUILD_DIR)/main.exe
OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/filter.o

# Default target
all: $(EXE)

$(EXE): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(OBJS) -o $@

# Compile each .c to .o and generate .lst
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	$(CC) $(CFLAGS) -S $< -o $(BUILD_DIR)/$*.lst

# Clean build directory
clean:
	rm -rf $(BUILD_DIR)/*

.PHONY: all clean
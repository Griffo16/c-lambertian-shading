# ---------------------------------------------------------------
#  SDL2 C project Makefile
#  Compiles every .c file under src/ (including subfolders) and
#  links them with SDL2 into bin/$(TARGET).
# ---------------------------------------------------------------

TARGET   := app

CC       := gcc
SRC_DIR  := src
INC_DIR  := include
OBJ_DIR  := build
BIN_DIR  := bin

# Find all .c files in src/ recursively
SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

# SDL2 flags: prefer pkg-config, fall back to sdl2-config
SDL_CFLAGS := $(shell pkg-config --cflags sdl2 2>/dev/null || sdl2-config --cflags)
SDL_LIBS   := $(shell pkg-config --libs sdl2 2>/dev/null || sdl2-config --libs)

CFLAGS   := -std=c11 -Wall -Wextra -I$(INC_DIR) $(SDL_CFLAGS) -MMD -MP
LDFLAGS  := $(SDL_LIBS) -lm

# Build mode: `make` = debug, `make release` = optimised
CFLAGS_DEBUG   := -g -O0 -DDEBUG
CFLAGS_RELEASE := -O2 -DNDEBUG

.PHONY: all debug release run clean

all: debug

debug: CFLAGS += $(CFLAGS_DEBUG)
debug: $(BIN_DIR)/$(TARGET)

release: CFLAGS += $(CFLAGS_RELEASE)
release: clean $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

run: debug
	./$(BIN_DIR)/$(TARGET)

clean:
	rm -rf $(OBJ_DIR)/*.o $(OBJ_DIR)/*.d $(OBJ_DIR)/*/ $(BIN_DIR)

-include $(DEPS)

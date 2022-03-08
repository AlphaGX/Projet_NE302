# Tar config
NAMES=LAPIERRE_GARDE_ROUGE_RANC
PREFIX=http

# Compilation
CC=gcc
FLAGS=-Wall -Wextra -Werror -g

# Files and directories
SRC=$(wildcard *.c)

OBJS=$(SRC:.c=.o)
OBJ_PATH=objs/

BIN=parser

# Rules

# Default Rule
all: dir $(OBJS)
	$(CC) $(FLAGS) -o $(BIN) $(OBJ_PATH)*

# Creating directories
dir:
	@mkdir -p $(OBJ_PATH)

# All objects rule
%.o: %.c
	$(CC) $(FLAGS) -c $^ -o $(OBJ_PATH)$@

# Quick run
run: all
	@./$(BIN) test0.txt 0

# Cleaning the files
clean:
	@echo cleaning objects and exec
	rm -rf $(OBJ_PATH)*.o $(BIN)
	rmdir $(OBJ_PATH)

# Create an archive
tar: clean
	dir=$$(basename $$PWD) && echo "compressing $(dir)" && cd .. && \
	tar cvfz "$(PREFIX)-$(NAMES).tgz" \
	--transform="s,^$$dir,$(PREFIX)-$(NAMES)," \
	--exclude="$(IGNORE)" "$$dir" --verbose --show-transformed-names

# Ignore non file targets
.PHONY: all dir run clean tar

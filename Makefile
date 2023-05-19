##
## EPITECH PROJECT, 2023
## Bootstrap
## File description:
## Makefile
##

.SILENT:

# --- Project Settings ---

# Change this to your compiler, if empty, it will use gcc
CC = g++

# Change this to your source folder,
# Leave blank if you want to compile all files in the current workspace
FILES_SOURCE = src

# Change this to your include folder, leave blank if you don't have one
INCLUDE_SOURCE = include

# Add your flags here
CFLAGS = -W -Wall -Wextra -std=c++17

LDFLAGS = -lraylib

# Change this to your program name
NAME = YinChillang

# ------------------------

# --- Do not touch ---

ifeq ($(CC), g++)
	FILES_EXTENTION = cpp
else ifeq ($(CC), gcc)
	FILES_EXTENTION = c
endif

SRC = $(shell find $(FILES_SOURCE) -name "*.$(FILES_EXTENTION)")

OBJ = $(SRC:.$(FILES_EXTENTION)=.o)

CPPFLAGS = -I./$(INCLUDE_SOURCE) -I./src/Main/ -I./src/Primitives/ -I./src/PostProcessor/

ifeq ($(NAME),)
	NAME = program
endif

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
RESET = \033[0m

COLUMNS = $(shell tput cols)
HALF_COLUMNS = $(shell expr $(COLUMNS) / 4)
NB_FILES := $(words $(SRC))

ifneq ($(NB_FILES), 1)
	FILES_NAME = Files
else
	FILES_NAME = File
endif

ifneq ($(words $(CFLAGS)), 1)
	FLAGS_NAME = flags
else
	FLAGS_NAME = flag
endif

.PHONY: run

all: $(NAME)
	@echo "$(GREEN)$(NB_FILES) $(FILES_NAME) compiled successfully !$(RESET)"
	@echo "$(GREEN)Used $(FLAGS_NAME) : $(RESET)$(WHITE)$(CFLAGS)$(RESET)"
	@echo "$(GREEN)Program name: $(RESET)$(MAGENTA)$(NAME)$(RESET)"

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) -lconfig++ $(LDFLAGS)
	@echo $(shell printf "%-$(HALF_COLUMNS)s" " " | tr " " "-")

%.o: %.$(FILES_EXTENTION)
	@echo "$(BLUE)Compiling $<$(RESET)"
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	@echo "$(RED)$(NB_FILES) $(FILES_NAME) deleted !$(RESET)"

fclean:	clean
	@$(RM) $(NAME)
	@echo "$(RED)Binary './$(NAME)' deleted !$(RESET)"

re:	fclean all
	@echo "$(YELLOW)Program recompiled !$(RESET)"

run: all
	@echo $(shell printf "%-$(HALF_COLUMNS)s" " " | tr " " "-")
	@echo "$(BLUE)Running program...$(RESET)"
	@echo $(shell printf "%-$(HALF_COLUMNS)s" " " | tr " " "-")
	@./$(NAME) $(ARGS)

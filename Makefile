# Colors
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[1;33m
NC=\033[0m

# Executable
NAME = ft_nm
CC = cc
FLAGS = -Wall -Wextra -Werror 

# Includes
INCLUDES = -I./inc -I./libft/inc

# Libft
LIBFT = libft/libft.a
LIBFT_DIR = libft

# Source & object
SRC_DIR = src
OBJ_DIR = obj

SRC_FILES = main \
	core/elf_utils core/file_utils core/handle_elf_file \
	core/elf_parser_32 core/elf_parser_64 \
	sections/sections_32/read_sections_32 sections/sections_32/section_utils_32 \
	sections/sections_64/read_sections_64 sections/sections_64/section_utils_64 \
	symbols/symbols_32/collect_symbols_32 \
	symbols/symbols_32/display_symbols_32 \
	symbols/symbols_32/get_symbol_letter_32 \
	symbols/symbols_32/read_symbols_32 \
	symbols/symbols_32/skip_symbol_32 \
	symbols/symbols_32/sort_symbols_32 \
	symbols/symbols_32/symbol_builder_32 \
	symbols/symbols_64/collect_symbols_64 \
	symbols/symbols_64/display_symbols_64 \
	symbols/symbols_64/get_symbol_letter_64 \
	symbols/symbols_64/read_symbols_64 \
	symbols/symbols_64/skip_symbol_64 \
	symbols/symbols_64/sort_symbols_64 \
	symbols/symbols_64/symbol_builder_64 \

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES:=.c))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:=.o))

# Tests
TEST_DIR      = tests
TEST_SCRIPT   = $(TEST_DIR)/run_tests.sh
TEST_OBJ_DIR  = $(TEST_DIR)/obj
TEST_EXP_DIR  = $(TEST_DIR)/expected
TEST_ACT_DIR  = $(TEST_DIR)/actual

# Default target
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@echo "${GREEN}Creating executable $(NAME)${NC}"
	@$(CC) $(OBJ) $(LIBFT) -no-pie -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "${YELLOW}Compiling $<${NC}"
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "${GREEN}Building libft${NC}"
	@$(MAKE) -C $(LIBFT_DIR)

# Cleaning rules
clean:
	@echo "${RED}Cleaning object files${NC}"
	@rm -rf $(OBJ_DIR)
	@echo "${YELLOW}Cleaning libft${NC}"
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "${RED}Removing executable $(NAME)${NC}"
	@rm -f $(NAME)
	@echo "${YELLOW}Full clean of libft${NC}"
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# Test rules
test: all
	@echo "\n${YELLOW}Running test suite...${NC}\n"
	@cd $(TEST_DIR) && ./run_tests.sh

test_clean:
	@echo "${RED}Cleaning test outputs${NC}"
	@rm -rf $(TEST_OBJ_DIR) $(TEST_EXP_DIR) $(TEST_ACT_DIR)

test_re: test_clean test

.PHONY: all clean fclean re test test_clean test_re
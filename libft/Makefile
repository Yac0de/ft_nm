# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/17 15:07:23 by ymeziane          #+#    #+#              #
#    Updated: 2023/10/18 13:30:56 by ymeziane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIE
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc

RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[1;33m
NC=\033[0m

SRC_IS = ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint
SRC_STR = ft_strlen ft_strlcpy ft_strlcat ft_strchr ft_strrchr \
			ft_strnstr ft_strcmp ft_strncmp ft_substr ft_strjoin ft_strtrim \
			ft_split ft_strmapi ft_striteri ft_strdup ft_strcpy
SRC_MEM = ft_memset ft_bzero ft_memcpy ft_memmove ft_memchr \
			ft_memcmp ft_calloc
SRC_TO = ft_atoi ft_atol ft_toupper ft_tolower ft_itoa	
SRC_PUT = ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd
SRC_LST = ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast \
			ft_lstadd_back ft_lstdelone ft_lstclear ft_lstiter \
			ft_lstmap ft_print_list_content_int
SRC_UTILS = ft_count_digit ft_hex_len ft_swap
SRC_GNL = get_next_line_utils get_next_line
SRC_PRINTF = ft_handle_percent ft_printf ft_handle_char \
            ft_handle_hex ft_handle_int ft_handle_pointer \
			ft_handle_string ft_handle_unsigned ft_process_string

SRC_IS := $(addsuffix .c, $(SRC_IS))
SRC_STR := $(addsuffix .c, $(SRC_STR))
SRC_MEM := $(addsuffix .c, $(SRC_MEM))
SRC_TO := $(addsuffix .c, $(SRC_TO))
SRC_PUT := $(addsuffix .c, $(SRC_PUT))
SRC_LST := $(addsuffix .c, $(SRC_LST))
SRC_UTILS := $(addsuffix .c, $(SRC_UTILS))
SRC_GNL := $(addsuffix .c, $(SRC_GNL))
SRC_PRINTF := $(addsuffix .c, $(SRC_PRINTF))

SRCS_IS = $(addprefix $(SRC_DIR)/ft_is/, $(SRC_IS))
SRCS_STR = $(addprefix $(SRC_DIR)/ft_str/, $(SRC_STR))
SRCS_MEM = $(addprefix $(SRC_DIR)/ft_mem/, $(SRC_MEM))
SRCS_TO = $(addprefix $(SRC_DIR)/ft_to/, $(SRC_TO))
SRCS_PUT = $(addprefix $(SRC_DIR)/ft_put/, $(SRC_PUT))
SRCS_LST = $(addprefix $(SRC_DIR)/ft_lst/, $(SRC_LST))
SRCS_UTILS = $(addprefix $(SRC_DIR)/ft_utils/, $(SRC_UTILS))
SRCS_GNL = $(addprefix $(SRC_DIR)/get_next_line/, $(SRC_GNL))
SRCS_PRINTF = $(addprefix $(SRC_DIR)/printf/, $(SRC_PRINTF))

SRCS = $(SRCS_IS) $(SRCS_STR) $(SRCS_MEM) $(SRCS_TO) $(SRCS_PUT) $(SRCS_LST) $(SRCS_UTILS) $(SRCS_GNL) $(SRCS_PRINTF)
OBJS = $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRCS:.c=.o))

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "${YELLOW}Compiling $<${NC}"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(NAME): $(OBJS)
	@echo "${GREEN}Linking into $(NAME)${NC}"
	@ar rcs $(NAME) $(OBJS)

clean:
	@echo "${RED}Cleaning object files...${NC}"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "${RED}Removing library $(NAME)${NC}"
	@rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: athierry <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/17 22:36:58 by athierry          #+#    #+#              #
#    Updated: 2023/06/23 23:23:25 by athierry         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# ******************************* NAMES ************************************** #
# **************************************************************************** #

NAME = minishell

# **************************************************************************** #
# ******************************* FLAGS ************************************** #
# **************************************************************************** #

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
CPPFLAGS = -Wall -Wextra -Werror -std=c++98

CHECKFLAGS = -fsanitize=address -g3
PPCHECKFLAGS = -fsanitize=address -g3

DEBUGFLAGS = -Wall -Wextra -Werror -g3
CPPDEBUGFLAGS = -Wall -Wextra -Werror -g3

ifeq ($(MAKECMDGOALS),debug)
CFLAGS += $(DEBUGFLAGS)
CPPFLAGS += $(PPDEBUGFLAGS)
endif

ifeq ($(MAKECMDGOALS),check)
CFLAGS += $(CHECKFLAGS)
CPPFLAGS += $(CPPCHECKFLAGS)
endif

RM = rm -f

# **************************************************************************** #
# ******************************* INCLUDE************************************* #
# **************************************************************************** #

HEAD_PATH = include/

# **************************************************************************** #
# ******************************* SOURCES ************************************ #
# **************************************************************************** #

MAIN_PATH =
MAIN_FILES = main.cpp

MAIN = $(addprefix $(MAIN_PATH),$(MAIN_FILES))

PARSR_PATH = parsr/
PARSR_FILES = parsr.cpp
PARSR = $(addprefix $(PARSER_PATH),$(PARSER_FILES))

SERVR_PATH = servr/
SERVR_FILES = servr.cpp
SERVR = $(addprefix $(LAUNCHR_PATH),$(LAUNCHR_FILES))

BUILTIN_PATH = builtin/
BUILTIN_FILES = cd.c 
BUILTIN = $(addprefix $(BUILTIN_PATH),$(BUILTIN_FILES))

SRCS_PATH = srcs/
SRCS_FILES = $(MAIN) $(PARSER) $(LAUNCHR) $(BUILTIN)
SRCS = $(addprefix $(SRCS_PATH),$(SRCS_FILES))
		
# **************************************************************************** #
# ******************************* OBJECTS ************************************ #
# **************************************************************************** #

OBJS_PATH = obj/
OBJS_FILES = $(SRCS_FILES:.c=.o)
OBJS = $(addprefix $(OBJS_PATH),$(OBJS_FILES))

# **************************************************************************** #
# ******************************* DEPENDENCIES ******************************* #
# **************************************************************************** #

DEPS = $(OBJS:.o=.d)

# **************************************************************************** #
# ******************************* RULES ************************************** #
# **************************************************************************** #

.PHONY: all
all: $(NAME)

-include $(DEPS)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lreadline

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@[ -d $(OBJS_PATH) ] || mkdir -p $(OBJS_PATH)
	@[ -d $(OBJS_PATH)$(MAIN_PATH) ] || mkdir -p $(OBJS_PATH)$(MAIN_PATH)
	@[ -d $(OBJS_PATH)$(PARSER_PATH) ] || mkdir -p $(OBJS_PATH)$(PARSER_PATH)
	@[ -d $(OBJS_PATH)$(LAUNCHR_PATH) ] || mkdir -p $(OBJS_PATH)$(LAUNCHR_PATH)
	@[ -d $(OBJS_PATH)$(BUILTIN_PATH) ] || mkdir -p $(OBJS_PATH)$(BUILTIN_PATH)
	@[ -d $(OBJS_PATH)$(LIBFT_PATH) ] || mkdir -p $(OBJS_PATH)$(LIBFT_PATH)
	$(CC) -MMD $(CPPFLAGS) -o $@ -c $< -lreadline

.PHONY: clean
clean:
	$(RM) $(OBJS) $(DEPS)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all

.PHONY: dirty
dirty: re
	@$(RM) $(OBJS) $(DEPS)

.PHONY: debug
debug: dirty

.PHONY: check
check: dirty

.DEFAULT_GOAL := all

# **************************************************************************** #

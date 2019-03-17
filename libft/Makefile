# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/13 13:11:49 by aben-azz          #+#    #+#              #
#    Updated: 2019/03/17 18:56:42 by aben-azz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libft.a
SRC				=	ft_counti.c ft_round.c ft_intlen.c ft_ftoa.c ft_pow.c \
ft_count.c ft_indexof.c ft_isupper.c ft_islower.c ft_atoi.c ft_isalnum.c \
ft_bzero.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd.c  \
ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_memalloc.c ft_memccpy.c \
ft_lstdel.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c \
ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c \
ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c ft_strclr.c \
ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c \
ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c ft_strtrim.c \
ft_strsplit.c ft_strstr.c ft_strsub.c ft_toupper.c ft_strmapi.c ft_strncat.c \
ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c \
ft_putnbr.c ft_isalpha.c ft_tolower.c get_next_line.c ft_repeat_char.c \
ft_utoa_base.c ft_intlen_base.c min.c max.c ft_printf.c geters.c \
handle_numbers.c handlers.c ft_lstrev.c ft_lstdestroy.c ft_count_words.c \
ft_itoa_base.c rgb2dec.c ft_percent.c get_color_from_percent.c ft_rand.c

_END			=	\x1b[0m
_BOLD			=	\x1b[1m
_UNDER			=	\x1b[4m
_REV			=	\x1b[7m
_GREY			=	\x1b[30m
_RED			=	\x1b[31m
_GREEN			=	\x1b[32m
_YELLOW			=	\x1b[33m
_BLUE			=	\x1b[34m
_PURPLE			=	\x1b[35m
_CYAN			=	\x1b[36m
_WHITE			=	\x1b[37m
_IGREY			=	\x1b[40m
_IRED			=	\x1b[41m
_IGREEN			=	\x1b[42m
_IYELLOW		=	\x1b[43m
_IBLUE			=	\x1b[44m
_IPURPLE		=	\x1b[45m
_ICYAN			=	\x1b[46m
_IWHITE			=	\x1b[47m
INCLUDE			=	-Iincludes/
CFLAGS			=	-Wall -Wextra -Werror
MSG				=	Compilation de la libft:
GCC				=	gcc $(CFLAGS) $(INCLUDE)

SRCPATH			=	./src
SRCBINARY		=	./
SRCOBJ			=	obj/

OBJ				=	$(patsubst %.c,${OBJDIR}%.o,$(SRCS))
SRCS			=	$(addprefix $(SRCPATH)/, $(SRC))
LONGEST			=	$(shell echo $(notdir $(SRCS)) | tr " " "\n" | awk ' { if (\
				length > x ) { x = length; y = $$0 } }END{ print y }' | wc -c)

$(OBJDIR)%.o:	%.c
	@$(GCC) -o $@ $< -c
	@printf "$(_BOLD)$(_PURPLE)$(MSG)$(_END) $(_CYAN)%-$(LONGEST)s\
	$(_END)" $(notdir $<)
	@if test -s $*.c; then \
	printf "$(_GREEN)[OK]\n$(_END)";\
	else \
	printf "$(_RED)[ERROR]\n$(_END)"; fi

$(NAME):		$(OBJ)
	@echo "$(_BOLD)$(_YELLOW)Creation de la libft ...$(_END)"
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "$(_BOLD)$(_GREEN)Compilation de la libft terminée => ${NAME}$(_END)"

all:			$(NAME)

clean:
			@/bin/rm -rf $(OBJ) $(SRCOBJ)
			@echo "$(_BOLD)$(_RED)Suppression des objets terminée$(_END)"

fclean:			clean
			@/bin/rm -rf $(NAME) .DS_Store
			@echo "$(_BOLD)$(_RED)Suppression de {${NAME}} terminée$(_END)"

re:			fclean  all


.PHONY:		all clean fclean re

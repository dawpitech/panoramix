##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Makefile
##

CC	:=	gcc

CFLAGS	=	-std=gnu17
CFLAGS	+=	-W
CFLAGS	+=	-Wall
CFLAGS	+=	-Wextra
CFLAGS	+=	-Wundef
CFLAGS	+=	-Wshadow
CFLAGS	+=	-Wunreachable-code
CFLAGS	+=	-pedantic
CFLAGS	+=	-iquote include/ -g3
CFLAGS	+=	-MMD -MP

BDIR	=	.build

SRC		=	$(shell find "src" -name "*.c")
OBJ		=	$(SRC:%.c=$(BDIR)/%.o)

NAME	=	panoramix

.DEFAULT_GOAL := all

.PHONY: all
all: $(NAME)

$(BDIR)/%.o: %.c
	@ mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS)

$(NAME): $(OBJ)
	$(CC) $^ $(CFLAGS) -o $@

.PHONY: clean
clean:
	@ rm -rf $(BDIR)

.PHONY: fclean
fclean: clean
	@ rm -f $(NAME)

.NOTPARALLEL: re
.PHONY: re
re: fclean all

-include $(OBJ:.o=.d)

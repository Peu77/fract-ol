# #pragma omp parallel
# -fopenmp
# gcc -fopenmp -o fract_ol main.c libmlx.a -lXext -lX11 -lm && ./fract_ol

NAME = fract_ol
CC = cc
CFLAGS = -I ft_printf -I ft_printf/libft
MLX = libmlx.a
FT_PRINTF = ft_printf/libftprintf.a

SRC = main.c \
	  input.c \
	  utils.c \
	  fractals.c \
 	  render.c \


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ft_printf
	@$(CC) -o $(NAME) $(OBJ) $(FT_PRINTF) $(MLX) -lXext -lX11 -lm

%.o: %.c
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	@make -C ft_printf clean
	@rm -f $(OBJ)

fclean: clean
	@make -C ft_printf fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
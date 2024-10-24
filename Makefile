NAME = fractol
CC = cc
CFLAGS = -I ft_printf -I ft_printf/libft -framework OpenGL -framework AppKit
MLX = libmlx.a
FT_PRINTF = ft_printf/libftprintf.a
BIN_DIR = bin

SRC = main.c \
   input.c \
   utils.c \
   fractals.c \
   render_thread.c \
   event_handler.c \
   color.c

OBJ = $(SRC:%.c=$(BIN_DIR)/%.o)

all: $(BIN_DIR) $(NAME)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(NAME): $(OBJ)
	@make -C ft_printf
	@$(CC) -o $@ $(OBJ) $(FT_PRINTF) $(MLX) -lm $(CFLAGS)

$(BIN_DIR)/%.o: %.c
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	@make -C ft_printf clean
	@rm -f $(OBJ)

fclean: clean
	@make -C ft_printf fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
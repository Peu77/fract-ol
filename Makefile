NAME = fractol
CC = cc
CFLAGS = -I ft_printf -I ft_printf/libft -I minilibx -framework OpenGL -framework AppKit
FT_PRINTF = ft_printf/libftprintf.a
MINILIBX = minilibx/libmlx.a
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
	@make -C minilibx
	@$(CC) -o $@ $(OBJ) $(FT_PRINTF) $(MINILIBX) -lm $(CFLAGS)

$(BIN_DIR)/%.o: %.c
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	@make -C ft_printf clean
	@make -C minilibx clean
	@rm -f $(OBJ)

fclean: clean
	@make -C ft_printf fclean
	@make -C minilibx clean
	@rm -f $(NAME)

re:
	@make fclean
	@make -C ft_printf fclean
	@make -C minilibx fclean
	@make all

.PHONY: all clean fclean re
NAME = fractol
CC = cc
CFLAGS = -I ft_printf -I ft_printf/libft -I minilibx -framework OpenGL -framework AppKit
FT_PRINTF = ft_printf/libftprintf.a
MINILIBX_DIR = minilibx
BIN_DIR = bin

SRC = main.c \
   input.c \
   utils.c \
   fractals.c \
   render_thread.c \
   common_render.c \
   event_handler.c \
   color.c

OBJ = $(SRC:%.c=$(BIN_DIR)/%.o)

ifeq ($(shell uname), Linux)
	CFLAGS = -I ft_printf -I ft_printf/libft -I minilibx-linux -lXext -lX11 -lm
	MINILIBX_DIR = minilibx-linux
endif

MINILIBX = $(MINILIBX_DIR)/libmlx.a

all: $(BIN_DIR) $(NAME)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(NAME): $(OBJ)
	@make -C ft_printf
	@make -C $(MINILIBX_DIR)
	@$(CC) -o $@ $(OBJ) $(FT_PRINTF) $(MINILIBX) -lm $(CFLAGS)

$(BIN_DIR)/%.o: %.c
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	@make -C ft_printf clean
	@make -C $(MINILIBX_DIR) clean
	@rm -f $(OBJ)

fclean: clean
	@make -C ft_printf fclean
	@make -C $(MINILIBX_DIR) clean
	@rm -f $(NAME)

re:
	@make fclean
	@make -C ft_printf fclean
	@make -C $(MINILIBX_DIR) clean
	@make all

.PHONY: all clean fclean re
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:30:11 by eebert            #+#    #+#             */
/*   Updated: 2024/10/24 10:30:18 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

# include <stdbool.h>

# define WIDTH 1000
# define HEIGHT 900
# define TITLE "Fractol"

# ifdef __linux__
#  define ESC 65307
#  define SPACE 32
#  define ARROW_RIGHT 65363
#  define ARROW_LEFT 65361
#  define ARROW_UP 65362
#  define ARROW_DOWN 65364
# endif

# ifdef __APPLE__
#  define ESC 53
#  define SPACE 49
#  define ARROW_RIGHT 124
#  define ARROW_LEFT 123
#  define ARROW_UP 126
#  define ARROW_DOWN 125
# endif

# define NUM_THREADS 16

//#define CUSTOM_CURSOR

typedef struct s_vec2
{
	double				x;
	double				y;
}						t_vec2;

typedef struct s_vec2i
{
	int					x;
	int					y;
}						t_vec2i;

typedef int				(*t_get_color_func)(int, const int);

t_get_color_func		get_next_color_func(void);

struct					s_fractal;

typedef int				(*t_fractal_in_set)(double, double, struct s_fractal *);

typedef struct s_complex
{
	double				r;
	double				i;
}						t_complex;

typedef struct s_fractal
{
	struct s_complex	c;
	int					max_iter;

	t_fractal_in_set	in_set;
}						t_fractal;

typedef struct s_render_data
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*img_data;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
	double				min_x;
	double				max_x;
	double				min_y;
	double				max_y;
	t_fractal			*fractal;
	t_get_color_func	get_color_func;
	bool				update_frame;
}						t_render_data;

void					init_fractal(t_fractal *data);

void					init_render_data(t_render_data *data);

void					draw_custom_cursor(void *mlx, void *win);

void					draw_help_text(t_render_data *render_data);

int						parse_args(int argc, char **argv, t_fractal *data);

int						in_set_mandelbrot(double x, double y, t_fractal *data);

int						in_set_julia(double x, double y, t_fractal *data);

int						in_burning_ship(double x, double y, t_fractal *data);

int						in_set_nova(double x, double y, t_fractal *data);

void					apply_color_of_fractal_at_pos(
							t_render_data *render_data,
							t_vec2 index, t_vec2 z);

int						mouse_hook(int button, int x, int y, void *param);

int						key_hook(int key, void *param);

void					safe_exit(t_render_data *render_data);

// utils

float					ft_atof(const char *str);

#endif
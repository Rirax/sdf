/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlechapt <rlechapt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/18 15:55:13 by rlechapt          #+#    #+#             */
/*   Updated: 2015/01/19 22:57:19 by rlechapt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	TABtoDRAW(t_env *e)
{
	int	i;
	int	j;

	i = 0;
	ft_putnbr(e->count);
	while (i < e->count)
	{
		j = i + 1;
		while (j < e->count)
		{
			if (e->mp[i]->y == e->mp[j]->y && e->mp[j]->x == e->mp[i]->x + 1)
				horizontal_projection(e, i, j);
			else if (e->mp[i]->x == e->mp[j]->x &&
					e->mp[j]->y == e->mp[i]->y + 1)
				vertical_projection(e, i, j);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
}

int		key_hook(int keycode, t_env *e)
{
	printf("key: %d\n", keycode);
	if (keycode == 65363)
		e->moveX += 10;
	if (keycode == 65361)
		e->moveX -= 10;
	if (keycode == 65364)
		e->moveY += 10;
	if (keycode == 65362)
		e->moveY -= 10;
	if (keycode == 61)
		e->cste += 2;
	if (keycode == 45)
		e->cste -= 2;
	if (keycode == 65307)
		exit(0);
	return (0);
}

/*void	control(t_env *e)
{
	int	i;

	i = 0;

	while (i < e->count)
	{
		ft_putstr("x:");
		ft_putnbr(e->mp[i]->x);
		ft_putchar(' ');
		ft_putstr("y:");
		ft_putnbr(e->mp[i]->y);
		ft_putchar(' ');
		ft_putstr("z:");
		ft_putnbr(e->mp[i]->z);
		ft_putchar('\n');
		i++;
	}
}*/

void	get_tab(t_env *e, char **tmp)
{
	int		i;
	int		j;
	int		k;
	char	**tmp2;

	if ((e->mp = (t_map**)malloc(sizeof(t_map*) * e->count)) == NULL)
		return ;
	i = 0;
	k = 0;
	while (tmp[i])
	{
		tmp2 = ft_strsplit(tmp[i], ' ');
		j = 0;
		while (tmp2[j])
		{
			e->mp[k] = (t_map *)malloc(sizeof(t_map));
			e->mp[k]->x = j + 1;
			e->mp[k]->y = i + 1;
			e->mp[k]->z = ft_atoi(tmp2[j]);
			j++;
			k++;
		}
		i++;
	}
}

void	get_long(t_env *e)
{
	int		i;
	int		j;
	char	**tmp;
	char	**tmp2;

	tmp = ft_strsplit(e->str, '\n');
	i = 0;
	e->count = 0;
	while (tmp[i])
	{
		tmp2 = ft_strsplit(tmp[i], ' ');
		j = 0;
		while (tmp2[j])
			j++;
		e->count += j;
		i++;
	}
	get_tab(e, tmp);
}

int		loop_hook(t_env *e)
{
	if (e->moveX != e->Xsav || e->moveY != e->Ysav || e->cste != e->csts)
	{
		ft_clear_image(e);
		TABtoDRAW(e);
		e->Xsav = e->moveX;
		e->Ysav = e->moveY;
		e->csts = e->cste;
	}
	return (0);
}

int		expose_hook(t_env *e)
{
	e->moveX = 400;
	e->moveY = 400;
	e->cste = 25;
	e->black = mlx_get_color_value(e->mlx, 0x000000);
	e->color = mlx_get_color_value(e->mlx, 0xFFFFFF);
	TABtoDRAW(e);
	return (0);
}

char	*keep_numbers(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] >= 48 && str[i] <= 57)
			i++;
		if (str[i] != '\n' && str[i] != ' ')
		{
			if ((str[i] == 43 || str[i] == 45) &&
					(str[i + 1] >= 48 && str[i + 1] <= 57))
				;
			else
				str[i] = ' ';
		}
		i++;
	}
	return (str);
}

int		main(int argc, char **argv)
{
	int		fd;
	int		ret;
	char	buf[BUFF_SIZE + 1];
	t_env	e;

	argc = argc;
	e.str = "";
	fd = open(argv[1], O_RDONLY);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		e.str = ft_strjoin(e.str, buf);
	}
	e.str = keep_numbers(e.str);
	get_long(&e);
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, 1920, 1080, "fdf");
	e.img = mlx_new_image(e.mlx, 1920, 1080);
	e.data = mlx_get_data_addr(e.img, &e.bpp, &e.sizeline, &e.endian);
	mlx_key_hook(e.win, key_hook, &e);
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_loop_hook(e.mlx, loop_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}

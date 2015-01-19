/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlechapt <rlechapt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 21:54:27 by rlechapt          #+#    #+#             */
/*   Updated: 2015/01/19 23:02:53 by rlechapt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_image(t_env *e, int x, int y)
{
	ft_putnbr(x);
	ft_putchar('\n');
	ft_putnbr(y);
	ft_putchar('\n');
//	while (x >= 0 && x <= 1920 && y >= 0 && y <= 1080)
//	{
		e->p = y * e->sizeline + (e->bpp / 8) * x;
		ft_memcpy(&e->data[e->p], &e->color, (e->bpp / 8));
//	}
}

void	ft_clear_image(t_env *e)
{
	int	x;
	int	y;

	x = -1;
	while (++x < 1920)
	{
		y = -1;
		while (++y < 1080)
			ft_memcpy(e->data + (y * e->sizeline) + (x * (e->bpp / 8)),
					&e->black, e->bpp / 8);
	}
}

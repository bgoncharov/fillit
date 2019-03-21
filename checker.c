/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogoncha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 11:58:26 by bogoncha          #+#    #+#             */
/*   Updated: 2019/03/20 11:58:30 by bogoncha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		is_valid(int c, int i)
{
	if (c == '.' || c == '#'
		|| ((c == '\n') && ((i % 5 == 4) || (i == 20))))
		return (1);
	return (0);
}

int		check_tet(char *buf, int i)
{
	int		count;

	/*if (i == 19)
		return (0);*/
	count = 0;
	if (buf[i] == '#')
	{
		if (i > 0 && buf[i - 1] == '#')
			count++;
		if (i < 19 && buf[i + 1] == '#')
			count++;
		if (i >= 5 && buf[i - 5] == '#')
			count++;
		if (i <= 14 && buf[i + 5] == '#')
			count++;
	}
	return (count + check_tet(buf, ++i));
}

int		check_buf(char *buf)
{
	int		i;
	int		part;
	int		start;
	int		res;

	i = 0;
	part = 0;
	while (buf[i] && is_valid(buf[i], i) && part <= 4)
	{
		if (buf[i] == '#')
		{
			part++;
			if (part == 1)
				start = i;
		}
		i++;
	}
	if (i >= 20 && !buf[i] && part == 4 && (res = check_tet(buf, start)))
	{
		if (res == 6 || res == 8)
			return (1);
	}
	else
		ft_error();
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:28:15 by ymeziane          #+#    #+#             */
/*   Updated: 2023/11/07 14:27:14 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	handle_string(va_list args)
{
	char	*c;
	int		count;

	count = 0;
	c = (char *)va_arg(args, char *);
	if (!c)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (*c)
	{
		ft_putchar_fd(*c, 1);
		count++;
		c++;
	}
	return (count);
}

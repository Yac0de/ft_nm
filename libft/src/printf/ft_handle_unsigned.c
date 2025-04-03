/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:36:15 by ymeziane          #+#    #+#             */
/*   Updated: 2023/11/24 15:30:08 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	count_digit_unsigned(unsigned int n)
{
	unsigned int	digits;

	digits = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		digits++;
		n /= 10;
	}
	return (digits);
}

static void	ft_putnbr_unsignedint_fd(unsigned int n, unsigned int fd)
{
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
		ft_putchar_fd(n + '0', fd);
}

int	handle_unsigned(va_list args)
{
	int				count;
	unsigned int	val;

	val = (unsigned int)va_arg(args, unsigned int);
	count = count_digit_unsigned(val);
	ft_putnbr_unsignedint_fd(val, 1);
	return (count);
}

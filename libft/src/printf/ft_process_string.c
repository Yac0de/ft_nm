/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:28:50 by ymeziane          #+#    #+#             */
/*   Updated: 2023/11/24 15:30:08 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_specifier(const char specifier, va_list args)
{
	if (specifier == 'c')
		return (handle_char(args));
	else if (specifier == 's')
		return (handle_string(args));
	else if (specifier == 'p')
		return (handle_pointer(args));
	else if (specifier == 'd' || specifier == 'i')
		return (handle_int(args));
	else if (specifier == 'u')
		return (handle_unsigned(args));
	else if (specifier == 'x' || specifier == 'X')
		return (handle_hex(args, specifier));
	else if (specifier == '%')
		return (handle_percent('%'));
	return (0);
}

int	process_string(const char *format, va_list args)
{
	int	count;

	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			count += handle_specifier(*format, args);
			format++;
		}
		else
		{
			ft_putchar_fd(*format, 1);
			count++;
			format++;
		}
	}
	return (count);
}

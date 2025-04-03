/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:41:39 by ymeziane          #+#    #+#             */
/*   Updated: 2023/11/24 15:30:08 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_hex_len(uintptr_t ptr)
{
	int	len;

	len = 0;
	while (ptr)
	{
		ptr /= 16;
		len++;
	}
	return (len);
}

static void	print_hex_recursive(uintptr_t ptr)
{
	const char	hex_chars[] = "0123456789abcdef";

	if (ptr >= 16)
		print_hex_recursive(ptr / 16);
	write(1, &hex_chars[ptr % 16], 1);
}

int	handle_pointer(va_list args)
{
	uintptr_t	ptr;
	int			count;

	ptr = (uintptr_t)va_arg(args, void *);
	if (!ptr)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	count = 2;
	count += get_hex_len(ptr);
	print_hex_recursive(ptr);
	return (count);
}

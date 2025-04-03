/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:47:32 by ymeziane          #+#    #+#             */
/*   Updated: 2023/11/24 15:30:08 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_hex_len(unsigned int num)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num)
	{
		num /= 16;
		len++;
	}
	return (len);
}

static void	print_hex_recursive(unsigned int num, const char *hex_chars)
{
	if (num >= 16)
		print_hex_recursive(num / 16, hex_chars);
	write(1, &hex_chars[num % 16], 1);
	return ;
}

int	handle_hex(va_list args, char letter)
{
	int				count;
	unsigned int	num;
	const char		lowercase_hex_chars[] = "0123456789abcdef";
	const char		uppercase_hex_chars[] = "0123456789ABCDEF";

	count = 0;
	num = va_arg(args, unsigned int);
	count += get_hex_len(num);
	if (letter == 'x')
		print_hex_recursive(num, lowercase_hex_chars);
	else
		print_hex_recursive(num, uppercase_hex_chars);
	return (count);
}

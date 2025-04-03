/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:54:24 by ymeziane          #+#    #+#             */
/*   Updated: 2023/11/27 15:08:33 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*dest;
	int			i;

	i = 1;
	dest = NULL;
	if (BUFFER_SIZE == 0 || fd < 0)
		return (0);
	if (ft_chr(buff) == 1)
	{
		ft_buf_cut(buff);
		dest = ft_join(dest, buff);
	}
	while (i > 0 && ft_chr(buff) == 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i <= 0)
			return (dest);
		buff[i] = '\0';
		dest = ft_join(dest, buff);
	}
	return (dest);
}

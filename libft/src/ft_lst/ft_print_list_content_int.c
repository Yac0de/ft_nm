/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list_content_int.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:45:06 by ymeziane          #+#    #+#             */
/*   Updated: 2023/12/12 17:50:59 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_list_content_int(t_list *lst)
{
	if (!lst)
		return ;
	while (lst)
	{
		ft_putnbr_fd(*((int *)lst->content), 1);
		ft_putchar_fd('\n', 1);
		lst = lst->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnth.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:49:05 by ymeziane          #+#    #+#             */
/*   Updated: 2023/12/26 10:19:49 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnth(t_list *lst, unsigned int nth)
{
	while (lst && nth > 0)
	{
		lst = lst->next;
		nth--;
	}
	return (lst);
}

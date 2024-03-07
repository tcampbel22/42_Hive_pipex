/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_count.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:05:19 by tcampbel          #+#    #+#             */
/*   Updated: 2023/12/12 10:40:18 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_count(char a, int *ptr)
{
	if (*ptr == -1)
		return (-1);
	if (write(1, &a, 1) == -1)
	{
		*ptr = -1;
		return (-1);
	}
	return (1);
}

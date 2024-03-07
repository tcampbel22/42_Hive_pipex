/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:09:32 by tcampbel          #+#    #+#             */
/*   Updated: 2023/11/22 11:25:45 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_count(char *str, int *ptr)
{
	int	count;

	count = 0;
	if (str == NULL)
		return (ft_putstr_count("(null)", ptr));
	while (*str)
	{
		count += ft_putchar_count(*str, ptr);
		str++;
	}
	return (count);
}

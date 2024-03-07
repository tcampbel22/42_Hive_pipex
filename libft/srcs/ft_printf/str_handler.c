/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:26:42 by tcampbel          #+#    #+#             */
/*   Updated: 2023/12/12 10:46:47 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	str_handler(char flag, va_list ap, int *ptr)
{
	int	count;

	count = 0;
	if (flag == 'c')
		count += ft_putchar_count(va_arg(ap, int), ptr);
	else if (flag == 's')
		count += ft_putstr_count(va_arg(ap, char *), ptr);
	else if (flag == 'd' || flag == 'i')
		count += ft_putnbr_count(va_arg(ap, int), ptr);
	else if (flag == 'x' || flag == 'X')
		count += ft_puthex_count(va_arg(ap, unsigned int), flag, ptr);
	else if (flag == 'u')
		count += ft_putnbr_count(va_arg(ap, unsigned int), ptr);
	else if (flag == 'p')
	{
		count += ft_putstr_count("0x", ptr);
		count += ft_puthex_count(va_arg(ap, unsigned long long), flag, ptr);
	}
	else if (flag == '%')
		count += ft_putchar_count('%', ptr);
	return (count);
}

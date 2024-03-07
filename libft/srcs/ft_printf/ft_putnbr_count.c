/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:37:32 by tcampbel          #+#    #+#             */
/*   Updated: 2023/11/22 11:43:52 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	digit_counter(long nb)
{
	int	count;

	count = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		count++;
		nb *= -1;
	}
	while (nb > 0)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

int	ft_putnbr_count(long nb, int *ptr)
{
	if (nb < 0)
	{
		ft_putchar_count('-', ptr);
		ft_putnbr_count(-nb, ptr);
	}
	else if (nb < 10)
		ft_putchar_count(nb + 48, ptr);
	else if (nb >= 10)
	{
		ft_putnbr_count(nb / 10, ptr);
		ft_putchar_count((nb % 10) + 48, ptr);
	}
	return (digit_counter(nb));
}

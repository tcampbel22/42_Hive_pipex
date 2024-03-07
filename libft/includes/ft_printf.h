/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:34:42 by tcampbel          #+#    #+#             */
/*   Updated: 2023/12/22 11:17:49 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *str, ...);
int	str_handler(char flag, va_list ap, int *ptr);
int	ft_putchar_count(char c, int *ptr);
int	ft_putstr_count(char *s, int *ptr);
int	ft_putnbr_count(long n, int *ptr);
int	ft_puthex_count(unsigned long nb, char flag, int *ptr);
#endif

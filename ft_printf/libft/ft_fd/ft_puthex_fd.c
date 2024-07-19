/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:52:41 by smontuor          #+#    #+#             */
/*   Updated: 2023/11/16 17:57:55 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex_fd(unsigned int num, char format, int fd)
{
	char	*base;
	int		print_length;

	print_length = 0;
	if (format == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (num == 0)
		print_length += ft_putchar_fd('0', fd);
	else
		print_length += ft_putnbrbase_wrapper_fd(num, base, fd);
	return (print_length);
}

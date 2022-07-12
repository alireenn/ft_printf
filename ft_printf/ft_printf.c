/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:16:20 by anovelli          #+#    #+#             */
/*   Updated: 2022/03/02 16:23:37 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

t_flag	*new_flag(t_flag *flag)
{
	flag->count = 0;
	return (flag);
}

int	ft_deno(char *str, int i, t_flag *flag)
{
	if (str[i] == 'c')
		ft_c(va_arg(flag->arg, int), flag);
	else if (str[i] == 's')
		ft_s(va_arg(flag->arg, char *), flag);
	else if (str[i] == 'd' || str[i] == 'i')
		ft_di(va_arg(flag->arg, int), flag);
	else if (str[i] == 'x')
		ft_x(va_arg(flag->arg, unsigned int), flag, "0123456789abcdef");
	else if (str[i] == 'X')
		ft_x(va_arg(flag->arg, unsigned int), flag, "0123456789ABCDEF");
	else if (str[i] == 'p')
		ft_p(va_arg(flag->arg, unsigned long long), flag);
	else if (str[i] == 'u')
		ft_u(va_arg(flag->arg, unsigned int), flag);
	else if (str[i] == '%')
		flag->count += write(1, "%", 1);
	return (i);
}

int	ft_printf(const char *str, ...)
{
	t_flag	*flag;
	int		i;
	int		len;

	i = -1;
	len = 0;
	flag = (t_flag *)malloc(sizeof(t_flag));
	if (!flag)
		return (0);
	flag = new_flag(flag);
	va_start(flag->arg, str);
	while (str[++i])
	{
		if (str[i] == '%')
		{
			i++;
			i = ft_deno((char *)str, i, flag);
		}
		else
			len += write(1, &str[i], 1);
	}
	va_end(flag->arg);
	len += flag->count;
	free (flag);
	return (len);
}

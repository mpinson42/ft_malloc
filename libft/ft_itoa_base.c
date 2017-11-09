/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 14:58:53 by mpinson           #+#    #+#             */
/*   Updated: 2017/04/06 14:58:57 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_len(intmax_t n, int base)
{
	int i;

	i = 0;
	while (n != 0)
	{
		n = n / base;
		i++;
	}
	return (i);
}

static void	is_neg(int *neg, intmax_t *n)
{
	if (n[0] < 0)
	{
		neg[0] = 0;
		n[0] = -n[0];
	}
}

static char	*init(int *neg, int *i)
{
	char *cmp;

	cmp = "0123456789ABCDEF";
	neg[0] = 1;
	i[0] = 0;
	return (cmp);
}

char		*ft_itoa_base(intmax_t n, int base)
{
	int		i;
	int		len;
	int		neg;
	char	*str;
	char	*cmp;

	cmp = init(&neg, &i);
	len = ft_get_len(n, base);
	is_neg(&neg, &n);
	if (n == 0)
		return (ft_strdup("0"));
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len + 1] = 0;
	while (len + 1)
	{
		str[len] = cmp[n % base];
		n = n / base;
		len--;
	}
	if (str[0] == '0')
	{
		cmp = str;
		str = ft_strsub(cmp, 1, ft_strlen(str) - 1);
		free(cmp);
	}
	return (str);
}

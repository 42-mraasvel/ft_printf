/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/25 14:52:30 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/13 17:05:28 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char			*d;
	const unsigned char		*s;

	d = dest;
	s = src;
	if (d == s)
		return (dest);
	if (dest > src)
	{
		while (n > 0)
		{
			n--;
			d[n] = s[n];
		}
	}
	else if (dest < src)
		dest = ft_memcpy(dest, src, n);
	return (dest);
}

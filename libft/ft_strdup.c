/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 16:10:10 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/01 08:49:32 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*d;

	len = ft_strlen(s);
	d = ft_calloc(len + 1, 1);
	if (d == 0)
		return (0);
	ft_memcpy(d, s, len + 1);
	return (d);
}

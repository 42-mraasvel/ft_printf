/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 10:38:05 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/01 18:16:37 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*dest;
	unsigned int	i;

	if (s == 0 || f == 0)
		return (0);
	i = ft_strlen(s);
	dest = (char*)ft_calloc(i + 1, sizeof(char));
	if (dest == 0)
		return (0);
	i = 0;
	while (s[i] != 0)
	{
		dest[i] = (*f)(i, s[i]);
		i++;
	}
	return (dest);
}

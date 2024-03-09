/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:14:55 by aggrigor          #+#    #+#             */
/*   Updated: 2024/03/08 22:27:58 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	s_len;
	unsigned int	substr_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len < start)
		substr_len = 0;
	else if (s_len < len)
		substr_len = s_len;
	else
		substr_len = len;
	substr = (char *)malloc(substr_len + 1);
	if (substr == NULL)
		return (NULL);
	s += start;
	substr[substr_len] = '\0';
	while (substr_len--)
		substr[substr_len] = s[substr_len];
	return (substr);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (s == NULL)
		return (len);
	while (s[len])
		len++;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*joined_str;
	char	*str_ptr;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	joined_str = (char *)malloc(s1_len + s2_len + 1);
	if (joined_str == NULL)
		return (NULL);
	str_ptr = joined_str;
	while (*s1)
		*str_ptr++ = *s1++;
	while (*s2)
		*str_ptr++ = *s2++;
	*str_ptr = '\0';
	return (joined_str);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;
	const char	*compare_start;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	while (i < len && big[i] != '\0')
	{
		if (big[i] == little[0])
		{
			j = 0;
			compare_start = big + i;
			while (i + j < len && big[i + j] != '\0'
				&& little[j] != '\0'
				&& big[i + j] == little[j])
				j++;
			if (little[j] == '\0')
				return ((char *)compare_start);
			i += 1;
		}
		else
			i++;
	}
	return (NULL);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL || fd < 0)
		return ;
	while (*s)
		write(fd, s++, 1);
}

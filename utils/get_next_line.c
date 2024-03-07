/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:06:04 by aggrigor          #+#    #+#             */
/*   Updated: 2024/01/29 15:38:32 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	update_linked_list(t_list **last_node, char *buf)
{
	if ((*last_node)->value == NULL)
		(*last_node)->value = buf;
	else
	{
		(*last_node)->next = ft_lstnew(buf);
		(*last_node) = (*last_node)->next;
	}
}

void	free_prev_parts(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		del((*lst)->value);
		free(*lst);
		*lst = next;
	}
	*lst = NULL;
}

char	*make_result_line(char *result, t_list **line, int line_len)
{
	int		i;
	int		j;
	t_list	*line_ptr;
	t_list	*next_node;

	i = 0;
	line_ptr = *line;
	while (i < line_len && line_ptr->value)
	{
		j = 0;
		next_node = line_ptr->next;
		while (i < line_len && line_ptr->value[j])
			result[i++] = line_ptr->value[j++];
		if (line_ptr->value[j] == '\0')
		{
			ft_lstdelone(line_ptr, free);
			line_ptr = next_node;
		}
	}
	if (line_ptr)
		ft_strcpy(line_ptr->value, line_ptr->value + j);
	*line = line_ptr;
	result[line_len] = '\0';
	return (result);
}

int	ft_read_line(int fd, t_list *line)
{
	char	*buf;
	t_list	*last_node;
	ssize_t	bytes_read;

	last_node = line;
	buf = line->value;
	while (!is_end_of_line(buf))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return (0);
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == (ssize_t)(-1))
			return (0);
		else if (bytes_read == 0)
		{
			free(buf);
			return (1);
		}
		buf[bytes_read] = '\0';
		update_linked_list(&last_node, buf);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_list	*line;
	int				line_len;
	char			*result;

	result = NULL;
	if (BUFFER_SIZE < 1 || fd < 0 || read(fd, result, 0) == -1)
		return (NULL);
	if (line == NULL)
		line = ft_lstnew(NULL);
	if (!ft_read_line(fd, line) || line->value == NULL)
	{
		free_prev_parts(&line, free);
		return (NULL);
	}
	line_len = count_line_len(line);
	result = (char *)malloc(line_len + 1);
	if (result == NULL)
		return (NULL);
	result = make_result_line(result, &line, line_len);
	return (result);
}

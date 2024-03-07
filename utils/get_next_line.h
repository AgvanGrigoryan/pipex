/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:06:27 by aggrigor          #+#    #+#             */
/*   Updated: 2024/02/03 14:50:02 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif 

typedef struct s_list
{
	char			*value;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
int		ft_read_line(int fd, t_list *line);
char	*make_result_line(char *result, t_list **line, int line_len);
int		count_line_len(t_list *line);
char	*ft_strcpy(char *dest, char *src);
int		is_end_of_line(char *buf);
t_list	*ft_lstnew(void *content);
void	ft_lstdelone(t_list *lst, void (*del)(void *));

#endif 

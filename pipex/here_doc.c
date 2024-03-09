/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 12:31:04 by aggrigor          #+#    #+#             */
/*   Updated: 2024/03/09 12:31:07 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

int	check_here_doc(int argc, char **argv)
{
	if (argc - 1 >= 5 && ft_strcmp(argv[1], "here_doc") == 0)
		return (1);
	return (0);
}

void	init_here_doc_pipe(t_pipex *pipex)
{
	pipex->here_doc_pipe = malloc(sizeof(int [2]));
	if (pipex->here_doc_pipe == NULL)
		perror_exit(MALLOC_ERR, pipex);
	if (pipe(pipex->here_doc_pipe[0]) == -1)
		perror_exit(PIPE_ERR, pipex);
}

void	here_doc_read(t_pipex *pipex)
{
	char	*buff;
	int		buff_size;

	while (1)
	{
		buff = get_next_line(0);
		buff_size = ft_strlen(buff);
		if (buff == NULL || ft_strcmp(buff, pipex->limiter) == 0)
		{
			free(buff);
			break ;
		}
		write(pipex->here_doc_pipe[0][1], buff, buff_size);
		free(buff);
		buff = NULL;
	}
	close(pipex->here_doc_pipe[0][1]);
}

void	here_doc(t_pipex *pipex)
{
	pipex->cmd_counts = pipex->prog_argc - 4;
	pipex->limiter = ft_strjoin(pipex->prog_args[2], "\n");
	if (pipex->limiter == NULL)
		perror_exit(JOIN_ERR, pipex);
	init_here_doc_pipe(pipex);
	here_doc_read(pipex);
}

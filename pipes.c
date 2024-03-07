/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:10:06 by aggrigor          #+#    #+#             */
/*   Updated: 2024/03/07 21:34:27 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipes(t_pipex *pipex)
{
	int	i;
	if (pipex->is_here_doc == 1)
	{
		pipex->here_doc_pipe = malloc(sizeof(int [2]));
		if (pipex->here_doc_pipe == NULL)
			exit(EXIT_FAILURE);
		if (pipe(pipex->here_doc_pipe[0]) == -1)
		{
			free(pipex->here_doc_pipe);
			exit(EXIT_FAILURE);
		}
	}
	pipex->pipes = malloc(sizeof(int [2]) * (pipex->cmd_counts - 1));
	if (pipex->pipes == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < pipex->cmd_counts - 1)
	{
		if (pipe(pipex->pipes[i]) == -1)
		{
			free(pipex->pipes);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_counts - 1)
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
		i++;
	}
	if (pipex->is_here_doc == 1)
	{
		close(pipex->here_doc_pipe[0][0]);
		close(pipex->here_doc_pipe[0][1]);
	}
	else
		close(pipex->fileout_fd);
	close(pipex->filein_fd);
}

void	dups(t_pipex *pipex, int i)
{
	if (i == 0)
	{
		if (pipex->is_here_doc == 1)
			dup2(pipex->here_doc_pipe[0][0], STDIN_FILENO);
		else
			dup2(pipex->filein_fd, 0);
		dup2(pipex->pipes[0][1], 1);
	}
	else if (i == pipex->cmd_counts - 1)
	{
		dup2(pipex->pipes[i - 1][0], 0);
		dup2(pipex->fileout_fd, 1);
	}
	else
	{
		dprintf(2, "stexic\n");
		dup2(pipex->pipes[i - 1][0], STDIN_FILENO);
		dup2(pipex->pipes[i][1], STDOUT_FILENO);
	}
	close_pipes(pipex);
}

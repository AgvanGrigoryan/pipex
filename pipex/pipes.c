/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:10:06 by aggrigor          #+#    #+#             */
/*   Updated: 2024/03/09 12:25:41 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	init_pipes(t_pipex *pipex)
{
	int	i;

	pipex->pipes = malloc(sizeof(int [2]) * (pipex->cmd_counts - 1));
	if (pipex->pipes == NULL)
		perror_exit(MALLOC_ERR, pipex);
	i = 0;
	while (i < pipex->cmd_counts - 1)
	{
		if (pipe(pipex->pipes[i]) == -1)
			perror_exit(PIPE_ERR, pipex);
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
	close(pipex->fileout_fd);
	pipex->fileout_fd = -1;
	close(pipex->filein_fd);
	pipex->filein_fd = -1;
}

void	first_cmd_dups(t_pipex *pipex)
{
	if (pipex->is_here_doc == 1)
	{
		if (dup2(pipex->here_doc_pipe[0][0], 0) == -1)
			perror_exit(DUP_ERR, pipex);
	}
	else
	{
		if (dup2(pipex->filein_fd, 0) == -1)
			perror_exit(DUP_ERR, pipex);
	}
	if (dup2(pipex->pipes[0][1], 1) == -1)
		perror_exit(DUP_ERR, pipex);
}

void	dups(t_pipex *pipex, int i)
{
	if (i == 0)
		first_cmd_dups(pipex);
	else if (i == pipex->cmd_counts - 1)
	{
		if (dup2(pipex->pipes[i - 1][0], 0) == -1)
			perror_exit(DUP_ERR, pipex);
		if (dup2(pipex->fileout_fd, 1) == -1)
			perror_exit(DUP_ERR, pipex);
	}
	else
	{
		if (dup2(pipex->pipes[i - 1][0], 0) == -1)
			perror_exit(DUP_ERR, pipex);
		if (dup2(pipex->pipes[i][1], 1) == -1)
			perror_exit(DUP_ERR, pipex);
	}
	close_pipes(pipex);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:13:12 by aggrigor          #+#    #+#             */
/*   Updated: 2024/03/07 21:32:52 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_processes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_counts)
	{
		if (wait(NULL) == -1)
		{
			exit(EXIT_SUCCESS);
		}
		i++;
	}
}

void	create_processes(t_pipex *pipex)
{
	pid_t	pid;
	int		i;

	i = 0;
	while (i < pipex->cmd_counts)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			dups(pipex, i);
			config_cmd(pipex, i);
			// dprintf(2, "eyoo\n");
			// dprintf(2, "'%d'\n", execve(pipex->cmd_path, pipex->cmd_args, pipex->cmd_envp));
			if (execve(pipex->cmd_path, pipex->cmd_args, pipex->cmd_envp) == -1)
			{
				exit(EXIT_FAILURE); // MAYBE CREATE CUSTOM EXIT FUNCTION FOR FREE 'PIPEX' STRUCT values
			}
		}
		dprintf(2, "i: %d\n", i);
		i++;
	}
}

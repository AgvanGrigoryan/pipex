/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:13:12 by aggrigor          #+#    #+#             */
/*   Updated: 2024/03/08 22:32:21 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

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
			perror_exit(FORK_ERR, pipex);
		if (pid == 0)
		{
			dups(pipex, i);
			config_cmd(pipex, i);
			if (execve(pipex->cmd_path, pipex->cmd_args, pipex->cmd_envp) == -1)
			{
				perror_exit(EXECVE_ERR, pipex);
			}
		}
		i++;
	}
}

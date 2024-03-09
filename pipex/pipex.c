/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:09:25 by aggrigor          #+#    #+#             */
/*   Updated: 2024/03/08 23:01:28 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	args_validation(int argc, char *argv[], t_pipex *pipex)
{
	if (argc - 1 < MIN_ARGS)
		perror_exit(INVALID_ARG_CNT, pipex);
	if (pipex->is_here_doc == 1)
	{
		pipex->filein_fd = -1;
		pipex->fileout_fd = ft_open_file(argv[argc - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (pipex->fileout_fd == -1)
			perror_exit(FILEOUT_ERR, pipex);
	}
	else
	{
		pipex->filein_fd = ft_open_file(argv[1], O_RDONLY, 0);
		if (pipex->filein_fd == -1)
			perror_exit(FILEIN_ERR, pipex);
		pipex->fileout_fd = ft_open_file(argv[argc - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (pipex->fileout_fd == -1)
			perror_exit(FILEOUT_ERR, pipex);
	}
}

void	init_pipex(int argc, char **argv, char **envp, t_pipex *pipex)
{
	pipex->pipes = NULL;
	pipex->cmd_args = NULL;
	pipex->cmd_envp = envp;
	pipex->cmd_path = NULL;
	pipex->filein_fd = -1;
	pipex->fileout_fd = -1;
	pipex->is_here_doc = check_here_doc(argc, argv);
	pipex->here_doc_pipe = NULL;
	pipex->limiter = NULL;
	pipex->prog_argc = argc;
	pipex->prog_args = argv;
	pipex->cmd_counts = argc - 3;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	init_pipex(argc, argv, envp, &pipex);
	args_validation(argc, argv, &pipex);
	if (pipex.is_here_doc == 1)
		here_doc(&pipex);
	init_pipes(&pipex);
	create_processes(&pipex);
	close_pipes(&pipex);
	wait_processes(&pipex);
	free_pipex(&pipex);
	return (EXIT_SUCCESS);
}

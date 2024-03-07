/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:09:25 by aggrigor          #+#    #+#             */
/*   Updated: 2024/03/07 21:36:19 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	check_here_doc(int argc, char **argv, t_pipex *pipex)
{
	pipex->is_here_doc = (argc - 1 >= 5 && ft_strncmp(argv[1], "here_doc", 8) == 0);
}

void	args_validation(int argc, char *argv[], t_pipex *pipex)
{
	if (argc - 1 < MIN_ARGS)
		print_error_and_exit("Invalid count of arguments\n", CUSTOM_PRINT);
	check_here_doc(argc, argv, pipex);
	if (pipex->is_here_doc == 1)
	{
		pipex->fileout_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (pipex->fileout_fd == -1)
			print_error_and_exit(argv[argc - 1], ERRNO_PRINT);
	}
	else
	{
		pipex->filein_fd = open(argv[1], O_RDONLY);
		if (pipex->filein_fd == -1)
			print_error_and_exit(argv[1], ERRNO_PRINT);
		pipex->fileout_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (pipex->fileout_fd == -1)
		{
			if (close(pipex->filein_fd) == -1)
				print_error_and_exit(argv[1], ERRNO_PRINT);
			print_error_and_exit(argv[argc - 1], ERRNO_PRINT);
		}
	}
}

void	print_error_and_exit(char *str, int is_custom_msg)
{
	if (is_custom_msg == CUSTOM_PRINT)
		ft_putstr_fd(str, 2);
	else
		perror(str);
	exit(EXIT_FAILURE);
}

void	init_pipex(int argc, char **argv, char **envp, t_pipex *pipex)
{
	pipex->prog_argc = argc;
	pipex->prog_args = argv;
	pipex->cmd_envp = envp;
	if (pipex->is_here_doc == 1)
	{
		pipex->cmd_counts = argc - 4;
		pipex->limiter = argv[2];
	}
	else
		pipex->cmd_counts = argc - 3;
}

void	here_doc(t_pipex *pipex)
{
	char	*buff;
	int		buff_size;
	
	pipex->limiter = ft_strjoin(pipex->limiter, "\n");

	while (1)
	{
		buff = get_next_line(0);
		buff_size = ft_strlen(buff);
		if (buff == NULL || ft_strncmp(buff, pipex->limiter, buff_size) == 0)
		{
			break;
		}
		write(pipex->here_doc_pipe[0][1], buff, buff_size);
		free(buff);
	}
	close(pipex->here_doc_pipe[0][1]);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	args_validation(argc, argv, &pipex);
	init_pipex(argc, argv, envp, &pipex);
	init_pipes(&pipex);
	if (pipex.is_here_doc == 1)
		here_doc(&pipex);
	create_processes(&pipex);
	// printf("hey\n");
	close_pipes(&pipex);
	// printf("here\n");
	wait_processes(&pipex);
	// printf("the end\n");
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:45:39 by aggrigor          #+#    #+#             */
/*   Updated: 2024/03/08 22:59:03 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_pipex(t_pipex *pipex)
{
	if (pipex->pipes != NULL)
		free(pipex->pipes);
	if (pipex->cmd_args != NULL)
		free_matrix(pipex->cmd_args);
	if (pipex->cmd_path != NULL)
		free(pipex->cmd_path);
	if (pipex->is_here_doc == 1)
	{
		if (pipex->here_doc_pipe != NULL)
			free(pipex->here_doc_pipe);
		if (pipex->limiter != NULL)
			free(pipex->limiter);
	}
}

void	perror_exit(int err_num, t_pipex *pipex)
{
	if (err_num == INVALID_ARG_CNT)
		ft_putstr_fd("Invalid count of arguments\n", 2);
	else if (err_num == FILEOUT_ERR)
		perror(pipex->prog_args[pipex->prog_argc - 1]);
	else if (err_num == FILEIN_ERR)
		perror(pipex->prog_args[1]);
	else if (err_num == FILEIN_ERR)
		perror(pipex->prog_args[1]);
	else if (err_num == JOIN_ERR)
		perror("join failed");
	else if (err_num == MALLOC_ERR)
		perror("malloc failed");
	else if (err_num == PIPE_ERR)
		perror("pipe failed");
	else if (err_num == FORK_ERR)
		perror("fork failed");
	else if (err_num == DUP_ERR)
		perror("dup failed");
	else if (err_num == CMD_NOT_FOUND)
		ft_putstr_fd(": Command not found\n", 2);
	else if (err_num == EXECVE_ERR)
		perror("execve failed");
	free_pipex(pipex);
	exit(EXIT_FAILURE);
}

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

int	ft_strcmp(char *s1, char *s2)
{
	while ((*s1 && *s2) && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned int)*s1 - (unsigned int)*s2);
}

int	ft_open_file(char *file, int open_flag, int mode)
{
	return (open(file, open_flag, mode));
}

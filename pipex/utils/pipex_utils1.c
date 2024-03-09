/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:09:31 by aggrigor          #+#    #+#             */
/*   Updated: 2024/03/08 22:35:22 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**get_envp_paths(char *envp[], t_pipex *pipex)
{
	char	**paths;
	int		i;

	i = 0;
	paths = NULL;
	while (envp && envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != NULL)
		{
			paths = ft_split(envp[i] + 5, ':');
			if (paths == NULL)
				perror_exit(MALLOC_ERR, pipex);
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*find_cmd_in_paths(char *cmd_name, char **paths)
{
	char	*cmd_path;
	char	*path_with_slash;
	int		i;

	path_with_slash = ft_strjoin("/", cmd_name);
	if (path_with_slash == NULL)
		return (NULL);
	i = 0;
	cmd_path = cmd_name;
	while (paths && paths[i])
	{
		cmd_path = ft_strjoin(paths[i], path_with_slash);
		if (cmd_path == NULL)
			break ;
		if (access(cmd_path, F_OK) == 0 && access(cmd_path, X_OK) == 0)
			break ;
		free(cmd_path);
		cmd_path = cmd_name;
		i++;
	}
	free(path_with_slash);
	path_with_slash = NULL;
	return (cmd_path);
}

char	*get_cmd_path(char *cmd_name, char **paths, t_pipex *pipex)
{
	char	*cmd_path;

	cmd_path = NULL;
	if (access(cmd_name, F_OK) == 0 && access(cmd_name, X_OK) == 0)
		cmd_path = cmd_name;
	else
	{
		cmd_path = find_cmd_in_paths(cmd_name, paths);
		if (cmd_path == NULL)
			perror_exit(MALLOC_ERR, pipex);
		else if (cmd_path == cmd_name)
		{
			ft_putstr_fd(cmd_path, 2);
			perror_exit(CMD_NOT_FOUND, pipex);
		}
	}
	free_matrix(paths);
	paths = NULL;
	return (cmd_path);
}

void	config_cmd(t_pipex *pipex, int i)
{
	char	**paths;

	if (pipex->is_here_doc == 1)
		i += 1;
	pipex->cmd_args = ft_split(pipex->prog_args[i + 2], ' ');
	if (pipex->cmd_args == NULL)
		perror_exit(MALLOC_ERR, pipex);
	paths = get_envp_paths(pipex->cmd_envp, pipex);
	pipex->cmd_path = get_cmd_path(pipex->cmd_args[0], paths, pipex);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

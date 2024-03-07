/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:09:31 by aggrigor          #+#    #+#             */
/*   Updated: 2024/03/07 21:00:50 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	cmd_not_found(char *cmd_path)
{
	ft_putstr_fd(cmd_path, 2);
	ft_putstr_fd(": Command NOT found\n", 2);
	exit(EXIT_FAILURE);
}

char	**get_envp_paths(char *envp[])
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
			{
				//maybe free paths
				perror("Paths spliting");
				exit(EXIT_FAILURE);
			}
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
			break;
		if (access(cmd_path, F_OK) == 0 && access(cmd_path, X_OK) == 0)
			break;
		free(cmd_path);
		cmd_path = cmd_name;
		i++;
	}
	free(path_with_slash);
	return (cmd_path);
}

char	*get_cmd_path(char *cmd_name, char **paths)
{
	char	*cmd_path;

	cmd_path = NULL;
	if (access(cmd_name, F_OK) == 0 && access(cmd_name, X_OK) == 0)
		cmd_path = cmd_name;
	else
	{
		cmd_path = find_cmd_in_paths(cmd_name, paths);
		if (cmd_path == NULL)
		{
			// maybe free struct values
			free_matrix(paths);
			perror(cmd_name);
			exit(EXIT_FAILURE);
		}
		// else if(cmd_path == cmd_name)
		// {
		// 	cmd_not_found(cmd_name);
		// }
	}
	free_matrix(paths);
	return (cmd_path);
}

void	config_cmd(t_pipex *pipex, int i)
{
	char	**paths;
	if (pipex->is_here_doc == 1)
		i += 1;
	pipex->cmd_args = ft_split(pipex->prog_args[i + 2], ' ');
	if (pipex->cmd_args == NULL)
		exit(EXIT_FAILURE); // maybe free struct values
	paths = get_envp_paths(pipex->cmd_envp);
	pipex->cmd_path = get_cmd_path(pipex->cmd_args[0], paths);
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

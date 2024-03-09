/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:39:28 by aggrigor          #+#    #+#             */
/*   Updated: 2024/03/09 12:28:10 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// write, read, close, access, dup, dup2, execve, fork, pipe, unlink,
# include <unistd.h>
// open
# include <fcntl.h>
// malloc, free, exit
# include <stdlib.h>
// perror
# include <stdio.h>
// strerror
# include <string.h>
// wait, waitpid
# include <sys/wait.h>
// for errno
# include <sys/errno.h>

# define MIN_ARGS 4
// CUSTOM ERRORS
# define INVALID_ARG_CNT 1
# define FILEOUT_ERR 2
# define FILEIN_ERR 3
# define JOIN_ERR 4
# define MALLOC_ERR 5
# define PIPE_ERR 6
# define FORK_ERR 7
# define DUP_ERR 8
# define CMD_NOT_FOUND 9
# define EXECVE_ERR 10

typedef struct s_pipex
{
	int		(*pipes)[2];
	char	**prog_args;
	char	**cmd_args;
	char	**cmd_envp;
	char	*cmd_path;
	int		prog_argc;
	int		cmd_counts;
	int		filein_fd;
	int		fileout_fd;
	int		is_here_doc;
	int		(*here_doc_pipe)[2];
	char	*limiter;
}	t_pipex;

//pipes.c
void	init_pipes(t_pipex *pipex);
void	close_pipes(t_pipex *pipex);
void	first_cmd_dups(t_pipex *pipex);
void	dups(t_pipex *pipex, int i);

//processes.c
void	wait_processes(t_pipex *pipex);
void	create_processes(t_pipex *pipex);

//here_doc.c
int		check_here_doc(int argc, char **argv);
void	here_doc(t_pipex *pipex);

//pipex_utils1.c
char	**get_envp_paths(char *envp[], t_pipex *pipex);
char	*find_cmd_in_paths(char *cmd_name, char **paths);
char	*get_cmd_path(char *cmd_name, char **paths, t_pipex *pipex);
void	config_cmd(t_pipex *pipex, int i);
void	free_matrix(char **matrix);

//pipex_utils2.c
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
void	ft_putstr_fd(char *s, int fd);

//pipex_utils3.c
void	free_pipex(t_pipex *pipex);
void	perror_exit(int err_num, t_pipex *pipex);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(char *s1, char *s2);
int		ft_open_file(char *file, int open_flag, int mode);

//ft_split.c
char	**ft_split(char const *s, char c);

//get_next_line.c
char	*get_next_line(int fd);

#endif
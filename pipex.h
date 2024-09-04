/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoros- <aamoros-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 01:35:24 by aamoros-          #+#    #+#             */
/*   Updated: 2024/09/04 17:57:33 by aamoros-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include "libft/include/libft.h"

# define STDIN 0
# define STDOUT 1

typedef struct s_pipex
{
	char	***cmd;
	char	**cmds;
	int		infile;
	int		outfile;
	char	**paths;
	int		i;
	int		pipe_fd[2];
	int		cmd_count;
	pid_t	*pids;
	int		**pipes;
}	t_pipex;

t_pipex	*parse_args(int argc, char **argv, char **envp, t_pipex *pipex);
void	open_files(t_pipex *pipex, char *in, char *out);
void	free_pipex(t_pipex *pipex);
void	parse_commands_and_pipes(t_pipex *pipex, char **argv, int argc);
void	validate_and_duplicate_command(const char *cmd, t_pipex *pipex);
void	error_exit(t_pipex *pipex, char *msg, int err);
void	ft_free_split(char **split);
void	validate_and_split_command(const char *cmd, t_pipex *pipex);
void	duplicate_and_verify_command(t_pipex *pipex);
void	command_not_found(t_pipex *pipex);
void	validate_and_duplicate_command(const char *cmd, t_pipex *pipex);
void	execute_command(t_pipex *pipex, char **envp);
void	handle_execve_error(t_pipex *pipex);
void	handle_redirection(t_pipex *pipex);
void	execute_child_process(t_pipex *pipex, char **envp);
int		execute_and_wait(t_pipex *pipex, char **envp);
void	init_pipex(t_pipex *pipex);
void	free_string_array(char **array);
void	free_command_array(char ***cmd_array);
void	free_pipes(int **pipes, int count);

#endif
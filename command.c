/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoros- <aamoros-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 23:37:46 by aamoros-          #+#    #+#             */
/*   Updated: 2024/09/04 17:57:21 by aamoros-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(t_pipex *pipex, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_exit(pipex, "Fork failed", 1);
	else if (pid == 0)
		execute_child_process(pipex, envp);
	else
		pipex->pids[pipex->i] = pid;
}

void	execute_child_process(t_pipex *pipex, char **envp)
{
	int	i;

	handle_redirection(pipex);
	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
		i++;
	}
	if (execve(pipex->cmd[pipex->i][0], pipex->cmd[pipex->i], envp) == -1)
		handle_execve_error(pipex);
}

void	handle_redirection(t_pipex *pipex)
{
	if (pipex->i == 0)
	{
		dup2(pipex->infile, STDIN_FILENO);
		dup2(pipex->pipes[0][1], STDOUT_FILENO);
	}
	else if (pipex->i == pipex->cmd_count - 1)
	{
		dup2(pipex->pipes[pipex->i - 1][0], STDIN_FILENO);
		dup2(pipex->outfile, STDOUT_FILENO);
	}
	else
	{
		dup2(pipex->pipes[pipex->i - 1][0], STDIN_FILENO);
		dup2(pipex->pipes[pipex->i][1], STDOUT_FILENO);
	}
}

void	handle_execve_error(t_pipex *pipex)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(pipex->cmd[pipex->i][0], 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
	else
	{
		ft_putstr_fd("Error executing command: ", 2);
		ft_putstr_fd(pipex->cmd[pipex->i][0], 2);
		ft_putstr_fd("\n", 2);
		exit(126);
	}
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

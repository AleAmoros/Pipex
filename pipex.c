/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoros- <aamoros-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 01:35:50 by aamoros-          #+#    #+#             */
/*   Updated: 2024/09/04 17:57:30 by aamoros-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipex(t_pipex *pipex)
{
	pipex->cmd = NULL;
	pipex->cmds = NULL;
	pipex->infile = 0;
	pipex->outfile = 0;
	pipex->paths = NULL;
	pipex->i = 0;
	pipex->cmd_count = 0;
	pipex->pids = NULL;
	pipex->pipes = NULL;
}

void	initialize_pipex(int argc, char **argv, char **envp, t_pipex *pipex)
{
	int	i;

	if (argc < 5)
	{
		ft_putstr_fd("Error: Not enough arguments\n", 2);
		exit(1);
	}
	init_pipex(pipex);
	parse_args(argc, argv, envp, pipex);
	pipex->cmd_count = argc - 3;
	pipex->pipes = ft_calloc(sizeof(int *), (pipex->cmd_count - 1));
	pipex->pids = ft_calloc(sizeof(pid_t), pipex->cmd_count);
	if (!pipex->pipes || !pipex->pids)
		error_exit(pipex, "Memory allocation failed", 1);
	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		pipex->pipes[i] = ft_calloc(sizeof(int), 2);
		if (!pipex->pipes[i] || pipe(pipex->pipes[i]) == -1)
			error_exit(pipex, "Pipe creation failed", 1);
		i++;
	}
}

int	execute_and_wait(t_pipex *pipex, char **envp)
{
	int	i;
	int	status;
	int	last_exit_code;

	last_exit_code = 0;
	pipex->i = -1;
	while (++pipex->i < pipex->cmd_count)
		execute_command(pipex, envp);
	i = -1;
	while (++i < pipex->cmd_count - 1)
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
	}
	i = -1;
	while (++i < pipex->cmd_count)
	{
		waitpid(pipex->pids[i], &status, 0);
		if (WIFEXITED(status))
			last_exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			last_exit_code = 128 + WTERMSIG(status);
	}
	return (last_exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		last_exit_code;

	initialize_pipex(argc, argv, envp, &pipex);
	last_exit_code = execute_and_wait(&pipex, envp);
	if (last_exit_code != 0)
	{
		ft_putstr_fd("Error: Command failed with exit code: ", 2);
		ft_putnbr_fd(last_exit_code, 2);
		ft_putstr_fd("\n", 2);
	}
	free_pipex(&pipex);
	return (last_exit_code);
}

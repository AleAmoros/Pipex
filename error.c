/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoros- <aamoros-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 01:35:52 by aamoros-          #+#    #+#             */
/*   Updated: 2024/09/04 17:57:26 by aamoros-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(t_pipex *pipex, char *msg, int err)
{
	perror(msg);
	free_pipex(pipex);
	exit(err);
}

void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_command_array(char ***cmd_array)
{
	int	i;
	int	j;

	if (!cmd_array)
		return ;
	i = 0;
	while (cmd_array[i])
	{
		j = 0;
		while (cmd_array[i][j])
		{
			free(cmd_array[i][j]);
			j++;
		}
		free(cmd_array[i]);
		i++;
	}
	free(cmd_array);
}

void	free_pipes(int **pipes, int count)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < count)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	free_pipex(t_pipex *pipex)
{
	free_string_array(pipex->cmds);
	free_command_array(pipex->cmd);
	free_string_array(pipex->paths);
	if (pipex->pids)
		free(pipex->pids);
	free_pipes(pipex->pipes, pipex->cmd_count - 1);
}

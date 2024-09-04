/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoros- <aamoros-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 22:59:16 by aamoros-          #+#    #+#             */
/*   Updated: 2024/09/04 17:57:39 by aamoros-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	validate_and_split_command(const char *cmd, t_pipex *pipex)
{
	pipex->cmd[pipex->i] = ft_split(cmd, ' ');
	if (!pipex->cmd[pipex->i])
		error_exit(pipex, "Error: Malloc failed\n", 1);
}

void	duplicate_and_verify_command(t_pipex *pipex)
{
	int		i;
	char	*str;

	i = 0;
	while (pipex->paths[i])
	{
		if (strlen(pipex->paths[i]) > 0
			&& pipex->paths[i][strlen(pipex->paths[i]) - 1] != '/')
			str = ft_strjoin(ft_strdup(pipex->paths[i]), ft_strdup("/"));
		else
			str = ft_strdup(pipex->paths[i]);
		str = ft_strjoin(str, ft_strdup(pipex->cmd[pipex->i][0]));
		if (access(str, F_OK | X_OK) != -1)
		{
			free(pipex->cmd[pipex->i][0]);
			pipex->cmd[pipex->i][0] = str;
			return ;
		}
		free(str);
		i++;
	}
	command_not_found(pipex);
}

void	command_not_found(t_pipex *pipex)
{
	ft_putstr_fd("Error: Command not found: ", 2);
	ft_putstr_fd(pipex->cmd[pipex->i][0], 2);
	ft_putstr_fd("\n", 2);
	free_pipex(pipex);
	exit(127);
}

void	validate_and_duplicate_command(const char *cmd, t_pipex *pipex)
{
	validate_and_split_command(cmd, pipex);
	duplicate_and_verify_command(pipex);
	pipex->i++;
}

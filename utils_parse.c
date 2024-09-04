/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoros- <aamoros-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 01:35:09 by aamoros-          #+#    #+#             */
/*   Updated: 2024/09/04 17:57:36 by aamoros-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_env_path(char **envp, t_pipex *pipex)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			break ;
		}
		i++;
	}
	if (!envp[i])
	{
		pipex->paths = ft_split("", ':');
		return ;
	}
	pipex->paths = ft_split(envp[i] + 5, ':');
	if (!pipex->paths)
		error_exit(pipex, "Error: Malloc failed\n", 1);
}

void	open_files(t_pipex *pipex, char *in, char *out)
{
	char	buf[1];

	pipex->infile = open(in, O_RDONLY);
	if (pipex->infile == -1)
	{
		if (errno == EISDIR)
			error_exit(pipex, "Error: Failed to open input file", 21);
		else
			error_exit(pipex, "Error: Failed to open input file", 1);
	}
	if (read(pipex->infile, buf, 0) == -1 && errno == EISDIR)
	{
		ft_putstr_fd("Error: Input file is a directory\n", 2);
		close(pipex->infile);
		free_pipex(pipex);
		exit(21);
	}
	pipex->outfile = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1)
		error_exit(pipex, "Error: Failed to open output file", 1);
}

void	parse_commands_and_pipes(t_pipex *pipex, char **argv, int argc)
{
	int	start;
	int	end;
	int	cmd_count;
	int	i;
	int	j;

	start = 2;
	end = argc - 1;
	cmd_count = (end - start);
	pipex->cmds = ft_calloc(sizeof(char *), (cmd_count + 1));
	if (!pipex->cmds)
		error_exit(pipex, "Error: Malloc failed\n", 1);
	i = start;
	j = 0;
	while (i < end)
	{
		pipex->cmds[j] = strdup(argv[i++]);
		if (!pipex->cmds[j++])
			error_exit(pipex, "Error: Malloc failed\n", 1);
	}
	pipex->cmd = ft_calloc(sizeof(char **), j + 1);
}

t_pipex	*parse_args(int argc, char **argv, char **envp, t_pipex *pipex)
{
	int	i;

	i = 0;
	get_env_path(envp, pipex);
	if (argc < 5)
		error_exit(pipex, "Error: Not enough arguments\n", 1);
	open_files(pipex, argv[1], argv[argc - 1]);
	parse_commands_and_pipes(pipex, argv, argc);
	while (pipex->cmds[i])
		validate_and_duplicate_command(pipex->cmds[i++], pipex);
	if (!pipex->cmds)
		error_exit(pipex, "Error: Malloc failed\n", 1);
	return (pipex);
}

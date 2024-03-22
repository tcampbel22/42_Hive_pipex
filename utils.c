/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:32:24 by tcampbel          #+#    #+#             */
/*   Updated: 2024/03/22 10:13:19 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

void	is_dir(t_pipe *pipex)
{
	int	fd;

	fd = open(pipex->cmd_arr[0], O_RDONLY);
	if (fd >= 0)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(pipex->cmd_arr[0], 2);
		ft_putstr_fd(": is a directory\n", 2);
		exit(127);
	}
}

void	get_path(char **envp, t_pipe *pipex)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			pipex->path_str = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
			if (!pipex->path_str)
				ft_exit_error("");
		}
		i++;
	}
	pipex->path_arr = ft_split(pipex->path_str, ':');
	if (!pipex->path_arr)
	{
		free(pipex->path_str);
		ft_exit_error("");
	}
	free(pipex->path_str);
}

void	create_cmd_path(t_pipe *pipex)
{
	int	i;

	i = 0;
	while (pipex->path_arr[i])
	{
		pipex->cmd_path = tripjoin(pipex->path_arr[i], "/", pipex->cmd_arr[0]);
		if (!pipex->cmd_path)
		{
			ft_free_array(pipex->cmd_arr);
			ft_free_array(pipex->path_arr);
			ft_exit_error("");
		}
		if (access(pipex->cmd_path, F_OK) == 0)
			break ;
		i++;
		free(pipex->cmd_path);
	}
}

void	check_cmd(char *cmd, t_pipe *pipex)
{
	if (ft_strchr(cmd, '\"'))
		pipex->cmd_arr = ft_skip_split(cmd, ' ', '\"');
	else
		pipex->cmd_arr = ft_skip_split(cmd, ' ', '\'');
	if (!pipex->cmd_arr)
	{
		ft_free_array(pipex->path_arr);
		ft_exit_error("");
	}
	if (access(pipex->cmd_arr[0], F_OK) == 0)
		pipex->cmd_path = pipex->cmd_arr[0];
	else
		create_cmd_path(pipex);
}

void	execute(char *cmd, char **envp, t_pipe *pipex)
{
	get_path(envp, pipex);
	check_cmd(cmd, pipex);
	is_dir(pipex);
	if (execve(pipex->cmd_path, pipex->cmd_arr, envp) < 0)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(pipex->cmd_arr[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	free(pipex->cmd_path);
	ft_free_array(pipex->cmd_arr);
}

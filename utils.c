/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:32:24 by tcampbel          #+#    #+#             */
/*   Updated: 2024/03/22 15:14:30 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_path(char **envp, t_pipe *pipex)
{
	int		i;
	char	*env_str;

	i = 0;
	while (envp[i])
	{
		env_str = ft_strnstr(envp[i], "PATH=", 5);
		if (env_str)
		{
			pipex->path_str = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
			if (!pipex->path_str)
				ft_exit_error("");
			break ;
		}
		i++;
	}
	if (env_str == NULL)
	{
		ft_printf(2, "pipex: %s: No such file or directory", pipex->cmd_arr[0]);
		ft_printf(2, "\n");
		exit(127);
	}
	split_path(pipex);
	free(pipex->path_str);
}

void	create_cmd_path(t_pipe *pipex)
{
	int	i;

	i = 0;
	pipex->flag = 0;
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
		{
			pipex->flag = 1;
			break ;
		}
		i++;
		free(pipex->cmd_path);
	}
}

void	check_cmd(char *cmd, t_pipe *pipex, char **envp)
{
	if (ft_strchr(cmd, '\"'))
		pipex->cmd_arr = ft_skip_split(cmd, ' ', '\"');
	else
		pipex->cmd_arr = ft_skip_split(cmd, ' ', '\'');
	if (!pipex->cmd_arr)
		ft_exit_error("");
	if (pipex->cmd_arr[0] == NULL)
	{
		ft_printf(2, "pipex: : command not found\n");
		ft_free_array(pipex->path_arr);
		ft_free_array(pipex->cmd_arr);
		exit(127);
	}
	get_path(envp, pipex);
	if (access(pipex->cmd_arr[0], F_OK) == 0)
		pipex->cmd_path = ft_strdup(pipex->cmd_arr[0]);
	else
		create_cmd_path(pipex);
}

void	execute(char *cmd, char **envp, t_pipe *pipex)
{
	check_cmd(cmd, pipex, envp);
	is_dir(pipex);
	ft_free_array(pipex->path_arr);
	if (execve(pipex->cmd_path, pipex->cmd_arr, envp) < 0)
	{
		ft_printf(2, "pipex: %s: command not found\n", pipex->cmd_arr[0]);
		if (pipex->flag == 1)
			free(pipex->cmd_path);
		ft_free_array(pipex->cmd_arr);
		exit(127);
	}
}

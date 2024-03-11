/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:32:24 by tcampbel          #+#    #+#             */
/*   Updated: 2024/03/11 15:08:04 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	pipex->cmd_arr = ft_split(cmd, ' ');
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
	if (execve(pipex->cmd_path, pipex->cmd_arr, envp) < 0)
		ft_exit_error(pipex->cmd_arr[0]);
	free(pipex->cmd_path);
	ft_free_array(pipex->cmd_arr);
}

char	*tripjoin(char const *s1, char const *s2, char const *s3)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*s4;

	i = -1;
	j = -1;
	k = -1;
	if (!s1 || !s2 || !s3)
		return (NULL);
	s4 = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1));
	if (!s4)
		return (NULL);
	while (s1[++i])
		s4[i] = s1[i];
	while (s2[++j])
		s4[i++] = s2[j];
	while (s3[++k])
		s4[i++] = s3[k];
	s4[i] = '\0';
	return (s4);
}

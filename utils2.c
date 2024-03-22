/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:57:36 by tcampbel          #+#    #+#             */
/*   Updated: 2024/03/22 15:13:31 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	split_path(t_pipe *pipex)
{
	pipex->path_arr = ft_split(pipex->path_str, ':');
	if (!pipex->path_arr)
	{
		free(pipex->path_str);
		ft_exit_error("");
	}
}

void	is_dir(t_pipe *pipex)
{
	int	fd;

	fd = open(pipex->cmd_arr[0], O_RDONLY);
	if (fd >= 0)
	{
		ft_printf(2, "pipex: %s: is a directory\n", pipex->cmd_arr[0]);
		ft_free_array(pipex->cmd_arr);
		ft_free_array(pipex->path_arr);
		close(fd);
		exit(127);
	}
	close(fd);
	if (ft_strnstr(pipex->cmd_arr[0], "./", 2) != NULL)
	{
		ft_printf(2, "pipex: %s: ", pipex->cmd_arr[0]);
		ft_printf(2, "No such file or directory\n");
		ft_free_array(pipex->cmd_arr);
		ft_free_array(pipex->path_arr);
		exit(127);
	}
}

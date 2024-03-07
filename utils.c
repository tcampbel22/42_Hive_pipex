/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:32:24 by tcampbel          #+#    #+#             */
/*   Updated: 2024/03/07 18:10:48 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **get_path(char **envp)
{
	int	i;
	char *path_str;
	char **path_arr;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			path_str = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
		i++;
	}

	path_arr = ft_split(path_str, ':');
	return(path_arr);
}

void	execute(char *cmd, char **envp)
{ 
	char **path;
	int i = 0;

	cmd = "Hello";
	path = get_path(envp);
	while (path[i])
	{
		printf("%s\n", path[i]);
		i++;
	}
//	get_cmd(cmd, envp);
}

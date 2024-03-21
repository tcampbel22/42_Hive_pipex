/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:39:32 by tcampbel          #+#    #+#             */
/*   Updated: 2024/03/21 13:45:33 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/includes/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_pipe
{
	char	**cmd_arr;
	char	*path_str;
	char	**path_arr;
	char	*cmd_path;
	int		fd[2];
	int		infile;
	int		outfile;
}	t_pipe;

void	ft_exit_error(char *str);
void	get_path(char **envp, t_pipe *pipex);
void	execute(char *cmd, char **envp, t_pipe *pipex);
char	*tripjoin(char const *s1, char const *s2, char const *s3);
void	check_cmd(char *cmd, t_pipe *pipex);

#endif

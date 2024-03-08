/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:39:32 by tcampbel          #+#    #+#             */
/*   Updated: 2024/03/08 17:24:40 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/includes/libft.h"
# include <sys/wait.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>


typedef struct s_pipe
{
	char	**cmd_arr; //2D array containing the base command in the the first string
	char	*path_str; //Initial path string 
	char	**path_arr; //Path string split into a 2D array
	char	*cmd_path; //Individual string containing entire command including flags
	int		fd[2];
	int		infile;
	int		outfile;
} t_pipe;

void	ft_exit_error(char *str, t_pipe *pipex);
void	get_path(char **envp, t_pipe *pipex);
void	execute(char *cmd, char **envp, t_pipe *pipex);
char	*ft_tripjoin(char const *s1, char const *s2, char const *s3);
void	check_cmd(char *cmd, t_pipe *pipex);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:39:32 by tcampbel          #+#    #+#             */
/*   Updated: 2024/03/07 17:43:03 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/includes/libft.h"
# include <sys/wait.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>


void	ft_exit_error(char *str);
char	**get_path(char **envp);
void	execute(char *cmd, char **envp);
#endif

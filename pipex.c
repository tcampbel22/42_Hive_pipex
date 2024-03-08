/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:49:19 by tcampbel          #+#    #+#             */
/*   Updated: 2024/03/08 18:09:18 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_command(char **av, char **envp, t_pipe *pipex)
{
	if ((dup2(pipex->infile, STDIN_FILENO) < 0) || (dup2(pipex->fd[1], STDOUT_FILENO) < 0))
		ft_exit_error("dup2() error ", pipex);
	close(pipex->infile);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	execute(av[2], envp, pipex);
}

void	second_command(char **av, char **envp, t_pipe *pipex)
{
	if ((dup2(pipex->outfile, STDOUT_FILENO) < 0) || (dup2(pipex->fd[0], STDIN_FILENO) < 0))
		ft_exit_error("dup2() error ", pipex);
	close(pipex->outfile);
	close(pipex->fd[1]);
	close(pipex->fd[0]);
	execute(av[3], envp, pipex);
}

void	ft_exit_error(char *str, t_pipe *pipex)
{
/*	if (pipex->cmd_arr)
		ft_free_array(pipex->cmd_arr);
	if (pipex->path_str)
		free(pipex->path_str);
	if (pipex->path_arr)
		ft_free_array(pipex->path_arr);
	if (pipex->cmd_path)
		free(pipex->cmd_path);*/
	if (pipex)
	perror(str);
	exit(1);
}

void	create_process(char **av, char **envp, t_pipe *pipex)
{
	pid_t	pid1; 
	pid_t	pid2;
	int		e_status;

	if (pipe(pipex->fd) == -1)
		ft_exit_error("", pipex);
	pid1 = fork();
	if (pid1 < 0)
		ft_exit_error("fork() error ", pipex);
	if (pid1 == 0)
		first_command(av, envp, pipex);
	pid2 = fork();
	if (pid2 < 0)
		ft_exit_error("fork() error ", pipex);
	if (pid2 == 0)
		second_command(av, envp, pipex);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	if ((waitpid(pid1, NULL, 0) < 0) || (waitpid(pid2, &e_status, 0) < 0))
		ft_exit_error("waitpid() error ", pipex);
	exit(WEXITSTATUS(e_status));
}


int	main(int ac, char **av, char **envp)
{
	t_pipe pipex;

	if (!envp[0])
		ft_exit_error("path error ", &pipex);
	if (ac != 5)
		ft_exit_error("invalid arg amount ", &pipex);
	if ((pipex.infile = open(av[1], O_RDONLY, 0444) < 0))
		ft_exit_error("open() error ", &pipex);
	if ((pipex.outfile = open(av[4], O_CREAT | O_TRUNC | O_RDWR, 0644) < 0))
		ft_exit_error("open() error ", &pipex);
	create_process(av, envp, &pipex);
	return (0);
}

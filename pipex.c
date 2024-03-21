/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:49:19 by tcampbel          #+#    #+#             */
/*   Updated: 2024/03/21 12:07:58 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_command(char **av, char **envp, t_pipe *pipex)
{
	pipex->infile = open(av[1], O_RDONLY, 0444);
	if (pipex->infile < 0)
		ft_exit_error(av[1]);
	if ((dup2(pipex->infile, STDIN_FILENO) < 0)
		|| (dup2(pipex->fd[1], STDOUT_FILENO) < 0))
		ft_exit_error("");
	close(pipex->infile);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	execute(av[2], envp, pipex);
}

void	second_command(char **av, char **envp, t_pipe *pipex)
{
	pipex->outfile = open(av[4], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (pipex->outfile < 0)
		ft_exit_error(av[4]);
	if ((dup2(pipex->outfile, STDOUT_FILENO) < 0)
		|| (dup2(pipex->fd[0], STDIN_FILENO) < 0))
		ft_exit_error("");
	close(pipex->outfile);
	close(pipex->fd[1]);
	close(pipex->fd[0]);
	execute(av[3], envp, pipex);
}

void	ft_exit_error(char *str)
{
	ft_putstr_fd("pipex: ", 2);
	perror(str);
	exit(127);
}

void	create_process(char **av, char **envp, t_pipe *pipex)
{
	pid_t	pid1;
	pid_t	pid2;
	int		e_status;

	if (pipe(pipex->fd) == -1)
		ft_exit_error("");
	pid1 = fork();
	if (pid1 < 0)
		ft_exit_error("");
	if (pid1 == 0)
		first_command(av, envp, pipex);
	pid2 = fork();
	if (pid2 < 0)
		ft_exit_error("");
	if (pid2 == 0)
		second_command(av, envp, pipex);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	if ((waitpid(pid1, &e_status, 0) < 0) || (waitpid(pid2, &e_status, 0) < 0))
		ft_exit_error("");
	exit(WEXITSTATUS(e_status));
}

int	main(int ac, char **av, char **envp)
{
	t_pipe	pipex;

	if (!envp[0])
		ft_exit_error("path error");
	if (ac != 5)
		ft_exit_error("invalid arg amount");
	else
		create_process(av, envp, &pipex);
}

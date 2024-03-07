/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:49:19 by tcampbel          #+#    #+#             */
/*   Updated: 2024/03/07 17:41:27 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_command(char **av, int *fd, char **envp, int infile)
{
	if (dup2(infile, STDIN_FILENO) < 0)
		ft_exit_error("dup2() error ");
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		ft_exit_error("dup2() error ");
	close(fd[0]);
	close(fd[1]);
	execute(av[2], envp);
}

void	second_command(char **av, int *fd, char **envp, int outfile)
{
	if (dup2(outfile, STDIN_FILENO) < 0)
		ft_exit_error("dup2() error: ");
	if (dup2(fd[0], STDOUT_FILENO) < 0)
		ft_exit_error("dup2() error: ");
	close(fd[1]);
	close(fd[0]);
	execute(av[4], envp);
}

void	ft_exit_error(char *str)
{
	perror(str);
	exit(1);
}

void	create_process(char **av, char **envp, int infile, int outfile)
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd[2];
//	int		e_status;

	outfile = 1;
	if(pipe(fd) < 0)
		ft_exit_error("");
	if ((pid1 = fork() < 0))
		ft_exit_error("fork() error ");
	else if (pid1 == 0)
		first_command(av, fd, envp, infile);
	if ((pid2 = fork() < 0))
		ft_exit_error("fork() error ");
	else if (pid2 == 0)
		second_command(av, fd, envp, outfile);
	close(fd[0]);
	close(fd[1]);
//	if ((waitpid(pid1, NULL, 0) < 0) || (waitpid(pid2, &e_status, 0) < 0))
//		ft_exit_error("waitpid() error ");
//	exit(WEXITSTATUS(e_status);
}


int	main(int ac, char **av, char **envp)
{
	int	infile = 1;
	int	outfile = 1;

	if (!envp[0])
		ft_exit_error("path error ");
	if (ac != 5)
		ft_exit_error("invalid arg amount ");
	if ((infile = open(av[1], O_RDONLY) < 0))
		ft_exit_error("open() error ");
	if ((outfile = open(av[4], O_CREAT | O_TRUNC | O_RDWR, 0644) < 0))
		ft_exit_error("open() error ");
	execute(av[2], envp);
	create_process(av, envp, infile, outfile);
	return (0);
}

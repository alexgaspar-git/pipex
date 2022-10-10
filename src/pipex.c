/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 16:55:47 by algaspar          #+#    #+#             */
/*   Updated: 2022/05/24 14:18:31 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exit(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	exec_cmd(char *cmd, char **envp)
{
	char	*fpath;
	char	**cmdsplit;
	int		check;

	fpath = parsing(cmd, envp);
	if (fpath == NULL)
	{
		write(2, "Error: command not found: ", 26);
		write(2, cmd, ft_strlen(cmd));
		write(2, "\n", 1);
		exit(EXIT_FAILURE);
	}
	cmdsplit = ft_split(cmd, ' ');
	if (cmdsplit == NULL)
		ft_exit();
	check = execve(fpath, cmdsplit, envp);
	if (check == -1)
	{
		free_paths(cmdsplit);
		ft_exit();
	}
}

void	ft_fork(int *pfd, char *cmd, char **envp, int parent)
{
	if (parent == 0)
	{
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[0]);
		exec_cmd(cmd, envp);
	}
	else if (parent == 1)
	{
		dup2(pfd[0], STDIN_FILENO);
		close(pfd[1]);
		exec_cmd(cmd, envp);
	}
}

void	pipex(char **argv, char **envp)
{
	int		pfd[2];
	int		check;
	pid_t	pid1;
	pid_t	pid2;

	check = pipe(pfd);
	if (check == -1)
		ft_exit();
	pid1 = fork();
	if (pid1 == -1)
		ft_exit();
	if (pid1 == 0)
		ft_fork(pfd, argv[2], envp, 0);
	else
	{
		pid2 = fork();
		if (pid2 == -1)
			ft_exit();
		if (pid2 == 0)
			ft_fork(pfd, argv[3], envp, 1);
	}
	close(pfd[0]);
	close(pfd[1]);
	waitpid(pid1, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	int	infile;
	int	outfile;

	if (argc != 5)
	{
		write(2, "You need 4 arguments to execute pipex\n", 38);
		return (1);
	}
	infile = open(argv[1], O_RDONLY);
	outfile = open(argv[4], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if ((infile == -1) | (outfile == -1))
		ft_exit();
	dup2(infile, STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	pipex(argv, envp);
	close(infile);
	close(outfile);
	return (0);
}

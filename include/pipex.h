/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 16:55:45 by algaspar          #+#    #+#             */
/*   Updated: 2022/05/24 14:54:13 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <time.h>
# include <fcntl.h>

void	exec_cmd(char *cmd, char **envp);
char	*find_path(char **envp);
void	ft_exit(void);
void	ft_fork(int *pfd, char *cmd, char **envp, int parent);
char	**ft_split(char const *s, char c);
char	*ft_strjoin_slash(char *s1, char *s2);
size_t	ft_strlen(const char *str);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	free_paths(char **paths);
char	*get_path(char *argv, char **paths);
char	*parsing(char *argv, char **envp);
void	pipex(char **argv, char **envp);

#endif
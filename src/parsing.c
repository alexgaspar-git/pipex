/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:14:40 by algaspar          #+#    #+#             */
/*   Updated: 2022/05/18 14:53:29 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **envp)
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) == NULL)
			i++;
		else
		{
			path = ft_strnstr(envp[i], "PATH=", 5);
			return (path);
		}
	}
	return (NULL);
}

char	*get_path(char *argv, char **paths)
{
	int		i;
	char	*fpath;

	i = 0;
	while (paths[i++])
	{
		fpath = ft_strjoin_slash(paths[i], argv);
		if (access(fpath, F_OK) == 0)
			return (fpath);
		free(fpath);
	}
	return (fpath);
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	*parsing(char *argv, char **envp)
{
	char	*envpath;
	char	**paths;
	char	**splitarg;
	char	*fpath;

	envpath = find_path(envp);
	paths = ft_split(envpath, ':');
	splitarg = ft_split(argv, ' ');
	fpath = get_path(splitarg[0], paths);
	free_paths(paths);
	return (fpath);
}

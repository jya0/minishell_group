/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 18:14:02 by jyao              #+#    #+#             */
/*   Updated: 2022/12/27 20:46:43 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
int	main(int argc, char *argv[])
{
	int		c[50];
	char	*delim;

	if (argc <= 1)
		return (-1);
	bzero((void *)c, 50 * sizeof(int));
	delim = calloc(strlen(argv[1]) + 1 + 1, sizeof(int));
	strcpy(delim, argv[1]);
	strcat(delim, "\n");
	write(1, "> ", 2);
	while (read(0, &c, 50 * sizeof(int)) > 0)
	{
		if (strcmp((const char *)c, delim) == 0)
			break ;
		write(1, "> ", 2);
		write(1, "line = ", 7);
		write(1, &c, 50 * sizeof(int));
		bzero((void *)c, 50 * sizeof(int));
		// sleep(1);
	}
	free(delim);
	return (0);
}
*/

int	main(int argc, char *argv[])
{
	char		*str;
	int			fd;

	if (argc <= 1)
		return (-1);
	fd = open("temp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd < -1)
		return (perror("Can't create file for heredoc!\n"), -1);
	while (1)
	{
		str = readline("> ");
		if (strcmp(str, argv[1]) == 0)
		{
			free(str);
			break ;
		}
		write(fd, str, strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	close(fd);
	fd = open("temp.txt", O_CREAT | O_RDONLY, 0777);
	if (unlink("temp.txt") != 0)
		return (perror("can't delete file!\n"), -1);
	return (0);
}

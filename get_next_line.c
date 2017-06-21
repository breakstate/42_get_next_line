/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoodley <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 10:45:49 by bmoodley          #+#    #+#             */
/*   Updated: 2017/06/18 15:34:47 by bmoodley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

//static void		new_expand(char *new)
//{
//
//}

static void		buffer_shift(char *buffer)
{
	int	i;

	i = 0;
	while (i < BUFF_SIZE)
	{
		buffer[i] = buffer[i + 1];
		i++;
	}
	buffer[BUFF_SIZE - 1] = '\0';
}

static int		decision_loop(char *buffer, char *newi, int *i)
{
	if (buffer[0] == '\n')
	{
		*newi = '\0';
		buffer_shift(buffer);
		return (0);
	}
	else if (buffer[0] == '\0')
	{
	}
	else
	{
		*newi = buffer[0];
		buffer_shift(buffer);
		(*i)++;
	}
	return (1);
}

int get_next_line(const int fd, char **line)
{
	int i;
	static int r = 0;
	static char buffer[BUFF_SIZE];
	char *new;

	new = (char *)malloc(sizeof(char) * 200);
	i = 0;
	*line = new;
	while (1)
	{
		if (strlen(buffer) < 1)
			r = read(fd, buffer, BUFF_SIZE);
		while (strlen(buffer) > 0)
		{
			if (decision_loop(buffer, &new[i], &i) == 0)
			{
				i = 0;
				return (1);
			}
		}
		if (r == 0 && strlen(buffer) == 0)
			return (0);
	}
}

int main()
{
	/*
	int fd;
	char *line;
	fd = open("test", O_RDONLY);
	while(get_next_line(fd, &line) == 1)
	{
		printf("%s", line);
	}
	*/
	
	int fd;
	char **line;
	int i = 0;

	fd = open("Text.txt", O_RDONLY);
	while (get_next_line(fd, line) == 1)
	{
		printf("%d |%s|\n", i, *line);
		i++;
		free(*line);
	}
	return (0);
}

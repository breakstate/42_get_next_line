/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoodley <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 10:45:49 by bmoodley          #+#    #+#             */
/*   Updated: 2017/06/23 12:45:08 by bmoodley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

static int		new_expand(char **new, int size)
{
	char	*stemp;
	puts("2seg here?");

	if ((stemp = (char *)malloc(sizeof(char) * BUFF_SIZE * (size + 1))) == NULL)
		return (-1);
	puts("3seg here?");
	ft_memcpy(stemp, *new, BUFF_SIZE * size);
	free (*new);
	*new = stemp;
	puts("4seg here?");
	return (1);
}

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
	char **new;
	int		size;

	size = 1;
	*new = (char *)malloc(sizeof(char) * BUFF_SIZE * size);//star
	i = 0;
	*line = *new;//star
	puts("1seg here?");
	while (1)
	{
		if (new_expand(new, size) == -1)//star
			return (-1);
		size++;
		if (strlen(buffer) < 1)
			r = read(fd, buffer, BUFF_SIZE);
		while (strlen(buffer) > 0)
		{
			if (decision_loop(buffer, &(*new[i]), &i) == 0)//star
			{
				i = 0;
				*line = *new;//added and star
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
		puts("hi");
		free(*line);
	}
	return (0);
}

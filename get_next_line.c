/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoodley <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 15:46:04 by bmoodley          #+#    #+#             */
/*   Updated: 2017/06/30 10:07:36 by bmoodley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"

static	void	new_expand(char **new, char *buffer, int *pos, int *i)
{
	char		*temp;
	char		*temp2;

	if (*new == NULL)
	{
		*new = ft_strsub(buffer, *pos, *i);
	}
	else
	{
		temp2 = ft_strsub(buffer, *pos, *i);
		temp = ft_strdup(*new);
		free(*new);
		*new = ft_strjoin(temp, temp2);
		free(temp);
		free(temp2);
	}
}

static	int		buf_parse(char **new, char *buffer, int *pos, int *r)
{
	int			i;

	i = 0;
	while (buffer[i + *pos] != '\0')
	{
		if (buffer[i + *pos] != '\n')
		{
			(i)++;
		}
		else if (buffer[i + *pos] == '\n')
		{
			new_expand(new, buffer, pos, &i);
			(i)++;
			*pos = *pos + i;
			return (1);
		}
	}
	new_expand(new, buffer, pos, &i);
	*pos = 0;
	i = 0;
	*r = -2;
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static char	buffer[BUFF_SIZE + 1];
	static int	r = -2;
	static int	pos = 0;
	char		*new;

	new = NULL;
	while (1)
	{
		if (pos == BUFF_SIZE || r == -2)
		{
			ft_bzero(buffer, BUFF_SIZE + 1);
			r = read(fd, buffer, BUFF_SIZE);
			pos = 0;
		}
		else if (r == -1)
			return (-1);
		else if (r == 0)
			return (0);
		else
			while (buf_parse(&new, buffer, &pos, &r))
			{
				*line = new;
				return (1);
			}
	}
}

int main()
{
	int fd;
	char **line;

	*line = NULL;
	fd = open("bible.txt", O_RDONLY);
	while ((get_next_line(fd, line)) == 1)
	{
		printf("%s\n", *line);
		free(*line);
	}
	free(*line);
	free(line);
	close(fd);
	return (0);
}

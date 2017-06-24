#include "get_next_line.h"

static void new_expand(char *new, char *buffer, int *pos, int *i)
{
	char *temp;
	char *temp2;

	temp2 = ft_strsub(pos, BUFF_SIZE - (pos + i));
	temp = ft_strdup(new);
	free(new);
	new = ft_strjoin(temp, temp2);
	free(temp);
	free(temp2);
}

static int buf_parse(char *new, char *buffer, int *pos, int *i, int *r)
{
	while (*r >= 0)
	{
		
		if (buffer[*i + *pos] != '\n')
		{
			(*i)++;
		}
		else if (buf[*i + *pos] == '\n')
		{
			(*i)++;
			*pos = *pos + *i;
			new_expand(new, buffer, pos, i, r);
			return (1);
		}
		(*r)--;
	}
	//add buffer to new
	*pos = 0;
	*i = 0;
	return (0);	
}

int get_next_line(const int fd, char **line)
{
	static char buffer[BUFF_SIZE];
	static int r = -1;
	static int pos = 0;
	int i;
	char *new;

	//if r != 1 return r (?)
	while (1)
	{
		if (r == 0)
		{
			//if(new) then...
			r = read(fd, buffer, BUFF_SIZE);
			i = 0;
		}
		else if (r == -1)
		{
			return (-1);
		}
		else
		{
			while (buf_parse(new, buffer, &pos, &i, &r))
			{
				return (1);
			}
		}
	}
}

int	main()
{
	int	fd;
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

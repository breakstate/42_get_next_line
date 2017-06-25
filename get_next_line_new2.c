#include "get_next_line.h"
#include "./libft/libft.h"
#include <stdio.h>

static void new_expand(char **new, char *buffer, int *pos, int *i)
{
	char *temp;
	char *temp2;
	printf("==========ENTER NE FUNCTION=========\n");//remove
	printf("new at start- >|%s|<\n", *new);//remove

	if (*new == NULL)
	{
		printf("if'd (empty new)\n");//
		*new = ft_strsub(buffer, *pos, *i);
	}
	else
	{
		printf("elsed (existing new)\n");//
		temp2 = ft_strsub(buffer, *pos, *i);//(pos, BUFF_SIZE - (pos + i));
		temp = ft_strdup(*new);
		free(*new);
		*new = ft_strjoin(temp, temp2);
		free(temp);
		free(temp2);
	}
	printf("new - >|%s|<\n", *new);//remove
	printf("===back to parser===\n");//remove
}

static int buf_parse(char **new, char *buffer, int *pos, int *i, int *r)
{
	printf("=========ENTER PARSER==========\nnew = |%s|\nbuffer = >|%s|<\n", *new, buffer);//remove
	while (buffer[*i + *pos] != '\0')//(*r >= 0)
	{
		printf("|i = %d|pos = %d|\n", *i, *pos);//remove
		
		if (buffer[*i + *pos] != '\n')
		{
			(*i)++;
		}
		else if (buffer[*i + *pos] == '\n')
		{
			printf("pos before ne = %d\n", *pos);//remove
			new_expand(new, buffer, pos, i);
			(*i)++;
			*pos = *pos + *i;
			printf("===back to GNL===\n");//remove
			return (1);
		}
		//(*r)--;
	}
	printf("pos = %d|i = %d|outisde while in parserrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr\n", *pos, *i);
	new_expand(new, buffer, pos, i);//add  new to buffer
	*pos = 0;
	*i = 0;
	*r = -2;
	return (0);	
}

int get_next_line(const int fd, char **line)
{
	printf("++++++++++++++++++++++++++++++BIG LOOP+++++++++++++++++++++++++++++++\n==========ENTER GNL FUNCTION========\n");//remove
	static char buffer[BUFF_SIZE + 1];
	static int r = -2;
	static int pos = 0;
	int i;
	char *new;
	new = NULL;
	*line = new;
	//if r != 1 return r (?)
	printf("gnl\n");//remove
	while (1)
	{
		if (pos == BUFF_SIZE || r == -2)//(r == 0)
		{
			printf(">>>RELOAD BUFFER<<<\npos = %d|r = %d\n", pos, r);//remove
			//if(new) then...
			bzero(buffer, BUFF_SIZE + 1);
			r = read(fd, buffer, BUFF_SIZE);
			i = 0;
			pos = 0;
			printf("new = %s\n", new);//remove
		}
		else if (r == -1)
			return (-1);
		else if (r == 0)
			return (0);
		else
		{
			printf("gnl4\n");//remove
			while (buf_parse(&new, buffer, &pos, &i, &r))
			{
				printf(">>>>>>>>>>>>>>>>RETURN<<<<<<<<<<<<<<\n");//remove
				*line = new;
				return (1);
			}
		}
	}
}

int	main()
{
	int	fd;
	char **line;
	int i = 1;
	int gnl = 0;
	printf("\n-------------------------------------------------------------------------------\n_______________________________________START___________________________________\n-------------------------------------------------------------------------------\n\n");//remove
	printf("buffer size - %d\n", BUFF_SIZE);//remove
	*line = NULL;
	fd = open("Text.txt", O_RDONLY);
	printf("test1\n");
	while (get_next_line(fd, line) == 1)
	{
		//printf("--------return box--------\n");
		//printf("|  gnl - %d\n", gnl);
		printf("|  %d --|%s|--\n", i, *line);
		//printf("--------return box--------\n");
		i++;
		free(*line);
	}
	printf("buffer size - %d\n", BUFF_SIZE);//remove
	return (0);
}

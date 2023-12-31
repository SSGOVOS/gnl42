/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubine <amoubine@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:31:42 by amoubine          #+#    #+#             */
/*   Updated: 2023/12/31 15:45:40 by amoubine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strchr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*readandjoin(int fd, char *buffer, char *str)
{
	ssize_t	i;

	i = 1;
	if (!buffer)
	{
		buffer =  malloc(1);
		*buffer = 0;
	}
	while (ft_strchr(buffer, '\n') == -1 && i != 0)
	{
		i = read(fd, str, BUFFER_SIZE);
		if (i < 0)
		{
			free(str);
			free(buffer);
			return (NULL);
		}
		str[i] = '\0';
		buffer = ft_strjoin(buffer, str);
	}
	free(str);
	return (buffer);
}

int	fun_tat7sb(char *buffer)
{
	int	i;
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	return (i);
}

char	*ft_free(char *s)
{
	free(s);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*str;
	char		*save;
	char		*nextline;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = malloc((size_t)BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	buffer[fd] = readandjoin(fd, buffer[fd], str);
	if (!buffer[fd])
		return (NULL);
	i = fun_tat7sb(buffer[fd]);
	if (!buffer[fd][0])
		nextline = NULL;
	else
	{
		nextline = malloc(i + 1);
		if(!nextline)
			return (ft_free(buffer[fd]));
		ft_memmove(nextline, buffer[fd], i);
		nextline[i] = '\0';
	}
	if (buffer[fd][i])
	{
		save = ft_strdup(&buffer[fd][i]);
		free(buffer[fd]);
		buffer[fd] = save;
	}
	else
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
	return (nextline);
}
// int main()
// {
// 	int i = open("apah", O_RDONLY | O_CREAT , 0777);
// 	// int d = open("get_next_line.c", O_RDONLY);
// 	char *s;
// 	// char *p;
// 	s = get_next_line(i);
// 	// p = get_next_line(d);
// 	printf("%s", s);
// 	// printf("%s", p);
// 	free(s);
// 	close(i);
// 	// s = get_next_line(i);
// 	// printf("%s", s);
// 	// free(s);

// 	// free(p);
// }

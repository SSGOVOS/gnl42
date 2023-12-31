/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubine <amoubine@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 01:12:14 by amoubine          #+#    #+#             */
/*   Updated: 2023/12/31 14:00:38 by amoubine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

	while (1)
	{
		i = read(fd, str, BUFFER_SIZE);
		if (i <= 0)
			break ;
		str[i] = '\0';
		buffer = ft_strjoin(buffer, str);
		if (ft_strchr(buffer, '\n') != -1)
			break ;
	}
	free(str);
	str = NULL;
	return (buffer);
}

int	fun_tat7sb(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
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
	char		*str;
	int			i;
	static char	*buffer;
	char		*save;
	char		*nextline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = malloc((size_t)BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	buffer = readandjoin(fd, buffer, str);
	if (!buffer || buffer[0] == '\0')
		return (ft_free(buffer));
	i = fun_tat7sb(buffer);
	nextline = malloc(i + 1);
	ft_memmove(nextline, buffer, i);
	nextline[i] = '\0';
	save = ft_strdup(&buffer[i]);
	free(buffer);
	buffer = save;
	return (nextline);
}
// int	main(void)
// {
// 	int		i;
// 	char	*s;

// 	i = open("text.txt", O_RDONLY);
// 	s = get_next_line(i);
// 	printf("%s" , s);
// 	free(s);
// 	// while ((s = get_next_line(i)) != NULL)
// 	// {
// 	// 	printf("%s", s);
// 	// 	free(s);
// 	// }
// 	close(i);
// 	s = get_next_line(i);
// 	printf("%s", s);
// 	free(s);
// }

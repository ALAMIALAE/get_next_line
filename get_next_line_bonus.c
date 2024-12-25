/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:38:00 by aben-dri          #+#    #+#             */
/*   Updated: 2024/12/09 17:45:51 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_next_line(char *buff)
{
	int		i;
	int		j;
	char	*next;

	i = 0;
	if (!buff)
		return (NULL);
	while (buff[i] != '\0' && buff[i] != '\n')
		i++;
	if (buff[i] != '\n')
	{
		free(buff);
		return (NULL);
	}
	next = malloc(ft_strlen(buff) - i + 1);
	if (!next)
		return (NULL);
	i = i + 1;
	j = 0;
	while (buff[i])
		next[j++] = buff[i++];
	next[j] = '\0';
	free(buff);
	return (next);
}

char	*ft_getting_line(char *buff)
{
	int		i;
	char	*str;

	i = 0;
	if (!*buff)
		return (NULL);
	while (buff[i] != '\0')
		i++;
	if (buff[i] == '\n')
		i++;
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (buff[i] != '\n' && buff[i] != '\0')
	{
		str[i] = buff[i];
		i++;
	}
	if (buff[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

char	*ft_reading_line(int fd, char *buff)
{
	char	*str;
	int		line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = malloc((size_t)BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	line = 1;
	while (line > 0)
	{
		line = read(fd, str, BUFFER_SIZE);
		if (line == -1)
			return (free(str), free(buff), NULL);
		str[line] = '\0';
		buff = ft_strjoin(buff, str);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (free(str), buff);
}

char	*get_next_line(int fd)
{
	static char	*buff[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	buff[fd] = ft_reading_line(fd, buff[fd]);
	if (!buff[fd])
		return (NULL);
	line = ft_getting_line(buff[fd]);
	buff[fd] = ft_next_line(buff[fd]);
	return (line);
}

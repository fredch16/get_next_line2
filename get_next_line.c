/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:44:09 by fredchar          #+#    #+#             */
/*   Updated: 2026/01/12 16:56:36 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// "12345\n678" len = 9 i = 6

int	ft_strlen(char *str)
{
	int	i;
	
	i = 0;
	while (str[i++])
		;
	return (i);
}

void	update_stash(char **stash, int index)
{
	char	*oldstash;
	char	*newstash;
	int		stash_len;

	stash_len = ft_strlen(oldstash);
	oldstash = *stash;
	newstash = (char *)malloc(sizeof(char) * (stash_len - (index + 1)));
	ft_strlcpy(newstash, (oldstash + 1), stash_len - index);
	free(*oldstash);
	*stash = newstash;
}

char	*extract_line(char **stash)
{
	char	*whole;
	int		i;
	char	*line;

	i = 0;
	whole = *stash;
	while (whole[i] && whole[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * i + 1);
	ft_strlcpy(line, whole, i + 1);
	update_stash(stash, i);
	return (line);
}

char	*get_next_line(int fd)
{
	static char *buffer[BUFFER_SIZE + 1];
	char 		*line;
	char		*stash;
	int			bytes;
	
	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= FOPEN_MAX)
		return (NULL);
	stash = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	while (!(ft_strchr(stash, '\n')))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == 0)
			break ;
		if (bytes == -1)
			return (free(stash), NULL); //error
		stash = ft_strjoin(stash, buffer);
	}
	if (!stash[0])
		return (NULL);
	else
		line = extract_line(&stash);
	return (line);
}
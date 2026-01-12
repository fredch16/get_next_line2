/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:44:09 by fredchar          #+#    #+#             */
/*   Updated: 2026/01/12 16:48:48 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char *get_next_line(int fd)
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
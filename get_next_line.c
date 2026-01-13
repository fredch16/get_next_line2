/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:44:09 by fredchar          #+#    #+#             */
/*   Updated: 2026/01/13 18:14:00 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*extract_line(char **stash)
{
	char	*line;
	char	*temp;
	int		i;

	i = 0;
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	if ((*stash)[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, *stash, i + 1);
	temp = ft_strdup(*stash + i);
	if (!temp)
		return (NULL);
	free(*stash);
	*stash = temp;
	return (line);
}

char	*stash_update(char *stash, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(stash, buffer);
	free(stash);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FOPEN_MAX)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer || !stash)
		return (free(buffer), free(stash), stash = NULL, NULL);
	bytes = 1;
	while (bytes > 0 && !ft_strchr(stash, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes > 0)
		{
			buffer[bytes] = '\0';
			stash = stash_update(stash, buffer);
		}
	}
	free(buffer);
	if (bytes == -1 || !stash || !*stash)
		return (free(stash), stash = NULL, NULL);
	return (extract_line(&stash));
}

// int main(int argc, char **argv)
// {
//     int     fd;
//     char    *line;

//     if (argc != 2)
//     {
//         printf("Usage: %s <file>\n", argv[0]);
//         return (1);
//     }

//     fd = open(argv[1], O_RDONLY);
//     if (fd < 0)
//     {
//         perror("open");
//         return (1);
//     }

//     while ((line = get_next_line(fd)) != NULL)
//     {
//         printf("%s", line);
//         free(line);
//     }
// 	// line = get_next_line(fd);
// 	// printf("1: %s", line);
// 	// free(line);

// 	// line = get_next_line(fd);
// 	// printf("2: %s", line);
// 	// free(line);

//     close(fd);
//     return (0);
// }
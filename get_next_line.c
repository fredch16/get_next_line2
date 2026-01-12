/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:44:09 by fredchar          #+#    #+#             */
/*   Updated: 2026/01/12 17:34:47 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// "12345\n678" len = 9 i = 6

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
	char	*oldstash;
	int		i;
	char	*line;
	char	*newstash;
	int		stash_len;

	i = 0;
	oldstash = *stash;
	while (oldstash[i] && oldstash[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * i + 2);
	ft_strlcpy(line, oldstash, i + 2);
	stash_len = ft_strlen(oldstash);
	newstash = (char *)malloc(sizeof(char) * (stash_len - (i + 1)));
	ft_strlcpy(newstash, (oldstash + i + 1), stash_len - i);
	free(oldstash);
	*stash = newstash;
	return (line);
}

void	stash_init(char **stash_pointer)
{
	char	*stash;

	stash = *stash_pointer;
	if (!stash)
	{
		stash = malloc(1);
		if (!stash)
			return ;
		stash[0] = '\0';
		*stash_pointer = stash;
	}
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
	char		buffer[BUFFER_SIZE + 1];
	static char	*stash;
	int			bytes;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= FOPEN_MAX)
		return (NULL);
	stash_init(&stash);
	while (!(ft_strchr(stash, '\n')))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == 0)
			break ;
		if (bytes == -1)
		{
			free(stash);
			stash = NULL;
			return (NULL);
		}
		buffer[bytes] = '\0';
		stash = stash_update(stash, buffer);
	}
	if (!stash[0])
		return (NULL);
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

//     close(fd);
//     return (0);
// }
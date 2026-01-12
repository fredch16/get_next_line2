/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:44:09 by fredchar          #+#    #+#             */
/*   Updated: 2026/01/12 17:16:43 by fredchar         ###   ########.fr       */
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

	oldstash = *stash;
	stash_len = ft_strlen(oldstash);
	newstash = (char *)malloc(sizeof(char) * (stash_len - (index + 1)));
	ft_strlcpy(newstash, (oldstash + index + 1), stash_len - index);
	free(oldstash);
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
	line = (char *)malloc(sizeof(char) * i + 2);
	ft_strlcpy(line, whole, i + 2);
	update_stash(stash, i);
	return (line);
}

char	*get_next_line(int fd)
{
	char buffer[BUFFER_SIZE + 1];
	char 		*line;
	static char		*stash;
	int			bytes;
	
	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= FOPEN_MAX)
		return (NULL);
	if (!stash)
	{
		stash = malloc(1);
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
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
		char *temp = ft_strjoin(stash, buffer);
		free(stash);
		stash = temp;
	}
	if (!stash[0])
		return (NULL);
	else
		line = extract_line(&stash);
	return (line);
}

int main(int argc, char **argv)
{
    int     fd;
    char    *line;

    if (argc != 2)
    {
        printf("Usage: %s <file>\n", argv[0]);
        return (1);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return (1);
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return (0);
}
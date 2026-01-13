/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:34:00 by fredchar          #+#    #+#             */
/*   Updated: 2026/01/13 15:57:40 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000000
# endif

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

// get_next_line_utils.c

char			*ft_strchr(const char *s, int c);
char			*ft_strdup(char *str);
unsigned int	ft_strlcat(char *dest, const char *src, unsigned int size);
unsigned int	ft_strlcpy(char *dst, const char *src, unsigned int dstsize);
char			*ft_strjoin(char const *s1, char const *s2);

// get_next_line.c

int				ft_strlen(char *str);
char			*get_next_line(int fd);

#endif
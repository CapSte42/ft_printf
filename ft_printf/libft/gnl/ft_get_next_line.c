/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:27:18 by smontuor          #+#    #+#             */
/*   Updated: 2023/11/14 18:57:23 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*****************************************************************************/
/*                 ft_remainder_trim                                         */
/*  aggiorna remainder rimuovendo la linea                                   */
/*  appena letta.                                                            */
/*  Scorre remainder fino a \n per trovare fine linea.                       */
/*  Alloca nuovo remainder senza la linea letta.                             */
/*  Copia il resto di remainder originale nel nuovo.                         */
/*  Libera quello originale e restituisce il nuovo.                          */
/*****************************************************************************/
char	*ft_remainder_trim(char *remainder)
{
	size_t	remainder_index;
	size_t	line_index;
	char	*line;

	remainder_index = 0;
	line_index = 0;
	while (remainder[remainder_index] != '\n' && remainder[remainder_index])
		remainder_index++;
	if (!remainder[remainder_index])
	{
		free(remainder);
		return (NULL);
	}
	line = ft_calloc(ft_strlen(remainder) - remainder_index + 1, sizeof(char));
	remainder_index++;
	while (remainder[remainder_index])
		line[line_index++] = remainder[remainder_index++];
	free(remainder);
	return (line);
}

/*****************************************************************************/
/*                 ft_get_line                                               */
/*  estrae la prima linea da remainder.                                      */
/*  Scansiona remainder fino a \n o EOF.                                     */
/*  Alloca line per contenere i byte fino a \n.                              */
/*  Copia i byte da remainder a line.                                        */
/*  Restituisce line contenente la prima riga.                               */
/*****************************************************************************/
char	*ft_get_line(char *remainder)
{
	char	*line;
	size_t	index;

	index = 0;
	if (!remainder[index])
		return (NULL);
	while (remainder[index] != '\n' && remainder[index])
		index++;
	line = ft_calloc(index + 2, sizeof(char));
	index = 0;
	while (*remainder != '\n' && *remainder)
		line[index++] = *remainder++;
	if (*remainder == '\n')
		line[index] = '\n';
	return (line);
}

/*****************************************************************************/
/*                 ft_read_line                                              */
/*  legge da fd in un buffer remainder.                                      */
/*  Finché non trova \n:                                                     */
/*  - Legge al massimo BUFFER_SIZE byte in read_remainder                    */
/*  - Concatena read_remainder a remainder                                   */
/*  - Libera e rialloca remainder per contenere tutto                        */
/*  Restituisce remainder contenente i dati letti                            */
/*  o NULL in caso di errore.                                                */
/*****************************************************************************/
char	*ft_read_line(int fd, char *remainder)
{
	char	*temp_remainder;
	char	*read_remainder;
	ssize_t	bytes_read;

	if (!remainder)
		remainder = ft_calloc(1, sizeof(char));
	temp_remainder = remainder;
	read_remainder = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes_read = 1;
	while (!ft_strchr(remainder, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, read_remainder, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(read_remainder);
			free(temp_remainder);
			return (NULL);
		}
		read_remainder[bytes_read] = '\0';
		temp_remainder = remainder;
		remainder = ft_strjoin(temp_remainder, read_remainder);
		free(temp_remainder);
	}
	free(read_remainder);
	return (remainder);
}

/*****************************************************************************/
/*                 get_next_line                                             */
/*  legge la linea successiva da un file                                     */
/*  descriptor fd. Usa un buffer statico remainder[]                         */
/*  per gestire lo stato tra chiamate multiple.                              */
/*  Legge da fd in remainder[], estrae la prima                              */
/*  linea in line, aggiorna remainder[].                                     */
/*  Restituisce la linea letta o NULL se EOF.                                */
/*****************************************************************************/
char	*ft_get_next_line(int fd)
{
	char		*line;
	static char	*remainder[FD_MAX];

	if (fd == -1 || BUFFER_SIZE <= 0 || fd >= FD_MAX)
		return (NULL);
	remainder[fd] = ft_read_line(fd, remainder[fd]);
	if (!remainder[fd])
		return (NULL);
	line = ft_get_line(remainder[fd]);
	remainder[fd] = ft_remainder_trim(remainder[fd]);
	return (line);
}

/*****************************************************************************/
/*						MAIN												 */
/*****************************************************************************
#include <stdio.h>

void	print_hex(char *str)
{
	while (*str)
	{
		printf("%02hhx ", *str);
		str++;
	}
	printf("\n");
}

int	main(int argc, char **argv)
{
	int		fds[argc - 1];
	char	*line;
	int		i;

	if (argc < 2)
	{
		printf("Uso: %s <file1> [<file2> ...]\n", argv[0]);
		return (1);
	}
	for (i = 1; i < argc; i++)
	{
		fds[i - 1] = open(argv[i], O_RDONLY);
		if (fds[i - 1] == -1)
		{
			perror("Errore nell'apertura del file");
			return (2);
		}
	}
	for (i = 0; i < argc - 1; i++)
	{
		printf("=== Contenuto del file: %s ===\n", argv[i + 1]);
		while ((line = get_next_line(fds[i])) != NULL)
		{
			print_hex(line);
			free(line);
		}
		printf("\n\n");
		if (close(fds[i]) == -1)
		{
			perror("Errore nella chiusura del file");
			return (3);
		}
	}
	return (0);
}
*/
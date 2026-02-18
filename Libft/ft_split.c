/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/29 16:28:00 by dachin        #+#    #+#                 */
/*   Updated: 2025/12/12 12:58:36 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		++i;
	}
	return (count);
}

static char	*ft_substr_split(char const *s, unsigned int sta, unsigned int end)
{
	char			*substring;
	unsigned int	i;

	i = 0;
	substring = malloc((end - sta + 1) * sizeof(char));
	if (!substring)
		return (NULL);
	while (sta < end)
	{
		substring[i] = s[sta];
		++i;
		++sta;
	}
	substring[i] = '\0';
	return (substring);
}

static void	*ft_free_array(char **arr, int arr_len)
{
	int	i;

	i = 0;
	if (!arr)
		return (NULL);
	while (i < arr_len)
	{
		free(arr[i]);
		++i;
	}
	free(arr);
	return (NULL);
}

static void	ft_split_init(int *i, int *j, int *start)
{
	*i = 0;
	*j = 0;
	*start = -1;
}

/**
 * @brief Allocates memory (using malloc(3)) and returns an array of strings
 * obtained by splitting ’s’ using the character ’c’ as a delimiter. The array
 * must end with a NULL pointer
 * @param s The string to be split.
 * @param c The delimiter character.
 * @return int The array of new strings resulting from the split. NULL if the
 * allocation fails.
 */
char	**ft_split(char const *s, char c)
{
	char	**arr_words;
	int		i;
	int		j;
	int		start;

	ft_split_init(&i, &j, &start);
	arr_words = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!arr_words)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c && start == -1)
			start = i;
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			arr_words[j] = ft_substr_split(s, start, i + 1);
			if (!arr_words[j])
				return (ft_free_array(arr_words, j));
			start = -1;
			j++;
		}
		i++;
	}
	arr_words[j] = NULL;
	return (arr_words);
}

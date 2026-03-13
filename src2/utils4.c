/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils4.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/13 10:00:00 by dachin        #+#    #+#                 */
/*   Updated: 2026/03/13 10:00:00 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	handle_bslash_quote(const char **s, int dq)
{
	if (dq && **s == '\\' && (*s)[1] == '"')
		return ((*s)++, 1);
	return (0);
}

// Advance s past one token, updating quote state
static void	advance_token(const char **s, int *sq, int *dq)
{
	while (**s && (**s != ' ' || *sq || *dq))
	{
		if (**s == '\'' && !*dq)
			*sq = !*sq;
		else if (**s == '"' && !*sq)
			*dq = !*dq;
		else if (*dq && **s == '\\' && (*s)[1] == '"')
			(*s)++;
		(*s)++;
	}
}

static int	count_cmd_args(const char *s)
{
	int	count;
	int	sq;
	int	dq;

	count = 0;
	sq = 0;
	dq = 0;
	while (*s)
	{
		while (*s == ' ' && !sq && !dq)
			s++;
		if (!*s)
			break ;
		count++;
		advance_token(&s, &sq, &dq);
	}
	return (count);
}

static char	*get_next_arg(const char **s)
{
	char	*buf;
	int		i;
	int		sq;
	int		dq;

	buf = malloc(ft_strlen(*s) + 1);
	if (!buf)
		return (NULL);
	i = 0;
	sq = 0;
	dq = 0;
	while (**s && (**s != ' ' || sq || dq))
	{
		if (**s == '\'' && !dq)
			sq = !sq;
		else if (**s == '"' && !sq)
			dq = !dq;
		else if (handle_bslash_quote(s, dq))
			buf[i++] = '"';
		else
			buf[i++] = **s;
		(*s)++;
	}
	buf[i] = '\0';
	return (buf);
}

char	**split_cmd_args(const char *s)
{
	char	**args;
	int		i;
	int		n;

	n = count_cmd_args(s);
	args = malloc(sizeof(char *) * (n + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (i < n)
	{
		while (*s == ' ')
			s++;
		args[i] = get_next_arg(&s);
		if (!args[i])
			return (free_array(args), NULL);
		i++;
	}
	args[n] = NULL;
	return (args);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:09:03 by aismaili          #+#    #+#             */
/*   Updated: 2023/12/08 19:19:03 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	check_pid(char *s_pid)
{
	int	pid;
	int	i;

	i = 0;
	while (s_pid[i])
	{
		if (!(s_pid[i] >= '0' && s_pid[i] <= '9'))
			ft_error_exit("wrong PID");
		i++;
	}
	pid = atoi(s_pid);
	if (pid <= 0)
		ft_error_exit("wrong PID");
	if (kill(pid, 0) == -1)
		ft_error_exit("wrong PID");
	return (pid);
}

void	ft_error_exit(char *str)
{
	ft_printf("%s\n", str);
	exit(1);
}

int	expand_buffer(t_dynamic_buffer *buffer, int new_capacity)
{
	char	*new_str;

	new_str = malloc(new_capacity);
	if (!new_str)
		return (0);
	ft_memcpy(new_str, buffer->str, buffer->len);
	free(buffer->str);
	buffer->str = new_str;
	buffer->capacity = new_capacity;
	return (1);
}

int	append_to_buffer(t_dynamic_buffer *buffer, char c)
{
	int	new_capacity;

	if (buffer->len + 1 >= buffer->capacity)
	{
		new_capacity = buffer->capacity * 2;
		if (!expand_buffer(buffer, new_capacity))
			return (0);
	}
	buffer->str[buffer->len] = c;
	buffer->len++;
	buffer->str[buffer->len] = 0;
	return (1);
}

void	safe_char(int *c, int *j, int *client_pid, t_dynamic_buffer **buffer)
{
	if (*j == 8)
	{
		if (*c == 0)
		{
			ft_printf("%s\n", (*buffer)->str);
			free((*buffer)->str);
			free(*buffer);
			(*buffer) = NULL;
			if (kill(*client_pid, SIGUSR2) == -1)
				ft_error_exit("Error sending signal to client");
			*client_pid = 0;
		}
		else
		{
			if (!append_to_buffer(*buffer, *c))
			{
				free((*buffer)->str);
				free(*buffer);
				ft_error_exit("Error appending to buffer");
			}
		}
		*c = 0;
		*j = 0;
	}
}

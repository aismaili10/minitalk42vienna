/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:28:43 by aismaili          #+#    #+#             */
/*   Updated: 2023/12/08 18:53:47 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "../libft/printf/ft_printf.h"

typedef struct s_dynamic_buffer
{
	char	*str;
	int		len;
	int		capacity;
}			t_dynamic_buffer;

void		ft_error_exit(char *str);
int			check_pid(char *s_pid);
void		safe_char(int *c, int *j, int *client_pid,
				t_dynamic_buffer **buffer);
int			expand_buffer(t_dynamic_buffer *buffer, int new_capacity);
int			append_to_buffer(t_dynamic_buffer *buffer, char c);

#endif

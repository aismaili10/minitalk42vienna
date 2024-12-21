/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:45:55 by aismaili          #+#    #+#             */
/*   Updated: 2023/12/05 15:32:48 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

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

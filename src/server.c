/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:44:06 by aismaili          #+#    #+#             */
/*   Updated: 2023/12/08 19:42:52 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void				receive_message(int sig, siginfo_t *siginfo,
						void *ucontext);

t_dynamic_buffer	*init_buffer(int initial_capacity)
{
	t_dynamic_buffer	*buffer;

	buffer = malloc(sizeof(t_dynamic_buffer));
	if (!buffer)
		return (0);
	buffer->str = malloc(initial_capacity);
	if (!buffer->str)
	{
		free(buffer);
		return (0);
	}
	buffer->str[0] = 0;
	buffer->len = 0;
	buffer->capacity = initial_capacity;
	return (buffer);
}

int	main(void)
{
	int					pid;
	struct sigaction	sig_b;

	pid = getpid();
	ft_printf("PID: %d\n", pid);
	sig_b.sa_sigaction = receive_message;
	sig_b.sa_flags = SA_SIGINFO;
	sigemptyset(&sig_b.sa_mask);
	if (sigaction(SIGUSR1, &sig_b, NULL) == -1 || sigaction(SIGUSR2, &sig_b,
			NULL) == -1)
	{
		ft_printf("Error setting signal handler\n");
		exit(1);
	}
	while (1)
	{
		pause();
	}
	return (0);
}

void	receive_message(int sig, siginfo_t *siginfo, void *ucontext)
{
	static int				c;
	static int				j;
	static int				client_pid;
	static t_dynamic_buffer	*buffer;

	if (buffer == NULL)
	{
		buffer = init_buffer(1000);
		if (!buffer)
			ft_error_exit("Error initializing buffer");
	}
	(void)ucontext;
	if (!client_pid)
		client_pid = siginfo->si_pid;
	if (sig == SIGUSR1)
		c |= (1 << j);
	j++;
	if (kill(client_pid, SIGUSR1) == -1)
	{
		free(buffer->str);
		free(buffer);
		ft_error_exit("Error sending signal to client");
	}
	safe_char(&c, &j, &client_pid, &buffer);
}

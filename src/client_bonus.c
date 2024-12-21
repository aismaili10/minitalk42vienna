/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:39:39 by aismaili          #+#    #+#             */
/*   Updated: 2023/12/08 19:08:42 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int		g_received_bit = 0;

void	handler_sig1(int sig)
{
	if (sig == SIGUSR1)
		g_received_bit = 1;
}

void	atob_bits(char c, int pid)
{
	int	j;

	j = 0;
	while (j < 8)
	{
		if (c & (1 << j))
		{
			if (kill(pid, SIGUSR1) == -1)
				ft_error_exit("Error sending SIGUSR1");
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				ft_error_exit("Error sending SIGUSR2");
		}
		while (g_received_bit == 0)
		{
		}
		g_received_bit = 0;
		j++;
	}
}

void	atob(char *str, int pid)
{
	int	i;

	i = 0;
	while (str[i])
	{
		atob_bits(str[i], pid);
		usleep(500);
		i++;
	}
	atob_bits('\0', pid);
}

void	handler_sig2(int sig)
{
	if (sig == SIGUSR2)
		ft_printf("Message received\n");
	exit(1);
}

int	main(int ac, char **av)
{
	struct sigaction	sig_1;
	struct sigaction	sig_2;
	int					pid;

	if (ac != 3)
	{
		ft_printf("Usage: ./client [PID] [message]\n");
		return (0);
	}
	pid = check_pid((av[1]));
	sig_1.sa_handler = handler_sig1;
	sig_2.sa_handler = handler_sig2;
	sigemptyset(&sig_1.sa_mask);
	sigemptyset(&sig_2.sa_mask);
	sig_1.sa_flags = 0;
	sig_2.sa_flags = 0;
	if (sigaction(SIGUSR1, &sig_1, NULL) == -1 || sigaction(SIGUSR2, &sig_2,
			NULL) == -1)
		ft_error_exit("Error setting signal handler");
	atob(av[2], pid);
	while (1)
	{
		pause();
	}
	return (0);
}

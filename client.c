/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:28:04 by caalbert          #+#    #+#             */
/*   Updated: 2023/02/07 12:30:09 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minitalk.h"

void	send_bytes(char c, pid_t pid);
void	streaming(char *str, pid_t pid);
void	ft_reciver(int sig);

int	main(int argc, char *argv[])
{
	pid_t			pid;
	char			*str;

	signal(SIGUSR1, ft_reciver);
	if (argc != 3)
	{
		ft_printf("Usage: %s <pid> <message>\n", argv[0]);
		return (0);
	}
	pid = ft_atoi(argv[1]);
	str = argv[2];
	streaming(str, pid);
	return (0);
}

void	send_bytes(char c, pid_t pid)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if (c & (1 << bit))
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(TIME_SLEEP);
		bit++;
	}
}

void	streaming(char *str, pid_t pid)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_bytes(str[i], pid);
		i++;
	}
	send_bytes('\n', pid);
}

void	ft_reciver(int sig)
{
	(void)sig;
}

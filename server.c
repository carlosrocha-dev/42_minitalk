/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:28:14 by caalbert          #+#    #+#             */
/*   Updated: 2023/05/23 06:08:19 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minitalk.h"

void	ft_sig_exit(int sig);
void	ft_sig_reciver(int sig, siginfo_t *info, void *context);
void	ft_setup_signals(void);

int	main(void)
{
	ft_printf("Use this pid: %d\n", getpid());
	ft_setup_signals();
	while (1)
		pause();
}

void	ft_setup_signals(void)
{
	struct sigaction	act;

	act.sa_handler = SIG_DFL;
	act.sa_sigaction = ft_sig_reciver;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, 0);
	sigaction(SIGUSR2, &act, 0);
	signal(SIGINT, ft_sig_exit);
	signal(SIGTERM, ft_sig_exit);
}

void	ft_sig_reciver(int sig, siginfo_t *info, void *context)
{
	static struct s_unicode		uni = {0, 0};

	(void)context;
	if (sig == SIGUSR2)
		uni.uni_char += 1 << uni.bit;
	uni.bit++;
	if (uni.bit == 8)
	{
		ft_putchar_fd(uni.uni_char, 1);
		uni.bit = 0;
		uni.uni_char = 0;
	}
	if (sig == SIGUSR1)
		kill(info->si_pid, SIGUSR1);
}

void	ft_sig_exit(int sig)
{
	(void)sig;
	exit(0);
}

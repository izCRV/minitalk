/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aizsak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:27:03 by aizsak            #+#    #+#             */
/*   Updated: 2023/01/31 09:09:32 by aizsak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	g_global;

static void	str_to_binary(char *s, pid_t pid, t_bin bin)
{
	bin.i = 0;
	while (bin.i <= (int)ft_strlen(s))
	{
		bin.y = 7;
		while (bin.y >= 0)
		{
			g_global = 0;
			if (s[bin.i] & 1 << bin.y)
			{
				if (kill(pid, SIGUSR1) == -1)
					exit(-1);
			}
			else
			{
				if (kill(pid, SIGUSR2) == -1)
					exit(-1);
			}
			while (g_global == 0)
				;
			bin.y--;
		}
		bin.i++;
	}
}

static void	signal_checker(int signum, siginfo_t *siginfo, void *ucontext)
{
	(void)ucontext;
	if (signum != SIGUSR1)
		exit(-1);
	if (siginfo->si_code != SI_USER)
		exit(-1);
}

static void	signal_handler(int signum, siginfo_t *siginfo, void *ucontext)
{
	(void)ucontext;
	signal_checker(signum, siginfo, ucontext);
	if (signum == SIGUSR1)
		g_global = 1;
	else if (signum == SIGUSR2)
		ft_printf("Charli Tango end of transmison.\n");
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	t_bin				bin;
	struct sigaction	signal_action;

	pid = ft_atoi(argv[1]);
	if (argc < 3 || pid < 0)
	{
		ft_printf("Valid form: ./client <pid_server><message>\n");
		exit(-1);
	}
	signal_action.sa_sigaction = signal_handler;
	sigemptyset(&signal_action.sa_mask);
	signal_action.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &signal_action, NULL) < 0)
		exit(-1);
	if (sigaction(SIGUSR1, &signal_action, NULL) < 0)
		exit(-1);
	str_to_binary(argv[2], pid, bin);
	exit(0);
}

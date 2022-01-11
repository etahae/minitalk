/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 14:31:29 by tnamir            #+#    #+#             */
/*   Updated: 2022/01/01 14:31:29 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

static void	bin_to_dec(char *p)
{
	int			i;
	int			var;
	int			base;

	i = 0;
	var = 0;
	base = 128;
	while (p[i])
	{
		var += base * (p[i] - 48);
		base = base / 2;
		i++;
	}
	write(1, &var, 1);
}

void	sighand(int sig, siginfo_t *siginfo, void *context)
{
	static char	p[8];
	static int	pid;
	static int	x;

	if (!pid)
		pid = siginfo->si_pid;
	if (pid != siginfo->si_pid)
	{
		pid = siginfo->si_pid;
		x = 0;
	}
	(void)context;
	if (sig == SIGUSR1)
		p[x++] = '0';
	else if (sig == SIGUSR2)
		p[x++] = '1';
	if (x == 8)
	{
		p[x] = '\0';
		bin_to_dec(p);
		x = 0;
	}
}

static void	ft_putnbr(int nb)
{
	char	x;

	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
	{
		x = nb + '0';
		write(1, &x, 1);
	}
}

int	main(void)
{
	struct sigaction	s;
	int					pid;

	pid = getpid();
	ft_putnbr(pid);
	write(1, "\n", 1);
	s.sa_sigaction = &sighand;
	s.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s, NULL);
	sigaction(SIGUSR2, &s, NULL);
	while (1)
		pause();
	return (0);
}

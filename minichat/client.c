#include <signal.h>
#include <unistd.h>

static int	aatoi(char *str)
{
	int	num;
	int	i;
	int	sign;

	i = 0;
	num = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * sign);
}

static void	putbinary(int nbr, char *bcode, int *i)
{
	char	bin[2];

	bin[0] = '0';
	bin[1] = '1';
	if (nbr >= 2)
	{
		putbinary(nbr / 2, bcode, i);
		putbinary(nbr % 2, bcode, i);
	}
	else
	{
		bcode[*i] = bin[nbr];
		*i += 1;
	}
}

static void	sendsignal(char c, int pid, int *sigcheck)
{
	if (c == '0')
			*sigcheck += kill(pid, SIGUSR1);
	if (c == '1')
			*sigcheck += kill(pid, SIGUSR2);
}

static void	pre_sendsignal(unsigned char c, int pid, int *sigcheck)
{
	int		y;
	char	binarystr[8];

	y = 0;
	if (c < 64)
	{
		binarystr[0] = '0';
		binarystr[1] = '0';
		y += 2;
	}
	else if (c >= 64 && c <= 127)
	{
		binarystr[0] = '0';
		y++;
	}
	putbinary(c, binarystr, &y);
	y = 0;
	while (y <= 8)
	{
		sendsignal(binarystr[y], pid, sigcheck);
		y++;
		usleep(800);
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	int		x;
	int		sigcheck;

	sigcheck = 0;
	x = 0;
	if (argc == 3)
	{
		pid = aatoi(argv[1]);
		if (pid != -1)
		{
			while (argv[2][x])
			{
				pre_sendsignal(argv[2][x], pid, &sigcheck);
				x++;
			}
			if (sigcheck == 0)
				write(1, "Message sent successfully !", 28);
			else
				write(1, "An error has occured !", 23);
		}
	}
	return (0);
}

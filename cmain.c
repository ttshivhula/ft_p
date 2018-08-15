/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 09:00:29 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/08/15 09:00:49 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftp.h>

static void	receive_data(int sock_fd, size_t size)
{
	char	buff[BUFF_SIZE];
	size_t	received;
	size_t	c;

	received = 0;
	while (received < size)
	{
		c = recv(sock_fd, buff, BUFF_SIZE, 0);
		write(1, buff, c);
		received += c;
	}
	received ? ft_putchar('\n') : 0;
}

static void	process_commands(int sock_fd, char *str)
{
	size_t	size;
	char	cmd[BUFF_SIZE];
	
	send(sock_fd, str, sizeof(cmd), 0);
	if (!ft_strncmp(str, "put", 3))
		client_put(sock_fd, ft_strchr(str, ' ') + 1);
	if (!ft_strncmp(str, "get", 3))
		client_get(sock_fd, ft_strchr(str, ' ') + 1);
	if (!ft_strncmp(str, "quit", 4))
			exit(0);
	recv(sock_fd, &size, sizeof(size_t), 0);
	receive_data(sock_fd, size);
}

static int	check_local(char *cmd)
{
	if (!ft_strncmp("clear", cmd, 5))
	{
		ft_putstr("\e[1;1H\e[2J");
		return (1);
	}
	if (!ft_strncmp("lcd", cmd, 3))
	{
		local_cd(ft_strchr(cmd, ' ') + 1);
		return (1);
	}
	if (!ft_strncmp("lpwd", cmd, 4))
	{
		local_pwd();
		return (1);
	}
	if (!ft_strncmp("lls", cmd, 3))
	{
		local_ls(cmd);
		return (1);
	}
	return (0);
}

static void	ftp_shell(int sock_fd)
{
	int			ret;
	char		cmd[BUFF_SIZE];

	ft_putstr("\x1b[34mftp >\x1b[0m ");
	ret = read(0, cmd, BUFF_SIZE - 1);
	cmd[ret - 1] = '\0';
	if (ret == 0)
		ft_putchar('\n');
	if (ret == 1 || check_local(cmd))
		return ;
	process_commands(sock_fd, cmd);
}

int			main(int c, char **v)
{
	struct sockaddr_in	addr;
	struct hostent		*host;
	int			fd;

	if (c != 3)
		ft_die("Usage: ./client host port\n", 1);
	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		ft_die(ERROR" client socket creation failed\n", 1);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(ft_atoi(v[2]));
	if ((host = gethostbyname(v[1])) == NULL)
		ft_die(ERROR" check your host\n", 1);
	ft_memcpy(&addr.sin_addr.s_addr, host->h_addr, host->h_length);
	if (connect(fd, (void*)&(addr), sizeof(addr)) < 0)
		ft_die(ERROR" unable to connect\n", 1);
	ft_putstr("\e[1;1H\e[2J");
	while (42)
		ftp_shell(fd);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 09:40:49 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/08/15 10:48:05 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftp.h>

static int	file_commands(int sock_fd, char *str)
{
	if (!ft_strncmp(str, "mkdir", 5))
		return (ft_mkdir(sock_fd, ft_strchr(str, ' ') + 1));
	if (!ft_strncmp(str, "rmdir", 5))
		return (ft_rmdir(sock_fd, ft_strchr(str, ' ') + 1));
	if (!ft_strncmp(str, "unlink", 6))
		return (ft_unlink(sock_fd, ft_strchr(str, ' ') + 1));
	return (0);
}

static void	command(int sock_fd, char *str)
{
	if (!ft_strncmp(str, "ls", 2))
		ftp_ls(sock_fd, str);
	else if (!ft_strncmp(str, "cd", 2))
		ftp_cd(sock_fd, ft_strchr(str, ' ') + 1);
	else if (!ft_strncmp(str, "get", 3))
		ftp_get(sock_fd, ft_strchr(str, ' ') + 1);
	else if (!ft_strncmp(str, "put", 3))
		ftp_put(sock_fd, ft_strchr(str, ' ') + 1);
	else if (!ft_strncmp(str, "pwd", 3))
		ftp_pwd(sock_fd);
	else if (!ft_strncmp(str, "quit", 4))
		ftp_quit(sock_fd);
	else if (file_commands(sock_fd, str))
		return ;
	else
		ftp_error(sock_fd);
}

static void	client_server_loop(int sock_fd)
{
	char	cmd[BUFF_SIZE];

	while (42)
	{
		ft_bzero(cmd, BUFF_SIZE);
		recv(sock_fd, cmd, sizeof(cmd), 0);
		command(sock_fd, cmd);
	}
}

static void	accept_clients(int sock_fd, socklen_t size)
{
	pid_t				pid;
	struct sockaddr_in	addr;
	int					client_fd;

	if (listen(sock_fd, 10000) == -1)
		ft_putstr(ERROR" Listen failed\n");
	else
	{
		client_fd = accept(sock_fd, (void*)&(addr), &size);
		while ((pid = fork()) == -1)
			ft_putstr(ERROR" fork failed\n");
		if (pid == 0)
			client_server_loop(client_fd);
	}
}

int			main(int c, char **v)
{
	struct sockaddr_in	addr;
	int					server_fd;

	if (c != 2)
		ft_die("Usage: ./server port\n", 1);
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		ft_die(ERROR" server socket creation failed\n", 1);
	addr.sin_port = htons(ft_atoi(v[1]));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(server_fd, (void*)&(addr), sizeof(addr)) < 0)
		ft_die(ERROR" server port bind failed\n", 1);
	ft_putstr("Server listening on port ");
	ft_putnbr(ntohs(addr.sin_port));
	ft_putstr(".\n");
	get_root();
	while (42)
		accept_clients(server_fd, sizeof(struct sockaddr_in));
	return (0);
}

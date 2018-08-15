/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 09:18:31 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/08/15 09:22:19 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftp.h>

void			client_get(int sock_fd, char *cmd)
{
	size_t	size;

	recv(sock_fd, &size, sizeof(size_t), 0);
	if (size > 0)
		receivefile(sock_fd, size, cmd);
}

static void		send_data(int sock_fd, void *buf, size_t size)
{
	size_t sent;

	sent = 0;
	if (size > 0)
	{
		progress(0.0, (float)size);
		while (sent < size)
		{
			progress((float)sent, (float)size);
			sent += send(sock_fd, buf + sent, BUFF_SIZE, 0);
		}
	}
}

void			client_put(int sock_fd, char *cmd)
{
	int		fd;
	size_t	size;
	void	*buf;

	fd = 0;
	size = 0;
	if (is_dir(cmd) || ((fd = open(cmd, O_RDONLY)) < 0))
	{
		send(sock_fd, &size, sizeof(size_t), 0);
		return ;
	}
	size = getsize(fd);
	buf = mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0);
	size = buf ? size : 0;
	send(sock_fd, &size, sizeof(size_t), 0);
	send_data(sock_fd, buf, size);
	munmap(buf, size);
	close(fd);
}

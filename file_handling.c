/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 08:54:35 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/08/15 17:12:56 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftp.h>

void	loading(int current)
{
	int i;
	char buff[21];
	
	i = 0;
	ft_bzero(buff, 21);
	while (++i <= 20)
	{
		if (i <= current / 5)
			buff[i - 1] = '#';
		else
			buff[i - 1] = '_';
	}
	ft_putstr(buff);
	ft_putstr("] ");
}

void	progress(float current, float max)
{
	float percentage;

	percentage = (current / max) * 100;
	ft_putstr("\033[A\033[2K");
	ft_putstr("\x1b[33mIO:\x1b[0m [");
	loading((int)percentage);
	ft_putnbr(((int)percentage > 100) ? 100 : (int)percentage);
	ft_putendl(" %");
}

int		receivefile(int sock_fd, size_t size, char *file_path)
{
	int		fd;
	char	buf[BUFF_SIZE];
	size_t	r;
	size_t	received;

	if ((fd = open(file_path, O_CREAT | O_TRUNC | O_WRONLY, 0644)) < 0)
		return (0);
	received = 0;
	ft_putchar('\n');
	progress(0, (float)size);
	while (received < size)
	{
		progress((float)received, (float)size);
		r = recv(sock_fd, buf, BUFF_SIZE, 0);
		write(fd, buf, r);
		received += r;
	}
	progress(received, (float)size);
	close(fd);
	return (1);
}

void	ftp_get(int sock_fd, char *str)
{
	int		fd;
	size_t	size;
	void	*buf;
	size_t	sent;

	fd = 0;
	sent = 0;
	fd = open(basename(str), O_RDONLY);
	size = getsize(fd);
	buf = mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0);
	send(sock_fd, &size, sizeof(size_t), 0);
	while (sent < size && (size > 0))
		sent += send(sock_fd, buf + sent, BUFF_SIZE, 0);
	munmap(buf, size);
	if (size > 0)
		buf = ft_strdup(SUCCESS" file received from server");
	else
		buf = ft_strdup(ERROR" file not received from server");
	size = ft_strlen(buf);
	send(sock_fd, &size, sizeof(size_t), 0);
	send(sock_fd, buf, size, 0);
	free(buf);
	close(fd);
}

void	ftp_put(int sock_fd, char *str)
{
	size_t	size;
	char	*buf;
	int		ret;

	ret = 0;
	recv(sock_fd, &size, sizeof(size_t), 0);
	if (size > 0)
		ret = receivefile(sock_fd, size, basename(str));
	if (ret == 0)
		buf = ft_strdup(ERROR" file not saved on server");
	else
		buf = ft_strdup(SUCCESS" file saved on server");
	size = ft_strlen(buf);
	send(sock_fd, &size, sizeof(size_t), 0);
	send(sock_fd, buf, size, 0);
	free(buf);
}

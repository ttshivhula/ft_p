#include <ftp.h>

void			client_get(int sock_fd, char *cmd)
{
	size_t	size;

	recv(sock_fd, &size, sizeof(size_t), 0);
	if (size > 0)
		receivefile(sock_fd, size, cmd);
}

void			client_put(int sock_fd, char *cmd)
{
	int	fd;
	size_t	size;
	void	*buf;
	size_t	sent;

	fd = 0;
	sent = 0;
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
	if (size > 0)
	{
		while (sent < size)
			sent += send(sock_fd, buf + sent, BUFF_SIZE, 0);
	}
	munmap(buf, size);
	close(fd);
}

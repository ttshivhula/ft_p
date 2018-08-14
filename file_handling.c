#include <ftp.h>

int	receivefile(int sock_fd, size_t size, char *file_path)
{
	int		fd;
	char	buf[BUFF_SIZE];
	size_t	r;
	size_t	received;

	if ((fd = open(file_path, O_CREAT | O_TRUNC | O_WRONLY, 0644)) < 0)
		return (0);
	received = 0;
	while (received < size)
	{
		r = recv(sock_fd, buf, BUFF_SIZE, 0);
		write(fd, buf, r);
		received += r;
	}
	close(fd);
	return (1);
}

void	ftp_get(int sock_fd, char *str)
{
	int	fd;
	size_t	size;
	void	*buf;
	size_t	sent;

	fd = 0;
	sent = 0;
	fd = open(basename(str), O_RDONLY);
	size = getsize(fd);
	buf = mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0);
	send(sock_fd, &size, sizeof(size_t), 0);
	if (size > 0)
	{
		while (sent < size)
			sent += send(sock_fd, buf + sent, BUFF_SIZE, 0);
	}
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
	int	ret;

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

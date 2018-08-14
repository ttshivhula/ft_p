#include <ftp.h>

void		free_ptr(char **ptr)
{
	int  i;

	i = -1;
	while (ptr[++i])
		free(ptr[i]);
	free(ptr);
}

void		execute_ls(char *str, int fd)
{
	extern char	**environ;
	char		**cmds;
	pid_t		pid;

	cmds = ft_strsplit(str, ' ');
	dup2(fd, 1);
	dup2(fd, 2);
	pid = fork();
	if (pid == 0)
		execve("/bin/ls", cmds, environ);
	else
	{
		wait(0);
		free_ptr(cmds);
	}
}

void		ftp_ls(int sock_fd, char *str)
{
	int	fd;
	size_t	size;
	char	*buff;
	size_t	sent;

	sent = 0;
	fd = open(".tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	execute_ls(str, fd);
	size = getsize(fd);
	buff = mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0);
	send(sock_fd, &size, sizeof(size_t), 0);
	while (sent < size)
		sent += send(sock_fd, buff + sent, BUFF_SIZE, 0);
	unlink(".tmp");
	munmap(buff, size);
}

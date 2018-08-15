/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 09:22:33 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/08/15 09:22:44 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftp.h>

void	ft_die(char *str, int exit_code)
{
	write(2, str, ft_strlen(str));
	exit(exit_code);
}

void	ftp_quit(int sock_fd)
{
	close(sock_fd);
	exit(0);
}

void	ftp_error(int sock_fd)
{
	char	buf[BUFF_SIZE];
	size_t	len;

	ft_strcpy(buf, ERROR" command not found");
	len = ft_strlen(buf);
	send(sock_fd, &len, sizeof(size_t), 0);
	send(sock_fd, buf, len, 0);
}

size_t	getsize(int fd)
{
	struct stat	buf;
	int			ret;

	ret = fstat(fd, &buf);
	if (ret == -1)
		return (0);
	return (buf.st_size);
}

int		is_dir(char *name)
{
	int			fd;
	struct stat	buf;
	int			ret;

	if ((fd = open(name, O_RDONLY)) == -1)
		return (0);
	ret = fstat(fd, &buf);
	close(fd);
	if (ret == -1)
		return (0);
	if (buf.st_mode & S_IFDIR)
		return (1);
	return (0);
}

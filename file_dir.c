/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 10:28:22 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/08/15 10:47:26 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftp.h>

int		ft_mkdir(int sock_fd, char *str)
{
	int		ret;
	char	*tmp;
	size_t	size;

	ret = mkdir(str, 0666);
	if (ret == -1)
		tmp = ft_strdup(ERROR" failed to create dir");
	else
		tmp = ft_strdup(SUCCESS" created the dir");
	size = ft_strlen(tmp);
	send(sock_fd, &size, sizeof(size_t), 0);
	send(sock_fd, tmp, size, 0);
	free(tmp);
	return (1);
}

int		ft_rmdir(int sock_fd, char *str)
{
	int		ret;
	char	*tmp;
	size_t	size;

	ret = rmdir(str);
	if (ret == -1)
		tmp = ft_strdup(ERROR" failed to remove dir");
	else
		tmp = ft_strdup(SUCCESS" removed dir");
	size = ft_strlen(tmp);
	send(sock_fd, &size, sizeof(size_t), 0);
	send(sock_fd, tmp, size, 0);
	free(tmp);
	return (1);
}

int		ft_unlink(int sock_fd, char *str)
{
	int		ret;
	char	*tmp;
	size_t	size;

	ret = unlink(str);
	if (ret == -1)
		tmp = ft_strdup(ERROR" failed to remove file");
	else
		tmp = ft_strdup(SUCCESS" removed file");
	size = ft_strlen(tmp);
	send(sock_fd, &size, sizeof(size_t), 0);
	send(sock_fd, tmp, size, 0);
	free(tmp);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 10:28:22 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/08/15 11:30:09 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftp.h>

static int	rmdir_helper(struct dirent *p, char *path, int path_len)
{
	int			ret;
	char		*buf;
	size_t		len;
	struct stat statbuf;

	ret = -1;
	if (!ft_strcmp(p->d_name, ".") || !ft_strcmp(p->d_name, ".."))
		return (0);
	len = path_len + ft_strlen(p->d_name) + 2;
	buf = malloc(len);
	if (buf)
	{
		snprintf(buf, len, "%s/%s", path, p->d_name);
		if (!stat(buf, &statbuf))
		{
			if (S_ISDIR(statbuf.st_mode))
				ret = remove_dir(buf, ft_strlen(buf));
			else
				ret = unlink(buf);
		}
		free(buf);
	}
	return (ret);
}

int			remove_dir(char *path, int path_len)
{
	DIR				*d;
	int				ret;
	struct dirent	*p;

	ret = -1;
	d = opendir(path);
	if (d)
	{
		ret = 0;
		while (!ret && (p = readdir(d)))
			ret = rmdir_helper(p, path, path_len);
		closedir(d);
	}
	if (!ret)
		ret = rmdir(path);
	return (ret);
}

int			ft_mkdir(int sock_fd, char *str)
{
	int		ret;
	char	*tmp;
	size_t	size;

	ret = mkdir(str, 0777);
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

int			ft_rmdir(int sock_fd, char *str)
{
	int		ret;
	char	*tmp;
	size_t	size;

	ret = remove_dir(str, ft_strlen(str));
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

int			ft_unlink(int sock_fd, char *str)
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

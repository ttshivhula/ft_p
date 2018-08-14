#include <ftp.h>

void	ftp_pwd(int sock_fd)
{
	char	str[MAXPATHLEN + 1];
	size_t	len;

	if (getcwd(str, MAXPATHLEN) == NULL)
	{
		ft_strcpy(str, ERROR" getcwd failed");
	}
	else
	{
		ft_strcat(str, "/");
		ft_strcpy(str, str + ft_strlen(get_root()));
	}
	len = ft_strlen(str);
	send(sock_fd, &len, sizeof(size_t), 0);
	send(sock_fd, str, len, 0);
}

void	ftp_cd(int sock_fd, char *str)
{
	int	ret;

	if (*str == 0)
		ret = chdir(get_root());
	else
		ret = chdir(str);
	if (ret == -1 || ft_strlen(get_dir()) < ft_strlen(get_root()))
		chdir(get_root());
	ftp_pwd(sock_fd);
}
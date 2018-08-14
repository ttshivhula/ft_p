#include <ftp.h>

void	local_cd(char *str)
{
	int	ret;
	char	cdir[MAXPATHLEN];
	
	ret = chdir(str);
	if (ret != -1)
	{
		ft_putstr("changed dir to: ");
		getcwd(cdir, MAXPATHLEN);
		ft_putendl(cdir);
	}
}

void	local_pwd(void)
{
	char	cdir[MAXPATHLEN];

	getcwd(cdir, MAXPATHLEN);
	ft_putendl(cdir);
}

void	local_ls(char *str)
{
	pid_t		child;
	extern char	**environ;
	char		**cmds;
	
	cmds = ft_strsplit(str, ' ');
	child = fork();
	if (child == 0)
		execve("/bin/ls", cmds, environ);
	else
	{
		wait(0);
		free_ptr(cmds);
	}
}

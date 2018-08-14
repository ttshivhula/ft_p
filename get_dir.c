#include <ftp.h>

char	*get_root(void)
{
	static char	root[MAXPATHLEN] = "";

	if (*root != 0)
		return (root);
	if (getcwd(root, MAXPATHLEN) == NULL)
		ft_die(ERROR" getcwd failed\n", 1);
	return (root);
}

char	*get_dir(void)
{
	static char	dir[MAXPATHLEN] = "";

	if (getcwd(dir, MAXPATHLEN) == NULL)
		ft_die(ERROR" getcwd failed\n", 1);
	return (dir);
}

char	*basename(char *str)
{
	char	*tmp;

	if (str == NULL)
		return (NULL);
	tmp = str + ft_strlen(str);
	while (tmp != str)
	{
		if (*(tmp - 1) == '/')
			break ;
		tmp--;
	}
	return (tmp);
	
}

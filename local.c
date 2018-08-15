/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 08:54:57 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/08/15 09:27:58 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftp.h>

void	local_cd(char *str)
{
	int		ret;
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
	char		**cmds;

	cmds = ft_strsplit(str, ' ');
	child = fork();
	if (child == 0)
		execv("/bin/ls", cmds);
	else
	{
		wait4(0, NULL, 0, NULL);
		free_ptr(cmds);
	}
}

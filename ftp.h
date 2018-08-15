/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 09:14:33 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/08/15 09:17:42 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_H
# define FTP_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/param.h>
# include <stdint.h>
# include <sys/wait.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <dirent.h>
# include <libft.h>

# define ERROR "\x1b[31mERROR:\x1b[0m"
# define SUCCESS "\x1b[32mSUCCESS:\x1b[0m"
# define BUFF_SIZE 1024

int		receivefile(int sock_fd, size_t size, char *file_path);
size_t	getsize(int fd);
int		is_dir(char *name);
char	*get_root(void);
char	*get_dir(void);
char	*basename(char *str);
void	ftp_ls(int sock_fd, char *str);
void	ftp_cd(int sock_fd, char *str);
void	ftp_get(int sock_fd, char *str);
void	ftp_put(int sock_fd, char *str);
void	ftp_pwd(int sock_fd);
void	ftp_quit(int sock_fd);
void	ftp_error(int sock_fd);
void	client_get(int sock_fd, char *cmd);
void	client_put(int sock_fd, char *cmd);
void	ft_die(char *str, int exit_code);
void	free_ptr(char **ptr);
void	local_cd(char *str);
void	local_pwd(void);
void	local_ls(char *str);
void	progress(float current, float max);

#endif

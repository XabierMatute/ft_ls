/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmatute- <xmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:11:44 by xmatute-          #+#    #+#             */
/*   Updated: 2025/02/12 13:28:09 by xmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char get_filetypechar(mode_t mode)
{
	switch (mode & S_IFMT) {
		case S_IFBLK:  return 'b';  // block device
		case S_IFCHR:  return 'c';  // character device
		case S_IFDIR:  return 'd';  // directory
		case S_IFIFO:  return 'p';  // FIFO/pipe
		case S_IFLNK:  return 'l';  // symlink
		case S_IFREG:  return '-';  // regular file
		case S_IFSOCK: return 's';  // socket
		default:       return '?';  // unknown
	}
}

void putpermisions(mode_t mode)
{
	ft_putchar(get_filetypechar(mode));
	ft_putchar((mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((mode & S_IROTH) ? 'r' : '-');
	ft_putchar((mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((mode & S_IXOTH) ? 'x' : '-');
}

int puthardlinks(nlink_t nlink)
{
	return ft_printf("%d", nlink);
}

int putuser(uid_t uid)
{
	struct passwd *pw = getpwuid(uid);
	if (pw != NULL)
		return ft_printf("%s", pw->pw_name);
	return ft_printf("%d", uid);
}

int putgroup(gid_t gid)
{
	struct group *gr = getgrgid(gid);
	if (gr != NULL)
		return ft_printf("%s", gr->gr_name);
	return ft_printf("%d", gid);
}

int putsize(off_t size)
{
	return ft_printf("%i", size);
}

int putdate(time_t mtime)
{
	char *date = ft_substr(ctime(&mtime), 4, 12);
	int i = ft_printf("%s", date);
	free(date);
	return i;
}

int put_disps(dev_t rdev)
{
	return (ft_printf("%i, %i", major(rdev), minor(rdev)));
}

void printfileinfo(struct stat file_stat)
{
	putpermisions(file_stat.st_mode);
	ft_putchar('\t');
	puthardlinks(file_stat.st_nlink);
	ft_putchar('\t');
	putuser(file_stat.st_uid);
	ft_putchar('\t');
	putgroup(file_stat.st_gid);
	ft_putchar('\t');
	if (((file_stat.st_mode & S_IFMT) == S_IFCHR) || ((file_stat.st_mode & S_IFMT) == S_IFBLK))
		put_disps(file_stat.st_rdev);
	else
		putsize(file_stat.st_size);
	ft_putchar('\t');
	putdate(file_stat.st_mtime);
	ft_putchar('\t');
}

void putfile_info(char const *path)
{
	struct stat file_stat;

	if (lstat(path, &file_stat))
	{
		ft_eprintf("ft_ls: cannot access '%s': %s\n", path, strerror(errno));
		return;
	}
	printfileinfo(file_stat);
}

void putfile_name(char const *file)
{
	ft_printf("%s", file);
}

void putsymlink(char const *path)
{
	char buf[1024];
    ssize_t len;

    len = readlink(path, buf, sizeof(buf)-1);
    
    if (len != -1) {
        buf[len] = '\0';
        ft_printf(" -> %s", buf);
    }
}

void put_file(const char *file, const t_flags flags)
{
    if (flags.l)
        putfile_info(file);
    putfile_name(file);
    if (flags.l)
        putsymlink(file);
    ft_putchar('\n');
}
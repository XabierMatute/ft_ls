/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmatute- <xmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:36:33 by xmatute-          #+#    #+#             */
/*   Updated: 2024/10/10 11:36:41 by xmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "stdio.h"
#include <string.h>
#include "main.h"
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void save_closedir(const char *path, DIR *dir)
{
	if (closedir(dir))
	{
		ft_eprintf("ft_ls: cannot close '%s': %s\n", path, strerror(errno));
		exit(errno);
	}
}

void	*save_calloc(size_t nmemb, size_t size)
{
	void *mem;

	if (!(mem = ft_calloc(nmemb, size)))
	{
		ft_eprintf("ft_ls: cannot allocate memory for %i * %i: %s\n", nmemb, size, strerror(errno));
		exit(errno);
	}
	return (mem);
}

void putpermisions(mode_t mode)
{
	ft_putchar((S_ISDIR(mode))  ? 'd' : '-');
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
	return ft_printf("%ld", nlink);
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

void printfileinfo(struct stat file_stat)
{
	putpermisions(file_stat.st_mode);
	ft_putchar(' ');
	puthardlinks(file_stat.st_nlink);
	ft_putchar(' ');
	putuser(file_stat.st_uid);
	ft_putchar(' ');
	putgroup(file_stat.st_gid);
	ft_putchar(' ');
	putsize(file_stat.st_size);
	ft_putchar(' ');
	putdate(file_stat.st_mtime);
	ft_putchar(' ');

}
char *make_absolute_path(const char *dir_path, const char *file_name)
{
	char *tmp = ft_strjoin(dir_path, "/");
	if (!tmp)
	{
		ft_eprintf("ft_ls: cannot allocate memory for %s/%s: %s\n", dir_path, file_name, strerror(errno));
		exit(errno);
	}	
	char *path = ft_strjoin(tmp, file_name);
	if (!path)
	{
		ft_eprintf("ft_ls: cannot allocate memory for %s/%s: %s\n", dir_path, file_name, strerror(errno));
		exit(errno);
	}
	free(tmp);
	return path;
}

void putfile_info(char *file, const char *dir_path)
{
	struct stat file_stat;
	char *path = make_absolute_path(dir_path, file);
	if (lstat(path, &file_stat))
	{
		ft_eprintf("ft_ls: cannot access '%s': %s\n", path, strerror(errno));
		return;
	}
	free(path);
	printfileinfo(file_stat);
}

void putfile_name(char *file)
{
	printf("%s\n", file);
}

void putfile(char *file, const char *path, const t_flags flags)
{
	if (!flags.a && file[0] == '.')
		return;
	if (flags.l)
		putfile_info(file, path);
	putfile_name(file);
}

size_t	count_files(const char *path, const t_flags flags)
{
	size_t	i = 0;
	DIR		*dir = opendir(path);
	struct dirent	*file;

	if (!dir)
	{
		ft_eprintf("ft_ls: cannot access '%s': %s\n", path, strerror(errno));
		return(0);
	}
	errno = 0;
	while ((file = readdir(dir)))
	{
		errno = 0;
		if (file->d_name[0] != '.' || flags.a)
			i++;
	}
	save_closedir(path, dir);
	if (errno)
	{
		ft_eprintf("ft_ls: cannot read '%s': %s\n", path, strerror(errno));
		exit(errno);
	}
	return (i);
}

char **get_files(const char *path, const t_flags flags)
{
	DIR				*dir = opendir(path);
	struct dirent 	*file = NULL;
	char			**files = save_calloc(count_files(path, flags) + 1, sizeof(char *));
	size_t			i = 0;

	if (errno)
		return (NULL);
	if (!dir)
	{
		ft_eprintf("ft_ls: cannot access '%s': %s\n", path, strerror(errno));
		return(NULL);
	}
	errno = 0;
	while ((file = readdir(dir)))
	{
		errno = 0;
		if (file->d_name[0] != '.' || flags.a)
		{
			files[i] = ft_strdup(file->d_name);
			i++;
		}
	}
	save_closedir(path, dir);
	if (errno)
	{
		ft_eprintf("ft_ls: cannot read '%s': %s\n", path, strerror(errno));
		free(files);
		exit(errno);
	}
	files[i] = NULL;
	return (files);
}

char **listfiles_r(char **files, const char *path, t_flags flags)
{
	size_t i = 0;

	while (files[i])
		i++;
	while (i)
		putfile(files[--i], path, flags);
	return (files);
}

size_t	get_blocks(char *file, const char *dir_path)
{
	struct stat file_stat;
	char *path = make_absolute_path(dir_path, file);
	if (lstat(path, &file_stat))
	{
		ft_eprintf("ft_ls: cannot access '%s': %s\n", path, strerror(errno));
		free(path);
		return 0;
	}
	free(path);
	return (file_stat.st_blocks / 2);
}

size_t	get_blocksnum(char **files, const char *path)
{
	size_t blocks = 0;

	while (*files)
	{
		blocks += get_blocks(*files, path);
		files++;
	}
	
	return (blocks);
}

char **listfiles(char **files, const char *path, t_flags flags)
{
	size_t i = 0;

	if (flags.l)
		ft_printf("total %i\n", get_blocksnum(files, path));
	if (flags.r)
		return (listfiles_r(files, path, flags));
	while (files[i])
	{
		putfile(files[i], path, flags);
		i++;
	}
	return (files);
}


void putdirectory(char *file, const char *path, const t_flags flags)
{
	if (!flags.a && file[0] == '.')
		return;
	char *dir_path = make_absolute_path(path, file);
	ft_putchar('\n');
	ft_ls(dir_path, flags);
	free(dir_path);
}

int isdir(const char *dir_path, const char *file)
{
	struct stat file_stat;
	char *path = make_absolute_path(dir_path, file);
	if (lstat(path, &file_stat))
	{
		ft_eprintf("ft_ls: cannot access '%s': %s\n", path, strerror(errno));
		return 0;
	}
	free(path);
	
	return S_ISDIR(file_stat.st_mode);
}

void listRfiles(char **files, const char *path, const t_flags flags)
{
	size_t i = 0;

	while (files[i])
	{
		if (isdir(path, files[i]) && ft_strncmp(files[i], ".", 2) && ft_strncmp(files[i], "..", 3))
			putdirectory(files[i], path, flags);
		i++;
	}
}

time_t	get_mtime(const char *file, const char *dir_path)
{
	struct stat file_stat;
	char *path = make_absolute_path(dir_path, file);
	if (lstat(path, &file_stat))
	{
		ft_eprintf("ft_ls: cannot access '%s': %s\n", path, strerror(errno));
		return 0;
	}
	free(path);
	
	return (file_stat.st_mtime);
}

char **sort_files_a(char **files)
{
	size_t	i = 0;

	while (files[i])
	{
		size_t	j = 0;
		while (files[j + 1 + i])
		{
			if (ft_strncmp(files[j], files[j + 1], strlen(files[j]) + 1) > 0)
				ft_swap_p((void *)&files[j], (void *)&files[j + 1]);
			j++;
		}
		i++;
	}
	return(files);
}

char **sort_files_t(char **files, const char *path)
{
	size_t	i = 0;

	while (files[i])
	{
		size_t	j = 0;
		while (files[j + 1 + i])
		{
			if (get_mtime(files[j], path) < get_mtime(files[j + 1], path))
				ft_swap_p((void *)&files[j], (void *)&files[j + 1]);
			j++;
		}
		i++;
	}
	return(files);
}

char **sort_files(char **files, const char *path, const t_flags flags)
{
	files = sort_files_a(files);
	if (flags.t)
		return (sort_files_t(files, path));
	return (files);
}

int ft_ls(const char *path, const t_flags flags)
{
	errno = 0;
	char **files = get_files(path, flags);

	if (!files || errno)
		return (errno);
	
	files = sort_files(files, path, flags);
	if (flags.R)
		ft_printf("%s:\n", path);
    listfiles(files, path, flags);

	if (flags.R)
		listRfiles(files, path, flags);

	free2((void **)files);
    return (0);
}



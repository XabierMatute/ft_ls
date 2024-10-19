/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xmatute- <xmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:36:33 by xmatute-          #+#    #+#             */
/*   Updated: 2024/10/18 20:08:41 by xmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
	putsize(file_stat.st_size);
	ft_putchar('\t');
	putdate(file_stat.st_mtime);
	ft_putchar('\t');
}

char *make_absolute_path(const char *dir_path, const char *file_name)
{
	if (!dir_path || !dir_path[0])
		return  (ft_strdup(file_name));
	
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
	ft_printf("%s", file);
}

void putsymlink(char const *file, char const *dir_path)
{
	char buf[1024];
    ssize_t len;
	char *path = make_absolute_path(dir_path, file);

    len = readlink(path, buf, sizeof(buf)-1);

	free(path);

    if (len != -1) {
        buf[len] = '\0';
        ft_printf(" -> %s", buf);
    }
}

void putfile(char *file, const char *path, const t_flags flags)
{
	if (!flags.a && file[0] == '.')
		return;
	if (flags.l)
		putfile_info(file, path);
	putfile_name(file);
	if (flags.l)
		putsymlink(file, path);
	ft_putchar('\n');
}

size_t	count_files(const char *path, const t_flags flags)
{
	size_t	i = 0;
	DIR		*dir = opendir(path);
	struct dirent	*file;

	if (!dir)
	{
		ft_eprintf("ft_ls: cannot access '%s': %s\n", path, strerror(errno));
		return (0);
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
		ft_eprintf("ft_ls: error reading '%s': %s\n", path, strerror(errno));
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
			files[i++] = ft_strdup(file->d_name);
	}
	save_closedir(path, dir);
	if (errno)
		ft_eprintf("ft_ls: error reading '%s': %s\n", path, strerror(errno));
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
		putfile(files[i++], path, flags);
	return (files);
}


void putdirectory(char *file, const char *path, const t_flags flags)
{
	if (!flags.a && file[0] == '.')
		return;
	char *dir_path = make_absolute_path(path, file);
	ft_putchar('\n');
	list_directory(dir_path, flags);
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

void listRfiles_r(char **files, const char *path, const t_flags flags)
{
	size_t i = 0;

	while (files[i])
		i++;
	while (i)
	{
		if (isdir(path, files[--i]) && ft_strncmp(files[i], ".", 2) && ft_strncmp(files[i], "..", 3))
			putdirectory(files[i], path, flags);
	}
}

void listRfiles(char **files, const char *path, const t_flags flags)
{
	size_t i = 0;

	if (flags.r)
	{
		listRfiles_r(files, path, flags);
		return;
	}
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

char **sort_files_t(char **files, char *path)
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

char **sort_files(char **files, char *path, const t_flags flags)
{
	files = sort_files_a(files);
	if (flags.t)
		return (sort_files_t(files, path));
	return (files);
}

int list_directory(char *path, const t_flags flags)
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

void list_file(char *file, const t_flags flags)
{
	putfile(file, "", flags);
}

int list_directories_r(char **dirs, const t_flags flags)
{
	size_t	i = 0;

	while (dirs[i])
		i++;
	while (i)
	{
		if (isdir("", dirs[--i]))
		{
			ft_printf("%s:\n", *dirs);
			list_directory(*dirs, flags);
			if (dirs[1])
				ft_putchar('\n');	
		}
		else
			list_file(dirs[i], flags);
	}
	return (0);
}

int list_only_directories(char **dirs, const t_flags flags)
{
	while (*dirs)
	{
		if (isdir("", *dirs))
		{
			ft_printf("%s:\n", *dirs);
			list_directory(*dirs, flags);
			if (dirs[1])
				ft_putchar('\n');	
		}
		dirs++;
	}
	return (0);
}

int list_files(char **dirs, const t_flags flags)
{
	while (*dirs)
	{
		if (!isdir("", *dirs))
			list_file(*dirs, flags);
		dirs++;
	}
	return (0);
}

int list_directories(char **dirs, const t_flags flags)
{
	dirs = sort_files(dirs, "", flags);
	if (flags.r)
		return (list_directories_r(dirs, flags));
	
	list_files(dirs, flags);
	ft_putchar('\n');
	list_only_directories(dirs, flags);
	return (0);
}

int ft_ls(char **paths, const t_flags flags)
{
	if (ft_parrlen((void **)paths) == 0)
		return(list_directory(".", flags));
	if (ft_parrlen((void **)paths) == 1)
		return(list_directory(paths[0], flags));
	return(list_directories(paths, flags));
}

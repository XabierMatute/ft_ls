//
// Created by xmatute- on 8/19/24.
//

#include "ft_ls.h"
#include "stdio.h"
#include <string.h>
#include "main.h"
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void printflags(t_flags flags) //for debugging purposes
{
	printf("flags: -");
	if (flags.l)
	{
		printf("l");
	}
	if (flags.R)
	{
		printf("R");
	}
	if (flags.a)
	{
		printf("a");
	}
	if (flags.r)
	{
		printf("r");
	}
	if (flags.t)
	{
		printf("t");
	}
	printf("\n");
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
	char *path = ft_strjoin(tmp, file_name);

	free(tmp);
	return path;
}

void putfile_info(struct dirent *file, const char *dir_path)
{
	struct stat file_stat;
	char *path = make_absolute_path(dir_path, file->d_name);
	if (lstat(path, &file_stat))
	{
		ft_eprintf("ft_ls: cannot access '%s': %s\n", path, strerror(errno));
		return;
	}
	free(path);
	printfileinfo(file_stat);
}

void putfile_name(struct dirent *file)
{
	printf("%s\n", file->d_name);
}

void putfile(struct dirent *file, const char *path, const t_flags flags)
{
	if (!flags.a && file->d_name[0] == '.')
		return;
	if (flags.l)
	{
		putfile_info(file, path);
	}
	putfile_name(file);
}

void listdir(DIR *dir, const char *path, const t_flags flags)
{
	struct dirent *file;

	errno = 0;
	while ((file = readdir(dir)))
	{
		putfile(file, path, flags);
		errno = 0;
	}
	if (errno)
	{
		ft_eprintf("ft_ls: cannot read '%s': %s\n", path, strerror(errno));
		exit(errno);
	}
}

void putdirectory(struct dirent *file, const char *path, const t_flags flags)
{
	if (!flags.a && file->d_name[0] == '.')
		return;
	char *dir_path = make_absolute_path(path, file->d_name);
	ft_printf("%s:\n", dir_path);
	ft_ls(dir_path, flags);
	free(dir_path);
}

int isdir(const char *dir_path, const struct dirent *file)
{
	struct stat file_stat;
	char *path = make_absolute_path(dir_path, file->d_name);
	if (lstat(path, &file_stat))
	{
		ft_eprintf("ft_ls: cannot access '%s': %s\n", path, strerror(errno));
		return 0;
	}
	free(path);
	
	return S_ISDIR(file_stat.st_mode);
}

void listRdir(DIR *dir, const char *path, const t_flags flags)
{
	struct dirent *file;

	errno = 0;
	while ((file = readdir(dir)))
	{
		if (ft_strncmp(file->d_name, ".", 2) == 0 || ft_strncmp(file->d_name, "..", 3) == 0)
			continue;
		if (isdir(path, file))
		{
			putdirectory(file, path, flags);
		}
		errno = 0;
	}
	if (errno)
	{
		ft_eprintf("ft_ls: cannot read '%s': %s\n", path, strerror(errno));
		exit(errno);
	}
}

int recursive_ls(const char *path, const t_flags flags)
{
	DIR *dir = opendir(path);
	if (!dir)
	{
		ft_eprintf("ft_ls: cannot access '%s': %s\n", path, strerror(errno));
		return (errno);
	}

    listRdir(dir, path, flags);

	if (closedir(dir))
	{
		ft_eprintf("ft_ls: cannot close '%s': %s\n", path, strerror(errno));
		return (errno);
	}
    return (0);
}

int ft_ls(const char *path, const t_flags flags)
{
	printf("ft_ls: %s\n", path); //for debugging purposes
	printflags(flags); //for debugging purposes

	DIR *dir = opendir(path);
	if (!dir)
	{
		ft_eprintf("ft_ls: cannot access '%s': %s\n", path, strerror(errno));
		return (errno);
	}

    listdir(dir, path, flags);

	if (closedir(dir))
	{
		ft_eprintf("ft_ls: cannot close '%s': %s\n", path, strerror(errno));
		return (errno);
	}

	if (flags.R)
		return (recursive_ls(path, flags));
    return (0);
}



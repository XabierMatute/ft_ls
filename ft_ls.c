//
// Created by xmatute- on 8/19/24.
//

#include "ft_ls.h"
#include "stdio.h"
#include <string.h>
#include "main.h"

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

	#include <sys/stat.h>
	#include <pwd.h>
	#include <grp.h>
	#include <time.h>

void putpermisions(mode_t mode)
{
	ft_putchar((S_ISDIR(mode)) ? 'd' : '-');
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


// int putfile_l(struct dirent *file) //beta
// {


	int putfile_l(struct dirent *file)
	{
		struct stat file_stat;
		if (lstat(file->d_name, &file_stat) == -1)
		{
			perror("ft_ls");
			return -1;
		}

		putpermisions(file_stat.st_mode);
		ft_putchar(' ');

		// Number of hard links
		printf("%ld", file_stat.st_nlink);

		// Owner name
		struct passwd *pw = getpwuid(file_stat.st_uid);
		if (pw != NULL)
		{
			printf(" %s", pw->pw_name);
		}
		else
		{
			printf(" %d", file_stat.st_uid);
		}

		// Group name
		struct group *gr = getgrgid(file_stat.st_gid);
		if (gr != NULL)
		{
			printf(" %s", gr->gr_name);
		}
		else
		{
			printf(" %d", file_stat.st_gid);
		}

		// File size
		printf(" %ld", file_stat.st_size);

		// Last modified time
		char time_buffer[80];
		struct tm *time_info = localtime(&file_stat.st_mtime);
		strftime(time_buffer, sizeof(time_buffer), "%b %d %H:%M", time_info);
		printf(" %s", time_buffer);

		// File name
		printf(" %s\n", file->d_name);

		return 0;
	}

// }

int putfile(struct dirent *file, t_flags flags) //beta
{
	if (file->d_name[0] == '.' && !flags.a)
	{
		return '.';
	}
	if (flags.l)
	{
		return putfile_l(file);
	}
	else
	{
		return printf("%s\n", file->d_name);
	}
}

void listcontent(DIR *dir, const t_flags flags)
{
    struct dirent *file;
    while ((file = readdir(dir)))
    {
        putfile(file, flags);
    }
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

    listcontent(dir, flags);

    return (closedir(dir));
}



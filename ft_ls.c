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

void putfile(struct dirent *file, t_flags flags) //beta
{
	if (file->d_name[0] == '.' && !flags.a)
	{
		return;
	}
	if (flags.l)
	{
		//print long format
	}
	else
	{
		printf("%s\n", file->d_name);
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



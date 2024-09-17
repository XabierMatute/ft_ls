//
// Created by xmatute- on 7/3/24.
//

#include "get_path.h"

static size_t count_paths(int argc, char const *argv[])
{
    size_t count;

    count = 0;
    while (argc--)
        if (argv[argc][0] != '-')
            count++;
    return (count);
}

char **get_paths(int argc, char const *argv[])
{
    char **paths;
    size_t i;

    i = count_paths(argc, argv);
    paths = ft_calloc(i + 1, sizeof(char *));
    while (argc--)
        if (argv[argc][0] != '-')
            paths[--i] = ft_strdup(argv[argc]);
    return (paths);
}
#include "main.h"

t_flags get_flags(int argc, char const *argv[])
{
	t_flags flags;
	int				i = 1;

	ft_bzero(&flags, sizeof(t_flags));

	while (i < argc)
	{
		if (argv[i][0] == '-')
		{
			int j = 0;

			while (argv[i][j])
			{
				switch (argv[i][j])
				{
				case 'l' :
					flags.l = 1;
					break;
				case 'R' :
					flags.R = 1;
					break;
				case 'a' :
					flags.a = 1;
					break;
				case 'r' :
					flags.a = 1;
					break;
				case 't' :
					flags.t = 1;
					break;
				default:
					//ureconiced flag
					break;
				}
				j++;
			}
		}
		i++;
	}
	return (flags);
}

static int parse_imput(int argc, char const *argv[])
{
	const t_flags	flags = get_flags(argc, argv);
	int				i = 1;
	int				ee = -42;

	while (i < argc)
	{
		if (argv[i][0] != '-')
		{
			ee = ft_ls(argv[i], flags);
			if (ee != 0)
				return (ee);
		}
		i++;
	}
	if (ee == -42)
		return (ft_ls(".", flags));
	return (0);
}

/*static int default_ls()
{
	t_flags flags;

	ft_bzero(&flags, sizeof(t_flags));
	return (ft_ls(".", flags));
}*/

int main(int argc, char const *argv[])
{
	//ft_printf("Entrando a ls\n");
	/*if (argc  < 2)
		return (default_ls());*/
	return (parse_imput(argc, argv));


#include "main.h"

static int parse_imput(int argc, char const *argv[])
{
    return (ft_ls(get_paths(argc, argv), get_flags(argc, argv)));
}

static int default_ls()
{
    t_flags flags;

    ft_bzero(&flags, sizeof(t_flags));
    return (ft_ls(ft_strdup("."), flags));
}

int main(int argc, char const *argv[])
{
    ft_printf("Entrando a ls\n");
    if (argc  < 2)
        return (default_ls());
    return (parse_imput(argc, argv));
}

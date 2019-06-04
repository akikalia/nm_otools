#include "nm.h"

void print_all(t_list *symbols)
{
	t_symbol * temp;
	while(symbols)
	{
		temp = symbols->content;
		if (temp->value)
			ft_printf("%016llx %s\n", temp->value, temp->name);
		else
			ft_printf("%16s %s\n","" , temp->name);
		symbols = symbols->next;
	}
}

int symbol_cmp(t_symbol *s1, t_symbol *s2)
{
	return (ft_strcmp(s1->name, s2->name));
}

static void	place(t_node *n, t_list **alst, int *flag)
{
	n->temp->next = n->curr;
	if (n->prev != NULL)
		n->prev->next = n->temp;
	else
		*alst = n->temp;
	*flag = 0;
}

void		ft_lstadd_sorted(t_list **alst,
int (*cmp)(t_symbol*a, t_symbol*b), t_symbol *s, int flag)
{
	t_node		n;

	n.prev = NULL;
	n.temp = ft_lstnew((void*)s, sizeof(*s));
	n.curr = *alst;
	if (n.curr == NULL)
	{
		*alst = n.temp;
		flag = 0;
	}
	while (n.curr && flag)
	{
		if (cmp(n.curr->content, (void*)s) > 0)
			place(&n, alst, &flag);
		n.prev = n.curr;
		n.curr = n.curr->next;
	}
	if (n.curr == NULL && flag)
		n.prev->next = n.temp;
}

int ft_nm(void *file)
{
	mach64(file);
	mach32(file);
	fat64(file);
	fat32(file);
	return 0;
}

int error(char *file, char *str)
{
	ft_printf("%s : %s\n", file, str);
	return (-1);
}

int run_file(char *file)
{
	int fd;
	struct stat stt;
	void *file_copy;

	fd = open(file, O_RDONLY);
	if ((fstat(fd, &stt) < 0) || (fd < 0 && errno == EACCES))
		return error(file, "Permission denied");
	else if(fd < 0)
		return error(file, "No such file or directory");
	if(S_ISDIR(stt.st_mode))
		return error(file, "Is a directory");
	if ((file_copy = mmap(NULL,stt.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) < 0)
		return error(file, "Mmap failed");
	if (ft_nm(file_copy) < 0)
		return error(file, "Failed to get symbols");
	munmap(file_copy, stt.st_size);
	close(fd);
	return 0;
}

int main(int argc, char **argv)
{
	int i;

	i = 1;
	if (argc == 1)
		return run_file("a.out");
	while (i < argc)
	{
		run_file(argv[i]);
		i++;
	}
	return 0;
}

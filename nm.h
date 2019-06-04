#include <mach-o/nlist.h>
#include <mach-o/loader.h>
#include <unistd.h>
#include <sys/mman.h>
#include "libft/libft.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct	s_node
{
	t_list		*prev;
	t_list		*curr;
	t_list		*temp;
}				t_node;

typedef struct s_symbol
{
	unsigned long	value;
	char			*name;
	uint8_t			type;

}				t_symbol;


int mach64(void *file);
int mach32(void *file);
int fat32(void *file);
int fat64(void *file);
uint32_t swap_uint32( uint32_t val );
void		ft_lstadd_sorted(t_list **alst,
int (*cmp)(t_symbol*a, t_symbol*b), t_symbol *s, int flag);
int symbol_cmp(t_symbol *s1, t_symbol *s2);
void print_all(t_list *symbols);

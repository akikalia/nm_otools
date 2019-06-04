#include "nm.h"

void print_table(struct symtab_command * sym, char * ptr)
{
    struct nlist_64 *tbl;
	t_list *symbols;
	t_symbol* entry;
	char *str;
    uint32_t i;

	symbols = NULL;
	str = ptr + sym->stroff;
    tbl = (struct nlist_64 *)(ptr + sym->symoff);
	i = 0;
    while (i < sym->nsyms)
    {
		entry = malloc(sizeof(t_symbol));
		entry->name = str + tbl->n_un.n_strx;
	   	entry->value =  tbl->n_value;
		entry->type = tbl->n_type;
		ft_lstadd_sorted(&symbols, &symbol_cmp, entry, 1);
		tbl++;
		i++;
    }
	print_all(symbols);
}

int mach64(void *file)
{
	struct mach_header_64 *header;
	struct load_command *load_cmd;
	uint32_t i;

	header = file;
	load_cmd = (struct load_command *)(header + 1);
	i = 0;
	while(i < header->ncmds)
	{
		if (load_cmd->cmd == LC_SYMTAB)
			print_table((struct symtab_command *)load_cmd, file);
		load_cmd = (void *)load_cmd + load_cmd->cmdsize;
		i++;
	}
	return 0;
}

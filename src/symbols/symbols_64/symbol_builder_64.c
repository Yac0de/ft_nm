#include "../../../inc/ft_nm.h"

// Constructs a t_symbol_64 from a symbol info context.
// Fills in name and type (uppercase or lowercase depending on binding).
// Returns '?' type if info is invalid or incomplete.
t_symbol_64 build_symbol_64(t_symbol_info_64 *info)
{
	t_symbol_64 symbol;

	symbol.name = NULL;
	symbol.type = '?';

	if (!info || !info->sym || !info->strtab || !info->sections)
	{
		ft_putstr_fd("Error: NULL pointer in build_symbol_64\n", 2);
		return symbol;
	}

	symbol.sym = *(info->sym);
	symbol.name = info->strtab + info->sym->st_name;
	symbol.type = get_symbol_letter_64(info);

	if (ELF64_ST_BIND(info->sym->st_info) == STB_LOCAL)
		symbol.type = ft_tolower(symbol.type);

	return symbol;
}

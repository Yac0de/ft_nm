#include "../../../inc/ft_nm.h"

// Constructs a t_symbol_32 from a symbol info context.
// Fills in symbol name and type (uppercase or lowercase depending on binding).
// Returns a symbol with type '?' if the input context is invalid.
t_symbol_32 build_symbol_32(t_symbol_info_32 *info)
{
	t_symbol_32 symbol;

	symbol.name = NULL;
	symbol.type = '?';

	// Safety check: ensure all required fields are present
	if (!info || !info->sym || !info->strtab || !info->sections)
		return(ft_putstr_fd("Error: NULL pointer in build_symbol_32\n", 2), symbol);

	// Copy raw symbol structure
	symbol.sym = *(info->sym);

	// Resolve symbol name from the string table
	symbol.name = info->strtab + info->sym->st_name;

	// Determine nm-style symbol letter (e.g. T, U, B, etc.)
	symbol.type = get_symbol_letter_32(info);

	// Use lowercase for local (non-global) symbols, like `nm` does
	if (ELF32_ST_BIND(info->sym->st_info) == STB_LOCAL)
		symbol.type = ft_tolower(symbol.type);

	return symbol;
}

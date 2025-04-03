#include "../../../inc/ft_nm.h"

// Constructs a t_symbol_32 from a raw ELF32 symbol.
// Fills in name and type (upper/lower depending on binding).
// If pointers are NULL, returns a fallback symbol with type '?'.
t_symbol_32 build_symbol_32(Elf32_Sym sym, char *strtab, Elf32_Shdr *sections)
{
	t_symbol_32 symbol;

	symbol.sym = sym;
	symbol.name = NULL;
	symbol.type = '?';

	// Defensive check in case of missing string table or section table
	if (!strtab || !sections)
		return (ft_putstr_fd("Error: NULL pointer in build_symbol_32\n", 2), symbol);

	symbol.name = strtab + sym.st_name;
	symbol.type = get_symbol_letter_32(&sym, sections);

	// Use lowercase for local (non-global) symbols, like nm does
	if (ELF32_ST_BIND(sym.st_info) == STB_LOCAL)
		symbol.type = ft_tolower(symbol.type);

	return symbol;
}

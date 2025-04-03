#include "../../../inc/ft_nm.h"

// Returns 1 if the symbol should be skipped (not relevant for nm output).
// Filters out section symbols, file symbols, and some no-type symbols.
int skip_symbol_64(Elf64_Sym *sym)
{
	uint8_t type = ELF64_ST_TYPE(sym->st_info);

	// Ignore section symbols (like .text, .data) and file symbols
	if (type == STT_SECTION || type == STT_FILE)
		return 1;

	// Skip undefined symbols with no type but defined section (often internal)
	if (type == STT_NOTYPE && sym->st_shndx != SHN_UNDEF)
		return 1;

	// Valid symbol to keep
	return 0;
}

#include "../../../inc/ft_nm.h"

// Returns 1 if the symbol should be skipped (not relevant for nm output).
// Filters out section symbols, file symbols, and symbols with no name.
// Keeps symbols with type STT_NOTYPE if they have a valid name.
int skip_symbol_64(t_symbol_info_64 *info)
{
	if (!info || !info->sym || !info->strtab)
		return 1; // Invalid context or corrupted symbol

	uint8_t type = ELF64_ST_TYPE(info->sym->st_info);

	// Ignore symbols representing a section or file (not real symbols)
	if (type == STT_SECTION || type == STT_FILE)
		return 1;

	// Ignore symbols without a name (anonymous or invalid entries)
	if (info->sym->st_name == 0 || info->strtab[info->sym->st_name] == '\0')
		return 1;

	// Otherwise, symbol is valid and should be kept
	return 0;
}

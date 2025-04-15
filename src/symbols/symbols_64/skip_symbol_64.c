#include "../../../inc/ft_nm.h"

// Returns 1 if the symbol should be skipped (not relevant for nm output).
// Filters out section symbols, file symbols, and symbols with no name.
// Keeps symbols with type STT_NOTYPE if they have a valid name.
int skip_symbol_64(Elf64_Sym *sym, const char *strtab)
{
	if (!sym || !strtab)
		return 1;

	uint8_t type = ELF64_ST_TYPE(sym->st_info);

	// Skip symbols of type SECTION or FILE (internal use only)
	if (type == STT_SECTION || type == STT_FILE)
		return 1;

	// Skip symbols with no name
	if (sym->st_name == 0 || strtab[sym->st_name] == '\0')
		return 1;

	// Keep everything else, even STT_NOTYPE with a name (like __GNU_EH_FRAME_HDR)
	return 0;
}

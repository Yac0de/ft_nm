#include "../../../inc/ft_nm.h"

// Returns 1 if the symbol should be skipped (not relevant for nm output).
// Filters out section symbols, file symbols, and symbols with no name.
// Keeps symbols with type STT_NOTYPE if they have a valid name.
int skip_symbol_32(t_symbol_info_32 *info)
{
	if (!info || !info->sym || !info->strtab)
		return 1;

	uint8_t type = ELF32_ST_TYPE(info->sym->st_info);

	// Skip symbols of type SECTION or FILE (internal use only)
	if (type == STT_SECTION || type == STT_FILE)
		return 1;

	// Skip symbols with no name
	if (info->sym->st_name == 0 || info->strtab[info->sym->st_name] == '\0')
		return 1;

	// Keep everything else, even STT_NOTYPE with a name (like __GNU_EH_FRAME_HDR)
	return 0;
}

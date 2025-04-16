#include "../../../inc/ft_nm.h"

// Maps an ELF32 symbol to its nm-style letter representation.
// Determines the symbol letter based on:
// - binding (local/global/weak),
// - section index (SHN_UNDEF, SHN_ABS, SHN_COMMON),
// - section type (e.g., SHT_PROGBITS, SHT_NOBITS),
// - section flags (SHF_ALLOC, SHF_WRITE, SHF_EXECINSTR).
// Returns '?' for unknown or invalid symbols.
char get_symbol_letter_32(t_symbol_info_32 *info)
{
	if (!info->sym || !info->sections)
		return '?';

	uint8_t bind = ELF32_ST_BIND(info->sym->st_info);
	Elf32_Half shndx = info->sym->st_shndx;

	// Handle weak symbols (global/local)
	if (bind == STB_WEAK)
		return (shndx == SHN_UNDEF ? 'w' : 'W');

	// Special section indexes
	if (shndx == SHN_UNDEF)
		return 'U'; // Undefined symbol
	if (shndx == SHN_ABS)
		return 'A'; // Absolute symbol
	if (shndx == SHN_COMMON)
		return 'C'; // Common block
	if (shndx >= SHN_LORESERVE)
		return '?'; // Reserved/invalid section

	// Inspect the section's type and flags
	Elf32_Shdr section = info->sections[shndx];
	uint32_t flags = section.sh_flags;
	uint32_t shtype = section.sh_type;

	char letter = '?';

// Match against common section types and permissions
	if (shtype == SHT_NOBITS && (flags & SHF_ALLOC) && (flags & SHF_WRITE))
		letter = 'B'; // .bss → uninitialized data
	else if ((flags & SHF_ALLOC) && (flags & SHF_EXECINSTR))
		letter = 'T'; // .text → executable code
	else if ((flags & SHF_ALLOC) && (flags & SHF_WRITE))
		letter = 'D'; // .data → initialized writable data
	else if ((flags & SHF_ALLOC) && !(flags & SHF_WRITE))
		letter = 'R'; // .rodata → read-only data
	else if (shtype == SHT_DYNAMIC)
		letter = 'D'; // dynamic symbol table entries

	// Convert to lowercase for local symbols (STB_LOCAL)
	if (bind == STB_LOCAL && letter != '?')
		letter += 32;

	return letter;
}

#include "../../../inc/ft_nm.h"

// Maps an ELF32 symbol to its nm-style letter representation.
// Determines the letter based on section type, flags, binding (local/global),
// and handles special sections like .bss, .data, .rodata, .text, etc.
char get_symbol_letter_32(t_symbol_info_32 *info)
{
	if (!info->sym || !info->sections)
		return '?';

	uint8_t bind = ELF32_ST_BIND(info->sym->st_info);
	// uint8_t type = ELF32_ST_TYPE(sym->st_info);
	Elf32_Half shndx = info->sym->st_shndx;

	if (bind == STB_WEAK)
		return (shndx == SHN_UNDEF ? 'w' : 'W');

	if (shndx == SHN_UNDEF)
		return 'U';
	if (shndx == SHN_ABS)
		return 'A';
	if (shndx == SHN_COMMON)
		return 'C';
	if (shndx >= SHN_LORESERVE)
		return '?';

	Elf32_Shdr section = info->sections[shndx];
	uint32_t flags = section.sh_flags;
	uint32_t shtype = section.sh_type;

	char letter = '?';

	if (shtype == SHT_NOBITS && (flags & SHF_ALLOC) && (flags & SHF_WRITE))
		letter = 'B'; // .bss
	else if ((flags & SHF_ALLOC) && (flags & SHF_EXECINSTR))
		letter = 'T'; // .text
	else if ((flags & SHF_ALLOC) && (flags & SHF_WRITE))
		letter = 'D'; // .data
	else if ((flags & SHF_ALLOC) && !(flags & SHF_WRITE))
		letter = 'R'; // .rodata
	else if (shtype == SHT_DYNAMIC)
		letter = 'D';

	// Local symbols use lowercase
	if (bind == STB_LOCAL && letter != '?')
		letter += 32;

	return letter;
}

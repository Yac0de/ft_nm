#include "../../../inc/ft_nm.h"

// Returns true if the section matches a BSS segment (uninitialized data)
static int is_bss(Elf32_Shdr *s)
{
	return (s->sh_type == SHT_NOBITS &&
			(s->sh_flags & SHF_ALLOC) &&
			(s->sh_flags & SHF_WRITE));
}

// Returns true if the section is executable code (text section)
static int is_text(Elf32_Shdr *s)
{
	return (s->sh_type == SHT_PROGBITS &&
			(s->sh_flags & SHF_ALLOC) &&
			(s->sh_flags & SHF_EXECINSTR));
}

// Returns true if the section is writable data
static int is_data(Elf32_Shdr *s)
{
	return (s->sh_type == SHT_PROGBITS &&
			(s->sh_flags & SHF_ALLOC) &&
			(s->sh_flags & SHF_WRITE));
}

// Maps an ELF32 symbol to its nm-style letter representation.
// Handles weak, undefined, BSS, text, data, and unknown types.
char get_symbol_letter_32(Elf32_Sym *sym, Elf32_Shdr *sections)
{
	if (!sym || !sections)
		return '?';

	// Weak symbols: 'w' if undefined, 'W' if defined
	if (ELF32_ST_BIND(sym->st_info) == STB_WEAK)
		return (sym->st_shndx == SHN_UNDEF ? 'w' : 'W');

	// Undefined symbol: 'U'
	if (sym->st_shndx == SHN_UNDEF)
		return 'U';

	// Reserved/unsupported section index: mark as unknown
	if (sym->st_shndx >= SHN_LORESERVE)
		return '?';

	Elf32_Shdr section = sections[sym->st_shndx];

	if (is_bss(&section)) return 'B';
	if (is_text(&section)) return 'T';
	if (is_data(&section)) return 'D';

	// If no match, return '?'
	return '?';
}

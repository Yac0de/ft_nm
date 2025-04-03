#include "../inc/ft_nm.h"

// Prepares all required contexts from ELF headers and section headers,
// then launches the symbol-reading logic for 64-bit ELF files.
static void print_symbol_section_locations_64(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr, char *shstrtab)
{
	// Build section context to locate symtab/strtab by name
	t_section_ctx_64 ctx_sections = {
		.ehdr = ehdr,
		.shdr = shdr,
		.shstrtab = shstrtab
	};

	Elf64_Shdr *symtab, *strtab;

	// Look for .symtab + .strtab or .dynsym + .dynstr
	if (!find_sym_and_str_tab_64(&ctx_sections, &symtab, &strtab))
		return (ft_putstr_fd("Error: symtab or strtab not found (64)\n", 2));

	// Create symbol context and delegate to main read logic
	t_symbol_ctx_64 ctx = {
		.map = (void *)ehdr,
		.symtab = symtab,
		.strtab = strtab
	};

	read_symbols_64(&ctx);
}

// Entry point for reading sections in a 64-bit ELF file.
// Extracts section headers and names, then launches symbol parsing.
void	read_sections_64(void *map)
{
	Elf64_Ehdr	*ehdr = (Elf64_Ehdr *)map;
	Elf64_Shdr	*shdr = (Elf64_Shdr *)(map + ehdr->e_shoff);
	Elf64_Shdr	*shstr = &shdr[ehdr->e_shstrndx];
	char		*shstrtab = (char *)(map + shstr->sh_offset);

	print_symbol_section_locations_64(ehdr, shdr, shstrtab);
}

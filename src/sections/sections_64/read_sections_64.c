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

	// Create the context used by the symbol parser
	t_symbol_ctx_64 ctx = {
		.map = (void *)ehdr,
		.symtab = symtab,
		.strtab = strtab
	};

	// Trigger the main symbol reading routine
	read_symbols_64(&ctx);
}

// Entry point for reading sections in a 64-bit ELF file.
// Extracts the section headers and section header string table,
// then passes everything to the dispatcher to locate and read symbols.
void	read_sections_64(void *map)
{
	// Access ELF header and locate section header table
	Elf64_Ehdr	*ehdr = (Elf64_Ehdr *)map;
	Elf64_Shdr	*shdr = (Elf64_Shdr *)(map + ehdr->e_shoff);

	// Find and load the section header string table
	Elf64_Shdr	*shstr = &shdr[ehdr->e_shstrndx];
	char		*shstrtab = (char *)(map + shstr->sh_offset);

	// Pass control to the symbol section parser
	print_symbol_section_locations_64(ehdr, shdr, shstrtab);
}

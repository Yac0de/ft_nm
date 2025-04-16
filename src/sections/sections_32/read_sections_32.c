#include "../../../inc/ft_nm.h"

// Prepares all required contexts from ELF headers and section headers,
// then launches the symbol-reading logic for 32-bit ELF files.
static void print_symbol_section_locations_32(Elf32_Ehdr *ehdr, Elf32_Shdr *shdr, char *shstrtab)
{
	// Build section context to locate symtab/strtab by name
	t_section_ctx_32 ctx_sections = {
		.ehdr = ehdr,
		.shdr = shdr,
		.shstrtab = shstrtab
	};

	Elf32_Shdr *symtab, *strtab;

	// Look for .symtab + .strtab or .dynsym + .dynstr
	if (!find_sym_and_str_tab_32(&ctx_sections, &symtab, &strtab))
		return (ft_putstr_fd("Error: symtab or strtab not found (32)\n", 2));

	// Create the context used by the symbol parser
	t_symbol_ctx_32 ctx = {
		.map = (void *)ehdr,
		.symtab = symtab,
		.strtab = strtab
	};

	// Trigger the main symbol reading routine
	read_symbols_32(&ctx);
}

// Entry point for reading sections in a 32-bit ELF file.
// Extracts the section headers and section header string table,
// then passes everything to the dispatcher to locate and read symbols.
void read_sections_32(void *map)
{
	// Access ELF header and locate section header table
	Elf32_Ehdr *ehdr = (Elf32_Ehdr *)map;
	Elf32_Shdr *shdr = (Elf32_Shdr *)(map + ehdr->e_shoff);

	// Find and load the section header string table
	Elf32_Shdr *shstr = &shdr[ehdr->e_shstrndx];
	char *shstrtab = (char *)(map + shstr->sh_offset);

	// Pass control to the symbol section parser
	print_symbol_section_locations_32(ehdr, shdr, shstrtab);
}

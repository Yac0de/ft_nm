#include "../inc/ft_nm.h"

// Prints an error matching the `nm` output when an invalid ELF file is detected.
static int	print_format_error(const char *filename)
{
	ft_putstr_fd("nm: ", 2);
	ft_putstr_fd((char *)filename, 2);
	ft_putstr_fd(": file format not recognized\n", 2);
	return INVALID_ELF;
}

// Checks if the section header table fits within the mapped file.
static int	is_section_header_table_within_bounds(t_file *file, Elf64_Ehdr *ehdr)
{
	size_t shdr_size = ehdr->e_shnum * sizeof(Elf64_Shdr);

	return (ehdr->e_shoff <= file->size && ehdr->e_shoff + shdr_size <= file->size);
}

// Verifies that the section header string table fits within the file.
static int	validate_shstrtab(t_file *file, Elf64_Shdr *shstr)
{
	return (shstr->sh_offset + shstr->sh_size <= file->size);
}

// Retrieves the section header string table (shstrtab).
// If the index is invalid, prints a warning and returns NULL (as nm would).
static char *get_shstrtab(t_file *file, Elf64_Shdr *shdr, Elf64_Ehdr *ehdr)
{
	if (ehdr->e_shstrndx >= ehdr->e_shnum)
	{
		ft_putstr_fd("nm: warning: ", 2);
		ft_putstr_fd((char *)file->name, 2);
		return(ft_putstr_fd(" has a corrupt string table index - ignoring\n", 2), NULL);
	}

	Elf64_Shdr *shstr = &shdr[ehdr->e_shstrndx];
	if (!validate_shstrtab(file, shstr))
		return NULL;

	return (char *)(file->map + shstr->sh_offset);
}

// Builds the context required to locate ELF64 symbols in the file.
// Returns:
// - SYMBOLS_OK     → valid ELF and symbols successfully found
// - NO_SYMBOLS     → valid ELF but no symbols found
// - INVALID_ELF    → invalid ELF (error message already printed)
static int	get_symbol_ctx_64(t_file *file, t_symbol_ctx_64 *ctx)
{
	if (file->size < sizeof(Elf64_Ehdr))
		return print_format_error(file->name);

	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)file->map;

	if (!is_section_header_table_within_bounds(file, ehdr))
		return print_format_error(file->name);

	Elf64_Shdr *shdr = (Elf64_Shdr *)(file->map + ehdr->e_shoff);
	char *shstrtab = get_shstrtab(file, shdr, ehdr);

	t_section_ctx_64 sctx = {
		.ehdr = ehdr,
		.shdr = shdr,
		.shstrtab = shstrtab
	};

	Elf64_Shdr *symtab;
	Elf64_Shdr *strtab;

	if (!find_sym_and_str_tab_64(&sctx, &symtab, &strtab))
		return NO_SYMBOLS;

	if ((symtab->sh_offset + symtab->sh_size > file->size)
		|| (strtab->sh_offset + strtab->sh_size > file->size))
	{
		ft_putstr_fd("nm: warning: ", 2);
		ft_putstr_fd((char *)file->name, 2);
		ft_putstr_fd(" has a section extending past end of file\n", 2);
		return NO_SYMBOLS;
	}
	ctx->map = file->map;
	ctx->file_size = file->size;
	ctx->symtab = symtab;
	ctx->strtab = strtab;
	return SYMBOLS_OK;
}

// Top-level dispatcher for parsing and displaying ELF64 symbols.
// Ensures consistent error handling and outputs messages that exactly match `nm`.
// Returns 0 on success, 1 on any error or if no symbols are found.
int	parse_and_display_elf64_symbols(t_file *file)
{
	t_symbol_ctx_64 ctx;
	int result;

	result = get_symbol_ctx_64(file, &ctx);
	if (result == INVALID_ELF)
		return 1;

	if (result == SYMBOLS_OK)
		return read_symbols_64(&ctx);

	if (result == NO_SYMBOLS)
	{
		ft_putstr_fd("nm: ", 2);
		ft_putstr_fd((char *)file->name, 2);
		ft_putstr_fd(": no symbols\n", 2);
		return 1;
	}

	return 0;
}

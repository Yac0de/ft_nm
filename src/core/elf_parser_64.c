#include "../inc/ft_nm.h"

// Prints an error matching the `nm` output when an invalid ELF file is detected.
static int	print_format_error(const char *filename)
{
	ft_putstr_fd("nm: ", 2);
	ft_putstr_fd((char *)filename, 2);
	ft_putstr_fd(": file format not recognized\n", 2);
	return INVALID_ELF;
}

// Returns 1 if the section header table is fully contained within the file.
static int	is_section_header_table_within_bounds(t_file *file, Elf64_Ehdr *ehdr)
{
	size_t shdr_size = ehdr->e_shnum * sizeof(Elf64_Shdr);

	return (ehdr->e_shoff <= file->size && ehdr->e_shoff + shdr_size <= file->size);
}

// Returns 1 if the section header string table fits within the mapped file.
static int	validate_shstrtab(t_file *file, Elf64_Shdr *shstr)
{
	return (shstr->sh_offset + shstr->sh_size <= file->size);
}

// Retrieves the section header string table (.shstrtab).
// If the index is invalid, prints a warning and returns NULL (matching nm's behavior).
static char *get_shstrtab(t_file *file, Elf64_Shdr *shdr, Elf64_Ehdr *ehdr)
{
	// ELF header contains an index into the section header array
	if (ehdr->e_shstrndx >= ehdr->e_shnum)
	{
		ft_putstr_fd("nm: warning: ", 2);
		ft_putstr_fd((char *)file->name, 2);
		return(ft_putstr_fd(" has a corrupt string table index - ignoring\n", 2), NULL);
	}

	// Look up the section containing the strings
	Elf64_Shdr *shstr = &shdr[ehdr->e_shstrndx];
	if (!validate_shstrtab(file, shstr))
		return NULL;

	// Return a pointer to the start of the string table
	return (char *)(file->map + shstr->sh_offset);
}

// Builds the ELF32 symbol context (symtab, strtab, etc).
// Returns:
// - SYMBOLS_OK     → valid ELF and symbols successfully found
// - NO_SYMBOLS     → valid ELF but no usable symbols
// - INVALID_ELF    → invalid ELF format (error already printed)
static int	get_symbol_ctx_64(t_file *file, t_symbol_ctx_64 *ctx)
{
	// Sanity check: file must be large enough for an ELF header
	if (file->size < sizeof(Elf64_Ehdr))
		return print_format_error(file->name);

	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)file->map;

	// Validate that the section header table fits within file bounds
	if (!is_section_header_table_within_bounds(file, ehdr))
		return print_format_error(file->name);

	// Get section header array and section name table
	Elf64_Shdr *shdr = (Elf64_Shdr *)(file->map + ehdr->e_shoff);
	char *shstrtab = get_shstrtab(file, shdr, ehdr);

	// Prepare context for searching symbol and string tables
	t_section_ctx_64 sctx = {
		.ehdr = ehdr,
		.shdr = shdr,
		.shstrtab = shstrtab
	};

	Elf64_Shdr *symtab;
	Elf64_Shdr *strtab;

	// Find .symtab and .strtab sections; return if missing
	if (!find_sym_and_str_tab_64(&sctx, &symtab, &strtab))
		return NO_SYMBOLS;

	// Validate that both sections fit entirely in the file
	if ((symtab->sh_offset + symtab->sh_size > file->size)
		|| (strtab->sh_offset + strtab->sh_size > file->size))
	{
		ft_putstr_fd("nm: warning: ", 2);
		ft_putstr_fd((char *)file->name, 2);
		ft_putstr_fd(" has a section extending past end of file\n", 2);
		return NO_SYMBOLS;
	}

	// .symtab must have a valid entry size
	if (symtab->sh_entsize == 0)
		return print_format_error(file->name);

	// Build the context used by the symbol reader
	ctx->map = file->map;
	ctx->file_size = file->size;
	ctx->symtab = symtab;
	ctx->strtab = strtab;
	return SYMBOLS_OK;
}

// Top-level function to parse and display ELF32 symbols.
// Returns 0 on success, 1 on error or if no symbols were found.
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

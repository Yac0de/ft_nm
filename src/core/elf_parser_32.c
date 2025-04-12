#include "../inc/ft_nm.h"

// Prints an error matching the `nm` output when an invalid ELF file is detected.
static int	print_format_error(const char *filename)
{
	ft_putstr_fd("nm: ", 2);
	ft_putstr_fd((char *)filename, 2);
	ft_putstr_fd(": file format not recognized\n", 2);
	return INVALID_ELF;
}

// Verifies that the section header table is within the file bounds.
static int	validate_section_headers(t_file *file, Elf32_Ehdr *ehdr)
{
	size_t shdr_size;

	if (ehdr->e_shoff > file->size)
		return 0;
	shdr_size = ehdr->e_shnum * sizeof(Elf32_Shdr);
	if (ehdr->e_shoff + shdr_size > file->size)
		return 0;
	return 1;
}

// Verifies that the section header string table fits within the file.
static int	validate_shstrtab(t_file *file, Elf32_Shdr *shstr)
{
	return (shstr->sh_offset + shstr->sh_size <= file->size);
}

// Retrieves the section header string table (shstrtab).
// If the index is invalid, prints a warning and returns NULL (as nm would).
static char *get_shstrtab(t_file *file, Elf32_Shdr *shdr, Elf32_Ehdr *ehdr)
{
	if (ehdr->e_shstrndx >= ehdr->e_shnum)
	{
		ft_putstr_fd("nm: warning: ", 2);
		ft_putstr_fd((char *)file->name, 2);
		return(ft_putstr_fd(" has a corrupt string table index - ignoring\n", 2), NULL);
	}

	Elf32_Shdr *shstr = &shdr[ehdr->e_shstrndx];
	if (!validate_shstrtab(file, shstr))
		return NULL;

	return (char *)(file->map + shstr->sh_offset);
}

// Builds the context required to locate ELF32 symbols in the file.
// Returns:
// - SYMBOLS_OK     → valid ELF and symbols successfully found
// - NO_SYMBOLS     → valid ELF but no symbols found
// - INVALID_ELF    → invalid ELF (error message already printed)
static int	get_symbol_ctx_32(t_file *file, t_symbol_ctx_32 *ctx)
{
	if (file->size < sizeof(Elf32_Ehdr))
		return print_format_error(file->name);

	Elf32_Ehdr *ehdr = (Elf32_Ehdr *)file->map;

	if (!validate_section_headers(file, ehdr))
		return print_format_error(file->name);

	Elf32_Shdr *shdr = (Elf32_Shdr *)(file->map + ehdr->e_shoff);
	char *shstrtab = get_shstrtab(file, shdr, ehdr);

	t_section_ctx_32 sctx = {
		.ehdr = ehdr,
		.shdr = shdr,
		.shstrtab = shstrtab
	};

	Elf32_Shdr *symtab;
	Elf32_Shdr *strtab;

	if (!find_sym_and_str_tab_32(&sctx, &symtab, &strtab))
		return NO_SYMBOLS;

	ctx->map = file->map;
	ctx->symtab = symtab;
	ctx->strtab = strtab;
	return SYMBOLS_OK;
}

// High-level entrypoint to parse and display ELF32 symbols.
// Handles all error types and prints appropriate messages matching `nm`.
int	parse_and_display_elf32_symbols(t_file *file)
{
	t_symbol_ctx_32 ctx;
	int result = get_symbol_ctx_32(file, &ctx);

	if (result == INVALID_ELF)
		return 1;

	if (result == NO_SYMBOLS)
	{
		ft_putstr_fd("nm: ", 2);
		ft_putstr_fd((char *)file->name, 2);
		return(ft_putstr_fd(": no symbols\n", 2), 1);
	}

	return read_symbols_32(&ctx);
}

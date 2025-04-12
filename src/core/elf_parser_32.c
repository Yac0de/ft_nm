#include "../inc/ft_nm.h"

#define SYMBOLS_OK     1
#define NO_SYMBOLS     0
#define INVALID_ELF   -1

// Prints a standardized error message for invalid ELF files.
static int	print_format_error(const char *filename)
{
	ft_putstr_fd("nm: ", 2);
	ft_putstr_fd((char *)filename, 2);
	ft_putstr_fd(": file format not recognized\n", 2);
	return INVALID_ELF;
}

// Checks if the section headers table is valid and within bounds.
static int	validate_section_headers(t_file *file, Elf32_Ehdr *ehdr)
{
	size_t shdr_size;

	if (ehdr->e_shoff > file->size)
		return 0;
	shdr_size = ehdr->e_shnum * sizeof(Elf32_Shdr);
	if (ehdr->e_shoff + shdr_size > file->size)
		return 0;
	if (ehdr->e_shstrndx >= ehdr->e_shnum)
		return 0;
	return 1;
}

// Checks if the section header string table fits within the file.
static int	validate_shstrtab(t_file *file, Elf32_Shdr *shstr)
{
	if (shstr->sh_offset + shstr->sh_size > file->size)
		return 0;
	return 1;
}

// Extracts and builds the context needed to read ELF32 symbols.
// Returns:
// - SYMBOLS_OK     → valid ELF + symbols found
// - NO_SYMBOLS     → valid ELF but no .symtab/.dynsym
// - INVALID_ELF    → invalid ELF (already printed error)
static int	get_symbol_ctx_32(t_file *file, t_symbol_ctx_32 *ctx)
{
	if (file->size < sizeof(Elf32_Ehdr))
		return print_format_error(file->name);

	Elf32_Ehdr *ehdr = (Elf32_Ehdr *)file->map;

	if (!validate_section_headers(file, ehdr))
		return print_format_error(file->name);

	Elf32_Shdr *shdr = (Elf32_Shdr *)(file->map + ehdr->e_shoff);
	Elf32_Shdr *shstr = &shdr[ehdr->e_shstrndx];

	if (!validate_shstrtab(file, shstr))
		return print_format_error(file->name);

	char *shstrtab = (char *)(file->map + shstr->sh_offset);

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

// Parse and display all ELF32 symbols from the mapped file.
// Returns 0 on success, 1 on error (e.g. nm: <ELF>: no symbols).
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
		ft_putstr_fd(": no symbols\n", 2);
		return 1;
	}

	return read_symbols_32(&ctx);
}

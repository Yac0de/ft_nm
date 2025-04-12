#include "../inc/ft_nm.h"

// Extracts and builds the context needed to read ELF32 symbols.
// Returns 1 if both .symtab/.strtab or .dynsym/.dynstr were found, 0 otherwise.
static int get_symbol_ctx_32(void *map, t_symbol_ctx_32 *ctx)
{
	Elf32_Ehdr *ehdr = (Elf32_Ehdr *)map;
	Elf32_Shdr *shdr = (Elf32_Shdr *)(map + ehdr->e_shoff);
	Elf32_Shdr *shstr = &shdr[ehdr->e_shstrndx];
	char *shstrtab = (char *)(map + shstr->sh_offset);

	// Create a helper context to pass section info to the lookup function
	t_section_ctx_32 sctx = {
		.ehdr = ehdr,
		.shdr = shdr,
		.shstrtab = shstrtab
	};

	Elf32_Shdr *symtab;
	Elf32_Shdr *strtab;

	// Try to find both symbol and string tables
	if (!find_sym_and_str_tab_32(&sctx, &symtab, &strtab))
		return 0;

	// Store in the final symbol context
	ctx->map = map;
	ctx->symtab = symtab;
	ctx->strtab = strtab;
	return 1;
}

// Parse and display all ELF32 symbols from the mapped file.
// Returns 0 on success, 1 on error (e.g. nm: <ELF>: no symbols).
int	parse_and_display_elf32_symbols(t_file *file)
{
	t_symbol_ctx_32 ctx;

	if (!get_symbol_ctx_32(file, &ctx))
	{
		ft_putstr_fd("nm: ", 2);
		ft_putstr_fd((char *)file->name, 2);
		ft_putstr_fd(": no symbols\n", 2);
		return 1;
	}

	return read_symbols_32(&ctx);
}

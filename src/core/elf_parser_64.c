#include "../inc/ft_nm.h"

// Extracts and builds the context needed to read ELF64 symbols.
// Returns 1 if both .symtab/.strtab or .dynsym/.dynstr were found, 0 otherwise.
static int	get_symbol_ctx_64(void *map, t_symbol_ctx_64 *ctx)
{
	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)map;
	Elf64_Shdr *shdr = (Elf64_Shdr *)(map + ehdr->e_shoff);
	Elf64_Shdr *shstr = &shdr[ehdr->e_shstrndx];
	char *shstrtab = (char *)(map + shstr->sh_offset);

	// Create a helper context to pass section info to the lookup function
	t_section_ctx_64 sctx = {
		.ehdr = ehdr,
		.shdr = shdr,
		.shstrtab = shstrtab
	};

	Elf64_Shdr *symtab;
	Elf64_Shdr *strtab;

	// Try to find both symbol and string tables
	if (!find_sym_and_str_tab_64(&sctx, &symtab, &strtab))
		return 0;

	// Store in the final symbol context
	ctx->map = map;
	ctx->symtab = symtab;
	ctx->strtab = strtab;
	return 1;
}

// Parse and display all ELF32 symbols from the mapped file.
// Returns 0 on success, 1 on error (e.g. no symbol table found).
int	parse_and_display_elf64_symbols(void *map)
{
	t_symbol_ctx_64 ctx;

	if (!get_symbol_ctx_64(map, &ctx))
		return (ft_putstr_fd("Error: symtab or strtab not found (64)\n", 2), 1);

	return read_symbols_64(&ctx);
}

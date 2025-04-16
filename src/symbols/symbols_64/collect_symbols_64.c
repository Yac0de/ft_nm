#include "../../../inc/ft_nm.h"

// Filters and builds a clean list of t_symbol_64 from raw ELF symbols.
// Skips useless/invalid symbols, allocates the list, and fills out_count.
// Returns NULL on allocation or logic error.
static t_symbol_64 *filter_and_build_symbols_64(t_symbol_build_ctx_64 *ctx, int *out_count)
{
	if (!ctx || !ctx->symbols || !ctx->strtab_data || !ctx->sections || !out_count)
		return NULL;

	t_symbol_64 *list = malloc(sizeof(t_symbol_64) * ctx->symbol_count);
	if (!list)
		return (ft_putstr_fd("Error: malloc failed in collect_symbols_64\n", 2), NULL);

	int j = 0;
	for (int i = 0; i < ctx->symbol_count; i++)
	{
		t_symbol_info_64 info = {
			.sym = &ctx->symbols[i],
			.strtab = ctx->strtab_data,
			.sections = ctx->sections
		};

		// Filter out anonymous or unprintable symbols
		if (!skip_symbol_64(&info) && ctx->strtab_data[ctx->symbols[i].st_name] != '\0')
			list[j++] = build_symbol_64(&info);
	}

	*out_count = j; // Return the final count of valid symbols
	return list;
}

// Extracts and prepares the symbol list from the ELF64 symbol table.
// Returns NULL if the symbol table is invalid or cannot be read safely.
// If successful, returns a filtered and sorted list of t_symbol_64 symbols.
t_symbol_64 *collect_symbols_64(t_symbol_ctx_64 *ctx, int *out_count)
{
	// Defensive checks on context and inputs
	if (!ctx || !ctx->map || !ctx->symtab || !ctx->strtab || !out_count)
		return NULL;

	// Shortcut to ELF header and file size
	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)ctx->map;

	// Validate that the .symtab section does not overflow the file
	Elf64_Off sym_offset = ctx->symtab->sh_offset;
	Elf64_Xword sym_size = ctx->symtab->sh_size;

	if (sym_offset + sym_size > ctx->file_size)
		return NULL;

	// Validate that .symtab size is a multiple of symbol struct size
	if (sym_size % sizeof(Elf64_Sym) != 0)
		return NULL;

	// Prepare a context for building and filtering the final symbol list
	t_symbol_build_ctx_64 bctx = {
		.symbols = (Elf64_Sym *)(ctx->map + sym_offset),
		.symbol_count = sym_size / sizeof(Elf64_Sym),
		.strtab_data = (char *)(ctx->map + ctx->strtab->sh_offset),
		.sections = (Elf64_Shdr *)(ctx->map + ehdr->e_shoff)
	};

	// Build and return the list of symbols
	return filter_and_build_symbols_64(&bctx, out_count);
}

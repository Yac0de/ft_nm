#include "../../../inc/ft_nm.h"

// Filters and builds a clean list of t_symbol_64 from raw ELF symbols.
// Skips useless/invalid symbols, allocates the list, and fills out_count.
// Returns NULL on allocation or logic error.
static t_symbol_64 *filter_and_build_symbols_64(t_symbol_build_ctx_64 *ctx, int *out_count)
{
	if (!ctx || !ctx->symbols || !ctx->strtab_data || !ctx->sections || !out_count)
		return NULL;

	// Allocate the maximum possible number of symbols
	t_symbol_64 *list = malloc(sizeof(t_symbol_64) * ctx->symbol_count);
	if (!list)
		return (ft_putstr_fd("Error: malloc failed in collect_symbols_64\n", 2), NULL);

	int j = 0;
	for (int i = 0; i < ctx->symbol_count; i++)
	{
		// Prepare context for symbol classification and filtering
		t_symbol_info_64 info = {
			.sym = &ctx->symbols[i],
			.strtab = ctx->strtab_data,
			.sections = ctx->sections
		};

		// Skip anonymous or unprintable symbols
		if (!skip_symbol_64(&info) &&
		ctx->strtab_data[ctx->symbols[i].st_name] != '\0')
			list[j++] = build_symbol_64(&info); // Build the final symbol object and append to output
	}

	// Return actual number of valid symbols found
	*out_count = j;
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

	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)ctx->map;

	// Ensure .symtab doesn't exceed the file size
	Elf64_Off sym_offset = ctx->symtab->sh_offset;
	Elf64_Xword sym_size = ctx->symtab->sh_size;

	if (sym_offset + sym_size > ctx->file_size)
		return NULL;

	// Ensure .symtab size is properly aligned to entry size
	if (sym_size % sizeof(Elf64_Sym) != 0)
		return NULL;

	// Setup context for symbol extraction
	t_symbol_build_ctx_64 bctx = {
		.symbols = (Elf64_Sym *)(ctx->map + sym_offset),
		.symbol_count = sym_size / sizeof(Elf64_Sym),
		.strtab_data = (char *)(ctx->map + ctx->strtab->sh_offset),
		.sections = (Elf64_Shdr *)(ctx->map + ehdr->e_shoff)
	};

	// Filter, build, and return the usable symbols
	return filter_and_build_symbols_64(&bctx, out_count);
}

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
		// Filter out anonymous or unprintable symbols
		if (!skip_symbol_64(&ctx->symbols[i]) &&
			ctx->strtab_data[ctx->symbols[i].st_name] != '\0')
				list[j++] = build_symbol_64(ctx->symbols[i], ctx->strtab_data, ctx->sections);
	}

	*out_count = j; // Return the final count of valid symbols
	return list;
}

// Collects and prepares symbols from an ELF64 file.
// Converts raw ELF symbols into an array of t_symbol_64.
// Returns NULL on error, or the list of symbols with count in out_count.
t_symbol_64 *collect_symbols_64(t_symbol_ctx_64 *ctx, int *out_count)
{
	if (!ctx || !ctx->map || !ctx->symtab || !ctx->strtab || !out_count)
		return NULL;

	// Validate that the symbol table has a sane size
	if (ctx->symtab->sh_size % sizeof(Elf64_Sym) != 0)
		return (ft_putstr_fd("Error: corrupted symtab size\n", 2), NULL);

	// Build a context object to pass symbol data to the builder function
	t_symbol_build_ctx_64 bctx = {
		.symbols = (Elf64_Sym *)(ctx->map + ctx->symtab->sh_offset),
		.symbol_count = ctx->symtab->sh_size / sizeof(Elf64_Sym),
		.strtab_data = (char *)(ctx->map + ctx->strtab->sh_offset),
		.sections = (Elf64_Shdr *)(ctx->map + ((Elf64_Ehdr *)ctx->map)->e_shoff)
	};

	return filter_and_build_symbols_64(&bctx, out_count);
}

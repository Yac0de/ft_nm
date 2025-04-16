#include "../../../inc/ft_nm.h"

// Reads, filters, sorts, and displays all ELF32 symbols.
// Returns SYMBOLS_OK on success, NO_SYMBOLS if no valid symbols were found.
int	read_symbols_32(t_symbol_ctx_32 *ctx)
{
	int count = 0;

	// Parse the ELF file and collect usable symbols
	t_symbol_32 *symbols = collect_symbols_32(ctx, &count);

	// If collection failed or resulted in no symbols, return as "no symbols"
	if (!symbols || count == 0)
		return NO_SYMBOLS;

	// Sort the symbols alphabetically by name (and by value if needed)
	sort_symbols_32(symbols, count);

	// Display them in the standard nm format
	display_symbols_32(symbols, count);

	// Clean up the allocated symbol list
	free(symbols);

	return SYMBOLS_OK;
}

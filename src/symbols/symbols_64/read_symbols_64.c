#include "../../../inc/ft_nm.h"

// Reads, filters, sorts, and displays all ELF64 symbols.
// Returns SYMBOLS_OK on success, NO_SYMBOLS if no valid symbols were found.
int	read_symbols_64(t_symbol_ctx_64 *ctx)
{
	int count = 0;

	// Parse the ELF file and collect usable symbols
	t_symbol_64 *symbols = collect_symbols_64(ctx, &count);

	// If collection failed or resulted in no symbols, return as "no symbols"
	if (!symbols || count == 0)
		return NO_SYMBOLS;

	// Sort the symbols alphabetically by name (and by value if needed)
	sort_symbols_64(symbols, count);

	// Display them in the standard nm format
	display_symbols_64(symbols, count);

	// Clean up the allocated symbol list
	free(symbols);

	return SYMBOLS_OK;
}

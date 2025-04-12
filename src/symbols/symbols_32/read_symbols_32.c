#include "../../../inc/ft_nm.h"

// Reads, filters, sorts, and displays all ELF32 symbols.
// Returns SYMBOLS_OK on success, NO_SYMBOLS if no valid symbols found.
int	read_symbols_32(t_symbol_ctx_32 *ctx)
{
	int count = 0;
	t_symbol_32 *symbols = collect_symbols_32(ctx, &count);

	// If no symbols could be collected or none are valid, fallback to "no symbols"
	if (!symbols || count == 0)
		return NO_SYMBOLS;

	sort_symbols_32(symbols, count);
	display_symbols_32(symbols, count);
	free(symbols);
	return SYMBOLS_OK;
}

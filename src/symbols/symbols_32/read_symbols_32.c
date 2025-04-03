#include "../../../inc/ft_nm.h"

// Orchestrates the full process of reading, sorting and displaying ELF32 symbols.
// Returns 0 on success, 1 on error (collection, sort or display failure).
int read_symbols_32(t_symbol_ctx_32 *ctx)
{
	int count = 0;
	t_symbol_32 *symbols = collect_symbols_32(ctx, &count);

	if (!symbols)
		return (ft_putstr_fd("Error: failed to collect symbols (32)\n", 2), 1);

	// No symbols found: nothing to display, but not an error
	if (count == 0)
		return (free(symbols), 0);

	// Sort symbols alphabetically by name
	if (!sort_symbols_32(symbols, count))
		return (free(symbols), ft_putstr_fd("Error: failed to sort symbols\n", 2), 1);

	// Display symbols to stdout in nm-compatible format
	if (!display_symbols_32(symbols, count))
		return (free(symbols), ft_putstr_fd("Error: display failed\n", 2), 1);

	free(symbols);
	return (0);
}

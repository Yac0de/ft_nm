#include "../../../inc/ft_nm.h"

// Sorts the symbols alphabetically by name using insertion sort.
// Returns 1 on success, 0 if input is invalid.
int sort_symbols_32(t_symbol_32 *symbols, int count)
{
	if (!symbols || count <= 0)
		return 0; // Invalid input

	// Insertion sort: simple, stable and sufficient for small symbol lists
	for (int i = 1; i < count; i++)
	{
		int j = i;

		// Shift elements until the current symbol is in the right place
		while (j > 0 && ft_strcmp(symbols[j - 1].name, symbols[j].name) > 0)
		{
			// Swap adjacent symbols
			t_symbol_32 tmp = symbols[j];
			symbols[j] = symbols[j - 1];
			symbols[j - 1] = tmp;
			j--;
		}
	}
	return 1;
}

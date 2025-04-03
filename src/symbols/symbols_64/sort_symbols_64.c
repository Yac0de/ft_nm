#include "../../../inc/ft_nm.h"

// Sorts the symbols alphabetically by name using insertion sort.
// Returns 1 on success, 0 if input is invalid.
int sort_symbols_64(t_symbol_64 *symbols, int count)
{
	if (!symbols || count <= 0)
		return 0;

	// Insertion sort
	for (int i = 1; i < count; i++)
	{
		int j = i;
		while (j > 0 && ft_strcmp(symbols[j - 1].name, symbols[j].name) > 0)
		{
			t_symbol_64 tmp = symbols[j];
			symbols[j] = symbols[j - 1];
			symbols[j - 1] = tmp;
			j--;
		}
	}
	return 1;
}

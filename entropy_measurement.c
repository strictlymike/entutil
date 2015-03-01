/* File: entropy_measurement.c
   Author: Michael Bailey
   License: WTFPL - http://www.wtfpl.net/
*/

#include <math.h>
#include <string.h>

#include "entropy_measurement.h"

extern unsigned char bit_counts[];

static const int _nibble_possible_values = 16;
static const int _byte_possible_values = 256;

long double ent_by_bit_max = 0;
long double ent_by_nibble_max = 0;
long double ent_by_byte_max = 0;


void ent_init(void)
{
	ent_by_bit_max = 1;
	ent_by_nibble_max = log2l(_nibble_possible_values);
	ent_by_byte_max = log2l(_byte_possible_values);
}

int ent_by_bit(long double *ent, unsigned char *s, size_t l)
{
	unsigned long int	bits = (8 * l);
	unsigned long int	bits_set = 0;
	unsigned long int	bits_clr = 0;

	long double		p_set = 0;
	long double		p_clr = 0;
	long double		_ent = 0;

	size_t			i;

	if (l == 0)
		return -1;

	for (i=0; i<l; i++)
		bits_set += bit_counts[*(s+i)];
	
	bits_clr = bits - bits_set;

	p_set = ((long double)bits_set) / bits;
	p_clr = ((long double)bits_clr) / bits;

	/* When calculating entropy, 0 * lg(0) is defined as 0 */

	if (p_set)
		_ent += -p_set * log2l(p_set);

	if (p_clr)
		_ent += -p_clr * log2l(p_clr);

	*ent = _ent;

	return 0;
}

int _ent_by_nibble_max(void)
{
	return log2l(_nibble_possible_values);
}

int ent_by_nibble(long double *ent, unsigned char *s, size_t l)
{
	const int		nibbles_per_byte = 2;

	unsigned long int	nibs = (nibbles_per_byte * l);
	unsigned long int	occurrences[_nibble_possible_values];

	int			i = 0;
	long double		p = 0;
	long double		_ent = 0;

	if ((l == 0) || (ent == NULL) || (s == NULL)) {
		return -1;
	}

	memset(&occurrences[0], 0, sizeof(occurrences));

	for (i=0; i<l; i++) {
		occurrences[*(s+i) & 0x0f]++;
		occurrences[(*(s+i) >> 4) & 0x0f]++;
	}

	for (i=0; i<_nibble_possible_values; i++) {
		p = ((long double)occurrences[i]) / nibs;
		/* When calculating entropy, 0 * lg(0) is defined as 0 */
		if (p)
			_ent += -p * log2l(p);
	}

	*ent = _ent;

	return 0;
}

int ent_by_byte(long double *ent, unsigned char *s, size_t l, int skipping)
{
	unsigned long int	occurrences[_byte_possible_values];
	int			i = 0;
	long double		p = 0;
	long double		_ent = 0;

	if ((l == 0) || (ent == NULL) || (s == NULL)) {
		return -1;
	}

	memset(&occurrences[0], 0, sizeof(occurrences));

	for (i=0; i<l; i+=(skipping + 1)) {
		occurrences[*(s+i)]++;
	}

	for (i=0; i<_byte_possible_values; i++) {
		p = ((long double)occurrences[i]) / l;
		if (p)
			_ent += -p * log2l(p);
	}

	*ent = _ent;

	return 0;
}

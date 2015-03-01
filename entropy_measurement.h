/* File: entropy_measurement.h
   Author: Michael Bailey
   License: WTFPL - http://www.wtfpl.net/
   Notes: Don't forget to call ent_init()
*/

#ifndef __ENTROPY_MEASUREMENT_H
#define __ENTROPY_MEASUREMENT_H

#include <sys/types.h>

void ent_init(void);
int ent_by_bit(long double *ent, unsigned char *s, size_t l);
int ent_by_nibble(long double *ent, unsigned char *s, size_t l);
int ent_by_byte(long double *ent, unsigned char *s, size_t l, int skipping);

extern long double ent_by_bit_max;
extern long double ent_by_nibble_max;
extern long double ent_by_byte_max;

#endif /* __ENTROPY_MEASUREMENT_H */

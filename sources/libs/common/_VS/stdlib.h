#pragma once

void memcpy(void *, const void *, int);
void memset(void *, int, int);
int memcmp(void *, const void *, int);
void *malloc(int);
void free(void *);
#define RAND_MAX 0x7fffffff


#define __disable_irq()
#define __set_MSP(x)
#define __enable_irq()

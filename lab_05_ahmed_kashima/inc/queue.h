#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

#include "data_struct.h"

int add_m(double **pin, double **pout, double *mas, double i);
int pop_m(double **pin, double **pout, double *mas, double *i);
void print_stack(data_t *head);
int add_s(data_t **pin, data_t **pout, data_t **full, double i);
int pop_s(data_t **pin, data_t **pout, data_t **empty, double *i);
data_t *create_j(double i);

#endif //_QUEUE_H_
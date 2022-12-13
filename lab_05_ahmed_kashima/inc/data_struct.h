#ifndef _DATA_STRUCT_H_
#define _DATA_STRUCT_H_

#define OK 0
#define ERR_READ 1
#define ERR_PARAM 2
#define ERR_MEMORY 3
#define ERR_NULL 4
#define ERR_RANGE 5
#define ERR_FILE 6
#define ERR_IO 7
#define ERR_FULL 8
#define ERR_EMPTY 9

#define N 1000
#define M 100

typedef struct data
{
	double i;
	struct data *next;
} data_t;

#endif //_DATA_STRUCT_H_
#include "../inc/queue.h"

data_t *create_j(double i)
{
	data_t *p = malloc(sizeof(data_t));
	if (p)
	{
		p->i = i; 
		p->next = NULL;
	}
	return p;
}

int add_m(double **pin, double **pout, double *mas, double i)
{
	if (!(*pin) || !mas || !(*pout))
		return ERR_NULL;
	**pin = i;
	*pin += 1;
	if (*pin == mas + N)
		*pin = mas;
	if (*pin == *pout)
		return ERR_FULL;
	
	//printf("pin %p\n", (void *)*pin);
	return OK;
}

int pop_m(double **pin, double **pout, double *mas, double *i)
{
	if (!pin || !pout || !mas)
		return ERR_FULL;
	*i = **pout;
	**pout = -1;
	(*pout)++;
	if (*pout == mas + N)
		*pout = mas;
	
	if (*pout == *pin)
		return ERR_EMPTY;
	
	//printf("pout %p\n", (void *)*pout);
	return 0;
}

void print_stack(data_t *head)
{
	if (!head)
		return;
	printf("\nStack:\n ");
	data_t *t = head;
	int i = 0; 
	while (t && i < N)
	{
		i++;
		printf("%f\n", t->i);
		t = t->next;
	}
	printf("\n");
}

int add_s(data_t **pin, data_t **pout, data_t **full, double i)
{
    //if (!pin || !pout ||)
	data_t *pin1 = *pin;
	data_t *new = create_j(i);
	if (new)
	{
	    if (!(*pout))
		{
		   *pout = new;
		    *pin = new;	
		}
	    else
		{
           pin1->next = new;
           *pin = new;	
		}		   
	}
	else 
	{
		return ERR_MEMORY;
	}
	int j;
	for (j = 0; full[j] && j < 2*N; j++);
	full[j] = new;
	//printf("new %p\n", (void *)new);
	return OK;
}

int pop_s(data_t **pin, data_t **pout, data_t **empty, double *i)
{
	
	*i = (*pout)->i;
	data_t *k = *pout;
	if(!(*pout)->next)
	{
		int j;
	    for (j = 0; empty[j]; j++);
	    empty[j] = k;
		free(k);
		
		//printf("free %p\n", (void *)k);
		*pout = NULL;
		return ERR_EMPTY;
	}
	*pout =(*pout)->next;
	
	int j;
	for (j = 0; empty[j]; j++);
	empty[j] = k;
	free(k);
	//printf("free %p\n", (void *)k);
	return OK;
}
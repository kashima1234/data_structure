#include "../inc/process.h"

uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}

void free_list(data_t *head)
{
	data_t *p;
	while (head)
	{
		p = head;
		head = head->next;
		free(p);
	}
}

double get_rand(int *p)
{
	return (p[1] - p[0])*(double)(rand()/(double)RAND_MAX) + p[0];
}

double find_min(double a, double b, double c)
{
	if (a < b && a < c)
		return a;
	if (b < a && b < c)
		return b;
	return c;
}

void check(double tstop, double t_all, int in1, int in2, int *p1, 
    int *p2, int *p3, int *p4)
{
	
	double t_alln, tstopn, tmin;
	double in1n = N; 
	double in2n;
	
	double time1 = ((double)(p1[1] + p1[0]))/2 * N;
	double time2 = ((double)(p3[1] + p3[0]))/2 * N;
	if (time1 > time2)
	{
		t_alln = time1; 
		tmin = time2;
	}
	else 
	{
		t_alln = time2; 
		tmin = time1;
	}
	in1n = t_alln / ((double)(p1[1] + p1[0])/2);

	in2n =  t_alln / ((double)(p2[1] + p2[0])/2);
    tstopn = t_alln - tmin - (double)(p4[1] + p4[0])/2 * in2n;
	tstopn *= -1;

	double pr1 = abs(t_alln - t_all) / t_alln * 100;  
	double pr2 = abs(in1n - in1) / in1n * 100;  
	double pr3 = abs(in2n - in2) / in2n * 100;

	double max;
    if( pr1 > pr2 && pr1 > pr3)
        max = pr1;
    else if (pr2 > pr1 && pr2 > pr3)
	{
        max = pr2;
	}
    else
	{
        max = pr3;
	}
	printf("Theory results: \n");
	printf("Time of process = %lf\n", t_alln);
	printf("Wait time = %lf\n", tstopn);
	printf("in 1 type  = %lf\n", in1n);
	printf("in 2 type  = %lf \n", in2n);
	printf("percent is %f\n", max);
}

void process_m(int *p1, int *p2, int *p3, int *p4)
{
	double mas[N] = {-1}; 
	double mas1[N] = {-1};
	double i;
	double *pin = mas, *pout = mas;//pin - tail pout - head;
	double *pin1 = mas1, *pout1 = mas1;
	
	long long int begin_time, end_time;
	double t1 = 0, t2 = 0, toa = 0, tmin = 0, tstop = 0, t_all = 0; 
	int flag1 = ERR_EMPTY;
	int flag2 = ERR_EMPTY;
	int flag = 0;
	int type = 1;
	int count_in1 = 0, count_out1 = 0, count_in2 = 0, count_out2 = 0;
	int count1 = 0, count2 = 0, count_sr1 = 0, count_sr2 = 0, iter;
	double time_in1 = 0, time_in2 = 0, t1_sr = 0, t2_sr = 0, t3_sr = 0, t4_sr = 0;
	
	begin_time = tick();
	iter = 0;
	while(count_out1 < N)
	{
		iter++;
	    /*for (int j = 0; j < N; j++)
		{
			printf("%lf ", mas[j]);
		}
		printf("\n");
		for (int j = 0; j < N; j++)
		{
			printf("%lf ", mas1[j]);
		}
		printf("\n");*/
		//printf("%lf %lf %lf\n", t1,t2,toa);
		if (flag1 == ERR_FULL || flag2 == ERR_FULL)
		{
			printf("Full first!\n");
			break;
		}
		
		if (t1 == 0)
		{
			t1 = get_rand(p1);
			t1_sr += t1;
		}
	    if (t2 == 0)
		{
			t2 = get_rand(p2);
			t2_sr += t2;
		}
		
		if (toa == 0)
		{
			if ((type == 1 && !flag1) || (!flag1 && flag2))
			{
				type = 1;
				toa = get_rand(p3);
				t3_sr += toa;
				//printf("pop 1\n");
				flag1 = pop_m(&pin, &pout, mas, &i);
				time_in1 += t_all - i;
				count_out1++;
				count1--;
				flag = 1;
			}
			else if (!flag2)
			{
				type = 2;
				toa = get_rand(p4);
				t4_sr += toa;
				//printf("pop 2\n");
				flag2 = pop_m(&pin1, &pout1, mas1, &i);
				time_in2 += t_all - i;
				count_out2++;
				count2--;
			}
		}
		if (toa)
		{
		    tmin = find_min(t1, t2, toa);
		}
		else 
		{
			if (t1 < t2)
				tmin = t1;
			else 
				tmin = t2;
		}
		//printf("%lf %lf %lf\n", t1,t2,toa);
		//printf("tmin %lf\n", tmin);
		if (tmin == t1)
		{
			//printf("add 1\n");
			flag1 = add_m(&pin, &pout, mas, t_all);
			count1++;
			count_in1++;
		}
		if (tmin == t2)
		{
			//printf("add 2\n");
			flag2 = add_m(&pin1, &pout1, mas1, t_all);
			count_in2++;
			count2++;
		}
		
		t1 -= tmin;
		t2 -= tmin;
		toa -= tmin;
		
		//printf("%lf %lf %lf\n\n", t1,t2,toa);
		if (toa < 0)
		{
			tstop += toa;
			toa = 0; 
		}
		t_all += tmin;
		count_sr1 += count1;
		count_sr2 += count2;
		
		if (count_out1 % 100 == 0 && flag)
		{
			printf("------------------------------\n");
			printf("out 1 type = %d \n", count_out1);
			printf("in 1 type  = %d\n", count_in1);
	        printf("in 2 type  = %d \n", count_in2);
	        printf("out 2 type = %d \n", count_out2);
			printf("wait in queue 1 type = %lf\n", time_in1 / count_out1);
	        printf("wait in queue 2 type = %lf\n", time_in2 / count_out2);
			printf("Number of calls in 1 = %d\n", count1);
	        printf("Number of calls in 2 = %d \n", count2 );
		//	printf("Middle number in 1   = %d\n", count_sr1/iter);
	      //  printf("Middle number in 2   = %d \n", count_sr2/iter );
			flag = 0;
			printf("\n");
		}
	}
	end_time = tick();
	printf("-------------------------------\n");
	printf("Time of Process = %lf\n", t_all);
	printf("Wait time = %lf\n", tstop);
	
	printf("in 1 type  = %d\n", count_in1);
	printf("in 2 type  = %d \n", count_in2);
	printf("out 1 type = %d \n", count_out1);
	printf("out 2 type = %d \n", count_out2);
	
	//printf("in_queue_sr1 = %lf\n", time_in1 / count_out1);
	//printf("in_queue_sr2 = %lf\n", time_in2 / count_out2);
	//printf("middle t1 = %lf\n", t1_sr / count_in1);
	//printf("middle t2 = %lf\n", t2_sr / count_in2);
	//printf("middle t3 = %lf\n", t3_sr / count_out1);
	//printf("middle t4 = %lf\n", t4_sr / count_out2);
	
	printf("time in ticks(Array) = %lld\n", end_time - begin_time);
	
	check(tstop, t_all, count_in1, count_in2, p1, p2, p3, p4);
	begin_time = tick(); 
}

void process_s(int *p1, int *p2, int *p3, int *p4, int f)
{
	
	data_t *empty[2*N] = {NULL};
	data_t *full[2*N] = {NULL};
	data_t *pin = NULL, *pout = NULL;
	
	data_t *empty1[2*N] = {NULL};
	data_t *full1[2*N] = {NULL};
	data_t *pin1 = NULL, *pout1 = NULL;
	
	double i;
	
	long long int begin_time, end_time;
	double t1 = 0, t2 = 0, toa = 0, tmin = 0, tstop = 0, t_all = 0; 
	int flag1 = ERR_EMPTY;
	int flag2 = ERR_EMPTY;
	int flag = 0;
	int type = 1;
	int count_in1 = 0, count_out1 = 0, count_in2 = 0, count_out2 = 0;
	int count1 = 0, count2 = 0, count_sr1 = 0, count_sr2 = 0, iter;
	double time_in1 = 0, time_in2 = 0, t1_sr = 0, t2_sr = 0, t3_sr = 0, t4_sr = 0;
	
	begin_time = tick();
	iter = 0;
	while(count_out1 < N && iter < 100000)
	{
		iter++;
		//printf("%d \n", iter);
	    /*for (int j = 0; j < N; j++)
		{
			printf("%lf ", mas[j]);
		}
		printf("\n");
		for (int j = 0; j < N; j++)
		{
			printf("%lf ", mas1[j]);
		}
		printf("\n");*/
		//printf("%lf %lf %lf\n", t1,t2,toa);
		//print_stack(pout);
		//print_stack(pout1);
		if (flag1 == ERR_FULL || flag2 == ERR_FULL)
		{
			puts("1st Queue is full!");
			break;
		}
		
		if (t1 == 0)
		{
			t1 = get_rand(p1);
			t1_sr += t1;
		}
	    if (t2 == 0)
		{
			t2 = get_rand(p2);
			t2_sr += t2;
		}
		
		
		if (toa == 0)
		{
			if ((type == 1 && pout) || (pout && !pout1))
			{
				for (int i = 0; i < N; i++)
				{
					if (full[i] == pout)	
					{
				    	full[i] = NULL;
				    }
				}
				type = 1;
				toa = get_rand(p3);
				t3_sr += toa;
				//printf("pop 1\n");
				flag1 = pop_s(&pin, &pout, empty, &i);
				time_in1 += t_all - i;
				count1--;
				count_out1++;
				flag = 1;
			}
			else if (pout1)
			{
				for (int i = 0; i < N; i++)
				{
					if (full1[i] == pout1)	
					{
				    	full1[i] = NULL;
				    }
				}
				type = 2;
				toa = get_rand(p4);
				t4_sr += toa;
				//printf("pop 2\n");
				flag2 = pop_s(&pin1, &pout1, empty1, &i);
				time_in2 += t_all - i;
				count2--;
				count_out2++;
			}
		}
		if (toa)
		{
		    tmin = find_min(t1, t2, toa);
		}
		else 
		{
			if (t1 < t2)
				tmin = t1;
			else 
				tmin = t2;
		}
		//printf("%lf %lf %lf\n", t1,t2,toa);
		//printf("tmin %lf\n", tmin);
		if (tmin == t1)
		{
			//printf("add 1\n");
			flag1 = add_s(&pin, &pout, full, t_all);
			count1++;
			for (int i = 0; i < N; i++)
			{
			    if (empty[i] == pin)	
				{
					empty[i] = NULL;
				}
			}
			
			count_in1++;
		}
		if (tmin == t2)
		{
			//printf("add 2\n");
			flag2 = add_s(&pin1, &pout1, full1, t_all);
			count2++;
			count_in2++;
			for (int i = 0; i < N; i++)
			{
			    if (empty1[i] == pin1)	
					empty1[i] = NULL;
			}
		}
		
		t1 -= tmin;
		t2 -= tmin;
		toa -= tmin;
		
		//printf("%lf %lf %lf\n\n", t1,t2,toa);
		if (toa < 0)
		{
			tstop += toa;
			toa = 0; 
		}
		t_all += tmin;
		count_sr1 += count1;
		count_sr2 += count2;
		
		if (count_out1 % 100 == 0 && flag && f != 1)
		{
			printf("------------------------------\n");
			printf("out 1 type = %d \n", count_out1);
			printf("in 1 type  = %d\n", count_in1);
	        printf("in 2 type  = %d \n", count_in2);
	        printf("out 2 type = %d \n", count_out2);
			printf("wait in queue 1 type = %lf\n", time_in1 / count_out1);
	        printf("wait in queue 2 type = %lf\n", time_in2 / count_out2);
			printf("Number of calls in 1 = %d\n", count1);
	        printf("Number of calls in 2 = %d \n", count2 );
			//printf("Middle number in 1   = %d\n", count_sr1/iter);
	        //printf("Middle number in 2   = %d \n", count_sr2/iter );
			flag = 0;
			printf("\n");
		}
	}
	end_time = tick();
	printf("-------------------------------\n");
	printf("Time of process = %lf\n", t_all);
	printf("Wait time = %lf\n", tstop);
	
	printf("in 1 type  = %d\n", count_in1);
	printf("in 2 type  = %d \n", count_in2);
	printf("out 1 type = %d \n", count_out1);
	printf("out 2 type = %d \n", count_out2);
	
	//printf("in_queue_sr1 = %lf\n", time_in1 / count_out1);
	//printf("in_queue_sr2 = %lf\n", time_in2 / count_out2);
	// printf("middle t1 = %lf\n", t1_sr / count_in1);
	// printf("middle t2 = %lf\n", t2_sr / count_in2);
	// printf("middle t3 = %lf\n", t3_sr / count_out1);
	// printf("middle t4 = %lf\n", t4_sr / count_out2);
	
	printf("time in ticks(linked_list) = %lld\n", end_time - begin_time);
    printf("memory is %lu\n", sizeof(data_t) * (count_in1 + count_in2));
	
	check(tstop, t_all, count_in1, count_in2, p1, p2, p3, p4);
	
	if (f)
	{
	    printf("\n-----------------\nEPMTY:\n");
		int o = 0;
	    for (int i = 0; i < N; i++)
     	{
		    if (empty[i])	
	    	{
	    		printf("%p \n",(void *)empty[i]);
				o++;
	    	}
	    }
		printf("EMPTY count = %d\n", o);
        printf("\nFULL: \n");
	    for (int i = 0; i < N; i++)
	    {
    	    if (full[i])
	        	printf("%p \n", (void *)full[i]);
	    }
		printf("\n --------------\nEPMTY1:\n");
		int o1 = 0;
	    for (int i = 0; i < N; i++)
     	{
		    if (empty1[i])	
	    	{
	    		printf("%p \n",(void *)empty1[i]);
				o1++;
	    	}
	    }
		printf("EMPTY1 count = %d\n", o1);
        printf("\nFULL1: \n");
	    for (int i = 0; i < N; i++)
	    {
    	    if (full1[i])
	        	printf("%p \n", (void *)full1[i]);
	    }
	}	
	free_list(pout);
	free_list(pout1);	
	begin_time = tick(); 
}


void little_process(int *p1, int *p2, int *p3, int *p4)
{
	data_t *empty[2*N] = {NULL};
	data_t *full[2*N] = {NULL};
	data_t *pin = NULL, *pout = NULL;
	
	data_t *empty1[2*N] = {NULL};
	data_t *full1[2*N] = {NULL};
	data_t *pin1 = NULL, *pout1 = NULL;
	
	double i;
	
	long long int begin_time, end_time;
	double t1 = 0, t2 = 0, toa = 0, tmin = 0, tstop = 0, t_all = 0; 
	int flag1 = ERR_EMPTY;
	int flag2 = ERR_EMPTY;
	// int flag;
	int type = 1;
	int count_in1 = 0, count_out1 = 0, count_in2 = 0, count_out2 = 0;
	int count1 = 0, count2 = 0, count_sr1 = 0, count_sr2 = 0, iter;
	double time_in1 = 0, time_in2 = 0, t1_sr = 0, t2_sr = 0, t3_sr = 0, t4_sr = 0;
	
	begin_time = tick();
	iter = 0;
	while(count_out1 < 10)
	{
		iter++;
		if (flag1 == ERR_FULL || flag2 == ERR_FULL)
		{
			puts("Full first!");
			break;
		}
		
		if (t1 == 0)
		{
			t1 = get_rand(p1);
			t1_sr += t1;
		}
	    if (t2 == 0)
		{
			t2 = get_rand(p2);
			t2_sr += t2;
		}
		
		
		if (toa == 0)
		{
			if ((type == 1 && pout) || (pout && !pout1))
			{
				for (int i = 0; i < N; i++)
				{
					if (full[i] == pout)	
					{
				    	full[i] = NULL;
				    }
				}
				type = 1;
				toa = get_rand(p3);
				t3_sr += toa;
				printf("free 1 %p\n", (void *)pout);
				flag1 = pop_s(&pin, &pout, empty, &i);
				time_in1 += t_all - i;
				count1--;
				count_out1++;
				// flag = 1;
			}
			else if (pout1)
			{
				for (int i = 0; i < N; i++)
				{
					if (full1[i] == pout1)	
					{
				    	full1[i] = NULL;
				    }
				}
				type = 2;
				toa = get_rand(p4);
				t4_sr += toa;
				printf("free 2 %p\n", (void *)pout1);
				flag2 = pop_s(&pin1, &pout1, empty1, &i);
				time_in2 += t_all - i;
				count2--;
				count_out2++;
			}
		}
		if (toa)
		{
		    tmin = find_min(t1, t2, toa);
		}
		else 
		{
			if (t1 < t2)
				tmin = t1;
			else 
				tmin = t2;
		}

		if (tmin == t1)
		{
			flag1 = add_s(&pin, &pout, full, t_all);
			printf("new 1  %p\n", (void *)pin);
			count1++;
			for (int i = 0; i < N; i++)
			{
			    if (empty[i] == pin)
					empty[i] = NULL;
			}
			
			count_in1++;
		}
		if (tmin == t2)
		{
			flag2 = add_s(&pin1, &pout1, full1, t_all);
			printf("new 2  %p\n", (void *)pin1);
			count2++;
			count_in2++;
			for (int i = 0; i < N; i++)
			{
			    if (empty1[i] == pin1)	
					empty1[i] = NULL;
			}
		}
		
		t1 -= tmin;
		t2 -= tmin;
		toa -= tmin;
		
		if (toa < 0)
		{
			tstop += toa;
			toa = 0; 
		}
		t_all += tmin;
		count_sr1 += count1;
		count_sr2 += count2;
	}
	end_time = tick();
	printf("-------------------------------\n");
	printf("Time of process = %lf\n", t_all);
	printf("Wait time = %lf\n", tstop);
	
	printf("in 1 type  = %d\n", count_in1);
	printf("in 2 type  = %d \n", count_in2);
	printf("out 1 type = %d \n", count_out1);
	printf("out 2 type = %d \n", count_out2);
	
	// printf("middle t1 = %lf\n", t1_sr / count_in1);
	// printf("middle t2 = %lf\n", t2_sr / count_in2);
	// printf("middle t3 = %lf\n", t3_sr / count_out1);
	// printf("middle t4 = %lf\n", t4_sr / count_out2);
	
	printf("time in ticks(linked_list) = %lld\n", end_time - begin_time);
	
	for (int i = 0; i < N; i++)
		if (full[i])
			free(full[i]);
			
	for (int i = 0; i < N; i++)
		if (full1[i])
			free(full1[i]);
}
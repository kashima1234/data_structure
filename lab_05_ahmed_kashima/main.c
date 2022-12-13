#include "./inc/main.h"

void menu()
{

	printf("%s",
	"\t\t____________________________________\n"
	"\t\t|*|       ****Actions****        |*|\n"
	"\t\t|1|-> Run with Array             |*|\n"
	"\t\t|2|-> Run with linked list       |*|\n"
	"\t\t|3|-> Print parameters           |*|\n"
	"\t\t|4|-> Change parameters          |*|\n"
	"\t\t|5|-> Return original parameters |*|\n"
	"\t\t|6|-> Run with adresses          |*|\n"
	"\t\t|0|-> exit                       |*|\n"
	"\t\t====================================\n"
	"Your choice: ");
}

void info()
{
	printf("%s", 
	"\nThis program makes operations with queue\n"
	"Two queues, one OA;\n\tT1 from 1 to 5;\n\tT2 from 0 to 3\n"
	"\tT3 from 0 to 4;\n\tT4 from 0 to 1;\nAll times are double\n"
	"Number of calls is 1000\n"
	"for each 100 calls print info\n"
    "\n");
}

void clear_stream(void)
{
	int x;
	while ((x = getchar()) != '\n' && x != EOF) {}
}

int main()
{
	system("clear");
	int p1[2] = { 1,5 };
	int p2[2] = { 0,3 };
	int p3[2] = { 0,4 };
	int p4[2] = { 0,1 };
	setbuf(stdout, NULL);
	srand(time(NULL));
	int action;
	
	info();
	int k = 1;
	do
	{
		menu();
		if (scanf("%d", &action) == 1)
		{
			printf("\n");
            if (action == 0)
				k = 0;
			else if (action == 3)
			{
				printf("T1 from %d to %d;\n", p1[0], p1[1]);
				printf("T2 from %d to %d;\n", p2[0], p2[1]);
				printf("T3 from %d to %d;\n", p3[0], p3[1]);
				printf("T4 from %d to %d;\n", p4[0], p4[1]);
			}
			else if (action == 4)
			{
				printf("Input T1 from to(int int): ");
				int p[2];
				if (scanf("%d %d", p, p + 1) != 2 && p[0] < p[1])
				{
					puts("input error!");
					continue;
				}
				p1[0] = p[0];
				p1[1] = p[1];
				
				printf("Input T2 from to(int int): ");
				if (scanf("%d %d", p, p + 1) != 2 && p[0] < p[1])
				{
					puts("input error!");
					continue;
				}
				p2[0] = p[0];
				p2[1] = p[1];
				
				printf("Input T3 from to(int int): ");
				if (scanf("%d %d", p, p + 1) != 2 && p[0] < p[1])
				{
					puts("input error!");
					continue;
				}
				p3[0] = p[0];
				p3[1] = p[1];
				
				printf("Input T4 from to(int int): ");
				if (scanf("%d %d", p, p + 1) != 2 && p[0] < p[1])
				{
					puts("input error!");
					continue;
				}
				p4[0] = p[0];
				p4[1] = p[1];
			}
			else if (action == 5)
			{
				p1[0] = 1;
				p1[1] = 5;
				
				p2[0] = 0;
				p2[1] = 3;
				
				p3[0] = 0;
				p3[1] = 4;
				
				p4[0] = 0;
				p4[1] = 1;
			}
			else if (action == 1)
			{
				process_m(p1,p2,p3,p4);
				printf("Memory on Array %lu \n", sizeof(double)*N);
			}
			else if (action == 2)
				process_s(p1,p2,p3,p4,0);
			else if (action == 6)
				process_s(p1,p2,p3,p4,1);
		} 
		else 
		{
			clear_stream();
		    puts("\nInput error\n");
			continue;
		}
	} while (k);
	return 0;
}

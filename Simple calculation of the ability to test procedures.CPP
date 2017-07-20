#include<stdio.h>//Define input / output functions
#include<stdlib.h>//Define miscellaneous functions and memory allocation functions
#include<string.h>//string manipulation
#include<ctype.h>//Character processing
#include<time.h>//Define the function of time
void grap(void);//Initial menu
void cal(void);//Get random equations, calculate, score and record
void cheak(void);//View previous results		
int rand0(void);//random number
FILE *data;
int score;
char id[7];
int i;
int main()
{
	printf("Please input your four digit ID (e.g.AB1234):");
	gets(id);//Get ID
	if(id[6]=='\0'&&isalpha(id[0])&&isalpha(id[1])&&isdigit(id[2])&&
	isdigit(id[3])&&isdigit(id[4])&&isdigit(id[5]))//Limited ID form
	grap();
	else
	{
	printf("Your ID's format is error\n");
	main();
	}	
	return 0;
 } 
void grap(void)
{
	char num;
	for(i=0;i<50;i++)
	putchar('-');
	putchar('\n');
	puts("Please type in the corresponding number to select\n");
	puts("(1)	Start a test");
	puts("(2)	Check scores");
	puts("(3)	Exit");
	for(i=0;i<50;i++)
	putchar('-');
	putchar('\n');
	printf("Please input your choice:");
	int number;
	while(scanf("%d",&num)!=1)//Only integer to output 
	{
		while(getchar()=='\n');// Clean cache area
		printf("Please enter a integer number:");
	}
		switch(num)
		{
			case 1:
				cal();
				break;
			case 2:
				cheak();
				break;
			case 3:
				puts("Thank you!");
				break;//Exit program
			default:
				puts("Please type number from 1 to 3.");
				grap();
	}
}
void cal(void)
{	
 	int x,y,n,score=0,a[10],in[10][3],b[10],re[10],i;
	time_t start,end;
	char ID[7],typein[3],con[3],scan[7],sym[10];
	srand((unsigned)time(NULL));//When the seeds are used in the system
	getchar();//Undertake on a newline input
	printf("Are you ready?\n");
	getchar();//Enter any number to start 
	time(&start);//Record the initial time 
	for(i=0;i<10;i++)
	{
		n=rand()%4;
			switch(n){
				case 0:
					sym[i]='+';
					a[i]=rand()%100;
					b[i]=rand()%(100-a[i]);
					re[i]=a[i]+b[i];
					break;
				case 1:
					sym[i]='-';
					do
					{
					a[i]=rand()%100;
					b[i]=rand()%100;
					re[i]=a[i]-b[i];
					}while(re[i]>99||re[i]<0||a[i]<b[i]);
					break;
				case 2:
					sym[i]='*';
					do
					{
					a[i]=rand()%100;
					b[i]=rand()%100;
					re[i]=a[i]*b[i];
					}while(re[i]>99);
					break;
				case 3:
					sym[i]='/';
					
					do{
					a[i]=rand()%100;
					b[i]=rand()%100;
					re[i]=a[i]/b[i];
					}while(re[i]>99||re[i]<0||a[i]%b[i]!=0);
					break;
			}
		printf("%2d %c %2d = ",a[i],sym[i],b[i]);
		scanf("%d",&in[i]);
		x=re[i];
		y=*in[i];
		if(x==y)//scoring
		score+=10;
	}
	time(&end);//Record end time 
	printf("Your score is %d, use time: %lds\n",score,end-start);
	puts("Prob.		|Correct answer  |	Ur answer");
	for(i=0;i<10;i++)
	printf("(%d)%d %c %d =	%d			%d\n",i+1,a[i],sym[i],b[i],re[i],*in[i]);
	data=fopen("record.txt","a+");//Open file 
	if(data==NULL)//Check whether the file is normally open 
	{
		printf("Failed to open the file.\n");
		exit(1);
	}
	for(i=0;i<6;i++)
	fprintf(data,"%c",id[i]);
	fprintf(data,"		%d point(s)	%ld seconds\n",score,end-start);
	fclose(data);//Close file 
	grap();//Into the cycle menu
}
void cheak(void)
{
	char line[81],com[81];
	data=fopen("record.txt","r");//Open file 
	if(data==NULL)//Check whether the successful opening
	{
		printf("Failed to open the file.\n");
		exit(1);
	}
	while(fgets(line,81,data)!=NULL)//Output all the contents of the file 
	{
	if(!strncmp(line,id,6))//The output corresponding to the performance of ID 
	printf("%s",line);
}
	fclose(data);//Close file 
	grap();//Into the cycle menu 
}

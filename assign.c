 #include<stdio.h> 
//#include<conio.h>
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<time.h>


 
void init_shell() //entering into the shell 
{ 
	printf("\033[H\033[J");
	printf("The commands available in My shell\n");
	printf("***MAN command to know about any command***\n***syntax:MAN [command name(CD/PWD/FIND/History]***\n***Exit command to exit from the shell***\n***syntax:exit***\n***HISTORY to display last 10 commands used***\n***syntax:history***\n***PWD to know the path of present working directory***\n***syntax:PWD\n***FIND to search for a file in current directory***\n***syntax:find [filename]***\n***CD to change the current working directory***\n***syntax:CD [path]***\n");
} 
int processString(char* str, char** parsed, char** parsedpipe);
static int n;
static int temp;
char sucess[10]="success";
char *s=sucess;
char fail[10]="fail";
char *f=fail;

struct his
{
char com[1000];
int day;
int mon;
int year;
int hour;
int min;
int sec;
char status[20];
//struct his *next;
};
struct his hs[10];
void history(char* cmd,int day,int mon,int year,int hour,int min,int sec)
{
n=n%10;
if(n<10)
{
	strcpy(hs[n].com,cmd);
	hs[n].day=day;
	hs[n].mon=mon;
	hs[n].year=year;
	hs[n].hour=hour;
	hs[n].min=min;
	hs[n].sec=sec;
	//hs[n]->next=hs[n+1];
	n++;
	temp++;
}
}
void print_history()
{
if(temp<10){
	for(int i=0;i<n-1;i++)
	{
		printf("%s %d-%d-%d %d:%d:%d %s\n",hs[i].com,hs[i].day,hs[i].mon,hs[i].year,hs[i].hour,hs[i].min,hs[i].sec,hs[i].status);
	}
}
else{
	for(int i=n,j=0;j<10;i++,j++){
		i=i%10;
		printf("%s %d-%d-%d %d:%d:%d %s\n",hs[i].com,hs[i].day,hs[i].mon,hs[i].year,hs[i].hour,hs[i].min,hs[i].sec,hs[i].status);
	}
	//printf("%s %d-%d-%d %d:%d:%d \n",hs[n].com,hs[n].day,hs[n].mon,hs[n].year,hs[n].hour,hs[n].min,hs[n].sec);
}
}
void add_status(char r)
{	
	int t=n;
	if(r=='y'){
		strcpy(hs[--t].status,s);
	}
	else{
		strcpy(hs[--t].status,f);
	}
}
int reading_command(char* str) 
{ 
	char* c,h; 
	char s[100],hi[10]="History";
	int day,mon,year,hour,min,sec;
	time_t now;
	struct tm * time_pointer;
	time(&now);
	time_pointer = localtime(&now);
	scanf("%[^\n]%*c",s); 
	c=s;
	day=time_pointer->tm_mday;
	mon=time_pointer->tm_mon;
	year=time_pointer->tm_year+1900;
	hour=time_pointer->tm_hour;
	min=time_pointer->tm_min;
	sec=time_pointer->tm_sec;
	history(c,day,mon,year,hour,min,sec);
	if(strcmp(s,hi) != 0)
	add_status('n');
	else
	add_status('y');
	if (strlen(c) != 0) { 
		strcpy(str, c);
		return 0; 
	} else { 
		return 1;
	}
}

// Function to print Current Directory. 
void cursor() 
{ 
	char buffer[500]; 
	getcwd(buffer, sizeof(buffer)); 
	printf("\nMyshell@ubuntu:%s>>>", buffer); 
}

void MAN(char **cmd)
{
	
	char m[10];
	strcpy(m,cmd[1]);
	FILE *fp;
	fp = fopen(m, "r");
	char c;
	c=getc(fp);
	if(c==EOF)
	printf("no file is found");
	while(c != EOF)
	{
		printf("%c",c);
		c=getc(fp);
	}
}

void parsing(char* c,char** parsedc)
{
	int i; 

	for (i = 0; i < 300; i++) { 
		parsedc[i] = strsep(&c, " "); 

		if (parsedc[i] == NULL) 
			break; 
		if (strlen(parsedc[i]) == 0) 
			i--; 
	}
} 
// Function to execute builtin commands 
int mycmdparser(char **cmd) 
{
char find[5]="FIND";
char pwd[5]="PWD";
char cd[3]="CD";
char exi[5]="Exit";
char history[20]="History";
char man[5]="MAN";
char *e=exi;
char *c=cd;
char *p=pwd;
char *f=find;
char *h=history;
char *m=man;
if(strcmp(cmd[0],e) == 0)
{
	//printf("e");
	return -1;
}
else if(strcmp(cmd[0],p) == 0)
{
	char buffer[100];
	getcwd(buffer, sizeof(buffer)); 
	printf("\nPresent Working Directory:%s", buffer);
	return 1;
}
else if(strcmp(cmd[0],m) == 0)
{
	MAN(cmd);
	return 1;
}
else if(strcmp(cmd[0],c)==0)
{
	chdir(cmd[1]);
	return 1;
}
else if(strcmp(cmd[0],f) == 0)
{
		char s[30]="find ";
		char *parsedArgs[300];
		char *p=s;
		int x;
		strcat(p, cmd[1]);
		parsing(p,parsedArgs);
		x=mycmdparser(parsedArgs);
		return 1;	
}
else if(strcmp(cmd[0],h)==0)
{
	print_history();
	return 1;	
}
else 
{
	pid_t pid = fork(); //starting a new child to execute the command

	if (pid == -1) { 	//this means child process is not created
		printf("\nUnable to create the Fork command"); 
	} else if (pid == 0) { 
		int r=execvp(cmd[0], cmd); //execvp executes the command and r catches the result
		if (r< 0) { 
			printf("\ncommand not found");
		}//child process execution
		exit(r);  // child process termination
	} else { 
		int p; //parent process execution
		wait(&p); //catching the exit value returned by child process and waiting for child process to terminate
		p=255-p/255;
		if(p>=0)
		{
		add_status('y'); //adding status to history
		}
	} 
	return 0;
}
} 

int main() 
{ 
	char command[3000], *command_arg[300],e[30];
	int x; 
	int day,mon,year,hour,min,sec;
	time_t now;
	struct tm * time_pointer;
	time(&now);
	time_pointer = localtime(&now);
	while(1)
	{
		scanf("%[^\n]%*c",e);
		if(strcmp(e,"Entry")==0)
			x=1;
		else if(strcmp(e,"exit")==0)
			x=2;
		else x=0;
		switch (x)
		{
		case 1:	
			day=time_pointer->tm_mday;
			mon=time_pointer->tm_mon;
			year=time_pointer->tm_year+1900;
			hour=time_pointer->tm_hour;
			min=time_pointer->tm_min;
			sec=time_pointer->tm_sec;
			//history(buf,day,mon,year,hour,min,sec);
			history("Entry",day,mon,year,hour,min,sec);
			add_status('y');
			init_shell();
			while (1) { 
				cursor();	//directory your working in
				if (reading_command(command)) 	//takes the input
						continue; 		//if no input
				char *c=command;
				parsing(c,command_arg);
				int r=mycmdparser(command_arg);
				if(r == -1)
				{
					printf("Command line interpreter is stopped\n");
					add_status('y');
					break;
				}
				else if(r == 1)
				{		
					add_status('y');
				}
				else if(r== 0)
				{
				}
				
				else{
					printf("command not found\n");
				}
				
			} 
			break;
		case 2:
			exit(0);
			break;
		default:
			printf("Type Entry to enter into the shell\n");
		}
	}
	return 0; 
} 


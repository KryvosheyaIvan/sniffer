#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

const char* strHelp = 	"\t\t\t\t SNIFFER \n "
					   	" This is sniffer, saving IP addresses of incoming packets and number of packets from each IP.\n";
						  

/* Options that cli understands */
const char* options[] = 
{
	"start",
	"stop",
	"show",
	"select",
	"stat",
	"--help"
};

/* Handlers for options */
int start_hndlr(char** args);
int stop_hndlr(char** args);
int show_hndlr(char** args);
int selectIface_hndlr(char** args);
int stat_hndlr(char** args);
int help_hndlr(char** args);

/* returns number of handlers */
int numOfHndlrs(void);

/* Function returns pid of sniffer daemon */
int getDaemonPID(void);

/* Array of pointers to handlers */
int (*func_ptr[])(char**) = {
	&start_hndlr,
	&stop_hndlr,
	&show_hndlr,
	&selectIface_hndlr,
	&stat_hndlr,
	&help_hndlr,
};

int main(int argc, char* argv[])
{
	if(argc < 2) {
		printf("Please, enter command for sniffer. \n");
	}
	
	for(int i = 0; i < numOfHndlrs(); i++) {
		if(strcmp(argv[1],options[i]) == 0) {
			return (*func_ptr[i])(argv);
		}
	}
	
	exit(0);
}


/* Handlers for options */
int start_hndlr(char **args) {
	printf("start_hndlr \n");
	
	execvp("./daemon", args);
	
	return 0;
}

int stop_hndlr(char **args) {
	printf("stop_hndlr \n");
	char deb[100];
	
	int pid_to_kill = getDaemonPID();
	sprintf(deb,"ska: %d", pid_to_kill);
	printf("%s",deb);
	
	
	if(pid_to_kill != -1) {
		printf("kill! \n");
		kill(pid_to_kill,SIGINT);
	}
	
	return 0;
}

int show_hndlr(char** args) {
	printf("show_hndlr \n");
	return 0;
}

int selectIface_hndlr(char** args) {
	printf("selectIface_hndlr \n");
	return 0;
}

int stat_hndlr(char **args) {
	printf("stat_hndlr \n");
	return 0;
}

int help_hndlr(char **args) {
	printf("help_hndlr \n");
	printf("%s", strHelp);
	return 0;
}

/* returns number of handlers */
int numOfHndlrs(void) {
	return (sizeof(options) / sizeof(char*));	
}

/* Function returns pid of sniffer daemon */
int getDaemonPID(void) {

	int pid = -1;
	FILE* pid_file = fopen("/var/lib/sniffer/pid","w+");
	if(pid_file != NULL)
	{
		fscanf(pid_file,"%d",&pid);
	}
	
	return pid;
	
}







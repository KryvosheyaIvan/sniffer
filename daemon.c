#include <stdio.h>
#include <stdlib.h>		// exit
#include <sys/types.h>	//fork
#include <sys/stat.h>	//umask
#include <unistd.h>		//fork setsid
#include <syslog.h>
#include <signal.h>

#define SNIFF_PID_PATH "/var/lib/sniffer/pid.txt"

void sigInt_hdlr(int sig)
{
	/* Get own pid */
	pid_t myPID = getpid();
	syslog(LOG_INFO, "sniffer killed");
	kill(myPID,SIGKILL);
	//stop daemon
}

int main(int argc,char* argv[])
{
	/* Declare file were pid will be stored */
	FILE* pid_file = NULL;
	
	pid_t pid,sid;
	
	/* For of the parent process */
	pid = fork();
	
	/* Fork error */
	if( pid < 0 ) {
		exit(EXIT_FAILURE);
	}
	/* Succes. Exit parent process */
	if ( pid > 0) {
		exit(EXIT_SUCCESS);
	}
	
	/* Change file mode mask */
	umask(0);
	
	/* Start logging */
	openlog("kryvosheia_sniffer", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
	syslog(LOG_INFO, "sniffer launched with PID: %d", getpid());
	
	/* Create unique session ID (SID) */
	sid = setsid();
	if ( sid < 0) {
		/*Error*/
		exit(EXIT_FAILURE);
	}
	
	pid_file = fopen(SNIFF_PID_PATH,"w+");
	fprintf(pid_file,"%d", getpid());	
	fclose(pid_file);
	
	/* Close out standard file descriptors */
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	
	(void) signal(SIGINT, sigInt_hdlr);
	
	while(1)
	{
		sleep(30);
	}

	return 0;
}

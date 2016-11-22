/****************************
 * Scott Cooper 
 * cs 344 - smallsh
 * small shell written in C that will support exit, 
 * cd, and status
 * ***************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>    //for struct sigaction

#define MAX_ARGUM 512
#define MAX_LENGTH 2048

/********************
 * Checks to see the status of the background
 * processes.
 * ********************/
void checkBackgroundStatus()
{
	pid_t bgProcess = 0;
	int bgStatus;
	do{
		bgProcess = waitpid( -1, &bgStatus, WNOHANG);
		if( bgProcess > 0 )
		{
			if( WIFEXITED( bgStatus ) )
			{
				printf( "background pid %d is done: exit value %d\n", (int)bgProcess, WEXITSTATUS( bgStatus ) ); 
			}
			else if( WIFSIGNALED( bgStatus ) )
			{
				printf( "terminated by signal %d\n", WTERMSIG( bgStatus ) );
			}
		}

	}while( bgProcess > 0 );
}

/************************
 * Tries to run the commands sent to it. Has basic error
 * computing. Creates the start and exit pids. Loops through 
 * each argument and determines if they are valid or invalid
 * arguments.
 * * ********************/
void shellExe( char **commands, int numCom, struct sigaction *saCh, struct sigaction *sa, int *status)
{
	//set up variables
	pid_t startPid, exitPid;
	int bgProc = 0, in = -7, out = -7;
	int f1, f2;

	//check for if process should run in the background
	if( !strcmp( commands[numCom-1], "&" ) )
	{
		bgProc = 1;
		commands[numCom-1] = NULL;
	}

	startPid = fork();
	if( startPid == 0 )
	{
		if( bgProc != 1 )
		{
			sigaction( SIGINT, saCh, NULL );
		}

		// loop through each argument
		int argumentCount = 0;
		while( commands[argumentCount] != NULL )
		{
			if( !strcmp(commands[argumentCount], "<") ) {
				f1 = open( commands[argumentCount+1], O_RDONLY );
				if( f1 == -1 ) {
					perror( "cannot open badfile or input\n" );
					exit(1);
				}
				in = dup2(f1, 0);
				if(in == -1) {
					perror("dup2\n");
					exit(1);
				}
				commands[argumentCount] = NULL;

			}

			else if( !strcmp(commands[argumentCount], ">") ) 
			{
				f2 = open(commands[argumentCount+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if(f2 == -1) {
					perror("cannot open badfile or input\n");
					exit(1);
				}
				out = dup2(f2, 1);
				if(out == -1) {
					perror("dup2\n");
					exit(1);
				}
				commands[argumentCount] = NULL;
			}
			argumentCount++;

		}//while

		// execute the commands	
		execvp( commands[0], commands );
		perror( commands[0] );
		exit(1);
	}// !startPid
	else if( startPid > 0 )
	{
		if( bgProc == 1)
		{
			printf( "background pid is %d\n", startPid );
		}
		else
		{
			exitPid = waitpid( startPid, status, 0 );
			if( ( exitPid > 0 ) && WIFSIGNALED( *status ) )
			{
				printf( "terminated by signalPP %d\n", WTERMSIG( *status ), exitPid );

			}
		}

	} // startPid > 0
	else
	{
		printf( "process failed\n" );
	}

	checkBackgroundStatus();
}


/*********************
 * Gets the unput from the user and checks to see if it is a valid 
 * argument. Runs cd, and status, but sends anything else to the 
 * shellExe method. Has basic error returning. 
 * *******************/
void shellLoop()
{
	// variable initiation
	int status = 0, cont = 1;
	int backgroundStatus;


	//For file I/O 
	FILE *in;
	FILE *out;	

	// Initalize the sigaction struct
	struct sigaction sa, saCh;
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;

	saCh.sa_handler = SIG_DFL; //for background processes
	sa.sa_flags = 0;
	sigaction( SIGINT, &sa, &saCh );

	do{
		
		int valid = 1;
		// Allocate memory
		char *commandBuff = malloc( MAX_LENGTH );
		char **commandArgum = malloc( MAX_ARGUM * sizeof( char* ) );
		//set memory to null
		//memset( commandArgum, 0, sizeof( commandArgum ) );
		int count = 0;
		for( ; count < MAX_ARGUM; count++ )
		{
			commandArgum[count] = NULL;
		}

		//check background status
		checkBackgroundStatus(); 

		// Get the line from user
		printf(": ");
		fflush( stdout );
		fgets( commandBuff, MAX_LENGTH, stdin );

		// is the line empty?
		if( commandBuff[0] == '\n' )
		{
			valid = 0;
		}

		// is line a comment?
		if( commandBuff[0] == '#' )
		{
			valid = 0;
		}

		// Split up the command
		if( valid == 1 )
		{
			int i = 0;
			char* temp;
			strtok( commandBuff, "\n" );
			temp = strtok( commandBuff, " \n" );
			while( temp != NULL && i <= MAX_ARGUM )
			{
				commandArgum[i] = temp;
				i++;
				temp = strtok( NULL, " \n" );
			}
		}

		// number of arguments
		int numOfArguments = 0;
		while( commandArgum[numOfArguments] != NULL )
		{ 
			numOfArguments++;
		}
//printf("valid: %d", valid );
//printf("\narg: %s", commandArgum[1] );
//printf("num of arguments1: %d\n", numOfArguments);

		// check for cd, status
		if( valid == 1 )
		{
			// exiting???
			if( !strcmp( commandArgum[0], "exit" ) )
			{
				cont = 0;
			}
			// check for cd as first part 
			else if( strcmp( commandArgum[0], "cd" ) == 0 )
			{
//printf("\nin cd: next ");				
//printf("%d", numOfArguments );
				// what is the next part?
				if( commandArgum[1] == NULL )
				{
					char *home = getenv("HOME");
					chdir( home );
				}
				else if( chdir( commandArgum[1] ) == -1 )
				{
					printf("no such directory\n" );
				}
			}
			else if( !strcmp( commandArgum[0], "status" ) ) 
			{
//printf("\nin status\n" );
				if( WIFEXITED( status) )
				{
					printf( "exit value %d\n", WEXITSTATUS( status ) );
				}
				else if( WIFSIGNALED( status ) )
				{
					printf( "termintated by signal %d\n", WTERMSIG( status ) );

				}
			}
			else
			{
//printf("numArguments: %d\n", numOfArguments);
				shellExe( commandArgum, numOfArguments, &saCh, &sa, &status );
			}
		}

		// free allocated memory
		free( commandBuff );
		free( commandArgum );
	}while( cont );
}


int main()
{
	shellLoop();
	return 0;
}


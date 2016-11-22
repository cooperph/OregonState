#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Room structure
struct Room 
{
    char name[30];                  // Room Name
    int numOfConnect;                // Number of Connections
    struct Room* connections[6];    // array of the connections to this room
    char roomType[15];                   // START_ROOM, MID_ROOM, END_ROOM
};


/******************************************** 
 * FUNCTION: ShuffleArray
 * Takes in an array and shuffles the contents
 * Help gotten from a post on Stack overflow
 * Originally used a single pointer array  
 * instead of a double pointer array 
 ******************************************/
void shuffleArray(char **array, int length)
{
	int i, randomNum;
	for (i = 0; i < length; i++)
	{
		randomNum = rand() % length;
		char *temp = array[i];
		array[i] = array[randomNum];
		array[randomNum] = temp;
	}
}

/******************************************** 
 * FUNCTION: MakeConnection
 * Connects two rooms and only allows for the 
 * max number of connections for each room
 ******************************************/
void makeConnection( struct Room *room1, struct Room *room2, int max )
{
    if( room1->numOfConnect < max && room2->numOfConnect < max )
    {
        room1->connections[room1->numOfConnect] = room2;
        room1->numOfConnect++;
        room2->connections[room2->numOfConnect] = room1;
        room2->numOfConnect++;
    }
}

/******************************************** 
 * FUNCTION: connectionExists
 * Takes in 2 rooms and determines if there
 * a connection already or not
 *   1 = has connection
 *   2 = no connection
 ******************************************/
int connectionExists( struct Room *room1, struct Room *room2 )
{
    int i;
    for( i = 0; i < room1->numOfConnect; i++ )
    {
        if( room1->connections[i] == room2 )
        {
            return 1;
        }
    }
    return 0;
}

/******************************************** 
 * FUNCTION: makeRoomFiles
 * takes a room and makes a file in the 
 * directory to be viewed later 
 ******************************************/
void makeRoomFiles( struct Room room, int roomNumber )
{
	FILE *file;
	char roomName[2];
	int i;
	sprintf(roomName, "%d", roomNumber );
	file = fopen(roomName, "w");
	
	if( file == NULL )
	{
		printf( "\nERROR opening file");
		exit(1);
	}
	fprintf( file, "ROOM NAME: %s\n", room.name );
	for( i = 0; i < room.numOfConnect; i++ )
	{
		fprintf( file, "Connection %d: %s\n", i + 1, room.connections[i]->name );
	}
	fprintf( file, "ROOM TYPE: %s\n", room.roomType );
	
	fclose(file);
	
}

/******************************************** 
 * FUNCTION: makeDirectory
 * takes in a pid and creates a directory with 
 * name including pid. Once made it will change 
 * the current directory to directory name
 ******************************************/
void makeDirectory( int pid )
{
	char name[50];
	sprintf( name, "cooperph.rooms.%i", pid );
	if( mkdir( name, 0775) )
	{
		printf( "ERROR making directory");
		exit(1);
	}
	chdir(name);
	//return;
}


int main() {
	// initiate the RNG (roll those dice baby!)
	srand(time(NULL));
	
	char *rooms[] = { "Lumpy Space", "Tree Fort", "Fire Kingdom", "Pillow World", "Cotton Candy Forest", "Lady Rainicorn's House", "Marceline's Cave", "Candy Kingdom", "BMO's Play Room", "Cloud Kingdom" };
	struct Room gameBoard[7];
	int numRooms = 10, gameRooms = 7, maxConnections = 6, minConnections = 3;
	int totalConnections, randomNum, compName, cExist;
	int i = 0, pid = getpid();
	
	makeDirectory( pid );
	shuffleArray( rooms, numRooms );
	
/*	for( ; i < numRooms; i++ )
	{
	    printf("%s\n", rooms[i]);
  	}*/ 
	
	// place the first 7 rooms after the shuffle into the gameboard
	// and assign the rooms their roomType value
	// 0 - start,   1 - middle,   2 - final
	for(i = 0; i < gameRooms; i++)
	{
	    strcpy( gameBoard[i].name, rooms[i] );
	}
	
    // make the start, middle, and end room assignments
    for( i = 0; i < gameRooms; i++ )
    {
        if( i == 0 )
	    {
	        strcpy( gameBoard[i].roomType, "START_ROOM" );
	    }
	    else if( i > 0 && i < gameRooms - 1 )
	    {
	        strcpy( gameBoard[i].roomType, "MID_ROOM" );
	    }
	    else 
	    {
	        strcpy( gameBoard[i].roomType, "END_ROOM" );
	    }
	    gameBoard[i].numOfConnect = 0;
    }
  
/*	printf( "\nGame Board\n");
	for( i = 0; i < gameRooms; i++ )
	{
	    printf("%s", gameBoard[i].name);
	    printf("\t\t%i\n", gameBoard[i].numOfConnect);
	}*/
  
// make connections
    for ( i = 0; i < gameRooms; i++ )
    {
        totalConnections = rand() % 4 + 3;
        while( gameBoard[i].numOfConnect < totalConnections )
        {
            randomNum = rand() % gameRooms; // 
            compName = strcmp( gameBoard[i].name, gameBoard[randomNum].name);
            cExist = connectionExists( &gameBoard[i], &gameBoard[randomNum] );
            
            if( compName != 0 && !cExist )
            {
                makeConnection( &gameBoard[i], &gameBoard[randomNum], maxConnections);
            }
        }
    }
	
	for( i = 0; i < gameRooms; i++ )
	{
		makeRoomFiles( gameBoard[i], i+1 );
	}
	
// play game
	int steps = 0, continueGame = 1, currentRoom = 0;
	char word[50];
	char *path[30];
for (i = 0; i < 30; i++)
	{
		path[i] = (char *) malloc(64);
	}
	
// while loop to go through the program
// if( ! strcmp( r.roomType, "END_ROOM) ) - end game
// else print location/ connections/ where to
// 	check to see if connection exists
// 	yes - go to next place and steps++, no - error message and start over
	while( continueGame )
	{
		int valid = 0;

		printf("\nCURRENT LOCATION: %s", gameBoard[currentRoom].name );
		printf("\nPossible Connections: ");
		for( i = 0; i < gameBoard[currentRoom].numOfConnect; i++ )
		{
			printf(" %s,", gameBoard[currentRoom].connections[i]->name );

 		}
		printf("\nWHERE TO? >");
		fflush(stdout);
		fgets(word, sizeof(word), stdin);
		strtok( word, "\n");

		for( i = 0; i < gameBoard[currentRoom].numOfConnect; i++ )
		{
			if( !strcmp( gameBoard[currentRoom].connections[i]->name, word) )
			{
				valid = 1;
			}
		}
//printf("valid = %i", valid);
		if( valid )
		{
			for( i = 0; i < 7; i++ )
			{
				if( !strcmp( gameBoard[i].name, word ) )
				{
					currentRoom = i;
				}
			} 
			strcpy( path[steps], word );
			steps++;
		}
		else
		{
			printf("\nHUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.\n");
		}
		
		if( !strcmp( gameBoard[currentRoom].roomType, "END_ROOM" ) )
       		{
               		continueGame = 0;
        	}

	}

// End the Game
	printf("\nYOU HAVE FOUND THE END ROOM. CONGRATULATIONS!");
	printf("\nYOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:", steps);
	for( i = 0; i < steps; i++ )
	{
		printf(" \n%s", path[i] );
	}
	printf( "\n$\n" );
/*	printf( "\nGame Board\n");
	for( i = 0; i < gameRooms; i++ )
	{
	    printf("%s", gameBoard[i].name);
	    printf("\t\t%i\n", gameBoard[i].numOfConnect);
	}
	
	printf("\n1st room connections\n");
	for( i = 0; i < gameBoard[0].numOfConnect; i++ )
	{
		printf( "connection%i: %s\n", i, gameBoard[0].connections[i]);
	}
*/	
	
	return 0;
}


/**
	Written by: Brent Daniels-Soles
*/
#include "cls.h"

int main(int argc, char ** argv)
{

	char dir[500];

	//Gets the current directory
	getcwd(dir, 500);
	
	//Stores char number of arg
	int optret;
	opterr = 0;

	while( (optret = getopt(argc, argv, "lR")) != -1)
	{
		
		//Switch for what args you made
		switch(optret)
		{
			case 'l':
//				printf("You threw an 'l' flag\n");
				lArgPrint(dir);
				break;
			case 'R':
				RArgPrint(dir, 0);
//				printf("You threw an 'R' flag\n");
				break;
			case 'd':
				printf("Your directory is: %s\n", dir);
				break;
			case '?':
				printf("Command not recognized\n");
				break;
			default:
				printf("Usage: ./cls <args>\n");
				printf("Valid args: -l -R -d\n");
				break;
		}

	}

	//if no args then print list
	if(argc == 1)
	{
		defaultPrint(dir);
	}

	return 0;
}



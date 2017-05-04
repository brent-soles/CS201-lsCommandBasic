/**
	Written by: Brent Daniels-Soles
*/

#include "cls.h"

//Function to print the current directory files
//	@param1: String (current directory)
void defaultPrint(char * currdir)
{
	//checks validity of current directory
	if(!currdir)
	{
		printf("Directory Unable to Initialize\n");
		return;
	}
	
	//Struct to store directory entries
	struct dirent ** files;
	int verify;

	verify = scandir(currdir, &files, 0, alphasort);
	if(verify == 0)
	{
		printf("FAIL\n");
	}

	//Prints out the directory files (not . or ..)
	int i;
	for(i = 0; i < verify; ++i)
	{
		if( (strcmp(files[i]->d_name, ".")) != 0 && (strcmp(files[i]->d_name, "..")) != 0)
		{
			printf("%s\t", files[i]->d_name);
		}
	}

	printf("\n");	

	for(i = 0; i < verify; ++i)
	{
		free(files[i]);
	}

	free(files);
}

//Prints the long formatted directory
//	@param: current directory name
void lArgPrint(char * currdir)
{

	//Getting user name
	char * user = getlogin();
	if(!user)
	{
		printf("User not defined\n");
		return;
	}	


	if(!currdir)
	{
		printf("Directory Unable to Initialize\n");
		return;
	}

	//Directory entries struct
	struct dirent ** files;
	int verify;

	//Get the directory files
	//Stores them in &files struct
	verify = scandir(currdir, &files, 0, alphasort);
	if(verify == -1)
	{
		printf("Fatal Error 1\n");
		return;
	}

	//Number of memory blocks used
	int blocks = 0;
	
	//Computes number of blocks taken up
	int j;
	for(j = 0; j < verify; ++j)
	{
		

		struct stat temp;
		char t_string[256];
		realpath(currdir, t_string);
		strcat(t_string, "/");
		strcat(t_string, files[j]->d_name);
		if( (stat(t_string, &temp)) == -1 ) 
		{
			printf("Fatal Error 2\n");
			return;
		}
		
		blocks += temp.st_blocks;
	}

	//Print blocks as well as labels	
	printf("Total: %d\n", blocks);
	printf("Permissions\tLinks\tUser\tGroup\tSize\tD.O.M\t\t\t\tName\n");

	int i;
	for(i =0; i < verify; ++i)
	{
		//Dont't include . or ..
		if( (int)(strcmp(files[i]->d_name, ".")) != 0 && (int)(strcmp(files[i]->d_name, "..")) != 0 )
		{
			
			//Gets the full path to file
			char fullpath[256];
			realpath(currdir, fullpath);
			strcat(fullpath, "/");
			strcat(fullpath, files[i]->d_name);

			//Gets stats of current directory
			struct stat statbuf;
			stat(fullpath, &statbuf);

			//Prints the permissions or prints a dash
			printf( (S_ISDIR(statbuf.st_mode) ? "d" : "-") );
			printf( (statbuf.st_mode & S_IRUSR) ? "r" : "-");
			printf( (statbuf.st_mode & S_IWUSR) ? "w" : "-");
			printf( (statbuf.st_mode & S_IXUSR) ? "x" : "-");
			printf( (statbuf.st_mode & S_IRGRP) ? "r" : "-");
			printf( (statbuf.st_mode & S_IWGRP) ? "w" : "-");
			printf( (statbuf.st_mode & S_IXGRP) ? "x" : "-");
			printf( (statbuf.st_mode & S_IROTH) ? "r" : "-");
			printf( (statbuf.st_mode & S_IWOTH) ? "w" : "-");
			printf( (statbuf.st_mode & S_IXOTH) ? "x" : "-");

			//Prints the number of links
			//CAST WAS ADDED
			printf("\t%d", (int)statbuf.st_nlink);
		
			//Prints the user name
			printf("\t%s", user); 
	
			//Gets group Name			
			struct group * grp;
			grp = getgrgid(statbuf.st_gid);

			//Prints the group user belongs to
			printf("\t%s", grp->gr_name);			

			//Prints the size of the file
			//Cast was added
			printf("\t%d", (int)statbuf.st_size);
			
			//Gets the time
			struct tm * lastEdit;
			lastEdit = localtime(&statbuf.st_mtime);
				
			//Gets localized date
			char date[256];
			strftime(date, 256, nl_langinfo(D_T_FMT), lastEdit);

			//Prints the last edit
			printf("\t%s", date);		

			//Prints the name of the file
			printf("\t%s\n", files[i]->d_name);					
			

		}	
	}


	for(i = 0; i < verify; ++i)
	{
		free(files[i]);
	}
	
	free(files);
}

//Recursively list subdirectories and files
//	@param: current directory
//	@param: number of files
void RArgPrint(char * currdir)
{

	struct dirent ** files;
	int numfiles = scandir(currdir, &files, 0, alphasort);

	if(numfiles == -1)
	{
		printf("Fatal Error 3\n");
		return;
	}

	printf("%s:\n", currdir);

	int i;

	for(i = 0; i < numfiles; ++i)
	{
		printf("%s  ", files[i]->d_name);
	}

	printf("\n\n");

	for(i = 0; i < numfiles; ++i)
	{

		char fullpath[256];
//		printf("FPI: %s\n", fullpath);
		strcpy(fullpath, currdir);
		strcat(fullpath, "/");
		strcat(fullpath, files[i]->d_name);

//		printf("F: %s\n", fullpath);		
		
		struct stat statpath;
		stat(fullpath, &statpath);

		if( (strcmp(files[i]->d_name, ".")) != 0 && (strcmp(files[i]->d_name, "..")) != 0 )
		{
			if( (S_ISDIR(statpath.st_mode)) != 0 )
			{
//				printf("REC CALLED\n");
				printf("%s: ", files[i]->d_name);
				RArgPrint(fullpath);
				printf("\n");
			}
			else
			{
//				printf("%s ", files[i]->d_name);
			}
		}
		
//		printf("\n");
	}

	for(i = 0; i < numfiles; ++i)
	{
		free(files[i]);
	}
	
	free(files);

}








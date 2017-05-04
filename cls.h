/**
	Written by: Brent Daniels-Soles
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <grp.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <dirent.h>
#include <time.h>
#include <langinfo.h>
#include <string.h>


#define INITSTR "----------"

//Prints with no args
void defaultPrint(char*);

//Prints the long formatted
void lArgPrint(char*);

//Prints the recursive 
void RargPrint(char*, int);


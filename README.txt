**************************************************
**************************************************
		OPSYS_PROJ1
**************************************************
**************************************************


**************************************************
		    MEMBERS
**************************************************

Member 1: Dillon Prendergast
Member 2: Zachary Timmerman

**************************************************
		DIVISION OF LABOR
**************************************************

Dillon Prendergast
  -README
  -prompt
  -user-input
  -input-parsing
  -expansion of evironment variables
  -exit command
  -echo command

Zachary Timmerman
  -Path resolution
  -piping
  -makefie

**************************************************
		TAR ARCHIVE CONTENTS
**************************************************

project1_prendergast_timmerman.tar contents:

README.md
makefile
proj1.c //main program with implemented functions

**************************************************
		   COMPILATION
**************************************************

Completed Using:
Ubuntu Linux 4.13.0-32-generic
gcc version 5.4.0

**************************************************
		   THE MAKEFILE
**************************************************

To build:
$> make dzshell

To run:
$> ./dzshell

To clean:
$> make clean

**************************************************
		      BUGS
**************************************************

-Seg fault when two 'special characters' are
 entered consecutively w/o spaces.
 Appears to go out of index range when adding a
 space after second character, but cannot find
 why it only occurs with consecutive characters.

**************************************************
		UNFINISHED PORTIONS
**************************************************

-implement path resolution
-i/o redirection
-implement pipes
-background processing
-finish built ins

**************************************************
		     COMMENTS
**************************************************

-'$' character is output preceding a variable
 with the echo command

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

Zachary Timmerman
  -Path resolution
  -makefie

**************************************************
		TAR ARCHIVE CONTENTS
**************************************************

project1_prendergast_timmerman.tar contents:

README.md
makefile
proj1.c //implementation and functions

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

-Finish path resolution
-i/o redirection
-pipes
-background processing
-built ins

**************************************************
		     COMMENTS
**************************************************

-

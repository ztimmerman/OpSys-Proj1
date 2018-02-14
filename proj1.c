/*Dillon Prendergast
Operating Systems
Project 1- Shell
*/


/***********************INLUDED APIS****************/
#include <stdio.h>	//io
#include <string.h>	//c-strings
#include <stdlib.h>	//memcpy,memmove
#include <unistd.h>	//gethostname
#include <sys/types.h>	//fork
#include <sys/wait.h>	//wait
#include <dirent.h> 	//for directory entry search


/***********************CONSTANTS*********************/
#define BUFFER 255

/****************FUNCTIONS****************************/
void my_setup();
void my_prompt();
char *my_read();
char **my_parse(char *line,char **cmd);
char *parse_whitespace(char *line);
char **parse_arguments(char *line,char **cmd);
char **expand_variables(char **cmd);
char **expand_cmd(char **cmd);
void my_execute(char **cmd);
void my_clean(char *line,char **cmd);


int fileExists(const char * directory, const char * ourFile);

/*****************GLOBAL/ENVIRONMENT VAR*************/
char *MACHINE;
int done;
int badcmd;
/*********************MAIN FUNCT**********************/
int main(){

  char *line;
  char **cmd;

  while(1){

    my_setup();			//setup
    my_prompt();		//print propmt
    line=my_read();		//read input
				
				//Transform input
    cmd=my_parse(line,cmd);	
				//match patterns
    if(badcmd!=1)
      my_execute(cmd);		//execute command

    my_clean(line,cmd);			//print results
    
    if(done==1||badcmd==1)
	break;
				//cleanup
  }

    return 0;
}

/***********************SETUP FUNCT***********************/
//Set up environmental variables
void my_setup(){

  MACHINE=getenv("MACHINE");
  if(MACHINE==NULL){
	MACHINE=calloc(BUFFER,sizeof(char));
	gethostname(MACHINE,BUFFER);
  }			//allows proper prompt on Linux machines

}

/*******************PROMPT FUNCT***************************/
//Prints out the standard USER@MACHINE :: PWD prompt
void my_prompt(){
				//format found in Proj1.pdf
  printf("%s@%s :: %s =>",getenv("USER"),MACHINE,getenv("PWD"));
}


/*********************READ FUNCT*****************************/
//reads in user inputs command line
char *my_read(){

  int bufsize=BUFFER;
  char *input=calloc(bufsize,sizeof(char));

  fgets(input,bufsize,stdin);		//'\0' added in parse_white	
  return input;				//must free later
}


/*********************PARSE FUNCT****************************/
//Parses the user input, fixing format and breaking up arguments
char **my_parse(char *line,char **cmd){


  line=parse_whitespace(line);
  cmd=parse_arguments(line,cmd);

  cmd=expand_variables(cmd);
  cmd=expand_cmd(cmd);
  return cmd;
}


/*******************PARSE_WHITESPACE FUNCT*******************/
//distributes and deltes whitespace in the user input
char *parse_whitespace(char *line){
  int bufsize=BUFFER;
  int index=0;

  while(1){

    if(index==0){		//remove leading whitespace
      if(line[index]==' '){
        strncpy(line,&line[1],bufsize);
        continue;
      }
    }

    if(line[index]==' ' && (line[index+1]==' '||line[index+1]=='\t')){
      memmove(&line[index],&line[index+1],strlen(line)-index);
      continue;
    }
    else if(line[index]=='\t'){	//remove multiple whitespace
      line[index]=' ';
      continue;
    }

    else if(line[index]=='\n'){
      line[index]='\0';		//Adds terminating character to str
      continue;
    }
    else if(line[index]=='\0'){

      if(line[index-1]==' '){	//Removes trailing whitespace
	line[index-1]='\0';
	continue;
      }
	return line;
    }				//spaces around special char
    else if(line[index]=='|'||line[index]=='<'||line[index]=='>'
	||line[index]=='&'||line[index]=='$'||line[index]=='~'){

      if(index!=0 && line[index-1]!=' '){
	memmove(&line[index+1],&line[index],strlen(line)-index);
	line[index]=' ';
	continue;
      }
      if(line[index+1]!=' '){
       memmove(&line[index+2],&line[index+1],strlen(line)-index-2);
       line[index+1]=' ';
       continue;
      }
    }
			
    index++;
  }
}


/*********************PARSE_ARGUMENTS FUNCT*********************/
//create argument tokens by spaces, each is ended with '\0'
char **parse_arguments(char *line,char **cmd){

   int size=BUFFER;
   int index=0,start=0,end=0;

   cmd=calloc(size, sizeof(char *));
   
   for(int i=0;i<size;i++){
	cmd[i]=calloc(size,sizeof(char));
   }

   while(1){
			
     if(line[start]==' '){
	start++;
	continue;
     }
				//finds start/end of each arg
     for(int i=start;i<strlen(line);end=++i){
	if(line[i]==' '){
	  break;
	}
     }
				//copies arg into bucket
     memcpy(cmd[index],&line[start],(end-start));
     cmd[index][end-start]='\0';

     start=end;
     index++;

     if(line[index]=='\0'){
	return cmd;
     }
   }
}


/***********EXPAND VARIABLES FUNCT**********************/
//turns envvar into the envvar values
//**WARNING**
//IF THE VARIABLE IS INVALID, THE BUCKET IN CMD ARRAY
//BECOMES A NULL PTR
char **expand_variables(char **cmd){

  int size=BUFFER;

  for(int i=0;i<BUFFER;i++){	//runs through cmd array

    if(cmd[i]==NULL)		//invalid variable
	continue;

    if(cmd[i][0]=='\0'){	//stops at first empty string
      break;
    }
    
    if(cmd[i][0]=='$'){		//variables signaled by leading $
      cmd[i+1]=getenv(cmd[i+1]);//cuts off leading $ and gets env
    }
  }
  return cmd;
}
/**********************EXPAND CMD*********************/
//Expands commands into the path in the /bin directory
//Outputs error on false command
char **expand_cmd(char **cmd){
  int size=BUFFER;

  for(int i=0;i<size;i++){
    if(cmd[i]==NULL)		//NULL is from invalid variables
	continue;
    else if(cmd[i][0]=='\0'){	//ends on last argument
      break;
    }				//commands are found at the start,
    else{			//after pipes, or after '&'
      if(i==0||(cmd[i-1]!=NULL&&(cmd[i-1][0]=='|'||
       cmd[i-1][0]=='&'))){

	if(fileExists("/bin/",cmd[i])>=0){
	  char comm[size];
	  strcpy(comm,"/bin/");
          strcat(comm,cmd[i]);
	  strcpy(cmd[i],comm);
	}
	else{
	  if(strcmp(cmd[i],"exit")!=0){	
	    printf("%s: command not found\n",cmd[i]);
	    badcmd=1;
	  }
	  done=1;
	  return cmd;
	}
      }
    }
  }
  return cmd;
}


/*****************EXECUTE FUNCT**************************/
//
void my_execute(char **cmd){
 int size=BUFFER;
 int index=0;
 int status;

  if(done==1){
    pid_t pid=fork();

    if(pid==0){
	printf("Exiting Shell....\n");
	exit(0);
    }
    else{
	waitpid(pid,&status,0);
	return;
    }
  }
  
  for (int i=0;i<size;i++){
    if(strcmp(cmd[i],"/bin/echo")==0){
	pid_t pid=fork();
	if(pid==0){
	  for(int j=i;j<size;j++){
		if(cmd[j]==NULL){
		 printf("Invalid variable\n");
		 exit(0);
		}				//concatenates NULL
		else if(cmd[j][0]=='\0'){
		 cmd[j]=NULL;			//on end of execv argument
		}
	  }
	  execv(cmd[i],&cmd[i]);
	  exit(0);
	}
	else{
	  waitpid(pid,&status,0);
	  break;
	}
    }
  }
//} //end of while
  //Match against patterns
  //Execute based on pattern
  //Print results
}


/***********************CLEAN FUNCT***********************/
//frees allocated variables
void my_clean(char *line,char **cmd){

   int size=BUFFER;

   free(line);			//frees user input

   for(int i=0;i<size;i++){
				//frees cmd array buckets
     if(cmd[i]!=NULL && cmd[i][0]=='$'){
			
	free(cmd[i]);		
        if(cmd[i+1]!=NULL && cmd[i+1][0]!='\0'){
	  i++;		//indexes after a '$' are expanded
	}		//variable. These are found by
	continue;	//getenv, which does not need free
     }			//Invalid ouputs (NULL) must be freed
     free(cmd[i]);
   }
   free(cmd);


  if(getenv("MACHINE")==NULL)	//for non cs-machines
	free(MACHINE);

};

int fileExists(const char * directory, const char * ourFile) {
 DIR *dir;
 struct dirent *ent;
 int counter = 0;
 if ((dir = opendir (directory)) != NULL) {
   /* print all the files and directories within directory */
   while ((ent = readdir (dir)) != NULL) {
//      printf ("%s\n", ent->d_name);
    if (strcmp(ent->d_name,ourFile) == 0)	{
      closedir (dir);
      return counter;
    }  else  {
      counter++;
    }
   }
   closedir (dir);
   return -2;
 } else {
   /* could not open directory */
//    perror ("");
   return -1;
 }
}

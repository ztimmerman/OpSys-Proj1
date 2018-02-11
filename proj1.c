/*Dillon Prendergast
Operating Systems
Project 1- Bash
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER 255
#define ARGUMENTS 50
#define ARG_SIZE 25

void my_setup();
void my_prompt();
char *my_read();
char **my_parse(char *line,char **cmd);
char *parse_whitespace(char *line);
char **parse_arguments(char *line,char **cmd);
void my_execute(char **cmd);
void my_clean();

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
    my_execute(cmd);		//execute command
    my_clean();			//print results
				//cleanup
  }

    return 0;
}

void my_setup(){}

void my_prompt(){
  printf("bash-shell$");	//Needs to be changed to 
				//format found in Proj1.pdf
}

char *my_read(){

  int bufsize=BUFFER;
  char *input=calloc(bufsize,sizeof(char));

  fgets(input,bufsize,stdin);		//'\0' added in parse_white	
  return input;				//must free later
}

char **my_parse(char *line,char **cmd){


  line=parse_whitespace(line);
  cmd=parse_arguments(line,cmd);
//  cmd=expand_variables(cmd);
//  cmd=resolve_paths(cmd);

  return cmd;
}


char *parse_whitespace(char *line){
  int bufsize=BUFFER;
  int index=0;

  //char *copy=calloc(bufsize,sizeof(char));

  while(1){

    if(index==0){		//remove leading whitespace
      if(line[index]==' '){
        strncpy(line,&line[1],bufsize);
        continue;
      }
    }

    if(line[index]==' ' && (line[index+1]==' '||line[index+1]=='\t')){
      memmove(&line[index],&line[index+1],strlen(line)-index);
     // strncpy(line,line[index+1],bufsize);
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

      if(line[index-1]!=' '){
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

//create tokens by spaces, each is ended with '\0'
char **parse_arguments(char *line,char **cmd){

   int size=BUFFER;
   int index=0,end=0;
				//allocate possibility of 255
				//chars with one char btwn space
   cmd=calloc(size, sizeof(char *));
   
   for(int i=0;i<size;i++){
	cmd[i]=calloc(size,sizeof(char));
   }

   while(1){
				//separate by spaces
     if(line[index]==' '){
	index++;
	continue;
     }
     for(int i=index;i<strlen(line)-index;end=++i){
	if(line[i]==' '){
	  break;
	}
     }

     memcpy(cmd[index],&line[index],strlen(line)-(end-index));
     cmd[index][end-index]='\0';

     index=end;

     if(line[index]=='\0')
	return cmd;
   }
}

void my_execute(char **cmd){
  //Match against patterns
  //Execute based on pattern
  //Print results
}

void my_clean(){}

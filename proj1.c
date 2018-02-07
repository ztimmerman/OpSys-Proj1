/*Dillon Prendergast
Operating Systems
Project 1- Bash
*/

#include <stdio.h>
#include <string.h>

#define BUFFER 255

void my_setup();
void my_prompt();
char *my_read();
char **my_parse(char *line);
char *parse_whitespace(char *line);
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
    cmd=my_parse(line);		//match patterns
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

char **my_parse(char *line){

  char  **args;

  line=parse_whitespace(line);
  args=parse_arguments(parsed);
  args=expand_variables(args);
  args=resolve_paths(args);

  return cmd;
}


char *parse_whitespace(char *line){
  int bufsize=BUFFER;
  int index=0;

  //char *copy=calloc(bufsize,sizeof(char));

  while(1){

    if(index==0){		//remove leading whitespace
      if(line[index]==' '){
        strncpy(line,line[1],bufsize);
        break;
      }
    }

    if(line[index]==' ' && (line[index+1]==' '||line[index+1]=='\t')){
      strncpy(line,line[index+1],bufsize);
      break;
    }
    else if(line[index]=='\t'){	//remove multiple whitespace
      line[index]=' ';
      break;
    }

    if(line[index]=='\n'){
      line[index]='\0';		//Adds terminating character to str
      break;
    }
    if(line[index]=='\0'){

      if(line[index-1]==' '){	//Removes trailing whitespace
	line[index-1]='\0';
	break;
      }
    }
				//Add special characters
  }
}

void my_execute(char **cmd){
  //Match against patterns
  //Execute based on pattern
  //Print results
}

void my_clean(){}

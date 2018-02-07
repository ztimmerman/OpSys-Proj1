/*Dillon Prendergast
Operating Systems
Project 1- Bash
*/

#include <stdio.h>

#define BUFFER 255

void my_setup();
void my_prompt();
char *my_read();
char **my_parse(char *line);
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
  printf("bash-shell$");	//Not sure if more needed
}

char *my_read(){

  int bufsize=BUFFER;
  int position=0;
  char *input=calloc(bufsize,sizeof(char));

  fgets(input,bufsize,stdin);		//No '\0' yet...

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

void my_execute(char **cmd){
  //Match against patterns
  //Execute based on pattern
  //Print results
}

void my_clean(){}

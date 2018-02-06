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
  printf("bash$");
}

char *my_read(){
  return NULL;
}

char **my_parse(char *line){
  return NULL;
}

void my_execute(char **cmd){
  //Match against patterns
  //Execute based on pattern
  //Print results
}

void my_clean(){}

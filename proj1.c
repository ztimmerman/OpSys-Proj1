/*Dillon Prendergast
Operating Systems
Project 1- Bash
*/

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

/*Dillon Prendergast
Operating Systems
Project 1- Bash
*/

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

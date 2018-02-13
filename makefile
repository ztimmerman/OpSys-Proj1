file_res.x:	file_res.c
	gcc -o file_res.x file_res.c

dzshell: proj1.c
	gcc -o dzshell proj1.c

clean:
	rm dzshell

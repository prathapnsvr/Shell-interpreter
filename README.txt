Name: Nandikolla srivijay ram Prathap
ID: 2019H1030559G
How to execute:
	Open the terminal and execute this commands
	STEP 1 :  Type gcc assign.c
	STEP 2: Type ./a.out
	STEP 3: Type Entry to enter into the shell
Files present:
	assign.c
	CD.txt
	PWD.txt
	FIND.txt
	History.txt
Functions used:
Void  __init__()
****this function starts the shell by clearing the terminal and displays the Menu of all the commands that can be executed and there syntax.****
Void History()
****This function takes the command name and all the time and date values when the command is called and stores it in a structure array History. This function help in storing the last 10 command history****
Void print_history()
****This functions prints data in history structure array whenever History command is called.****
Void add_status(char c)
****This function add the status of command whether it is executed successfully or not. If Yes it saves success to the History of that command or saves as fail.****
Int reading_ command(char *str)
****this function takes the command from the shell and add it time and date to its history,by default the status of every command is taken as fail and update it later when the command is executed successfully.****
 Void cursor()
****This function prints the cursor along with the present working directory to understands where we are executing the commands.****
Void MAN(char **cmd)
****this function takes the pointer to the parsed command and called when the command is MAN.This displays the manual text file of each command.****
int mycmdparser(char **cmd)
****This function takes the pointer to  the parsed command and executes the command.It compares the command with all the inbuild commands and execute the appropriate code.If it doesn’t match with any of the given inbuild commands it execute the command with execvp command and returns an integer value which tells the execution status of the command to the main function****
void parsing(char *c,char **parsedc)
****This function splits the input command into different strings and stores it in a string array pointer which can be further useful to execute them as a command as well as arguments to that command.****
Reference Links:
https://www.geeksforgeeks.org/making-linux-shell-c/
https://www.computerhope.com/issues/ch000773.htm
https://www.geeksforgeeks.org/structures-c/
https://stackoverflow.com/questions/12499745/pass-the-value-from-child-to-parent-process
https://www.geeksforgeeks.org/exec-family-of-functions-in-c/
	
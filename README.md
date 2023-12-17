## File split merge

A program that can either split a file into n slices or merge the n slices back into the original file

Licensed under the GPLv3

To build: 
- On unix based systems (GNU/Linux, macOS, BSD) 
    - run make in a terminal window
    - run ./fsm
- On windows:
    - Need access to gcc (typically provided with MinGW) 
        - If make is install then run make
            - May need to rename the executable to add .exe
        - Else you must run the following command inside of the src folder
            - gcc -o fsm.exe main.c fileSize.c mergefile.c splitfile.c
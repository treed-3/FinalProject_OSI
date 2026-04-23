Kyle:

\- Role: C programmer

\- Responsibility:

&#x09;- C libraries

&#x20;	- definition variables

&#x09;- typedef struct

&#x09;- disk

&#x09;- freeMap

&#x20;	- fileTable

&#x09;- newline from fgets input

&#x09;- format system call

&#x09;- findFileBlock()

&#x09;- findFreeBlock()

&#x09;- create system call

&#x09;- write system call

&#x09;- read system call

&#x09;- delete system call



Tyler:

* Role: C programmer
* Responsibility:

  * ls system call
  * menu
  * **main:**

    * cmd
    * command
    * arg
    * calling formatDisk()
    * two print statements of "Loading file table from disk" and "File table loaded successfully"
    * calling printMenu()
  * **created always-true while loop with:**

    * print statement of "Enter system call or exit: "
    * fgets
    * stripping newline
    * split of command and argument
    * created if statements of user input "format", "create", "Read", "write", "del", "ls", "exit"



Concept mapping:

* System and program system call concepts utilized
* I/O disks and storage
* File systems
* Memory Address (pointers)

Relevance from concepts to file system simulator program:

* Keeping track of memory by referencing different aspects of where the memory is allocated for certain program functions.
* Many system calls created such as "format", "write", "del", "read", "ls", "create"
* printf statements waiting for user input
* Blocks and initialization of the disk
* Resemblance of user interaction with the file system such as looping menus that allow the user to read and modify the disk pertaining to the file system.


fast4
==

Themes: POSIX threads, File I/O, performance optimization, hash tables,
file parsing

The program will output a list the twenty most frequently used word common
amongst all files provided. The list is produced in descending order of
appearance. It parses one file at a time using multiple threads as long
as the file is greater than 80 bytes in length, where it will use only one.
The results are stored in a hash table, which is then fed into a linked-
list sorted by word count.
 
Clocked around .085s on average for 25 sample files (books from Project burg).

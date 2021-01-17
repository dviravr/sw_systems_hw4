# sw_systems_hw4

This reposotory was given as an assignment in a systems programming course at Ariel University.

The assignment was to read words from the standard input and print out the list of words that were seen in the input 
with the number of occurrences of each and every word. 
The list should be printed, depending on the parameter from the command line, in one
From the following ways:
* List sorted in ascending lexicographic order (default)
* List sorted in descending lexicographic order (by parameter).

### How to run the pogram

first you need to download the code from gitHub.
you can open the commad line in your computer and write:
```git clone https://github.com/dviravr/sw_systems_hw4.git```

after that you need to compile the pogram. 
we make for this make file so yoy can writr in your command line 
``` make```

And finally you can run the program, you have to ways to run the program: 
* `./frequency`
Print out the list of words seen in the input along with the number of occurrences for each word sorted in ascending lexicographic order.
* `./frequency r`
Print the list of words seen in the input along with the number of occurrences for each word sorted in descending lexicographic order

### **note:**
The program is designed to read text from a file, so it is recommended to prepare a file in advance and run with its help. In this case, the run bar will look like this:
`./frequency < file_you_want_to_run.txt`


@ DavidHarlap
@ dviravr

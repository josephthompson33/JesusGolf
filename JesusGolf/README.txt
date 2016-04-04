project3
joseph thompson

this program will ask the user to pick depth first search or breadth first search, and then search
a number of urls connected to the starting url given on the commandline

Known errors with program:
breadth first search only stops working when it encounters an error[3] malformed URL
depth first search will sometimes work, sometimes get caught in an infinite loop when searching 
for the next url to search, this happens when it is out of URLs. the program cannot take an invalid starting url. 

the main struggles i encountered with this project were logical errors pertaining to breadth first search
to start i did not make the graph correctly, had to add multiple counters and if statements. 
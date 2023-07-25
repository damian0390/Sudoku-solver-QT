# Sudoku-solver-QT
This is QT project that can help fill missing numbers in sudoku diagram.

After run the program, you will see an empty sudoku diagram. You can insert the known numbers into their positions and the program will automaticly complete numbers that can be deduced. The deduction proces uses two functions (algorithms):
- elimination - on the begining there are nine possible numbers you can insert into each position. after insertion the known number (x) into it's position (p) - the function eliminate x from possibilities in all positions in row, column and small square of p. When in one position remain only one possibility, the program insert the possibility into the position and run elimination function recursively.
- checking numbers - this function is checking in how many positions in row, column or small square one number can be inserted. when there is only one position, the program insert the number. The function is checking each number in each column, row ans small square. 

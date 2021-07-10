# Example of a ROOT fit using an external program

Compile the program that has to be used
```bash
g++ a_line_in_external_file.cpp -o a_line_in_external_file
```
This program takes x, m and q as arguments and prints out the value of `y=mx+q`
```bash
./a_line_in_external_file 3 0.5 1.2
2.700000
```

Run the macro which performs 3 fits (basic ROOT fit, using a custom function and using the external program).

Read the output in the terminal for execution time.
```
root -l myfit.C
```

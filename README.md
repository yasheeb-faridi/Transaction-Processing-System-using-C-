
## Transaction Processing System

This is a console application I created while learning programming in C++.

This project contains these files
* Header file(`ClientData.h`),

* A C++ source file(`ClientData.cpp`) containing the implementation of the class defined in the header file(often referred to as a "constructor file"),

* Another C++ (`file_app.cpp`) to create `credit.dat` file. The `credit.dat` file will be created based on the `ClientData` constructor method defined in the "ClientData::" class.

* And a C++ program (`writing_data.cpp`) to Insert Account Information of a new person.

* And a main source file(`transaction_program.cpp`) to handle all the transactions.




## Compilation and Execution
Note: In Windows you must have MinGW compiler installed and For Linux GNU/GCC installed.

Just running the Program in VS Code or another IDE is gonna give error because we are not Including the header file during Compilation.

We can compile them together using g++ and link them together into an executable named `main.exe` if on Windows or `main.out` on Linux.

The compiler will automatically find the `ClientData.h` header file since its included in `ClientData.cpp`

1. To create `credit.dat` file, I used this syntax:
> `g++ -o file_program file_app.cpp ClientData.cpp`

>and then run the executable in the terminal  
> `> .\file_program.exe` in Windows and 
`$ ./file_program.out` on Linux

>***Warning*** <Don't run this program again because it will delete the previous Records if you have already inserted data into it because it will Create a new `credit.dat` file >

2. To fill the records in `credit.dat` file using console:

I first compile `writing_data.cpp` source file with `ClientData.cpp` class file.
>`g++ -o data_input writing_data.cpp ClientData.cpp`
and then run the `.\data_input.exe` file in the console any number of times to fill the records.

3. To run the transaction processing program, first compile the output program:
> `g++ -o main transaction_processor.cpp ClientData.cpp`
and then execute `.\main.exe` or `./main.out` respectively in Windows and Linux to perform different types of transactions.


## Usage And Screenshots
![Screenshot 1][def1] 
![Screenshot 2][def2]
![Screenshot 3][def3]
![Screenshot 4][def4]

[def1]: image.png?raw=true
[def2]: image2.png?raw=true
[def3]: image3.png?raw=true
[def4]: image4.png?raw=true
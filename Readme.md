## Parallel Sorting and Merging using Threads

This program demonstrates a parallel sorting and merging algorithm using POSIX threads in C. The code reads a list of
integers from a text file, splits it into two sublists, sorts each sublist concurrently using separate threads, and then
merges the sorted sublists into a final sorted list, also using a dedicated thread.

### Features

- **Parallel Sorting:** Uses two threads to sort two sublists of the original list concurrently.
- **Parallel Merging:** Employs a dedicated thread to merge the two sorted sublists into a single sorted list.
- **File Input/Output:** Reads integers from a text file ("IntegerList.txt") and writes the sorted output to another
text file ("SortedIntegerList.txt").
- **Bubble Sort Algorithm:** The code utilizes the bubble sort algorithm for sorting the sublists.
- **Memory Management:** Dynamic memory allocation is used to store the lists and sublists.

### Tech Stack

- **Language:** C
- **Framework:** POSIX Threads (pthreads)
- **Technologies:** File I/O, String Manipulation, Memory Allocation, Multithreading

### Installation

This program requires the POSIX threads library (pthreads) to be installed. You should already have these libraries
installed if you are using a standard Linux or macOS system.

### Running the Project Locally

1. **Create an input file:** Create a file named "IntegerList.txt" in the same directory as the "Sorter.c" file. Add a
list of integers separated by commas in the file. For example:

```
10,5,8,2,1,9,4,7,6,3
```

2. **Compile the code:** Use a C compiler to compile the "Sorter.c" file:

```bash
gcc Sorter.c -o Sorter -lpthread
```

3. **Run the executable:** Execute the compiled program:

```bash
./Sorter
```

4. **Output file:** A new file "SortedIntegerList.txt" will be generated in the same directory, containing the sorted
list of integers.

### Configuration

- **File Names:** You can change the names of the input and output files in the `main` function.
- **List Size:** The initial list size is fixed to 500. You can modify this value in the `main` function by adjusting
the `malloc` call for `list1`.
- **Sorting Algorithm:** The code currently uses the bubble sort algorithm. Feel free to replace this with a more
efficient sorting algorithm like merge sort or quicksort.

### Testing

- Ensure that the "IntegerList.txt" file exists and contains a valid list of integers.
- Run the code and check the "SortedIntegerList.txt" file to verify that the output is correctly sorted.

### Contributing

Contributions are welcome! If you have any improvements or bug fixes, please feel free to create a pull request.

### Licensing

This code is licensed under the MIT License. See the LICENSE file for more details.

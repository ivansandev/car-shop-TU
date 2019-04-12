## Car Shop
The idea of this C console program is a **Car Shop**, which saves data to encrypted binary files. In addition, it can filter out products older than a given date, sorts them out by a certain type and searches for a specific product ID. I chose to use binary files here because firstly, they are faster than normal text files, and second, they are much more secure for more important data.

###Things used for this small project:
* Pointers
* Functions
* Structures
* Binary files

*Despite the main C files, other files are also provided that allow for reading the binary files which are generated later on by the main function.*

###How to run the file
1. Run the writeBin.c to write the data to a specific file
2. Run the readBin.c to check if the data is written correctly
3. Run the main.c to try out the main program
4. From now on, you can try the readBinOutdated & readBinSort files for reading the binary files that you've created through the main program.
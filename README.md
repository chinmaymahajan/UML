# UML

External Sorting - 
The size of the file is too big to be held in the memory during sorting. 
This algorithm minimizes the number of disk accesses and improves the sorting performance.

User Manual - 
Compiling Program  Command: 	 g++ external.cpp external.exe  
Program Execution 
  Here I am accepting Input file name (file to be sorted) output file name (file in which data to be stored) 
  order of sorting (ascending or descending) 0 for ascending 1 for descending and size of buffer memory as a command line argument. 
  
  Syntax:  	Program_Name Input_file Output_file Order_of _sorting Size_of _buffer 
  
  
  Command:  	./external input_file_name.txt output_file_name_.txt 0 4 	
              ./external  input_file_name.txt  output_file_name_.txt  0  4   
  
  Process: 
  •	Accepting input and output file name from user also the order of sorting and the buffer size.  
  •	Calculating the number of pages required and the records to fit on each page according to the buffered memory specified by the user.
  
  
  /* pseudocode */         
  total_size_of_file = (total_records * 16 );  //here 16 is bytes because the data type used is long long int                 
  memory_b = memory_b * 1000; //memory_bf is buffer memory specified by user, converting it into KBs	         
  memory_bytes = memory_b/16 ; //memory_bytes is number of records per page  	
  number_of_pages = total_records / memory_bytes; //number of pages required 
  
  •	Reading and Sorting chunks (equal to memory_bytes) of data as per the size specified by user. 
  
  •	Merging those chunks and simultaneously sorting them. 
  
  •	Writing the sorted data in the output file.    
  

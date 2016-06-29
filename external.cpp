#include <iostream>
#include <fstream> 
#include <time.h>
#include <stdlib.h>


void quickSort(long long int a[], long long int first, long long int last, int order);
long long int pivot(long long int a[], long long int first, long long int last, int order);
void swap(long long int& a, long long int& b);
void swapNoTemp(long long int& a, long long int& b);
void print(long long int array[], const long long int& N);
void mergeSort(long long int arr[], int l, int r, int order); 
void merge(long long int arr[], int l, int m, int r, int order);
static int iteration_quick, iteration_merge;
 
using namespace std;
 
int main(int argc, char *argv[])
{
    
    long long int memory_bytes = 0, memory_b =  atoi(argv[4]); // in MB
    long long int total_records = 0, line;
    long long int total_blocks = 0, count = 0, total_size_of_file = 0, number_of_pages = 0;
    int order = atoi(argv[3]);


    ifstream infile;
    ofstream outfile, tempfile;
    long long int i = 0;

    /*   Starting time  */
    double start_s=clock();
    /* time ends */

/*File opening starts and data reading */
    infile.open(argv[1],ios::in);
    outfile.open(argv[2],ios::out);
    tempfile.open("temp_file.input",ios::out);
    
    if (!infile.is_open()) 
    {
    cout<<"Please check the file name \n";
    return 0;
    }//if file is not open
             long long int g = 0;
             long long int size=7586259;                        

            long long int *bi = (long long int*)malloc(sizeof(long long int)*(size));

           while(!infile.eof())
            {
            
              infile>>bi[g];
              g++;

            total_records++;

        }  //while loop to count records present in file
        
       // cout<<"\nTotal records : "<<total_records<<"\n";
        
        total_size_of_file = (total_records * 16 ) ;
        
        cout<<"\nSize of File is : "<<total_size_of_file << "bytes";
        cout<<"\n Buffer Size is: "<<argv[4];
        
        memory_b = memory_b * 1000;
        memory_bytes = memory_b/16 ;

        if(memory_bytes > total_size_of_file)
            {
                cout<<"\nMemory specified is more than the file size";
                return 0;
            }

        cout<<"\nNumber of records per page : "<<memory_bytes;
        number_of_pages = total_records / memory_bytes;
        
        cout<<"\nNumber of pages required : "<<number_of_pages;

        int j = 0,  l = 0, ni = 0;
        long long int n =0, k =0;

       /*Dynamic allocation of memory for 2d array blocks[][] starts*/
       long long int **blocks;
        blocks = (long long int**) malloc(number_of_pages * sizeof(long long int *));
            if(blocks == NULL)
            {
            printf("\nout of memory\n");
            
            }//if
                for(int i = 0; i < number_of_pages; i++)
                    {
                    blocks[i] = (long long int*)malloc(memory_bytes * sizeof(long long int));
                    if(blocks[i] == NULL)
                        {
                        printf("\nout of memory\n");
                        
                        }//if
                    }//for
        /*Dynamic allocation of memory for 2d array blocks[][] ends*/

        long long int *arrdemo2d = (long long int*)malloc(sizeof(long long int)*(size));
        long long int *arrfinal = (long long int*)malloc(sizeof(long long int)*(size));

        cout<<"\nSorting Records using quick sort..";
        for(long long int i = 0; i <= total_records; i++)
        {
            arrdemo2d[n] = bi[i];
            n++;

            if(n>=memory_bytes)
            {
        quickSort(arrdemo2d, 0, memory_bytes - 1,order);
        for(long long int x = 0; x < n; x++)
            {
                blocks[k][x] = arrdemo2d[x]; 
            }
                k++;
                n = 0;

            }//if
    
        }//outer for
        cout<<"\nFinished Quick Sorting.. \n";
        int count1 = 0;
        long long int y = 0;
        cout<<"\n";
        cout<<"\nCreating block and sorting them"<<endl;

    for(int g = 0; g<number_of_pages;g++)
    {
        for(int j = 0; j<memory_bytes; j ++)
        {
     
     
       // tempfile<<"\t"<<g<<" "<<j<<" "<<blocks[g][j]<<" | ";
        arrfinal[y++] = blocks[g][j];
        } // inner for loop
      //  tempfile<<"\n\n";
    
    }//outer for loop
        cout<<"\nSorting block by block and Merging..\n";
        mergeSort(arrfinal,0,total_records-1,order);
        cout<<"\nWriting in a "<<argv[2]<<" file...\n";

            for(int z = 0; z<total_records; z++)
            {
                
                   outfile<<arrfinal[z]<<endl;
                   
            }

cout<<"\nYour file is Sorted..";   
double stop_s=clock();
double miliseconds = (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000;
double seconds = miliseconds/1000;
cout << "\ntime taken in  milliseconds : " << miliseconds;
cout<<"\nTotal Iteration for Quick Sort : "<<iteration_quick;
//cout<<"\nTotal Iteration for Merge Sort : "<<iteration_merge;
free(bi);
free(blocks);
free(arrdemo2d);
tempfile.close();
outfile.close();
infile.close();
return 0;
    }

void quickSort(long long int a[], long long int first, long long int last, int order ) 
{
    long long int pivotElement;
 
    if(first < last)
    {
        iteration_quick++;
        pivotElement = pivot(a, first, last, order);
        quickSort(a, first, pivotElement-1,order);
        quickSort(a, pivotElement+1, last,order);
    }
}

long long int pivot(long long int a[], long long int first, long long int last, int order) 
{
    long long int  p = first;
    long long int pivotElement = a[first];
 
    for(long i = first+1 ; i <= last ; i++)
    {
      //  If you want to sort the list in the other order, change "<=" to ">" 
        if(order == 1)
        {
            if(a[i] > pivotElement)
            {
                p++;
                swap(a[i], a[p]);
            }
        }//if descendig order 
        else
        {
            if(a[i] <= pivotElement)
            {
                p++;
                swap(a[i], a[p]);
            }

        } // else ascending order
    }
    swap(a[p], a[first]);
 
    return p;
}
 
void swap(long long int& a, long long int& b)
{
    long temp = a;
    a = b;
    b = temp;
}

void swapNoTemp(long long int& a, long long int& b)
{
    a -= b;
    b += a;// b gets the original value of a
    a = (b - a);// a gets the original value of b
}

/*Merging */ 

void merge(long long int arr[], int l, int m, int r, int order)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
  //  iteration_merge++;
    /* create temp arrays */
    //long long int L[n1], R[n2];
    long long int *L = (long long int*)malloc(sizeof(long long int)*(n1));
    long long int *R = (long long int*)malloc(sizeof(long long int)*(n2));
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if(order == 1)
        {

        if (L[i] > R[j]) //> for descending
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        }//order == 1
        else
        {
             if (L[i] <= R[j]) //> for descending
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
       are any */

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(long long int arr[], int l, int r, int order)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;
 
        // Sort first and second halves
        mergeSort(arr, l, m,order);
        mergeSort(arr, m+1, r,order);
 
        merge(arr, l, m, r,order);
    }
}

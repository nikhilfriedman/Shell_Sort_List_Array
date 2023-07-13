#include <stdio.h>
#include <stdlib.h>
#include "shell_array.h"
#include "sequence.h"

long *Array_Load_From_File(char *filename, int *size)
{
    // create file pointer 
    FILE * fp = fopen(filename, "rb");

    if(fp == NULL)
    {
        * size = 0;
        return(NULL);
    } 

    // seek to end, and assign size
    fseek(fp, 0, SEEK_END);
    * size = ftell(fp) / sizeof(long);
    // rewind to SEEK_SET
    rewind(fp);

    long * out = (long *) malloc((* size) * sizeof(long));

    if(out == NULL)
    {
        * size = 0;
        return(NULL);
    }

    // read contents of the binary file to * out
    int x = fread((out), sizeof(long), * size, fp);
    if(x < 1) {}

    fclose(fp);

    return(out);

}

int Array_Save_To_File(char *filename, long *array, int size)
{
    // create file
    FILE * fp = fopen(filename, "wb");

    // return blank file 
    if(array == NULL || size == 0)
    {
        return(0);
    }

    fwrite((array), sizeof(long), size, fp);

    int length = ftell(fp) / sizeof(long);

    fclose(fp);

    return(length);
}

void Array_Shellsort(long *array, int size, long *n_comp)
{
    // initialize variables and generate k values
    int k_size, i, j, l;
    long temp;
    long * k = Generate_2p3q_Seq(size, &k_size);

    // shell sort
    for(i = k_size - 1; i >= 0; i--)
    {
        for(j = k[i]; j < size; j++)
        {
            temp = array[j];
            l = j;

            while(l >= k[i] && array[l - k[i]] > temp)
            {
                array[l] = array[l - k[i]];
                l = l - k[i];
                (*n_comp)++; // comparisons in while loop
            }
            (*n_comp)++; // comparisons in for loop

            array[l] = temp;
        }
    }

    free(k);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell_array.h"
#include "shell_list.h"

static void free_linked(Node * n)
{
    Node * curr = n;

    while(curr -> next != NULL)
    {
        Node * temp = curr;
        curr = curr -> next;
        free(temp);
    }
}

static long list_size(Node * n)
{
    long ct = 0;

    while(n -> next != NULL)
    {
        ct++;
        n = n -> next;
    }

    return(ct);
}

int main(int argc, char * argv[])
{
    int size = 0;
    long n_comp = 0;

    if(strcmp("-l", argv[1]) == 0)
    {
        Node * list = List_Load_From_File(argv[2]);
        if(list == NULL) return EXIT_FAILURE;

        size = list_size(list);

        list = List_Shellsort(list, &n_comp);
        List_Save_To_File(argv[3], list);
        free_linked(list);
    }
    else if(strcmp("-a", argv[1]) == 0)
    {
        long * arr = Array_Load_From_File(argv[2], &size);
        if(arr == NULL) return EXIT_FAILURE;

        Array_Shellsort(arr, size, &n_comp);
        Array_Save_To_File(argv[3], arr, size);
        free(arr);
    }

    printf("\n%ld\n", n_comp);

    return EXIT_SUCCESS;
}

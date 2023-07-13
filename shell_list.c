#include <stdio.h>
#include <stdlib.h>
#include "shell_list.h"
#include "sequence.h"
#include <stdbool.h>
#include <limits.h>

static Node * cr_node(void)
{
    Node * out = (Node *) malloc(sizeof(Node));
    if(out == NULL) return NULL;

    out -> value = 0;
    out -> next = NULL;

    return(out);
}

Node *List_Load_From_File(char *filename)
{
    FILE * fp = fopen(filename, "r");

    if(fp == NULL) return(NULL);

    Node * head = cr_node();
    Node * curr = head;

    while(fread(&(curr -> value), sizeof(long), 1, fp) == 1)
    {
        curr -> next = cr_node();
        curr = curr -> next;
    }

    fclose(fp);

    return(head);
}

int List_Save_To_File(char *filename, Node *list)
{
    FILE * fp = fopen(filename, "wb");
    if(fp == NULL) return(0);

    int ct = 0;

    while(list -> next != NULL)
    {
        fwrite(&(list -> value), sizeof(long), 1, fp);
        list = list -> next;
        ct++;
    }

    fclose(fp);

    return(ct);
}

static int bubble(long k, long len, Node * n)
{
    bool sorted = false;
    long last_exchange = len + 1;

    int comp = 0;

    Node * curr = n;
    Node * prev = n;

    while(!sorted)
    {
        sorted = true;
        long last_element = last_exchange - 1;

        curr = n;
        prev = n;

        for(long i = 0; i < last_element; i++)
        {
            for(long j = 0; j < k; j++)
            {
                if(curr -> next != NULL) curr = curr -> next;
            }

            if(prev -> value > curr -> value)
            {
                long temp = prev -> value;
                prev -> value = curr -> value;
                curr -> value = temp;

                last_exchange = i + 1;
                sorted = false;

                comp++;
            }

            for(long j = 0; j < k; j++)
            {
                if(prev -> next != NULL) prev = prev -> next;
            }
        }
    }

    return(comp);
}

Node * List_Shellsort(Node * list, long * n_comp)
{
    if(list == NULL) return NULL;

    long n = 0;
    int size;

    Node * curr = list;

    while(curr -> next != NULL)
    {
        n++;
        curr = curr -> next;
    }
    
    long * k = Generate_2p3q_Seq(n, &size);

    // loop through k values
    for(int i = size - 1; i >= 0; i--)
    {
        long rep = n / k[i];
        long end = n % k[i];

        for(long j = 0; j < k[i]; j++)
        {
            if(j < end)
            {
                *n_comp += bubble(k[i], rep, list);
            }
            else
            {
                *n_comp += bubble(k[i], rep - 1, list);
            }

            curr = curr -> next;
        }
    }

    return(list);
}

#include <stdio.h>
#include <stdlib.h>
#include "sequence.h"

static int minimum(int x, int y)
{
    if(x <= y)
    {
        return(x);
    }

    return(y);
}

static int power(int x, int pwr)
{
    int i, out;
    out = 1;

    for(i = 0; i < pwr; i++)
    {
        out *= x;
    }

    return(out);
}

long *Generate_2p3q_Seq(int n, int *seq_size)
{
    int p_max, q_max, i;

    if(n <= 1)
    {
        // if n <= 1, set size to 0 and create malloc of size 0
        * seq_size = 0;
    }
    else
    {
        p_max = q_max = 0;

        // find max value of p
        while(power(2, p_max) < n) p_max++;
        p_max--;

        // find max value of q
        while(power(3, q_max) < n) q_max++;
        q_max--;

        // set sequence size based on max p and q
        * seq_size = ((q_max + 1) * (q_max + 2) / 2) + (p_max - q_max + 1) * (p_max - q_max);
    }

    // create malloc of size seq_size
    long * out = malloc((* seq_size) * sizeof(long));
    if(out == NULL)
    {
        // if malloc failure
        * seq_size = 0;
        return(NULL);
    }

    int p_loc, q_loc, p2, q3;
    p_loc = q_loc = 0;
    
    // generate 3-smooth 
    out[0] = 1;
    for(i = 1; i < * seq_size; i++)
    {
        p2 = 2 * out[p_loc];
        q3 = 3 * out[q_loc];

        out[i] = minimum(p2, q3);
        
        // increment
        p_loc += (p2 <= q3);
        q_loc += (p2 >= q3);
    }

    // return 
    return(out);
}

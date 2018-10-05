/*    Copyright (C) 2005 Robert Kooima                                       */
/*                                                                           */
/*    ELECTRO is free software;  you can redistribute it and/or modify it    */
/*    under the terms of the  GNU General Public License  as published by    */
/*    the  Free Software Foundation;  either version 2 of the License, or    */
/*    (at your option) any later version.                                    */
/*                                                                           */
/*    This program is distributed in the hope that it will be useful, but    */
/*    WITHOUT  ANY  WARRANTY;  without   even  the  implied  warranty  of    */
/*    MERCHANTABILITY or  FITNESS FOR A PARTICULAR PURPOSE.   See the GNU    */
/*    General Public License for more details.                               */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "vector.h"
#include "buffer.h"
#include "utility.h"

/*---------------------------------------------------------------------------*/

#ifdef CONF_MPI

#define BUCKETSZ (4 * 1024 * 1024)

struct bucket
{
    struct bucket *next;
    size_t         size;
};

static struct bucket *first = NULL;
static struct bucket *curr  = NULL;

static size_t count = 0;

/*---------------------------------------------------------------------------*/

int startup_buffer(void)
{
    /* All hosts begin with one empty bucket. */

    if ((first = curr = (struct bucket *) malloc(BUCKETSZ)))
    {
        count = sizeof (struct bucket);

        curr->next = NULL;
        curr->size = count;

        return 1;
    }
    return 0;
}

/*---------------------------------------------------------------------------*/

static void clear_buffer(void)
{
    struct bucket *prev = NULL;
    struct bucket *temp;

    /* Empty all buckets. */

    for (temp = first; temp->next; prev = temp, temp = temp->next)
        temp->size = sizeof (struct bucket);

    /* If the last bucket was not used during the recent cycle, release it. */

    if (temp != first && temp->size == sizeof (struct bucket))
    {
        free(temp);
        prev->next = NULL;
    }
    else
        temp->size = sizeof (struct bucket);

    /* Reset the read point to the beginning. */

    count = sizeof (struct bucket);
}

void sync_buffer(void)
{
    struct bucket *temp;
    int rank;
    int size;
    int n;

    assert_mpi(MPI_Comm_rank(MPI_COMM_WORLD, &rank));
    assert_mpi(MPI_Comm_size(MPI_COMM_WORLD, &size));

    char hostname[256];
    gethostname(hostname,255);
    //printf("process number: %d on host %s\n", rank, hostname);

    //    fprintf(stderr, "buffer %d %d\n", rank, size);

    if (rank != 0) clear_buffer();

    /* Iterate over all buckets. */

    for (curr = first; curr; curr = curr->next)
    {
        /* Broadcast this bucket, preserving client 'next' links. */

        n    = curr->size;
        temp = curr->next;

	assert_mpi(MPI_Bcast(&n,   4, MPI_BYTE, 0, MPI_COMM_WORLD));
	// fprintf(stderr, "assert mid %d %d %p %d\n", rank, size, curr, n);
	assert_mpi(MPI_Bcast(curr, n, MPI_BYTE, 0, MPI_COMM_WORLD));

	// fprintf(stderr, "assert end %d %d\n", rank, size);

        curr->next = temp;

        /* Loop until a non-full bucket is sent or received. */

        if (n < BUCKETSZ)
	  {
	    // fprintf(stderr, "breaking %d %d\n", rank, size);
	    break;
	  }

        /* If a client is out of buckets but more are coming, allocate. */

        if (rank && curr->next == NULL)
        {
            if ((curr->next = (struct bucket *) malloc(BUCKETSZ)))
                curr->next->next = NULL;
        }
	// fprintf(stderr, "loop end %d %d\n", rank, size);
    }

    if (rank == 0) clear_buffer();

    /* Rewind all hosts to read or write at the first bucket. */

    // fprintf(stderr, "buffer end %d %d\n", rank, size);

    curr = first;
}

/*---------------------------------------------------------------------------*/

static void send_data(const void *buf, size_t len)
{
    if (get_rank() == 0 && buf && len > 0)
    {
        size_t fit = BUCKETSZ - curr->size;

        /* Check if all of the data fit in the current bucket. */

        if (len < fit)
        {
            /* Append the data to the current bucket. */

            memcpy((char *) curr + curr->size, buf, len);
            curr->size += len;
        }
        else
        {
            /* Append as many data as will fit in the current bucket. */

            memcpy((char *) curr + curr->size, buf, fit);
            curr->size += fit;

            /* Ensure there is another bucket and handle the remaining data. */

            if (curr->next == NULL)
            {
                curr->next = (struct bucket *) malloc(BUCKETSZ);

                curr->next->next = NULL;
                curr->next->size = sizeof (struct bucket);
            }

            curr = curr->next;

            send_data((char *) buf + fit, len - fit);
        }
    }
}

static void recv_data(void *buf, size_t len)
{
    if (get_rank() != 0 && buf && len > 0)
    {
        size_t fit = curr->size - count;

        /* Check if the current bucket holds all of the requested data. */

        if (len < fit)
        {
            /* Copy the requested data from the current bucket. */

            memcpy(buf, (char *) curr + count, len);
            count += len;
        }
        else
        {
            /* Copy as many of the data as fit in the current bucket. */

            memcpy(buf, (char *) curr + count, fit);
            count += fit;

            /* Move to the next bucket and handle the remainder of the data. */

            curr  = curr->next;
            count = sizeof (struct bucket);

            recv_data((char *) buf + fit, len - fit);
        }
    }
}

int get_rank(void)
{
    int rank;

    assert_mpi(MPI_Comm_rank(MPI_COMM_WORLD, &rank));

    return rank;
}

/*---------------------------------------------------------------------------*/

#else  /* non-MPI stub functions*/

int startup_buffer(void)
{
    return 1;
}

void sync_buffer(void)
{
}

static void send_data(const void *buf, size_t len)
{
}

static void recv_data(void *buf, size_t len)
{
    memset(buf, 0, len);
}

int get_rank(void)
{
    return 0;
}

#endif /* MPI */

/*---------------------------------------------------------------------------*/

void send_array(const void *p, size_t n, size_t s)
{
    send_data(p, n * s);
}

void send_value(int i)
{
    send_data(&i, sizeof (int));
}

void send_event(char c)
{
    send_data(&c, sizeof (char));
}

void send_float(float f)
{
    send_data(&f, sizeof (float));
}

void send_index(unsigned int i)
{
    send_data(&i, sizeof (unsigned int));
}

/*---------------------------------------------------------------------------*/

void recv_array(void *p, size_t n, size_t s)
{
    recv_data(p, n * s);
}

int recv_value(void)
{
    int i;

    recv_data(&i, sizeof (int));
    return i;
}

char recv_event(void)
{
    char c;

    recv_data(&c, sizeof (char));
    return c;
}

float recv_float(void)
{
    float f;

    recv_data(&f, sizeof (float));
    return f;
}

unsigned int recv_index(void)
{
    unsigned int i;

    recv_data(&i, sizeof (unsigned int));
    return i;
}

/*---------------------------------------------------------------------------*/

void send_vector(vector_t V)
{
    send_index(vecnum(V));
    send_index(vecsiz(V));
    send_array(vecbuf(V), vecnum(V), vecsiz(V));
}

vector_t recv_vector(void)
{
    vector_t V;

    int num = recv_index();
    int siz = recv_index();

    V      = vecnew(num, siz);
    V->num = num;

    recv_array(vecbuf(V), num, siz);

    return V;
}

/*---------------------------------------------------------------------------*/

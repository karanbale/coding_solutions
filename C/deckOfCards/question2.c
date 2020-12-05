/*
A fellow developer has asked you to review the following code. Please
provide your feedback:
*/

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/*
* This is a circular buffer that allows enqueue or dequeue arbitrary
* amount of bytes. The buffer size is limited to BUF_SIZE.
*/

static char *GetErrorString(int x);

#define BUF_SIZE    4096

typedef struct {
   int write_index;
   int read_index;
   char *buf;
   int size;
} circular_buf_t;

circular_buf_t buf;

/*
* Enqueue (size) bytes from (client_buf) to the local buf
* memory of (client_buf) is allocated by the caller
*/
int enqueue(char *client_buf, int size)
{
   if (size > BUF_SIZE) {
       printf("%s", GetErrorString(3));
       return 3;
   }

   int part1 = buf.size - buf.write_index;
   memcpy(client_buf, buf.buf + buf.write_index, part1);

   if (part1 != size) {
       int part2 = size - part1;
       memcpy(client_buf+part1, buf.buf[0], part2);
   }

   return 0;
}

/*
* Dequeue (size) bytes from the local buf to (client_buf),
* (client_buf) is allocated by the caller. It is okay to assume
* (client_buf) is big enough to hold all the (size) bytes
*/
int dequeue(char *client_buf, int size)
{
   if (size < BUF_SIZE) {
       printf("%s", GetErrorString(2));
       return 2;
   }

   int copy_size = buf.write_index - buf.read_index + 1;
   memcpy(client_buf, buf.buf + buf.write_index, copy_size);

   return 0;
}

static char *GetErrorString(int x)
{
   char errorString[20];

   switch ( x )
   {
       case 0:
           errorString = "Success -- No error.";
           break;
       case 2:
           errorString = "Overflow!";
           break;
   }

   errorString[19] = 0;
   return errorString;
}


int main(int argc,char* argv[])
{
   // initialize buffer
   buf.buf = malloc(BUF_SIZE);
   buf.size = BUF_SIZE;

   // Perform enqueue() and dequeue();

   // All completed, return
   return 0;
}
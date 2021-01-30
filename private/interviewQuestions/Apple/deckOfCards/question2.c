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
} circular_buf_t;                                               // R.C.: I'd recommend moving struct definitions to header files

circular_buf_t buf;                                             // R.C.: I'd recommend moving global declarations to header files

/*
* Enqueue (size) bytes from (client_buf) to the local buf
* memory of (client_buf) is allocated by the caller
*/
int enqueue(char *client_buf, int size)
{
   if (size > BUF_SIZE) {
       printf("%s", GetErrorString(3));                         // R.C.: getErrorString cannot handle inputs other than 0 or 2.
       return 3;                                                // R.C.: return 3 as a macro, to improve readability and re-usibility
                                                                // returning macro, allows you to change it once and use it everywhere
   }
   
   int part1 = buf.size - buf.write_index;                      // R.C.: check part1 for underflow w.r.t size
                                                                // (i.e. what if size < part1 then, you need to update part1 = size - part1
                                                                // you need to accomodate 1 extra byte for string termination

   memcpy(client_buf, buf.buf + buf.write_index, part1);        // R.C.: you're copying from local buf to client buf, this needs correction

   // from client buffer, copy
   if (part1 != size) {                                         // R.C.: this will not work reliably when part1 > size, your check here
                                                                // is incomplete / partial
       int part2 = size - part1;
       memcpy(client_buf+part1, buf.buf[0], part2);             // R.C.: copying from local buf to client buf, needs correction
                                                                // also buf.buf[0] will send a character to const void*, you should send its base address
   }                                                            
                                                                // R.C.: write_index needs to be advance from its current position by number
                                                                // of bytes those were enqueued, consider wrap-over of index when advancing

   return 0;
}

/*
* Dequeue (size) bytes from the local buf to (client_buf),
* (client_buf) is allocated by the caller. It is okay to assume
* (client_buf) is big enough to hold all the (size) bytes
*/
int dequeue(char *client_buf, int size)
{
   if (size < BUF_SIZE) {                                           // R.C.: you can dequeue when size < BUF_SIZE, check needs to change
       printf("%s", GetErrorString(2));
       return 2;                                                    // R.C.: I'd return 2 as a macro, 
                                                                    // to improve readability and re-usibility of this error code
   }

   int copy_size = buf.write_index - buf.read_index + 1;            // R.C.: check for underflow, what if write_index < read_index? then
                                                                    // your index to start copying data from will change, along with # of bytes to copy
                                                                    // kudos for copying extra byte and considering string termination character :)

   memcpy(client_buf, buf.buf + buf.write_index, copy_size);        // R.C.: you should consider copying extra byte from start of index,
                                                                    // whenever write_index < read_index

   return 0;                                                        // R.C.: read_index needs to be advance from its current position by number
                                                                    // of bytes those were dequeued, consider wrap-over of index when advancing
}

static char *GetErrorString(int x)
{
   char errorString[20];                                            // R.C.: local variable, needs to be dynamic memory if it needs to be returned
                                                                    
   switch ( x )                                                     // R.C.: unable to handle unexpected values of x, no default case defined
   {
       case 0:
           errorString = "Success -- No error.";                    // R.C.: assigning string literal to a char array will lead to an error
           break;
       case 2:
           errorString = "Overflow!";                               // R.C.: assigning string literal to a char array will lead to an error
           break;
   }

   errorString[19] = 0;                                             // R.C.: If string is smaller than 20 chars, 
                                                                    // you should terminate string accordingly
   return errorString;                                              // R.C.: Returning local variable that will go out of scope please allocate
                                                                    // dynamic memory on heap and then return the pointer to that memory
                                                                    // remember to free it to avoid memory leaks
}


int main(int argc,char* argv[])
{
   // initialize buffer
   buf.buf = (char *) malloc(BUF_SIZE);                                      // R.C.: need a check if malloc operation was successful.
   buf.size = BUF_SIZE;

   // Perform enqueue() and dequeue();
                                                                    // R.C.: enqueue/dequeue function calls and related logic is missing
                                                                    // R.C.: not freeing up local buffer before exiting will cause memory leaks
   // All completed, return
   return 0;
}
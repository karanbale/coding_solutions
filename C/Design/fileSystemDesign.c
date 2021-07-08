
#include "../standardHeaders.h"

/* Objects */
typedef struct file_node_s {
   uint64_t id;
   struct file_node_s *parent, *child;
} file_node_t;

typedef struct file_attribute_s {
   char *name;
   int id;
   int type; /* plain file, directory, and etc */
   int permission, group, owner;
   int create_time, modify_time;
   int cylinder, track, block, size;
   /* ... */
} file_attribute_t;

typedef struct file_system_s {
   file_node_t *root;
   file_attribute_t *file_table;
   int num_files;
} file_system_t;

/* Methods */

/* file system management */
void file_system_init(file_system_t *fs);
int file_create(file_system_t *fs, char *path, char *name); /* create file according to given path & name, returns file id if successful*/
int file_get_fid(file_system_t *fs, char *path, char *name); /* map name to file id */
int file_delete(file_system_t *fs, char *path, char *name); /* delete a file according to file id */

/* file IO */
int file_open(file_system_t *fs, char *path, char *name, int mode); /* open a file for read/write/append; returns file id */ 
int file_read(int fid, char *buffer, int len);
int file_write(int fid, char *buffer, int len);

int dir_open(file_system_t *ts, char *path);
char *dir_read_next(int fid);

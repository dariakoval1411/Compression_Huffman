#ifndef HEADERMAP_H
#define HEADERMAP_H

typedef struct Header_Map{
    char **name;
    int size;
    int capacity;
}header;

header * createHeader(int);
int double_header_capacity(header*);
int add_header(header*,char*);
void free_header(header*);

#endif
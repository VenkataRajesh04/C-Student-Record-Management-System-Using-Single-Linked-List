#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student
{
    int rollno;
    char name[30];
    float percentage;
    struct student *next;
} SLL;

void add_record(SLL **);
void delete_record(SLL **);
void show_list(SLL *);
void modify_record(SLL *);
void save_record(SLL *);
void sort_list(SLL *);
void delete_all(SLL **);
void reverse_list(SLL **);
int CountNode(SLL *);

#endif


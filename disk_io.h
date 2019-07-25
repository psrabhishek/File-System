#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma once

struct file{
	char file_name[20];
	unsigned int starting_block, no_of_blocks, file_length;
};

typedef struct file File;

#define f 10
#define b 10
#define Meta()\
struct {\
	int magic;\
	int block_size;\
	int start_block;\
	int no_blocks;\
	int empty_blocks;\
	bool block_available[f/b];\
	int no_of_files;\
	File files[f/b];\
}\


unsigned int get_file_size(char* file_name);

static char hdd_file[20] = "";
static int filesize=1, blocksize=1;

void write_block(int block, void* buff);

int read_block(int block, void* buff);

void init(char* file_name);
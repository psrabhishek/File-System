#include"disk_io.h"

unsigned int get_file_size(char* file_name)
{
	FILE* fp = fopen(file_name, "rb");
	fseek(fp, 0, SEEK_END);
	unsigned int size = ftell(fp);
	fclose(fp);
	return size;
}

void write_block(int block, void* buff)
{
	FILE* fp = fopen(hdd_file, "rb+");
	fseek(fp, block * 16 * 1024, SEEK_SET);
	fwrite(buff, 1, 16 * 1024, fp);
	fclose(fp);
}

int read_block(int block, void* buff)
{
	FILE* fp = fopen(hdd_file, "rb+");
	if (!fp)
	{
		printf("Please mount proper disk\n");
		return 0;
	}
	fseek(fp, block * 16 * 1024, SEEK_SET);
	fread(buff, 1, 16 * 1024, fp);
	fclose(fp);
	return 1;
}

void init(char* file_name, int block_size)
{
	strcpy(hdd_file, file_name);
	/*int* n = (int*) malloc(4);
	FILE* fp = fopen(hdd_file, "rb+");
	fread(&n, 4, 1, fp);
	if (*n != 98989898)
	{
		printf("File is not formatted\n");
	}
	else
	{
		fread(&n, 4, 1, fp);
		printf("block size is %d\n", n);
		init_struct(get_file_size(file_name), n);

	}
	fclose(fp);*/
#undef f
#define f get_file_size(file_name)
#undef f
#define b block_size
}
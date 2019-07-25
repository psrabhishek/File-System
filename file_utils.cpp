#include"file_utils.h"



void store( char* filename, char* new_file_name, char*buff)
{
	int i, size = get_file_size(filename), j, blocks, offset, block_size, no_of_blocks;
	block_size = meta.block_size;
	blocks = size / block_size;
	if (size % block_size)
		blocks++;
	//printf("%d\n", size);
	for (i = 1; i < 6400 - blocks; i++)
	{
		if (!meta.block_available[i])
		{
			j = i;
			while (!meta.block_available[j] && j - i + 1 < blocks) j++;
			if (j - i + 1 == blocks)
			{
				FILE* fp = fopen(filename, "rb");
				for (int k = i; k < j; k++)
				{
					meta.block_available[k] = 1;
					fread(buff, 1, 16 * 1024, fp);
					write_block(k, buff);
				}
				if (blocks == size / (16 * 1024))
					offset = 16 * 1024;
				else
					offset = size % (16 * 1024);
				fread(buff, 1, offset, fp);
				write_block(j, buff);
				meta.block_available[j] = 1;
				meta.files[meta.no_of_files].file_length = size;
				strcpy(meta.files[meta.no_of_files].file_name, new_file_name);
				meta.files[meta.no_of_files].no_of_blocks = blocks;
				meta.files[meta.no_of_files].starting_block = i;
				meta.no_of_files++;
				memcpy(buff, &meta, sizeof(meta));
				write_block(0, buff);
				fclose(fp);
				return;
			}
			else i = j;
		}
	}
	printf("Could't store the give file\n");
}

void retrieve(char* filename, char* new_file_name, char*buff)
{
	int i, size, j, blocks, start;
	//printf("%d\n", meta.no_of_files);
	for (i = 0; i < meta.no_of_files; i++)
	{
		//printf("%s\n", meta.files[i].file_name);
		if (!strcmp(filename, meta.files[i].file_name))
			break;
	}
	if (i >= meta.no_of_files)
	{
		printf("Could't retrieve the give file\n");
		return;
	}
	size = meta.files[i].file_length;
	//printf("%d\n", size);
	start = meta.files[i].starting_block;
	blocks = meta.files[i].no_of_blocks;
	FILE* fp = fopen(new_file_name, "wb+");
	for (i = 0; i < blocks - 1; i++)
	{
		read_block(i + start, buff);
		fwrite(buff, 1, 16 * 1024, fp);
	}
	if (size % (16 * 1024))
	{
		read_block(i + start, buff);
		fwrite(buff, 1, size % (16 * 1024), fp);
	}
	else
	{
		read_block(i + start, buff);
		fwrite(buff, 1, 16 * 1024, fp);
	}
	fclose(fp);
}

void del( char* filename, char*buff)
{
	int i, size, j, blocks, start;
	//printf("%d\n", meta.no_of_files);
	for (i = 0; i < meta.no_of_files; i++)
	{
		//printf("%s\n", meta.files[i].file_name);
		if (!strcmp(filename, meta.files[i].file_name))
			break;
	}
	if (i >= meta.no_of_files)
	{
		printf("Could't find/delete the give file\n");
		return;
	}
	start = meta.files[i].starting_block;
	blocks = meta.files[i].no_of_blocks;
	meta.files[i] = meta.files[meta.no_of_files-1];
	meta.no_of_files--;
	for (i = start; i < blocks - 1; i++)
	{
		meta.block_available[i] = 0;
	}
	memcpy(buff, &meta, sizeof(meta));
	write_block(0, buff);
}

void list()
{
	int i, size, j, blocks, start;
	for (i = 0; i < meta.no_of_files; i++)
	{
		printf("%s\n", meta.files[i].file_name);
	}
	if (i == 0)
	{
		printf("No files found\n");
	}
}

void debug()
{
	int n = 0, i;
	for (i = 0; i < 6400; i++)
		if (!meta.block_available[i])
			n++;
	printf("Amount of blocks available is %d\n", n);
}
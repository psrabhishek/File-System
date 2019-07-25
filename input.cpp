#include"input.h"

void start()
{
	char buff[16 * 1024];
	char command[10], file_name[20], new_file_name[20];
	int i;
	while (true)
	{
		if(read_block(0, buff))
			memcpy(&meta, buff, sizeof(meta));
		printf("> ");

		scanf("%s", &command);
		for (i = 0; command[i]; i++)
			command[i] = tolower(command[i]);

		if (!strcmp(command, "format"))
		{
			meta.magic = 98989898;
			for (i = 0; i < meta.no_blocks; i++)
				meta.block_available[i] = 0;
			memcpy(buff, &meta, sizeof(meta));
			write_block(0, buff);
		}

		else if (!strcmp(command, "store"))
		{
			scanf("%s%s", &file_name, &new_file_name);
			store(file_name, new_file_name, buff);
		}

		else if (!strcmp(command, "get"))
		{
			scanf("%s%s", &file_name, &new_file_name);
			retrieve(file_name, new_file_name, buff);
		}

		else if (!strcmp(command, "del"))
		{
			scanf("%s", &file_name);
			del(file_name, buff);
		}

		else if (!strcmp(command, "ls"))
		{
			list();
		}

		else if (!strcmp(command, "debug"))
		{
			debug();
		}

		else if (!strcmp(command, "exit"))
		{
			break;
		}

		else
		{
			printf("no command \"%s\" found\n", command);
		}

	}
}
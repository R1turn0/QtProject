#include "common.h"

#pragma warning(disable : 4996)

//{x012,0x34} -> "1234"
int bytes_to_hexstr( const void* data,  int count,  char* hex)
{
	int i = 0;
	for( i; i < count; i++)
		sprintf(hex + 2*i, "%02X", ((unsigned char*)data)[i]);
	
    return 0;
}


int hexstr_to_bytes( const char* hex,  int count,  unsigned char* data)
{
    unsigned char temp[2];
    int i, j;

    if (hex == NULL || data == NULL || (int)strlen(hex) > count * 2)
    {
        return 1;
    }

    for (i = 0; i != count; ++i)
    {
        for (j = 0; j != 2; ++j)
        {
            if (hex[2 * i + j] >= '0' && hex[2 * i + j] <= '9')
            {
                temp[j] = hex[2 * i + j] - '0';
            }
            else if (hex[2 * i + j] >= 'A' && hex[2 * i + j] <= 'F')
            {
                temp[j] = hex[2 * i + j] - 'A' + 10;
            }
            else if (hex[2 * i + j] >= 'a' && hex[2 * i + j] <= 'f')
            {
                temp[j] = hex[2 * i + j] - 'a' + 10;
            }
            else
            {
                return 1;
            }
        }

        data[i] = (temp[0] << 4) + temp[1];
    }

    return 0;
}

int read_file(const char *filename, void *buffer, unsigned int buffer_max_length, unsigned int *file_size)
{
    FILE *fp = NULL;
    size_t fsize = 0;

    fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    fsize = ftell(fp);
    if (fsize == 0)
    {
        fclose(fp);
        return -2;
    }
    else if (fsize > buffer_max_length)
    {
        *file_size = (int)fsize;
        fclose(fp);
        return -3;
    }
    fseek(fp, 0, SEEK_SET);

    fread(buffer, 1, fsize, fp);
    *file_size = (int)fsize;

    fclose(fp);

    return 0;
}

int read_file_text(const char *filename, void *buffer, unsigned int buffer_max_length, unsigned int *file_size)
{
	FILE *fp = NULL;
	size_t fsize = 0;

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		return -1;
	}

	fseek(fp, 0, SEEK_END);
	fsize = ftell(fp);
	if (fsize == 0)
	{
		fclose(fp);
		return -2;
	}
	else if (fsize > buffer_max_length)
	{
		*file_size = (int)fsize;
		fclose(fp);
		return -3;
	}
	fseek(fp, 0, SEEK_SET);

	fread(buffer, 1, fsize, fp);
	*file_size = (int)fsize;

	fclose(fp);

	return 0;
}

int write_file(const char *filename, void *data, int data_length)
{
    FILE *fp = NULL;
    size_t fsize = 0;

    fp = fopen(filename, "wb");
    if (fp == NULL)
    {
        return -1;
    }

    fsize = fwrite(data, data_length, 1, fp);
    fclose(fp);

    return 0;
}
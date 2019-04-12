#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <string.h>

int main()
{
    int id;
    int productLength;
    char product[20];
    char productType[3];
    char date[11];

    FILE *fp;

    if ((fp = fopen("OUTdated.bin", "rb")) == NULL)
    {
        perror("Error writing.");
        exit(1);
    }

    while (1)
    {
        if (fread(&id, sizeof(int), 1, fp) != 1)
        {
            break;
        }
        printf("TEST\n");
        printf("ID: ");
        printf("%d\n", id);

        if (fread(&productLength, sizeof(int), 1,fp) != 1)
        {
            break;
        }
        if (fread(product, 1, productLength, fp) != productLength)
        {
            break;
        }
        printf("Product: ");
        printf("%s\n", product);

        if (fread(&productType, 1, 3, fp) != 3)
        {
            break;
        }
        printf("Product type: ");
        printf("%s\n", productType);
        
        if (fread(date, 1, 10, fp) != 10)
        {
            break;
        }
        printf("Date: ");
        printf("%s\n", date);
    }
    fclose(fp);

	// system("pause");
	return 0;
}

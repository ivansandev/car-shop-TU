#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <string.h>

void sortDate();

int main()
{
    int id;
    int productLength;
    char product[20];
    char productType[5];
    char date[12];

    FILE *fp;
    int runAgain;
    if ((fp = fopen("data.bin", "ab")) == NULL)
    {
        perror("Error writing.");
        exit(1);
    }
    while (1)
    {
        printf("ID: ");
        scanf("%d", &id);
        fwrite(&id, sizeof(int), 1, fp);
        getchar();

        printf("Product: ");
        fgets(product, 20, stdin);
        product[strlen(product)-1] = '\0';
        productLength = strlen(product)+1;

        fwrite(&productLength, sizeof(int), 1,fp);
        fwrite(product, 1, productLength, fp);

        printf("Product type: ");
        fgets(productType, 20, stdin);
        productType[strlen(productType)-1] = '\0';
        fwrite(productType, 1, 3, fp);
        
        printf("Date: ");
        fgets(date, 20, stdin);
        date[strlen(date)-1] = '\0';
        fwrite(date, 1, 10, fp);

        printf("Run again? ");
        scanf("%d", &runAgain);
        if (runAgain == 0)
            break;
        getchar();
    }
    fclose(fp);
	// system("pause");
	return 0;
}

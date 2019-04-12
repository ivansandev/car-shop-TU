#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <string.h>

struct carShop
{
    int id;
    int productLength;
    char product[20];
    char productType[5];
    char date[12];
};

struct carShop readFile(short *flag, FILE *fp);
short filter(char *type);
int outdated(char *givenDate);
char *findByID(char IDneeded);

int main()
{
    char type[10];
    printf("What is the type of product that you'd like to search for? \n");
    printf("Product type: ");
    scanf("%s", type);
    short sortSuccessful = filter(type);
    sortSuccessful ? printf("Filtering successful: yes.\n") : printf("Sorting successful: no");

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    char givenDate[12];
    printf("Filter out products older than a certain date...\n");
    printf("Please input the date by the format DD.MM.YYYY\n");
    printf("Date: ");
    scanf("%s", givenDate);
    int numberOutdatedProducts;
    numberOutdatedProducts = outdated(givenDate);
    printf("Number of products newer than %s: %d\nFile written.\n", givenDate, numberOutdatedProducts);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int IDneeded = 0;
    printf("Enter the ID of the product you are searching for...\n");
    printf("ID: ");
    scanf("%d", &IDneeded);
    printf("Product name of the specified ID: %s\n", findByID(IDneeded));

    system("pause");
    return 0;
}

struct carShop readFile(short *flag, FILE *fp)
{
    struct carShop car;

    if (fread(&car.id, sizeof(int), 1, fp) != 1)
    {
        *flag = 1;
    }
    if (fread(&car.productLength, sizeof(int), 1, fp) != 1)
    {
        *flag = 1;
    }
    if (fread(car.product, 1, car.productLength, fp) != car.productLength)
    {
        *flag = 1;
    }
    if (fread(car.productType, 1, 3, fp) != 3)
    {
        *flag = 1;
    }
    if (fread(car.date, 1, 10, fp) != 10)
    {
        *flag = 1;
    }

    return car;
}

short filter(char *type)
{
    short flag = 0;
    struct carShop car;

    FILE *fp, *fp2;

    if ((fp = fopen("data.bin", "rb")) == NULL)
    {
        perror("Error writing.");
        exit(1);
    }

    if ((fp2 = fopen("TV.bin", "wb")) == NULL)
    {
        perror("Error writing 2.");
        exit(2);
    }
    while (1)
    {
        car = readFile(&flag, fp);
        if (flag)
            break;
        // COMPARING PRODUCT TYPE TO PRODUCT TYPE
        if (strcmp(car.productType, type) == 0)
        {
            fwrite(&car.id, sizeof(int), 1, fp2);
            fwrite(&car.productLength, sizeof(int), 1, fp2);
            fwrite(car.product, 1, car.productLength, fp2);
            fwrite(car.productType, 1, 3, fp2);
            fwrite(car.date, 1, 10, fp2);
        }
    }
    fclose(fp);
    fclose(fp2);
    return 1;
}

int outdated(char *givenDate)
{
    short flag = 0;
    struct carShop car;

    char formattedDate[11];
    char formattedGivenDate[11];
    formattedGivenDate[0] = givenDate[6];
    formattedGivenDate[1] = givenDate[7];
    formattedGivenDate[2] = givenDate[8];
    formattedGivenDate[3] = givenDate[9];
    formattedGivenDate[4] = givenDate[5];
    formattedGivenDate[5] = givenDate[3];
    formattedGivenDate[6] = givenDate[4];
    formattedGivenDate[7] = givenDate[2];
    formattedGivenDate[8] = givenDate[0];
    formattedGivenDate[9] = givenDate[1];

    FILE *fp, *fp2;
    int count = 0;

    if ((fp = fopen("data.bin", "rb")) == NULL)
    {
        perror("Error writing.");
        exit(1);
    }
    if ((fp2 = fopen("OUTdated.bin", "wb")) == NULL)
    {
        perror("Error writing 2.");
        exit(2);
    }

    while (1)
    {
        car = readFile(&flag, fp);
        if (flag)
            break;
        car.date[10] = '\0';
        formattedDate[0] = car.date[6];
        formattedDate[1] = car.date[7];
        formattedDate[2] = car.date[8];
        formattedDate[3] = car.date[9];
        formattedDate[4] = car.date[5];
        formattedDate[5] = car.date[3];
        formattedDate[6] = car.date[4];
        formattedDate[7] = car.date[2];
        formattedDate[8] = car.date[0];
        formattedDate[9] = car.date[1];

        // formattedDate[10] = '\0';

        // printf("date: %s\n", formattedDate);
        // printf("formatted Given: %s\n", formattedGivenDate);
        // printf("strcmp: %d\n", strcmp(formattedDate, formattedGivenDate));

        if (strcmp(formattedDate, formattedGivenDate) > 0)
        {
            fwrite(&car.id, sizeof(int), 1, fp2);
            fwrite(&car.productLength, sizeof(int), 1, fp2);
            fwrite(car.product, 1, car.productLength, fp2);
            fwrite(car.productType, 1, 3, fp2);
            fwrite(car.date, 1, 10, fp2);
            count++;
        }
    }
    fclose(fp);
    fclose(fp2);
    return count;
}

char *findByID(char IDneeded)
{
    short flag = 0;
    struct carShop car;

    char emptyString[20];
    static char returnProduct[20];
    static char returnNoEntry[] = "NO ENTRY";

    FILE *fp, *fp2;

    if ((fp = fopen("data.bin", "rb")) == NULL)
    {
        perror("Error writing.");
        exit(1);
    }
    while (1)
    {
        car = readFile(&flag, fp);
        if (flag)
            break;
        if (car.id == IDneeded)
        {
            fclose(fp);
            strcpy(returnProduct, car.product);
            return returnProduct;
        }
    }
    fclose(fp);
    return returnNoEntry;
}
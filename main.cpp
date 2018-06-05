#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define null {NULL}

bool checkDigit(char);
void calcSum(char*, char*, int, int);
void calcMult(char*, char*, int, int);
char *reverse(char*, int);

size_t bufferSize = 100;

char sumResult[101] = null,
subResult[101] = null,
mulResult[100 * 100] = null;

int counterSum = 0;

int main()
{
    char *first = (char *)malloc(bufferSize),
            *second = (char *)malloc(bufferSize);

    // get numbers
    printf("Enter first number:\n");
    getline(&first, &bufferSize, stdin);

    printf("Enter second number:\n");
    getline(&second, &bufferSize, stdin);

    // calculate number's length
    int counterFirst = 0,
            counterSecond = 0;
    while (first[counterFirst] != '\n')
        counterFirst++;
    while (second[counterSecond] != '\n')
        counterSecond++;

    printf("first number's length: %d\n", counterFirst);
    printf("second number's length: %d\n", counterSecond);

    first = reverse(first, counterFirst);
    second = reverse(second, counterSecond);
    if (first == NULL || second == NULL)
        return 1;

    calcSum(first, second, counterFirst, counterSecond);

    printf("the resulting sum is:\n");
    for (int i = 0; i < counterSum; ++i) {
        printf("%c", sumResult[i]);
    }
    printf("\n");

    return 0;
}
void calcSum(char* first, char* second, int counterFirst, int counterSecond)
{
    int carrySum = 0;

    if (counterFirst == counterSecond)
    {
        for (int i = 0; i < counterFirst; ++i)
        {
            int a = first[i] - '0'
                    , b = second[i] - '0';
            int sum = a + b + carrySum;

            carrySum = sum / 10;
            sum %= 10;

            sumResult[counterSum++] = sum + '0';
        }
    }
    else
    {
        int i = 0;
        for (; i < (counterFirst < counterSecond ? counterFirst : counterSecond); ++i) {

            int a = first[i] - '0'
                    , b = second[i] - '0';
            int sum = a + b + carrySum;

            carrySum = sum / 10;
            sum %= 10;

            sumResult[counterSum++] = sum + '0';
        }
        if (counterFirst > counterSecond)
        {
            for (; i < counterFirst; ++i) {
                int a = first[i] - '0';
                int sum = a + carrySum;

                carrySum = sum / 10;
                sum %= 10;

                sumResult[counterSum++] = sum + '0';
            }
        }
        else // if (counterFirst < counterSecond)
        {
            for (; i < counterSecond; ++i) {

                int b = second[i] - '0';
                int sum = b + carrySum;

                carrySum = sum / 10;
                sum %= 10;

                sumResult[counterSum++] = sum + '0';
            }
        }
    }
    if (carrySum > 0)
        sumResult[counterSum++] = carrySum + '0';
    // reverse the result
    for (int i = 0; i < counterSum / 2; i++)
    {
        char tmp = sumResult[i];
        sumResult[i] = sumResult[(counterSum - 1) - i];
        sumResult[(counterSum - 1) - i] = tmp;
    }


}
char* reverse(char* str, int count)
{
    char *tmp = (char*)malloc(count);
    for (int i = 0; i < count; ++i)
    {
        if (!checkDigit(str[i]))
            return NULL;
        tmp[i] = str[(count - 1) - i];
    }
    return tmp;
}
void calcMult(char *first, char *second, int counterFirst, int counterSecond)
{
    if (counterFirst == counterSecond)
    {

    }
    else
    {

    }
}

bool checkDigit(char c)
{
    if (!(c >= '0' && c <= '9'))
        return false;
    return true;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define null {NULL}

bool checkDigit(char);
void calcSum(char*, char*, int, int);
void calcMult(char*, char*, int, int);
void calcSub(char*, char*, int, int);
char *reverse(char*, int);

size_t bufferSize = 100;

char sumResult[101],
subResult[101],
mulResult[100 + 100];

int counterSum = 0,
counterMul = 0,
counterSub = 0;

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
        if (checkDigit(first[counterFirst]))
            counterFirst++;
    while (second[counterSecond] != '\n')
        if (checkDigit(second[counterSecond]))
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

    calcMult(first, second, counterFirst, counterSecond);

    printf("the resulting multiplication is:\n");
    for (int i = 0; i < counterMul; ++i) {
        printf("%c", mulResult[i]);
    }
    printf("\n");

    calcSub(first, second, counterFirst, counterSecond);

    printf("the resulting subtraction is:\n");
    for (int i = 0; i < counterSub; ++i) {
        printf("%c", subResult[i]);
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
        tmp[i] = str[(count - 1) - i];
    }
    return tmp;
}
void calcMult(char *first, char *second, int counterFirst, int counterSecond)
{
    if (counterFirst == 0 || counterSecond == 0)
        return;

    memset(mulResult, '0', bufferSize * 2);

    counterMul = 0;
    for (int i = 0; i < counterFirst; ++i)
    {
        int a = first[i] - '0', carryMult = 0;
        int j = 0, c, carrySum;
        for (; j < counterSecond; ++j)
        {
            int b = second[j] - '0';
            int mul = a * b + carryMult;

            carryMult = mul / 10;
            mul %= 10;


            c = mulResult[counterMul + j] - '0';
            c += mul;
            carrySum = c / 10;
            c %= 10;
            mulResult[counterMul + j] = c + '0';


            for (int k = 1; k < counterFirst + counterSecond &&
                 carrySum > 0; ++k)
            {
                c = mulResult[counterMul + j + k] - '0';
                c += carrySum;

                carrySum = c / 10;
                c %= 10;
                mulResult[counterMul + j + k] = c + '0';
            }

        }
        j--;
        if (carryMult > 0)
        {
            for (int k = 1; k < counterFirst + counterSecond &&
                 carryMult > 0; ++k)
            {
                c = mulResult[counterMul + j + k] - '0';
                c += carryMult;

                carryMult = c / 10;
                c %= 10;
                mulResult[counterMul + j + k] = c + '0';
            }
        }

        counterMul++;
    }
    for (counterMul = counterFirst + counterSecond; counterMul >= 0; --counterMul)
        if (mulResult[counterMul] != '0')
            break;

    counterMul++;
    for (int i = 0; i < counterMul / 2; ++i) {
        char tmp = mulResult[i];
        mulResult[i] = mulResult[(counterMul - 1) - i];
        mulResult[(counterMul - 1) - i] = tmp;
    }
}

bool checkDigit(char c)
{
    if (!(c >= '0' && c <= '9'))
        return false;
    return true;
}
void calcSub(char* first, char* second, int counterFirst, int counterSecond)
{
    if (counterFirst < counterSecond) // first number is less than the second
        return;
    memset(subResult, '0', bufferSize);
    int i = 0;
    for (; i < counterSecond; ++i)
    {
        int a = first[i] - '0',
                b = second[i] - '0';
        int c;
        if (a >= b)
        {
            c = a - b;
        }
        else // if (a < b)
        {
            for (int j = i + 1; j < counterFirst; ++j)
            {
                int d = first[j] - '0';
                if (d > 0)
                {
                    for (int k = j; k > i; --k) // borrow chainly from higher ones to lower ones
                    {
                        d = first[k] - '0';
                        d--;
                        first[k] = d + '0';

                        int e = first[k - 1] - '0';
                        e += 10;
                        first[k - 1] = e + '0';
                    }
                    break;
                }
            }
            a = first[i] - '0';
            c = a - b;
        }
        if (c > 0)
            subResult[counterSub++] = c + '0';
        else
            counterSub = 0;
    }
    for (; i < counterFirst; ++i)
    {
        subResult[counterSub++] = first[i];
    }

    for (i = 0; i < counterFirst / 2; ++i) {
        char tmp = subResult[i];
        subResult[i] = subResult[(counterFirst - 1) - i];
        subResult[(counterFirst - 1) - i] = tmp;
    }

}


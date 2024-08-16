#include <stdio.h>

// time cost is O(logN)
int GCD(int m, int n)
{
    unsigned int r;
    while (n > 0)
    {
        r = m % n;
        m = n;
        n = r;
    }
    return m;
}

int main()
{
    int m, n;
    printf("please input two numbers: ");
    scanf("%d %d", &m, &n);
    printf("The GCD of %d and %d is %d\n", m, n, GCD(m, n));
    return 0;
}
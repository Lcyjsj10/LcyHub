#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
    double a = 2.0;
    double b = 3.0;
    printf("3.0^2是%f\n", pow(b, a));
    printf("-5的绝对值是%d\n", abs(-5));
    printf("-a的绝对值是%f\n", fabsf(-a));
    printf("3.1416的正弦值是%lf,余弦值是%lf,正切值是%lf\n", sin(3.1416), cos(3.1416), tan(3.1416));
    printf("3.1416的反正弦值是%lf,反余弦值是%lf,反正切值是%lf\n", asin(3.1416), acos(3.1416), atan(3.1416));
    printf("lne等于%f,lg100等于%f,log256等于%f\n", log(2.71828), log10(100.0), log2(256.0));
    printf("-4.5四舍五入位%f,上取整函数为%f,下取整函数为%f\n", round(-4.5), ceil(-4.5), floor(-4.5));
}
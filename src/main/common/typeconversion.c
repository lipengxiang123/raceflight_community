/* 
 * This file is part of RaceFlight. 
 * 
 * RaceFlight is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation, either version 3 of the License, or 
 * (at your option) any later version. 
 * 
 * RaceFlight is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * GNU General Public License for more details. 
 * 
 * You should have received a copy of the GNU General Public License 
 * along with RaceFlight.  If not, see <http://www.gnu.org/licenses/>.
 * You should have received a copy of the GNU General Public License 
 * along with RaceFlight.  If not, see <http://www.gnu.org/licenses/>.
 */ 
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "build_config.h"
#include "maths.h"
#ifdef REQUIRE_PRINTF_LONG_SUPPORT
void uli2a(unsigned long int num, unsigned int base, int uc, char *bf)
{
    int n = 0;
    unsigned int d = 1;
    while (num / d >= base)
        d *= base;
    while (d != 0) {
        int dgt = num / d;
        num %= d;
        d /= base;
        if (n || dgt > 0 || d == 0) {
            *bf++ = dgt + (dgt < 10 ? '0' : (uc ? 'A' : 'a') - 10);
            ++n;
        }
    }
    *bf = 0;
}
void li2a(long num, char *bf)
{
    if (num < 0) {
        num = -num;
        *bf++ = '-';
    }
    uli2a(num, 10, 0, bf);
}
#endif
void ui2a(unsigned int num, unsigned int base, int uc, char *bf)
{
    int n = 0;
    unsigned int d = 1;
    while (num / d >= base)
        d *= base;
    while (d != 0) {
        int dgt = num / d;
        num %= d;
        d /= base;
        if (n || dgt > 0 || d == 0) {
            *bf++ = dgt + (dgt < 10 ? '0' : (uc ? 'A' : 'a') - 10);
            ++n;
        }
    }
    *bf = 0;
}
void i2a(int num, char *bf)
{
    if (num < 0) {
        num = -num;
        *bf++ = '-';
    }
    ui2a(num, 10, 0, bf);
}
int a2d(char ch)
{
    if (ch >= '0' && ch <= '9')
        return ch - '0';
    else if (ch >= 'a' && ch <= 'f')
        return ch - 'a' + 10;
    else if (ch >= 'A' && ch <= 'F')
        return ch - 'A' + 10;
    else
        return -1;
}
char a2i(char ch, const char **src, int base, int *nump)
{
    const char *p = *src;
    int num = 0;
    int digit;
    while ((digit = a2d(ch)) >= 0) {
        if (digit > base)
            break;
        num = num * base + digit;
        ch = *p++;
    }
    *src = p;
    *nump = num;
    return ch;
}
#ifndef HAVE_ITOA_FUNCTION
static char *_i2a(unsigned i, char *a, unsigned base)
{
    if (i / base > 0)
        a = _i2a(i / base, a, base);
    *a = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[i % base];
    return a + 1;
}
char *itoa(int i, char *a, int base)
{
    if ((base < 2) || (base > 36))
        base = 10;
    if (i < 0) {
        *a = '-';
        *_i2a(-(unsigned) i, a + 1, base) = 0;
    } else
        *_i2a(i, a, base) = 0;
    return a;
}
#endif
char *ftoa(float x, char *floatString)
{
    int32_t value;
    char intString1[12];
    char intString2[12] = { 0, };
    char *decimalPoint = ".";
    uint8_t dpLocation;
    if (x > 0)
        x += 0.0005f;
    else
        x -= 0.0005f;
    value = (int32_t)(x * 1000.0f);
    itoa(ABS(value), intString1, 10);
    if (value >= 0)
        intString2[0] = ' ';
    else
        intString2[0] = '-';
    if (strlen(intString1) == 1) {
        intString2[1] = '0';
        intString2[2] = '0';
        intString2[3] = '0';
        strcat(intString2, intString1);
    } else if (strlen(intString1) == 2) {
        intString2[1] = '0';
        intString2[2] = '0';
        strcat(intString2, intString1);
    } else if (strlen(intString1) == 3) {
        intString2[1] = '0';
        strcat(intString2, intString1);
    } else {
        strcat(intString2, intString1);
    }
    dpLocation = strlen(intString2) - 3;
    strncpy(floatString, intString2, dpLocation);
    floatString[dpLocation] = '\0';
    strcat(floatString, decimalPoint);
    strcat(floatString, intString2 + dpLocation);
    return floatString;
}
#define white_space(c) ((c) == ' ' || (c) == '\t')
#define valid_digit(c) ((c) >= '0' && (c) <= '9')
float fastA2F(const char *p)
{
    int frac = 0;
    float sign, value, scale;
    while (white_space(*p)) {
        p += 1;
    }
    sign = 1.0f;
    if (*p == '-') {
        sign = -1.0f;
        p += 1;
    } else if (*p == '+') {
        p += 1;
    }
    value = 0.0f;
    while (valid_digit(*p)) {
        value = value * 10.0f + (*p - '0');
        p += 1;
    }
    if (*p == '.') {
        float pow10 = 10.0f;
        p += 1;
        while (valid_digit(*p)) {
            value += (*p - '0') / pow10;
            pow10 *= 10.0f;
            p += 1;
        }
    }
    scale = 1.0f;
    if ((*p == 'e') || (*p == 'E')) {
        unsigned int expon;
        p += 1;
        frac = 0;
        if (*p == '-') {
            frac = 1;
            p += 1;
        } else if (*p == '+') {
            p += 1;
        }
        expon = 0;
        while (valid_digit(*p)) {
            expon = expon * 10 + (*p - '0');
            p += 1;
        }
        if (expon > 308)
            expon = 308;
        while (expon >= 8) {
            scale *= 1E8f;
            expon -= 8;
        }
        while (expon > 0) {
            scale *= 10.0f;
            expon -= 1;
        }
    }
    return sign * (frac ? (value / scale) : (value * scale));
}

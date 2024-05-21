// Code ripped from https://www.sanfoundry.com/c-program-implement-rsa-algorithm/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Define variables
long int p, q, n, t, e[100], d[100], m[100], en[100], flag, temp[100], j, i;
char msg[100];
long int jMax = 0;

// Define functions
int prime(long int);
void ce();
long int cd(long int);
void encrypt();
void decrypt();

void main() {
    printf("\n[+] Enter first prime number: ");
    scanf("%d", &p);
    flag = prime(p);

    if (flag == 0) {
        printf("\n[-] Error: Invalid input. Exiting...\n");
        // getch();
        exit(1);
    }

    printf("\n[+] Enter another prime number: ");
    scanf("%d", &q);
    flag = prime(q);

    if (flag == 0 || p == q) {
        printf("\n[-] Error: Invalid input. Exiting...\n");
        // getch();
        exit(1);
    }

    printf("\n[+] Enter a message: ");
    fflush(stdin);
    scanf("%s", msg);

    for (i = 0; msg[i] != '\0'; i++) {
        m[i] = msg[i];
    }
        
    n = p * q;
    t = (p - 1) * (q - 1);
    ce();

    if (j < 2) {
        printf(
            "\n[-] Error: Entered primes are too small. Aborting...\n"
        );
        exit(1);
    } else {
        printf(
            "\nPossible values of e and d are: \\
            \n-------------------------------"
        );
        for (i = 0; i < jMax - 1; i++) {
            printf("\n%ld\t%ld", e[i], d[i]);
        }
        printf(
            "\n------------------------------\n"
        );
    }

    encrypt();
    decrypt();
}

int prime(long int pr) {
    /* 
    Taking the square root removes redundant calculations.
    While this algorithm isn't perfect computationally, it is simple and it works.
     */
    int i;
    j = sqrt(pr);

    if (j > jMax) {
        jMax = j;
    }

    for (i = 2; i <= j; i++) {
        if (pr % i == 0) {
            return 0;
        }
    }

    return 1;
}

void ce() {
    int k;
    k = 0;
    for (i = 2; i < t; i++) {
        if (t % i == 0) {
            continue;
        }

        flag = prime(i);
        if (flag == 1 && i != p && i != q) {
            e[k] = i;
            flag = cd(e[k]);
            if (flag > 0) {
                d[k] = flag;
                k++;
            }

            if (k == 99) { // If we've hit the char limit
                break;
            }
        }
    }
}

long int cd(long int x) {
    long int k = 1;
    while (1) {
        k = k + t;
        if (k % x == 0) {
            return (k / x);
        }
    }
}

void encrypt() {
    long int pt, ct, key = e[0], k, len;
    i = 0;
    len = strlen(msg);
    while (i != len) {
        pt = msg[i];
        pt = pt - 96; // Offset for ascii encoding
        k = 1;
        for (j = 0; j < key; j++) {
            k = k * pt;
            k = k % n;
        }
        temp[i] = k;
        ct = k + 96;
        en[i] = ct;
        i++;
    }

    en[i] = -1;
    printf("\n[>] The encrypted message:");
    for (i = 0; en[i] != -1; i++) {
        printf("%c", en[i]);
    }
}

void decrypt() {
    long int pt, ct, key = d[0], k;
    i = 0;
    while (en[i] != -1) {
        ct = temp[i];
        k = 1;
        for (j = 0; j < key; j++) {
            k = k * ct;
            k = k % n;
        }

        pt = k + 96; // Revert offset
        m[i] = pt;
        i++;
    }

    m[i] = -1;
    printf("\n[<] The decrypted message:\n");
    for (i = 0; m[i] != -1; i++) {
        printf("%c", msg[i]);
    }
    printf("\n");
}
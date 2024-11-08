#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MINPRIME 100
#define MAXPRIME 999

// 소수 판별 함수
int isPrime(int n) {
    if (n < 2) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;

    // 홀수만 판별
    int limit = sqrt(n);
    for (int i = 3; i <= limit; i += 2) {
        if (n % i == 0) return 0;  // 합성수면 0 리턴
    }
    return 1;  // 소수면 1 리턴
}

// 소수 랜덤 생성 함수
int genPrime() {
    int p;

    // MINPRIME ~ MAXPRIME 사이 소수 생성
    do {
        p = rand() % (MAXPRIME - MINPRIME + 1) + MINPRIME;
    } while (!isPrime(p));

    return p;
}

// gcd 함수(유클리드 호제법)
int getGCD(int x, int y) {
    int remain = 0;
    while (y != 0) {
        remain = x % y;
        x = y;
        y = remain;
    }
    return x;
}

// lcm 함수
int getLCM(int x, int y) { return ((x * y) / getGCD(x, y)); }

// 키 생성 함수
void genKeyE(int* e, int* d, int* n) {
    int p, q, l, et, dt;

    p = genPrime();
    q = genPrime();
    *n = p * q;
    l = getLCM(p - 1, q - 1);

    // 1<E<L, gcd(E,L)==1 만족하는 E 값 랜덤 생성
    do {
        et = rand() % ((l - 1) - 2 + 1) + 2;
    } while (getGCD(et, l) != 1);

    // 1<D<L, (E * D mod L)==1 만족하는 D 값 랜덤 생성
    for (int i = 2; i < l; i++) {
        if ((et * i) % l == 1) {
            dt = i;
            break;
        }
    }

    *e = et;
    *d = dt;

    // 임시 확인용
    printf("p=%d q=%d\nn=%d\nl=%d\ne=%d\nd=%d\n", p, q, *n, l, *e, *d);
    printf("gcd(p,q)=%d, gcd(p-1,q-1)=%d, gcd(e,l)=%d\n", getGCD(p, q),
           getGCD(p - 1, q - 1), getGCD(et, l));

}


// 암호화 함수

// 복호화 함수

int main(void) {
    srand(time(NULL));
    int e, d, n;
    genKeyE(&e, &d, &n);

    return 0;
}
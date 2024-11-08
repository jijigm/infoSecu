#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MINPRIME 100
#define MAXPRIME 999

int isPrime(int n);
int genPrime();
int gcd(int p, int q);
int lcm(int p, int q);
void genKeyE(int* E, int* D, int* N);

int main(void) {
    srand(time(NULL));
    int E, D, N;
    genKeyE(&E, &D, &N);

    return 0;
}

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
int gcd(int p, int q) {
    int remain = 0;
    while (q != 0) {
        remain = p % q;
        p = q;
        q = remain;
    }
    return p;
}

// lcm 함수
int lcm(int p, int q) { 
    return ((p * q) / gcd(p, q)); 
}

// 키 생성 함수
void genKeyE(int* E, int* D, int* N) {
    int p, q, e, d, L;

    p = genPrime();
    q = genPrime();
    L = lcm(p - 1, q - 1);

    // 1<E<L, gcd(E,L)==1 만족하는 E 값 랜덤 생성
    do {
        e = rand() % ((L - 1) - 2 + 1) + 2;
    } while (gcd(e, L) != 1);

    // 1<D<L, (E * D mod L)==1 만족하는 D 값 랜덤 생성
    for (int i = 2; i < L; i++) {
        if ((e * i) % L == 1) {
            d = i;
            break;
        }
    }

    *E = e;
    *D = d;
    *N = p * q;

    // 임시 확인용
    printf("p=%d q=%d\nL=%d\nN=%d\nE=%d\nD=%d\n", p, q, L,*N ,*E, *D);
    printf("gcd(p,q)=%d, gcd(p-1,q-1)=%d, gcd(E,l)=%d\n", gcd(p, q),
           gcd(p - 1, q - 1), gcd(e, L));

}


// 암호화 함수

// 복호화 함수


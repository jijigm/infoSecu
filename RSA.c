/*
	제목: RSA 알고리즘 구현
    교과목: 정보보안개론
    담당 교수: 박정민 교수
    학번: 
    이름: 
    과제 제출일: 24.10.02
*/
#define _CRT_SECURE_NO_WARNINGS
#define MAX 5
#define MAXPRIME 200
#define MINPRIME 100

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Queue {
    int text[MAX];
    int front;
    int rear;
} QueueType;

// 소수 판별
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

// 랜덤 소수 생성
int genPrime() {
    int p;

    // MINPRIME ~ MAXPRIME 사이 소수 생성
    do {
        p = rand() % (MAXPRIME - MINPRIME + 1) + MINPRIME;
    } while (!isPrime(p));

    return p;
}

// 최대공약수 리턴
int gcd(int p, int q) {
    int temp;

    while (q != 0) {
        temp = p % q;
        p = q;
        q = temp;
    }

    return p;
}

// 최소공배수 리턴
int lcm(int p, int q) { return p * q / gcd(p, q); }

// E 값을 구해서 리턴
int genE(int L) {
    int num;

    for (num = 2; num < L; num++)          // 1 < E < L
        if (gcd(num, L) == 1) return num;  // 조건에 부합하는 가장 작은 수

    return -1;
}

// D 값을 구해서 리턴
int genD(int E, int L) {
    int num;

    for (num = 2; num < L; num++)            // 1 < D < L
        if ((E * num) % L == 1) return num;  // 조건에 부합하는 가장 작은 수

    return -1;
}

// 고속 지수 모듈러 연산
int mod_exp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }

    return result;
}

// 암호화
int encryption(int plainText, int E, int N) { return mod_exp(plainText, E, N); }

// 복호화
int decryption(int cipherText, int D, int N) {
    return mod_exp(cipherText, D, N);
}

// 큐 구현 코드
void initQueue(QueueType* q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(QueueType* q) { return q->front == -1; }

int isFull(QueueType* q) { return (q->rear + 1) % MAX == q->front; }

void enqueue(QueueType* q, int value) {
    if (isFull(q)) {
        printf("큐가 가득 찼습니다.\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % MAX;
    q->text[q->rear] = value;
}

int dequeue(QueueType* q) {
    if (isEmpty(q)) {
        printf("큐가 비어 있습니다.\n");
        return -1;
    }
    int value = q->text[q->front];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }
    return value;
}

// main 함수
int main(void) {
    int plainText, cipherText, decryptedText;
    int p, q, N, L, E, D;
    int index = 0;

    QueueType plainTextQueue;
    QueueType cipherTextQueue;
    QueueType decryptedTextQueue;

    initQueue(&plainTextQueue);
    initQueue(&cipherTextQueue);
    initQueue(&decryptedTextQueue);

    srand(time(NULL));

    // p, q 생성
    do {
        p = genPrime();
        q = genPrime();
    } while (p == q);

    // N, L, E, D 생성
    N = p * q;
    L = lcm(p - 1, q - 1);
    E = genE(L);
    D = genD(E, L);

    // 평문 입력 받기
    for (int i = 0; i < MAX; i++) {
        while (1) {
            printf("평문 입력(숫자로): ");
            scanf("%d", &plainText);  // 평문입력
            if (plainText > N)
                printf("평문이 N(%d)보다 큽니다. 다시 입력하세요.\n", N);
            else
                break;
        }

        enqueue(&plainTextQueue, plainText);  // 평문을 평문큐에 저장

        cipherText = encryption(plainText, E, N);	// 암호문 생성
        enqueue(&cipherTextQueue, cipherText);

        decryptedText = decryption(cipherText, D, N);	// 복호문 생성
        enqueue(&decryptedTextQueue, decryptedText);
    }

    printf("\n");
    printf("N: %d\nL: %d\nE: %d\nD: %d", N, L, E, D);
    printf("\n");

    for (int i = 0; i < MAX; i++) {
        printf("\n");
        printf("평문: %d\n", dequeue(&plainTextQueue));
        printf("암호문: %d\n", dequeue(&cipherTextQueue));
        printf("복호문: %d\n", dequeue(&decryptedTextQueue));
    }

    return 0;
}
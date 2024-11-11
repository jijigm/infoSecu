/*
	����: RSA �˰��� ����
    ������: �������Ȱ���
    ��� ����: ������ ����
    �й�: 
    �̸�: 
    ���� ������: 24.10.02
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

// �Ҽ� �Ǻ�
int isPrime(int n) {
    if (n < 2) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;

    // Ȧ���� �Ǻ�
    int limit = sqrt(n);
    for (int i = 3; i <= limit; i += 2) {
        if (n % i == 0) return 0;  // �ռ����� 0 ����
    }
    return 1;  // �Ҽ��� 1 ����
}

// ���� �Ҽ� ����
int genPrime() {
    int p;

    // MINPRIME ~ MAXPRIME ���� �Ҽ� ����
    do {
        p = rand() % (MAXPRIME - MINPRIME + 1) + MINPRIME;
    } while (!isPrime(p));

    return p;
}

// �ִ����� ����
int gcd(int p, int q) {
    int temp;

    while (q != 0) {
        temp = p % q;
        p = q;
        q = temp;
    }

    return p;
}

// �ּҰ���� ����
int lcm(int p, int q) { return p * q / gcd(p, q); }

// E ���� ���ؼ� ����
int genE(int L) {
    int num;

    for (num = 2; num < L; num++)          // 1 < E < L
        if (gcd(num, L) == 1) return num;  // ���ǿ� �����ϴ� ���� ���� ��

    return -1;
}

// D ���� ���ؼ� ����
int genD(int E, int L) {
    int num;

    for (num = 2; num < L; num++)            // 1 < D < L
        if ((E * num) % L == 1) return num;  // ���ǿ� �����ϴ� ���� ���� ��

    return -1;
}

// ��� ���� ��ⷯ ����
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

// ��ȣȭ
int encryption(int plainText, int E, int N) { return mod_exp(plainText, E, N); }

// ��ȣȭ
int decryption(int cipherText, int D, int N) {
    return mod_exp(cipherText, D, N);
}

// ť ���� �ڵ�
void initQueue(QueueType* q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(QueueType* q) { return q->front == -1; }

int isFull(QueueType* q) { return (q->rear + 1) % MAX == q->front; }

void enqueue(QueueType* q, int value) {
    if (isFull(q)) {
        printf("ť�� ���� á���ϴ�.\n");
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
        printf("ť�� ��� �ֽ��ϴ�.\n");
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

// main �Լ�
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

    // p, q ����
    do {
        p = genPrime();
        q = genPrime();
    } while (p == q);

    // N, L, E, D ����
    N = p * q;
    L = lcm(p - 1, q - 1);
    E = genE(L);
    D = genD(E, L);

    // �� �Է� �ޱ�
    for (int i = 0; i < MAX; i++) {
        while (1) {
            printf("�� �Է�(���ڷ�): ");
            scanf("%d", &plainText);  // ���Է�
            if (plainText > N)
                printf("���� N(%d)���� Ů�ϴ�. �ٽ� �Է��ϼ���.\n", N);
            else
                break;
        }

        enqueue(&plainTextQueue, plainText);  // ���� ��ť�� ����

        cipherText = encryption(plainText, E, N);	// ��ȣ�� ����
        enqueue(&cipherTextQueue, cipherText);

        decryptedText = decryption(cipherText, D, N);	// ��ȣ�� ����
        enqueue(&decryptedTextQueue, decryptedText);
    }

    printf("\n");
    printf("N: %d\nL: %d\nE: %d\nD: %d", N, L, E, D);
    printf("\n");

    for (int i = 0; i < MAX; i++) {
        printf("\n");
        printf("��: %d\n", dequeue(&plainTextQueue));
        printf("��ȣ��: %d\n", dequeue(&cipherTextQueue));
        printf("��ȣ��: %d\n", dequeue(&decryptedTextQueue));
    }

    return 0;
}
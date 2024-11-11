#define _CRT_SECURE_NO_WARNINGS
#define MAX 5
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

int genPrime(void) {
    int randNum = rand();

    while (randNum < 100 || randNum > 200) {  // ���������Ǵ� ���� ��������
        randNum = rand();
    }

    for (int i = 2; i < randNum; i++) {  // �������ڰ� �Ҽ��� �ƴϸ� �ٽ� ����
        if (randNum % i == 0) {
            randNum = rand();
            while (randNum < 100 || randNum > 200) randNum = rand();
            i = 1;
        }
    }

    return randNum;
}

int gcd(int p, int q) {
    int temp;

    while (q != 0) {
        temp = p % q;
        p = q;
        q = temp;
    }

    return p;
}

int lcm(int p, int q) { return p * q / gcd(p, q); }

int genE(int L) {
    int num;

    for (num = 2; num < L; num++)          // 1 < E < L
        if (gcd(num, L) == 1) return num;  // ���ǿ� �����ϴ� ���� ���� ��

    return -1;
}

int genD(int E, int L) {
    int num;

    for (num = 2; num < L; num++)            // 1 < D < L
        if ((E * num) % L == 1) return num;  // ���ǿ� �����ϴ� ���� ���� ��

    return -1;
}

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

int encryption(int plainText, int E, int N) { return mod_exp(plainText, E, N); }

int decryption(int cipherText, int D, int N) {
    return mod_exp(cipherText, D, N);
}

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

    do {
        p = genPrime();
        q = genPrime();
    } while (p == q);

    N = p * q;
    L = lcm(p - 1, q - 1);
    E = genE(L);
    D = genD(E, L);

    for (int i = 0; i < MAX; i++) {
        while (1) {
            printf("�� �Է�(���ڷ�): ");
            scanf("%d", &plainText);  // ���Է�
            if (plainText > N)
                printf("���� N���� Ů�ϴ�. �ٽ� �Է��ϼ���.\n");
            else
                break;
        }

        enqueue(&plainTextQueue, plainText);  // ���� ��ť�� ����

        cipherText = encryption(plainText, E, N);
        enqueue(&cipherTextQueue, cipherText);

        decryptedText = decryption(cipherText, D, N);
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
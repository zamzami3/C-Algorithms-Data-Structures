#include <stdio.h>
#include <stdlib.h>

#define M 999
#define N 5

typedef int itemType;
typedef struct {
    itemType item[N];
    int front;
    int rear;
    int count;
} queue;

typedef struct {
    itemType data[N];
    int count;
} stack;

void initialize_q(queue *);
int queue_kosong(queue *);
int queue_penuh(queue *);
void enqueue(itemType, queue *);
itemType dequeue(queue *);

void initialize_s(stack *);
int stack_kosong(stack *);
int stack_penuh(stack *);
void push(itemType, stack *);
itemType pop(stack *);

void djikstra();
void inisialisasiTQR();
int dalam_antrian(itemType, queue *);
void rute();

void input();
void matriks();
void tampil(int [N][N]);

int Q[N][N] = {
    {M, 1, 3, M, M},
    {M, M, 1, M, 5},
    {3, M, M, 2, M},
    {M, M, M, M, 1},
    {M, M, M, M, M}
};

int TQ[N], R[N];
int asal, tujuan;

int main() {
    puts("Graph Djikstra");
    tampil(Q);
    input();
    djikstra();
    rute();
    matriks();
    puts("");
    return 0;
}

void matriks () {
    printf("Matriks TQ: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", TQ[i]);
    }
    puts("");
    printf("Matriks R: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", R[i]);
    }
}

void rute() {
    stack tumpukan;
    initialize_s(&tumpukan);
    int tujuan_asli = tujuan;
    printf("Rute dari %d ke %d = ", asal + 1, tujuan + 1);
    while (R[tujuan] != asal) {
        push(R[tujuan], &tumpukan);
        tujuan = R[tujuan];
    }
    printf("%d - ", asal + 1);
    while (!stack_kosong(&tumpukan)) {
        printf("%d - ", pop(&tumpukan) + 1);
    }
    printf("%d\n", tujuan_asli + 1);
    printf("Total beban = %d\n", TQ[tujuan_asli]);
}

void input() {
    printf("Masukkan asal: ");
    scanf("%d", &asal);
    asal--;
    printf("Masukkan tujuan: ");
    scanf("%d", &tujuan);
    tujuan--;
}

void djikstra() {
    queue antrian;
    initialize_q(&antrian);
    inisialisasiTQR();

    enqueue(asal, &antrian);
    while (!queue_kosong(&antrian)) {
        int currentNode = dequeue(&antrian);
        for (int i = 0; i < N; i++) {
            if (Q[currentNode][i] != M && Q[currentNode][i] + TQ[currentNode] < TQ[i]) {
                TQ[i] = Q[currentNode][i] + TQ[currentNode];
                R[i] = currentNode;
                if (i != asal && i != tujuan && !dalam_antrian(i, &antrian)) {
                    enqueue(i, &antrian);
                }
            }
        }
    }
}

void inisialisasiTQR() {
    for (int i = 0; i < N; i++) {
        if (i == asal) {
            TQ[i] = 0;
        } else {
            TQ[i] = M;
        }
    }
    for (int i = 0; i < N; i++) {
        R[i] = -1;
    }
}

int dalam_antrian(itemType x, queue *q) {
    for (int i = 0; i < q->count; i++) {
        int index = (q->front + i) % N;
        if (q->item[index] == x) {
            return 1;
        }
    }
    return 0;
}

void initialize_q(queue *q) {
    q->count = 0;
    q->front = 0;
    q->rear = 0;
}

int queue_kosong(queue *q) {
    return (q->count == 0);
}

int queue_penuh(queue *q) {
    return (q->count == N);
}

void enqueue(itemType x, queue *q) {
    if (!queue_penuh(q)) {
        q->item[q->rear] = x;
        q->rear = (q->rear + 1) % N;
        q->count++;
    } else {
        puts("Queue penuh.");
    }
}

itemType dequeue(queue *q) {
    if (!queue_kosong(q)) {
        itemType temp = q->item[q->front];
        q->front = (q->front + 1) % N;
        q->count--;
        return temp;
    } else {
        puts("Queue kosong.");
    }
}

void initialize_s(stack *s) {
    s->count = 0;
}

int stack_kosong(stack *s) {
    return (s->count == 0);
}

int stack_penuh(stack *s) {
    return (s->count == N);
}

void push(itemType x, stack *s) {
    if (!stack_penuh(s)) {
        s->data[s->count] = x;
        s->count++;
    } else {
        puts("Stack penuh.");
    }
}

itemType pop(stack *s) {
    if (!stack_kosong(s)) {
        s->count--;
        return s->data[s->count];
    } else {
        puts("Stack Kosong.");
    }
}

void tampil(int matriks[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matriks[i][j] == M)
                printf("M ");
            else
                printf("%d ", matriks[i][j]);
        }
        puts("");
    }
}

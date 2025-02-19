#include <stdio.h>
#include <stdlib.h>

typedef struct simpul Dnode;
struct simpul {
    int data;
    Dnode *previous, *next;
};

Dnode *head = NULL, *p, *before;

void pesantempat();
void tampil();
void dll_insertawal();
void dll_insertakhir();
void dll_insertbefore();

int main () {
    char jawab;

    puts ("\tDouble Linked List Insert Akhir\t");
    do {
        fflush(stdin);
        pesantempat();
        dll_insertakhir();
        fflush(stdin);
        printf ("Ingin menambah data lagi? (Y/T) ");
        jawab = getchar();
    } while ((jawab == 'y') || (jawab == 'Y'));
    tampil();
    puts ("Insert Before");
    fflush (stdin);
    pesantempat();
    fflush (stdin);
    dll_insertbefore();
    tampil();
    return 0;
}

void dll_insertbefore(){
    int key;

    printf ("Mau di taruh before node ke berapa? ");
    scanf ("%d", &key);

    before = head;

    if (head -> data == key) {
        dll_insertawal();
    } else {
        while (before -> data != key) {
            if (before -> next == NULL) {
                printf ("%d tidak ada", key);
                exit (0);
            } else {
                before = before -> next;
            }
        }
    p -> next = before;
    p -> previous = before -> previous;
    before -> previous -> next = p;
    before -> previous = p;
    }
}

void pesantempat() {
    int bil;

    printf ("Bilangan yang mau disimpan? ");
    scanf ("%d", &bil);

    p = (Dnode*) malloc (sizeof (Dnode));
    if (p == NULL) {
        puts ("Alokasi nya gagal");
        exit (0);
    } else {
        p -> data = bil;
        p -> next = NULL;
        p -> previous = NULL;
    }
}
void tampil(){
    Dnode *read;

    puts ("Isi dari DLL: ");
    read = head;

    while (read != NULL) {
        printf ("%d\n", read -> data);
        read = read -> next;
    }
}

void dll_insertakhir() {
    Dnode *tail;
    if (head != NULL) {
        tail = head;
        while (tail -> next != NULL)
            tail = tail -> next;
        p -> previous = tail;
        tail -> next = p;
        tail = p;
    } else {
        head = p;
    }
}

void dll_insertawal(){
    if (head != NULL) {
        p -> next = head;
        head -> previous = p;
    }
    head = p;
}

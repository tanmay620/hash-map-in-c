#include <stdio.h>
#include <string.h>

#define TABLE_SIZE 10
#define EMPTY_KEY ""

typedef struct {
    char key[50];
    int value;
} HashEntry;

HashEntry hashTable[TABLE_SIZE];
unsigned int hashFunction(const char* key) {
    unsigned int hash = 0;
    while (*key)
        hash = (hash * 31) + *key++;
    return hash % TABLE_SIZE;
}

void insert(const char* key, int value) {
    unsigned int index = hashFunction(key);
    while (strlen(hashTable[index].key) != 0) {
        index = (index + 1) % TABLE_SIZE;//linear probing
    }
    strcpy(hashTable[index].key, key);
    hashTable[index].value = value;
}


int search(const char* key) {
    unsigned int index = hashFunction(key);
    int startIndex = index;

    while (strlen(hashTable[index].key) != 0) {
        if (strcmp(hashTable[index].key, key) == 0)
            return hashTable[index].value;
        index = (index + 1) % TABLE_SIZE;
        if (index == startIndex) break;
    }
    return -1;
}

void display() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (strlen(hashTable[i].key) != 0)
            printf("Index %d: (%s, %d)\n", i, hashTable[i].key, hashTable[i].value);
        else
            printf("Index %d: EMPTY\n", i);
    }
}

int main() {
    insert("TUser1", 25);
    insert("User2", 90);
    insert("charli", 35);

    printf("Value for 'User2': %d\n", search("User2"));
    printf("Value for 'charli': %d\n", search("charli"));

    display();

    return 0;
}

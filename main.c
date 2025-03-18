#include <stdio.h>
#include <string.h>

#define TABLE_SIZE 10
#define EMPTY_KEY ""

typedef struct {
    char key[50];
    int value;
} HashEntry;

HashEntry hashTable[TABLE_SIZE];

// Hash function
unsigned int hashFunction(const char* key) {
    unsigned int hash = 0;
    while (*key)
        hash = (hash * 31) + *key++;
    return hash % TABLE_SIZE;
}

// Insert key-value pair
void insert(const char* key, int value) {
    unsigned int index = hashFunction(key);
    while (strlen(hashTable[index].key) != 0) { // Find an empty slot
        index = (index + 1) % TABLE_SIZE; // Linear probing
    }
    strcpy(hashTable[index].key, key);
    hashTable[index].value = value;
}

// Search for a key
int search(const char* key) {
    unsigned int index = hashFunction(key);
    int startIndex = index;

    while (strlen(hashTable[index].key) != 0) {
        if (strcmp(hashTable[index].key, key) == 0)
            return hashTable[index].value;
        index = (index + 1) % TABLE_SIZE; // Linear probing
        if (index == startIndex) break; // Full loop, key not found
    }
    return -1;
}

// Display the hash table
void display() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (strlen(hashTable[i].key) != 0)
            printf("Index %d: (%s, %d)\n", i, hashTable[i].key, hashTable[i].value);
        else
            printf("Index %d: EMPTY\n", i);
    }
}

// Main function
int main() {
    insert("Alice", 25);
    insert("Bob", 30);
    insert("Charlie", 35);

    printf("Value for 'Alice': %d\n", search("Alice"));
    printf("Value for 'Bob': %d\n", search("Bob"));

    display();

    return 0;
}

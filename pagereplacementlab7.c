#include <stdio.h>
#include <stdbool.h>

bool search(int key, int fr[], int capacity) {
    for (int i = 0; i < capacity; i++)
        if (fr[i] == key)
            return true;
    return false;
}

int predict(int pages[], int fr[], int pn, int index, int capacity) {
    int res = -1, farthest = index;
    for (int i = 0; i < capacity; i++) {
        int j;
        for (j = index; j < pn; j++) {
            if (fr[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == pn)
            return i;
    }
    return (res == -1) ? 0 : res;
}

void fifo(int pages[], int n, int capacity) {
    int fr[capacity];
    int page_faults = 0, page_hits = 0;
    int index = 0;

    for (int i = 0; i < n; i++) {
        if (!search(pages[i], fr, capacity)) {
            fr[index] = pages[i];
            index = (index + 1) % capacity;
            page_faults++;
        } else {
            page_hits++;
        }
    }
    printf("FIFO Page Faults: %d, Page Hits: %d\n", page_faults, page_hits);
}

void optimal(int pages[], int n, int capacity) {
    int fr[capacity];
    int page_faults = 0, page_hits = 0;
    int filled = 0;

    for (int i = 0; i < n; i++) {
        if (search(pages[i], fr, capacity)) {
            page_hits++;
            continue;
        }

        if (filled < capacity) {
            fr[filled++] = pages[i];
        } else {
            int j = predict(pages, fr, n, i + 1, capacity);
            fr[j] = pages[i];
        }
        page_faults++;
    }
    printf("Optimal Page Faults: %d, Page Hits: %d\n", page_faults, page_hits);
}

void lru(int pages[], int n, int capacity) {
    int fr[capacity];
    int recent[capacity];
    int page_faults = 0, page_hits = 0;
    int time = 0;

    for (int i = 0; i < capacity; i++) {
        fr[i] = -1;
        recent[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        bool hit = false;

        for (int j = 0; j < capacity; j++) {
            if (fr[j] == pages[i]) {
                time++;
                recent[j] = time;
                page_hits++;
                hit = true;
                break;
            }
        }

        if (!hit) {
            int lru = 0;
            for (int j = 1; j < capacity; j++)
                if (recent[j] < recent[lru])
                    lru = j;

            time++;
            fr[lru] = pages[i];
            recent[lru] = time;
            page_faults++;
        }
    }

    printf("LRU Page Faults: %d, Page Hits: %d\n", page_faults, page_hits);
}

int main() {
    int n, capacity;
    printf("Enter the size of the pages:\n");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page strings:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter the no of page frames:\n");
    scanf("%d", &capacity);

    fifo(pages, n, capacity);
    optimal(pages, n, capacity);
    lru(pages, n, capacity);

    return 0;
}

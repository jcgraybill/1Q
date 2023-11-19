#include <typeinfo>
#include <cstdlib>

struct node {
        uint64_t value;
        node *next;
};

node *g_head = NULL;
node *g_tail = NULL;
uint64_t g_length = 0;

uint64_t queue_length() {
        return g_length;
}

void enqueue(uint64_t value) {
        node *n = (node*)std::malloc(sizeof(node));
        n->value = value;
        n->next = NULL;
        if (g_tail) {
                g_tail->next = n;
        }
        if (! g_head) {
                g_head = n;
        } 
        g_tail = n;
        g_length++;
}

uint64_t dequeue() {
        if (g_head) {
                int value = g_head->value;
                node *previous_head = g_head;
                g_head = g_head->next;
                std::free(previous_head);
                g_length--;
                return value;
        } else {
                std::exit(1);
        }
}

bool queue_is_empty() {
    return g_length == 0;
}
#include <iostream>
#include <cctype>

struct node {
    int status;
    char data;
    struct node *next;
    struct node *adj;
};

struct node *p, *q, *start, *k, *l;

void create() {
    int flag = 0;
    char dat;
    start = nullptr;
    std::cout << "Enter the nodes in the graph (press x to exit): ";

    while (true) {
        std::cin >> dat;
        if (dat == 'x') {
            break;
        }
        p = new node;
        p->data = dat;
        p->status = 0;
        p->next = nullptr;
        p->adj = nullptr;

        if (flag == 0) {
            start = p;
            q = p;
            flag++;
        } else {
            q->next = p;
            q = p;
        }
    }
    p = start;
    while (p != nullptr) {
        std::cout << "Enter the links to " << p->data << " (x to exit): ";
        flag = 0;
        while (true) {
            std::cin >> dat;
            if (dat == 'x') {
                break;
            }
            k = new node;
            k->adj = nullptr;

            if (flag == 0) {
                p->adj = k;
                l = k;
                flag++;
            } else {
                l->adj = k;
                l = k;
            }
            q = start;
            while (q != nullptr) {
                if (q->data == dat) {
                    k->next = q;
                    q = q->next;
                    break; // Exit loop once node is found
                }
                q = q->next; // Ensure q progresses to avoid infinite loop
            }
        }
        p = p->next;
    }
}

void dfsUtil(node *startnode) {
    int sp = -1;
    node *stack[100];
    p = startnode;
    std::cout << p->data;
    p->status = -1;
    k = p->adj;

    while (true) {
        if (k != nullptr) {
            sp++;
            stack[sp] = k;
            q = k->next;

            if (q != nullptr && q->status == 0) {
                std::cout << " " << q->data;
                q->status = 1;
                k = q->adj;
            } else {
                k = k->adj;
            }
        } else {
            if (sp >= 0) {
                k = stack[sp];
                sp--;
                k = k->adj;
            } else {
                break;
            }
        }
    }
}

void dfs() {
    p = start;
    while (p != nullptr) {
        p->status = 0;
        p = p->next;
    }
    p = start;
    while (p != nullptr) {
        if (p->status == 0) {
            dfsUtil(p);
        }
        p = p->next;
    }
}

int main() {
    create();
    std::cout << "\n\nDFS for graph: ";
    dfs();
    std::cin.get(); // Use std::cin.get() instead of getchar() for better compatibility
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// BST Node
struct Node {
    char name[30];
    char phone[15];
    struct Node *left, *right;
};

// Create new node
struct Node* createNode(char name[], char phone[]) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->name, name);
    strcpy(newNode->phone, phone);
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert contact
struct Node* insert(struct Node* root, char name[], char phone[]) {
    if (root == NULL)
        return createNode(name, phone);

    if (strcmp(name, root->name) < 0)
        root->left = insert(root->left, name, phone);
    else if (strcmp(name, root->name) > 0)
        root->right = insert(root->right, name, phone);
    else
        printf("\nContact already exists!\n");

    return root;
}

// Search contact
void search(struct Node* root, char name[]) {
    if (root == NULL) {
        printf("\nContact not found.\n");
        return;
    }

    if (strcmp(name, root->name) == 0) {
        printf("\nContact Found!\nName: %s\nPhone: %s\n", root->name, root->phone);
    }
    else if (strcmp(name, root->name) < 0)
        search(root->left, name);
    else
        search(root->right, name);
}

// Find minimum value node
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Delete contact
struct Node* deleteNode(struct Node* root, char name[]) {
    if (root == NULL)
        return root;

    if (strcmp(name, root->name) < 0)
        root->left = deleteNode(root->left, name);
    else if (strcmp(name, root->name) > 0)
        root->right = deleteNode(root->right, name);
    else {
        // Node with one or no child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children
        struct Node* temp = minValueNode(root->right);
        strcpy(root->name, temp->name);
        strcpy(root->phone, temp->phone);
        root->right = deleteNode(root->right, temp->name);
    }
    return root;
}

// Display contacts (Inorder Traversal)
void display(struct Node* root) {
    if (root != NULL) {
        display(root->left);
        printf("Name: %-15s Phone: %s\n", root->name, root->phone);
        display(root->right);
    }
}

// Main function
int main() {
    struct Node* root = NULL;
    int choice;
    char name[30], phone[15];

    do {
        printf("\n--- Phone Directory System ---\n");
        printf("1. Insert Contact\n");
        printf("2. Search Contact\n");
        printf("3. Delete Contact\n");
        printf("4. Display All Contacts\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter Name: ");
            scanf("%s", name);
            printf("Enter Phone: ");
            scanf("%s", phone);
            root = insert(root, name, phone);
            break;

        case 2:
            printf("Enter Name to Search: ");
            scanf("%s", name);
            search(root, name);
            break;

        case 3:
            printf("Enter Name to Delete: ");
            scanf("%s", name);
            root = deleteNode(root, name);
            printf("Contact deleted (if existed).\n");
            break;

        case 4:
            printf("\nPhone Directory (Sorted Order):\n");
            display(root);
            break;

        case 5:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}

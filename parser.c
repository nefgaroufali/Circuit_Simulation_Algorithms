#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Structure to represent a circuit element
typedef struct CircuitElement {
    char type; // Type of the element (V, I, R, C, L, D, M, Q, etc.)
    char* name; // Name of the element
    char* node_plus; // First node
    char* node_minus; // Second node
    double value; // Value of the element
    struct CircuitElement* next; // Pointer to the next element in the linked list
} CircuitElement;

// Function to create a new CircuitElement
CircuitElement* createCircuitElement(char type, const char* name, const char* node_plus, const char* node_minus, double value) {
    CircuitElement* element = (CircuitElement*)malloc(sizeof(CircuitElement));
    element->name = (char*)malloc((strlen(name)+1)*sizeof(char));
    element->node_plus = (char*)malloc((strlen(node_plus)+1)*sizeof(char));
    element->node_minus = (char*)malloc((strlen(node_minus)+1)*sizeof(char));
    element->type = type;
    strcpy(element->name, name);
    strcpy(element->node_plus, node_plus);
    strcpy(element->node_minus, node_minus);
    element->value = value;
    element->next = NULL;
    return element;
}

// Function to add a new CircuitElement to the linked list
void addCircuitElement(CircuitElement** head, CircuitElement* element) {
    if (*head == NULL)
    {
        *head = element;
    }
    else
    {
        CircuitElement* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = element;
    }
}

// Function to print the list of circuit elements
void printCircuitElements(CircuitElement* head)
{
    CircuitElement* current = head;
    while (current != NULL)
    {
        printf("Type: %c, Name: %s, Node_plus: %s, Node_minus: %s, Value: %f\n", current->type, current->name, current->node_plus, current->node_minus, current->value);
        current = current->next;
    }
}

int main()
{
    FILE* file = fopen("test.txt", "r"); // Replace "sample.spice" with your input file name

    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    CircuitElement* head = NULL; // Linked list head

    char type, name[64], node1[64], node2[64];
    double value;

    while (fscanf(file, " %c %s %s %s %lf", &type, name, node1, node2, &value) == 5)
    {
        CircuitElement* element = createCircuitElement(type, name, node1, node2, value);
        addCircuitElement(&head, element);
    }

    fclose(file);

    // Print the list of circuit elements
    printCircuitElements(head);

    return 0;
}
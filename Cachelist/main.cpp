#include <iostream>
#include "LinkedList.h"
#include <cstring>
#define MAX_COMMAND_LENGTH 100

using namespace std;

int main() {
    LinkedList list;
    char command[MAX_COMMAND_LENGTH];
    unsigned long long int value;
    int iteratorNumber;
    int index;

    while(!feof(stdin))
    {
        scanf("%s", command);
        if(feof(stdin)!=0) {
            break;
        }
        else if (strcmp(command, ".A") == 0) {
            scanf("%s", command);
            cin >> value;
            if (strcmp(command, "BEG") == 0) {
                list.InsertBefore(list.getNodeAtIndex(0), value);
            } else if (strcmp(command, "END") == 0) {
                list.InsertBefore(list.getNodeAtIndex(list.getSize()-1), value);
            } else {
                sscanf(command, "%d", &iteratorNumber);
                list.InsertBefore(list.getIterator(iteratorNumber), value);
            }
        } else if (strcmp(command, "A.") == 0) {
            scanf("%s", command);
            cin >> value;
            if (strcmp(command, "BEG") == 0) {
                list.InsertAfter(list.getNodeAtIndex(0), value);
            } else if (strcmp(command, "END") == 0) {
                list.InsertAfter(list.getNodeAtIndex(list.getSize()-1), value);
            } else {
                sscanf(command, "%d", &iteratorNumber);
                list.InsertAfter(list.getIterator(iteratorNumber), value);
            }
        } else if (strcmp(command, "P") == 0) {
            scanf("%s", command);
            if (strcmp(command, "ALL") == 0)
                list.PrintAll();
            else {
                sscanf(command, "%d", &iteratorNumber);
                list.PrintIterator(iteratorNumber);
            }
        } else if (strcmp(command, "I") == 0) {
            cin >> iteratorNumber;
            continue;
        } else if (strcmp(command, "R") == 0) {
            scanf("%s", command);
            if (strcmp(command, "BEG") == 0) {
                list.Remove(list.getNodeAtIndex(0));
            } else if (strcmp(command, "END") == 0) {
                list.Remove(list.getNodeAtIndex(list.getSize()-1));
            } else {
                sscanf(command, "%d", &iteratorNumber);
                list.Remove(list.getIterator(iteratorNumber));
            }
        } else if (strcmp(command, "i") == 0) {
            cin >> iteratorNumber;
            scanf("%s", command);
            if (strcmp(command, "BEG") == 0) {
                list.InitializeIterator(iteratorNumber, 0);
            } else if (strcmp(command, "END") == 0) {
                list.InitializeIterator(iteratorNumber, list.getSize() - 1);
            } else {
                sscanf(command, "%d", &index);
                list.InitializeIterator(iteratorNumber, index);
            }
        } else if (strcmp(command, "+") == 0) {
            scanf("%s", command);
            sscanf(command, "%d", &iteratorNumber);
            list.MoveIteratorForward(iteratorNumber);
        } else if (strcmp(command, "-") == 0) {
            scanf("%s", command);
            sscanf(command, "%d", &iteratorNumber);
            list.MoveIteratorBackwards(iteratorNumber);
        }
    }
    return 0;
}

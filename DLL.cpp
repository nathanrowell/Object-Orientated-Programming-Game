// Nathan Rowell Section 013
#include "DNode.hpp"
#include "DLL.hpp"
#include <iostream>
#include <cstdlib>
using namespace std;

DLL::DLL(){
    first = nullptr;
    last = nullptr;
    numTasks = 0;
    tothrs = 0;
    totmin = 0;
}

DLL::DLL(string t, int p, int h, int m){
    DNode *newNode = new DNode(t,p,h,m);
    first = newNode;
    last = newNode;
    numTasks = 1;
    tothrs += newNode->task->hr;
    totmin += newNode->task->min;

}

DLL::~DLL(){
    DNode *current = first;
    DNode *temp = new DNode();
    while (current != nullptr) {
        temp = current->next;
        delete temp;
        current = current->next;


    }

}

void DLL::push(string n, int p, int h, int m) {
    DNode *current = first;
    DNode *newNode = new DNode(n,p,h,m);
    if (current == nullptr) {
        first = newNode;
        last = newNode;
        addTime(first->task->hr,first->task->min);
    }
    else {
        while (current->next != nullptr and current->task->priority < p) {
            current = current->next;



        }
        while (current->next != nullptr and current->next->task->priority == p) {
            current = current->next;
        }
        DNode *temp = current->next;
        current->next = newNode;
        newNode->prev = current;
        newNode->next = temp;
        if (newNode->next != nullptr) {
            newNode->next->prev = newNode;
        }

        if (current->next->next == nullptr)
            last = newNode;
        addTime(newNode->task->hr,newNode->task->min);
    }
    numTasks++;


}

Task *DLL::pop() {
    DNode *temp = first;
    first = first->next;
    first->prev = nullptr;
    numTasks--;
    temp->next = nullptr;
    temp->prev = nullptr;
    removeTime(temp->task->hr,temp->task->min);
    return temp->task;


}

int DLL::remove(int tn) {
    DNode *current = first;
    while (current != nullptr) {
        if (current->task->tasknum == tn) {
            removeTime(current->task->hr,current->task->min);

            if (current->next == nullptr && current->prev == nullptr) {
                first = nullptr;
                last = nullptr;
                delete current;
                return tn;
            }
            if (current == last) {
                last = current->prev;
                current->prev->next = nullptr;
                delete current;

            }
            else if (current == first) {
                first = current->next;
                current->next->prev = nullptr;
                delete current;

            }
            else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
            }
            numTasks--;
            return tn;
        }
        current = current->next;
    }
    delete current;
    return -1;
}

void DLL::addTime(int h, int m) {
    tothrs += h;
    totmin += m;
    if (totmin > 60) {
        while (totmin > 60) {
            tothrs += 1;
            totmin -= 60;
        }
    }

}

void DLL::removeTime(int h, int m) {
    tothrs -= h;
    totmin -= m;
    if (totmin < 0) {
        tothrs -= 1;
        totmin = 60 + totmin;
    }

}

void DLL::moveUp(int t) {
    DNode *current = first;
    DNode *temp;
    while (current != nullptr) {
        if (current->task->tasknum == t) {
            if (current == first) {
                first = current->next;
                first->prev = nullptr;
                last->next = current;
                current->prev = last;
                last = current;
                current->next = nullptr;
                current->task->priority = current->prev->task->priority;
            }
            else if (current->prev->prev == nullptr) {
                current->task->priority = current->prev->task->priority;
                temp = current->prev;
                current->prev = nullptr;
                temp->next=current->next;
                current->next=temp;
                temp->prev=current;
                first = current;
            }
            else {
                current->task->priority = current->prev->task->priority;
                temp = current->prev;
                current->prev->prev->next = current;
                current->prev = current->prev->prev;
                temp->next=current->next;
                current->next=temp;
                temp->prev=current;
                if (temp->next != nullptr) {
                    temp->next->prev = temp;
                }


            }
        }
        current = current->next;
    }
    delete temp;
}

void DLL::moveDown(int t) {
    DNode *current = last;
    DNode *temp;
    while (current != nullptr) {
        if (current->task->tasknum == t) {
            if (current == last) {
                last = current->prev;
                last->next=nullptr;
                first->prev = current;
                current->next=first;
                first = current;
                current->prev=nullptr;
                current->task->priority = current->next->task->priority;
            }
            else if (current->next->next == nullptr) {
                current->task->priority = current->prev->task->priority;
                temp = current->next;
                current->next = nullptr;
                temp->prev=current->prev;
                current->prev->next=temp;
                current->prev=temp;
                temp->next=current;
                last = current;
            }
            else {
                current->task->priority = current->next->task->priority;
                temp = current->next;
                current->next->next->prev=current;
                current->next = current->next->next;
                temp->prev=current->prev;
                current->prev=temp;
                temp->next=current;
                if (temp->prev == nullptr) {
                    first = temp;}



            }
        }
        current = current->prev;
    }
    delete temp;

}

void DLL::changePriority(int tn, int newp) {
    DNode *current = first;
    while (current != nullptr) {
        if (current->task->tasknum == tn) {
            current->task->priority = newp;
            break;
        }
        current = current->next;
    }
    Task *temp;
    temp->task = current->task->task;
    temp->priority = current->task->priority;
    temp->hr = current->task->hr;
    temp->min = current->task->min;
    tn = remove(current->task->tasknum);
    current = first;
    DNode *newNode = new DNode(temp->task,temp->priority,temp->hr,temp->min);
    newNode->task->tasknum = tn;
    if (current == nullptr) {
        first = newNode;
        last = newNode;
        addTime(first->task->hr,first->task->min);
    }
    else {
        while (current->next != nullptr and current->task->priority < temp->priority) {
            current = current->next;



        }
        while (current->next != nullptr and current->next->task->priority == temp->priority) {
            current = current->next;
        }
        DNode *temp = current->next;
        current->next = newNode;
        newNode->prev = current;
        newNode->next = temp;
        if (newNode->next != nullptr) {
            newNode->next->prev = newNode;
        }

        if (current->next->next == nullptr)
            last = newNode;
        addTime(newNode->task->hr,newNode->task->min);
    }
    numTasks++;

}

void DLL::listDuration(int *th, int *tm,int tp) {
    DNode *current = first;
    while (current != nullptr) {
        if (current->task->priority == tp) {
            *th += current->task->hr;
            *tm += current->task->min;
        }
        current = current->next;
    }
    if (*tm > 60) {
        while (*tm > 60) {
            *tm -= 60;
            *th += 1;
        }
    }

}

void DLL::printList() {
    cout << "Total Time Required: "<<tothrs<< ":"<<totmin<<endl;
    DNode *current = first;
    while (current != nullptr) {
        current->task->printTask();
        current = current->next;
    }
    cout << endl;

}

void DLL::printList(int p) {
    tothrs = 0;
    totmin = 0;
    DNode *current = first;
    while (current != NULL) {
        if (current->task->priority == p) {
            addTime(current->task->hr,current->task->min);
        }
        current = current->next;
    }
    cout << p <<": Total Time Required: "<< tothrs << ":"<< totmin <<endl;
    current = first;
    while (current != NULL) {
        if (current->task->priority == p) {
            current->task->printTask();
        }
        current = current->next;
    }
    cout << endl;
}

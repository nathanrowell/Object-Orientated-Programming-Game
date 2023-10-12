/*DNode.cpp*
        Created on: Apr 2, 2020
Author: 13027
*/
// Nathan Rowell Section 013
#include <cstdlib>
#include <iostream>
#include "DNode.hpp"
using namespace std;

DNode::DNode(string t, int p, int m, int s) {
    task = new Task(t, p, m, s);
    next = nullptr;
    prev = nullptr;
}
DNode::DNode() {
    task = nullptr;
    next = nullptr;
    prev = nullptr;
}
/* write your constructors here! */
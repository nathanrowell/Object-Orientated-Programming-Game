
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "TaskManager.hpp"
using namespace std;

int main() {
	srand(time(NULL));
	TaskManager *list = new TaskManager("C:\\Users\\Natha\\Downloads\\DLLTaskManager\\ListofTasks.txt");
}


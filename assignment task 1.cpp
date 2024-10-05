#include <iostream>
using namespace std;

// Node structure to represent each process
struct Process {
    int process_id;
    int execution_time;
    int remaining_time;
    Process* next;

    // Constructor to initialize a process
    Process(int id, int exec_time) {
        process_id = id;
        execution_time = exec_time;
        remaining_time = exec_time;
        next = nullptr;
    }
};

// Circular Linked List class to manage processes
class ProcessList {
private:
    Process* head;  // Head of the circular linked list
    int quantum;    // Time quantum for each cycle

public:
    ProcessList(int q) : head(nullptr), quantum(q) {}

    // Function to add a new process
    void addProcess(int id, int exec_time) {
        Process* newProcess = new Process(id, exec_time);
        if (!head) {
            head = newProcess;
            head->next = head;
        }
        else {
            Process* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newProcess;
            newProcess->next = head;
        }
    }

    // Function to simulate process scheduling
    void scheduleProcesses() {
        Process* current = head;
        Process* prev = nullptr;

        while (head) {
            cout << "\nProcess " << current->process_id << " is running." << endl;

            // Assign quantum time to process or use the remaining time if it's less than quantum
            int time_to_run = (current->remaining_time < quantum) ? current->remaining_time : quantum;
            current->remaining_time -= time_to_run;

            // Display remaining time of the current process
            cout << "Process " << current->process_id << " executed for " << time_to_run << " units. "
                << "Remaining time: " << current->remaining_time << " units." << endl;

            // Check if process has finished execution
            if (current->remaining_time <= 0) {
                cout << "Process " << current->process_id << " has completed execution and is removed.\n";

                // If the only process left, remove it and exit
                if (current == head && current->next == head) {
                    delete current;
                    head = nullptr;
                    return;
                }

                // Remove the process from the circular linked list
                if (current == head) {
                    // Head process is completing, update the head
                    Process* tail = head;
                    while (tail->next != head) {
                        tail = tail->next;
                    }
                    head = head->next;
                    tail->next = head;
                    delete current;
                    current = head;
                }
                else {
                    prev->next = current->next;
                    delete current;
                    current = prev->next;
                }
            }
            else {
                // Move to the next process if the current process hasn't finished
                prev = current;
                current = current->next;
            }
        }
    }

    // Function to display the state of the system
    void displayProcesses() {
        if (!head) {
            cout << "No processes in the system.\n";
            return;
        }

        Process* temp = head;
        do {
            cout << "Process ID: " << temp->process_id << ", Remaining Time: " << temp->remaining_time << endl;
            temp = temp->next;
        } while (temp != head);
    }
};

int main() {
    int quantum_time;
    cout << "Enter the quantum time: ";
    cin >> quantum_time;

    // Create the process list with the given quantum time
    ProcessList processList(quantum_time);

    // Add processes to the list
    processList.addProcess(1, 10);  // Process 1 with 10 units of execution time
    processList.addProcess(2, 5);   // Process 2 with 5 units of execution time
    processList.addProcess(3, 8);   // Process 3 with 8 units of execution time

    // Display initial process list
    cout << "Initial State of Processes:" << endl;
    processList.displayProcesses();

    // Start scheduling the processes
    cout << "\nStarting CPU Scheduling...\n";
    processList.scheduleProcesses();

    return 0;
}

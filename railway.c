#include <iostream>
using namespace std;

struct Coach {
    int id;
    int capacity;
    Coach* prev;
    Coach* next;
};

Coach* head = nullptr;
Coach* tail = nullptr;

// Add coach at the end
void addCoach(int id, int capacity) {
    Coach* newCoach = new Coach{id, capacity, nullptr, nullptr};

    if (head == nullptr) {
        head = tail = newCoach;
    } else {
        tail->next = newCoach;
        newCoach->prev = tail;
        tail = newCoach;
    }

    cout << "Coach added successfully!\n";
}

// Add coach at beginning
void addFirst(int id, int capacity) {
    Coach* newCoach = new Coach{id, capacity, nullptr, head};

    if (head == nullptr) {
        head = tail = newCoach;
    } else {
        head->prev = newCoach;
        head = newCoach;
    }

    cout << "Coach added at beginning!\n";
}

// Insert coach at a position (1-based)
void insertCoach(int id, int capacity, int pos) {
    if (pos <= 1 || head == nullptr) {
        addFirst(id, capacity);
        return;
    }

    Coach* temp = head;
    int i = 1;

    while (temp->next != nullptr && i < pos - 1) {
        temp = temp->next;
        i++;
    }

    Coach* newCoach = new Coach{id, capacity, temp, temp->next};

    if (temp->next != nullptr)
        temp->next->prev = newCoach;
    else
        tail = newCoach;

    temp->next = newCoach;

    cout << "Coach inserted successfully!\n";
}

// Delete coach by ID
void deleteCoach(int id) {
    Coach* temp = head;

    while (temp != nullptr && temp->id != id)
        temp = temp->next;

    if (temp == nullptr) {
        cout << "Coach not found!\n";
        return;
    }

    if (temp->prev != nullptr)
        temp->prev->next = temp->next;
    else
        head = temp->next;

    if (temp->next != nullptr)
        temp->next->prev = temp->prev;
    else
        tail = temp->prev;

    delete temp;
    cout << "Coach deleted successfully!\n";
}

// Display forward
void displayForward() {
    if (head == nullptr) {
        cout << "Train is empty!\n";
        return;
    }

    Coach* temp = head;
    cout << "\nENGINE <-> ";

    while (temp != nullptr) {
        cout << "[Coach " << temp->id
             << ", Capacity " << temp->capacity << "]";

        if (temp->next != nullptr)
            cout << " <-> ";

        temp = temp->next;
    }

    cout << " <-> END\n";
}

// Display backward
void displayBackward() {
    if (tail == nullptr) {
        cout << "Train is empty!\n";
        return;
    }

    Coach* temp = tail;
    cout << "\nEND <-> ";

    while (temp != nullptr) {
        cout << "[Coach " << temp->id << "] <-> ";
        temp = temp->prev;
    }

    cout << "ENGINE\n";
}

// Search coach
void searchCoach(int id) {
    Coach* temp = head;

    while (temp != nullptr) {
        if (temp->id == id) {
            cout << "Coach found! ID: " << temp->id
                 << ", Capacity: " << temp->capacity << "\n";
            return;
        }
        temp = temp->next;
    }

    cout << "Coach not found!\n";
}

// Count coaches and calculate capacity
void trainInfo() {
    int count = 0, total = 0;
    Coach* temp = head;

    while (temp != nullptr) {
        count++;
        total += temp->capacity;
        temp = temp->next;
    }

    cout << "\nTotal Coaches: " << count;
    cout << "\nTotal Passenger Capacity: " << total << "\n";
}

// Free memory
void clearTrain() {
    while (head != nullptr) {
        Coach* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
}

int main() {
    int choice, id, capacity, pos;

    do {
        cout << "\n===== TRAIN COACH MANAGEMENT =====\n";
        cout << "1. Add Coach at End\n";
        cout << "2. Add Coach at Beginning\n";
        cout << "3. Insert Coach at Position\n";
        cout << "4. Delete Coach\n";
        cout << "5. Display Train Forward\n";
        cout << "6. Display Train Backward\n";
        cout << "7. Search Coach\n";
        cout << "8. Train Information\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Coach ID and Capacity: ";
            cin >> id >> capacity;
            addCoach(id, capacity);
            break;

        case 2:
            cout << "Enter Coach ID and Capacity: ";
            cin >> id >> capacity;
            addFirst(id, capacity);
            break;

        case 3:
            cout << "Enter Coach ID and Capacity: ";
            cin >> id >> capacity;
            cout << "Enter position: ";
            cin >> pos;
            insertCoach(id, capacity, pos);
            break;

        case 4:
            cout << "Enter Coach ID to delete: ";
            cin >> id;
            deleteCoach(id);
            break;

        case 5:
            displayForward();
            break;

        case 6:
            displayBackward();
            break;

        case 7:
            cout << "Enter Coach ID to search: ";
            cin >> id;
            searchCoach(id);
            break;

        case 8:
            trainInfo();
            break;

        case 9:
            clearTrain();
            cout << "Train Simulator Closed!\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 9);

    return 0;
}

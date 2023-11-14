#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Define the structure for a student
struct Student {
    string name;
    int id;
    float grade;

    // Constructor to initialize data members
    Student(string n, int i) : name(n), id(i), grade(0) {}

    // Function to input grade for a student
    void inputGrade() {
        cout << "Enter grade for " << name << ": ";
        cin >> grade;
    }
};

// Function to calculate the average grade of a vector of students
float calculateAverage(const vector<Student>& students) {
    float sum = 0;
    for (const Student& s : students) {
        sum += s.grade;
    }
    return students.empty() ? 0 : sum / students.size();
}

// Function to display student information
void displayStudents(const vector<Student>& students) {
    cout << setw(15) << "Name" << setw(10) << "ID" << setw(10) << "Grade" << endl;
    cout << "------------------------------------" << endl;
    for (const Student& s : students) {
        cout << setw(15) << s.name << setw(10) << s.id << setw(10) << s.grade << endl;
    }
    cout << "------------------------------------" << endl;
    cout << "Average Grade: " << calculateAverage(students) << endl;
}

// Bubble Sort algorithm to sort students based on their grades
void bubbleSort(vector<Student>& students) {
    int n = students.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (students[j].grade > students[j + 1].grade) {
                // Swap students[j] and students[j + 1]
                swap(students[j], students[j + 1]);
            }
        }
    }
}

// Binary Search algorithm to find a student by ID
int binarySearch(const vector<Student>& students, int targetID) {
    int low = 0;
    int high = students.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (students[mid].id == targetID) {
            return mid; // Found the student
        } else if (students[mid].id < targetID) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1; // Student with the given ID not found
}

// Function to find the highest and lowest grades among students
void findHighestAndLowestGrades(const vector<Student>& students, float& highest, float& lowest) {
    if (students.empty()) {
        highest = 0;
        lowest = 0;
        return;
    }

    highest = students[0].grade;
    lowest = students[0].grade;

    for (const Student& s : students) {
        if (s.grade > highest) {
            highest = s.grade;
        }
        if (s.grade < lowest) {
            lowest = s.grade;
        }
    }
}

// Function to display a histogram of grade distribution
void displayGradeHistogram(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students available. Please add a student first.\n";
        return;
    }

    const int numBins = 10;  // Number of bins for the histogram
    vector<int> gradeCounts(numBins, 0);
    float binSize = (calculateAverage(students) / numBins);

    for (const Student& s : students) {
        int binIndex = s.grade / binSize;
        if (binIndex == numBins) {
            binIndex--;
        }
        gradeCounts[binIndex]++;
    }

    cout << "Grade Distribution Histogram:" << endl;
    for (int i = 0; i < numBins; i++) {
        float binStart = i * binSize;
        float binEnd = (i + 1) * binSize;
        cout << fixed << setprecision(2) << "[" << binStart << " - " << binEnd << "]: ";
        for (int j = 0; j < gradeCounts[i]; j++) {
            cout << "*";
        }
        cout << endl;
    }
}

int main() {
    vector<Student> students; // Vector to store student information
    int choice;

    do {
        cout << "1. Add Student\n";
        cout << "2. Enter Grades\n";
        cout << "3. Display Students\n";
        cout << "4. Sort Students by Grade\n";
        cout << "5. Search for Student by ID\n";
        cout << "6. Calculate Highest and Lowest Grades\n";
        cout << "7. Display Grade Distribution Histogram\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
                 case 1: {
                string name;
                int id;
                cout << "Enter student name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter student ID: ";
                cin >> id;
                students.push_back(Student(name, id));
                break;
            }
            case 2: {
                if (students.empty()) {
                    cout << "No students available. Please add a student first.\n";
                } else {
                    for (Student& s : students) {
                        s.inputGrade();
                    }
                }
                break;
            }
            case 3: {
                if (students.empty()) {
                    cout << "No students available. Please add a student first.\n";
                } else {
                    displayStudents(students);
                }
                break;
            }
            case 4: {
                if (students.empty()) {
                    cout << "No students available. Please add a student first.\n";
                } else {
                    bubbleSort(students);
                    cout << "Students sorted by grade.\n";
                }
                break;
            }
            case 5: {
                if (students.empty()) {
                    cout << "No students available. Please add a student first.\n";
                } else {
                    int targetID;
                    cout << "Enter student ID to search: ";
                    cin >> targetID;
                    int result = binarySearch(students, targetID);
                    if (result != -1) {
                        cout << "Student found:\n";
                        cout << "Name: " << students[result].name << "\n";
                        cout << "ID: " << students[result].id << "\n";
                        cout << "Grade: " << students[result].grade << "\n";
                    } else {
                        cout << "Student with ID " << targetID << " not found.\n";
                    }
                }
                break;
            }
            case 6: {
                float highest, lowest;
                findHighestAndLowestGrades(students, highest, lowest);
                cout << "Highest Grade: " << highest << endl;
                cout << "Lowest Grade: " << lowest << endl;
                break;
            }
            case 7: {
                displayGradeHistogram(students);
                break;
            }
            case 8:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 8);

    return 0;
}
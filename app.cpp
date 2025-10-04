#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Student {
    int id;
    char name[50];
    float gpa;
    char className[50];
};

struct Student students[MAX];
int n = 0;

HWND hEditID, hEditName, hEditGPA, hEditClass, hListBox;

void ShowStudents(HWND hwnd);
void DeleteStudent(int id);
void UpdateStudent(int id, char *newName, float newGpa, char *newClass);
void ExportToExcel();

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            CreateWindow("static", "ID:", WS_VISIBLE | WS_CHILD,
                         20, 20, 80, 20, hwnd, NULL, NULL, NULL);
            hEditID = CreateWindow("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
                                   100, 20, 150, 20, hwnd, NULL, NULL, NULL);

            CreateWindow("static", "Name:", WS_VISIBLE | WS_CHILD,
                         20, 60, 80, 20, hwnd, NULL, NULL, NULL);
            hEditName = CreateWindow("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
                                     100, 60, 150, 20, hwnd, NULL, NULL, NULL);

            CreateWindow("static", "GPA:", WS_VISIBLE | WS_CHILD,
                         20, 100, 80, 20, hwnd, NULL, NULL, NULL);
            hEditGPA = CreateWindow("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
                                    100, 100, 150, 20, hwnd, NULL, NULL, NULL);

            CreateWindow("static", "Class:", WS_VISIBLE | WS_CHILD,
                         20, 140, 80, 20, hwnd, NULL, NULL, NULL);
            hEditClass = CreateWindow("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
                                      100, 140, 150, 20, hwnd, NULL, NULL, NULL);

            CreateWindow("button", "Add Student", WS_VISIBLE | WS_CHILD,
                         280, 20, 120, 30, hwnd, (HMENU)1, NULL, NULL);

            CreateWindow("button", "Show Students", WS_VISIBLE | WS_CHILD,
                         280, 60, 120, 30, hwnd, (HMENU)2, NULL, NULL);

            CreateWindow("button", "Delete Student", WS_VISIBLE | WS_CHILD,
                         280, 100, 120, 30, hwnd, (HMENU)3, NULL, NULL);

            CreateWindow("button", "Update Student", WS_VISIBLE | WS_CHILD,
                         280, 140, 120, 30, hwnd, (HMENU)4, NULL, NULL);

            CreateWindow("button", "Export to Excel", WS_VISIBLE | WS_CHILD,
                         280, 180, 120, 30, hwnd, (HMENU)5, NULL, NULL);

            hListBox = CreateWindow("listbox", NULL,
                                    WS_VISIBLE | WS_CHILD | WS_BORDER | LBS_NOTIFY,
                                    20, 230, 440, 200, hwnd, NULL, NULL, NULL);
            break;
        }
        case WM_COMMAND: {
            if (LOWORD(wParam) == 1) { // Add Student
                char idStr[50], name[50], gpaStr[50], className[50];
                GetWindowText(hEditID, idStr, 50);
                GetWindowText(hEditName, name, 50);
                GetWindowText(hEditGPA, gpaStr, 50);
                GetWindowText(hEditClass, className, 50);

                float gpa = atof(gpaStr);

                if (gpa > 4.0) {
                    MessageBox(hwnd, "GPA must be <= 4.0", "Error", MB_OK | MB_ICONERROR);
                    break;
                }

                if (n < MAX) {
                    students[n].id = atoi(idStr);
                    strcpy(students[n].name, name);
                    students[n].gpa = gpa;
                    strcpy(students[n].className, className);
                    n++;
                    MessageBox(hwnd, "Student added!", "Info", MB_OK);
                }
            }
            if (LOWORD(wParam) == 2) { // Show Students
                ShowStudents(hwnd);
            }
            if (LOWORD(wParam) == 3) { // Delete Student
                char idStr[50];
                GetWindowText(hEditID, idStr, 50);
                int id = atoi(idStr);
                DeleteStudent(id);
                MessageBox(hwnd, "Student deleted (if found)", "Info", MB_OK);
                ShowStudents(hwnd);
            }
            if (LOWORD(wParam) == 4) { // Update Student
                char idStr[50], name[50], gpaStr[50], className[50];
                GetWindowText(hEditID, idStr, 50);
                GetWindowText(hEditName, name, 50);
                GetWindowText(hEditGPA, gpaStr, 50);
                GetWindowText(hEditClass, className, 50);

                int id = atoi(idStr);
                float gpa = atof(gpaStr);

                if (gpa > 4.0) {
                    MessageBox(hwnd, "GPA must be <= 4.0", "Error", MB_OK | MB_ICONERROR);
                    break;
                }

                UpdateStudent(id, name, gpa, className);
                MessageBox(hwnd, "Student updated (if found)", "Info", MB_OK);
                ShowStudents(hwnd);
            }
            if (LOWORD(wParam) == 5) { // Export Excel
                ExportToExcel();
                MessageBox(hwnd, "Exported to student.xlsx", "Info", MB_OK);
            }
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void ShowStudents(HWND hwnd) {
    SendMessage(hListBox, LB_RESETCONTENT, 0, 0);
    char result[256];
    for (int i = 0; i < n; i++) {
        sprintf(result, "ID: %d | Name: %s | GPA: %.2f | Class: %s",
                students[i].id, students[i].name, students[i].gpa, students[i].className);
        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)result);
    }
}

void DeleteStudent(int id) {
    for (int i = 0; i < n; i++) {
        if (students[i].id == id) {
            for (int j = i; j < n - 1; j++) {
                students[j] = students[j + 1];
            }
            n--;
            break;
        }
    }
}

void UpdateStudent(int id, char *newName, float newGpa, char *newClass) {
    for (int i = 0; i < n; i++) {
        if (students[i].id == id) {
            strcpy(students[i].name, newName);
            students[i].gpa = newGpa;
            strcpy(students[i].className, newClass);
            break;
        }
    }
}

void ExportToExcel() {
    FILE *f = fopen("student.xlsx", "w");
    if (!f) return;

    fprintf(f, "ID\tName\tGPA\tClass\n");
    for (int i = 0; i < n; i++) {
        fprintf(f, "%d\t%s\t%.2f\t%s\n", 
                students[i].id, students[i].name, students[i].gpa, students[i].className);
    }

    fclose(f);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
    const char CLASS_NAME[] = "MyAppWindow";

    WNDCLASS wc = { };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, "Quan Ly Sinh Vien",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) return 0;

    ShowWindow(hwnd, nCmdShow);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}


#define _CRT_SECURE_NO_WARNINGS
#define SEC 1000
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#if defined(_WIN32) || defined(_WIN64) 
#include <windows.h>
#include<conio.h>
#define Clear() system("cls")  

#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
#include <termios.h>
#include <unistd.h>

char getch() {
    struct termios oldt, newt;
    char ch;


    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;


    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();


    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}


char getche() {
    struct termios oldt, newt;
    char ch;


    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;


    newt.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();


    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#include <unistd.h>
#define CLEAR_SCREEN() printf("\033[H\033[J")
#define Sleep(seconds) sleep(seconds)
#else
#error "Unsupported platform"
#endif

typedef struct student {
    int id;
    char name[100];
    int age;
    char major[100];
    float grade;
    struct student* next;
} Student;
int firstTest = 3;
char* numToID(int num) {
    // 메모리 동적 할당
    char* fstr = (char*)malloc(4 * sizeof(char));
    if (fstr == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    sprintf(fstr, "%03d", num);

    return fstr;
}
void loading(int time) {
    char loadstr[100] = "Loading...";
    for (int i = 0; loadstr[i] != '\0'; i++) {
        printf("%c", loadstr[i]);
    Sleep(time);
    }
}

Student* createStudent(int id, char* name, int age, char* major, float grade) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    if (newStudent == NULL) {
        printf("Error: Memory allocation failed.");
        exit(1);
    }
    newStudent->id = id;
    snprintf(newStudent->name, sizeof(newStudent->name), "%s", name);
    newStudent->age = age;
    snprintf(newStudent->major, sizeof(newStudent->major), "%s", major);
    newStudent->grade = grade;
    newStudent->next = NULL;
    return newStudent;
}
void addStudent(Student** head, int id, char* name, int age, char* major, float grade) {
    Student* newStudent = createStudent(id, name, age, major, grade);
    if (*head == NULL) {
        *head = newStudent;
    }
    else {
        Student* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newStudent;
    }
}
void sort(Student* st) {
    Student* ptr = st;
    int count = 0;
    for (; ptr != NULL;) {
        count++;
        ptr = ptr->next;
    }
    ptr = st;
    //printf("%d", count);
    for (int i = 0; i < count; i++) {
        ptr = st;
        for (; ptr->next != NULL;) {
            if (ptr->grade > ptr->next->grade) {
            //printf("oh");
                int iid = ptr->id;
                float ggrade = ptr->grade;
                int aage = ptr->age;
                char nname[100];
                char mmajor[100];
                strcpy(nname, ptr->name);
                strcpy(mmajor, ptr->major);

                ptr->grade = ptr->next->grade;
                ptr->id = ptr->next->id;
                ptr->age = ptr->next->age;
                strcpy(ptr->name, ptr->next->name);
                strcpy(ptr->major, ptr->next->major);

                ptr->next->grade = ggrade;
                ptr->next->id = iid;
                ptr->next->age = aage;
                strcpy(ptr->next->name, nname);
                strcpy(ptr->next->major, mmajor);
            }
        ptr = ptr->next;
        }
    }
}

void returnM(int time) {
    for (int i = time; i > 0; i--) {
        Clear();
        printf("Saved ! Return to the main menu in %d seconds...", i);
        Sleep(SEC);
    }
}
int main() {
    //Student* student = (Student*)malloc(firstTest * sizeof(Student));  // 초기 크기 할당
    int arrSize = 0;
    //student student;
    FILE* input;
    FILE* output;
    //input = fopen("student_input", "r");
    output = fopen("student_output.txt", "r+");
    if (output != NULL) {
        
        input = fopen("student_output.txt", "r");
        if (input == NULL) {
            printf("Error: Could not open output file 'student_output.txt' for reading.\n");
            fclose(output);
            return 0;
        }
    }
    else {
        
        input = fopen("student_input.txt", "r");
        if (input == NULL) {
            printf("Error: Could not open input file 'student_input.txt'.\n");
            return 0;
        }

        
        output = fopen("student_output.txt", "w");
        if (output == NULL) {
            printf("Error: Could not open or create output file 'student_output.txt'.\n");
            fclose(input);
            return 0;
        }
    }
    Student* student = NULL;
    for (int i = 0;; i++) {
    /*
        if (arrSize >= firstTest) {
            firstTest += 1;
            Student* new_students = (Student*)realloc(student, firstTest * sizeof(Student));
            student = new_students;
        }
        if (fscanf(input, "%d,%99[^,],%d,%99[^,],%f\n", &(student[i].id), (student[i].name), &(student[i].age), (student[i].major), &(student[i].grade)) == EOF){
            break;
        }
        arrSize++;
    */

        int id;
        char name[100];
        int age;
        char major[100];
        float grade;

        if (fscanf(input, "%d,%99[^,],%d,%99[^,],%f\n", &id, name, &age, major, &grade) != EOF) {
            addStudent(&student, id, name, age, major, grade);
        }
        else {
            break;
        }
        arrSize++;
    }
        sort(student);
    Student* current = student;
    for (;;) {
        Clear();
        printf("--------------------------------\nStudent Record Management System\n\n-Select the menu.(You can type the number of menu.)\n1. Addition\n2. Modification\n3. Deletion\n4. Display\n5. Search by ID\nElse. Exit the program.");
        char ch = _getch();
        if (ch == '1') {
            Clear();
            Student* tcurrent = student;
            int idFin = 0;
            while (tcurrent->next != NULL) {
                if (idFin < tcurrent->id) {
                    idFin = tcurrent->id;
                }
                Student* temp = tcurrent;
                tcurrent = tcurrent->next;
            }
            //printf("idfinal : %d", idFin + 1);
            Student temp = {(idFin + 1), "Chiara", 21, "CompSci", 4.5, NULL};
            printf("Type the student's information.\nName : ");
            scanf("%s", temp.name);
            printf("Major : ");
            scanf("%s", temp.major);
            printf("Age : ");
            scanf("%d", &(temp.age));
            printf("Grade : ");
            scanf("%f", &(temp.grade));
            /*
            if (arrSize >= firstTest) {
                firstTest += 1;
                Student* new_students = (Student*)realloc(student, firstTest * sizeof(Student));
                student = new_students;
            }*/
            //student[arrSize] = temp;
            addStudent(&tcurrent, temp.id, temp.name, temp.age, temp.major, temp.grade);
            arrSize++;
            sort(student);
            loading(300);
            returnM(3);
        }
        else if (ch == '2') {
            Clear();
            int idCom;
            printf("Type the ID of the student you want to edit the information from : ");
            scanf("%d", &idCom);
            Student* ptr = student;
            int boolFind = 0;
            for (int i = 0; ptr != NULL; i++) {
                if (ptr->id == idCom) {
                    boolFind = 1;
                    printf("Is this the right student information to delete ?\n------------------------------------\n");
                    printf("ID : %-3s | Name : %-15s | Age : %2d | Major : %-10s | Grade : %.2f\n", numToID(ptr->id), ptr->name, ptr->age, ptr->major, ptr->grade);
                    printf("------------------------------------\nIf it is right, Press \"Y\" Key.");
                    ch = _getch();
                    if (ch == 'Y' || ch == 'y') {
                        //Student temp = { ptr->id, "Emma", 20, "Magic", 0.1,ptr->next};
                        printf("Type the student's new information.\nName : ");
                        scanf("%s", ptr->name);
                        printf("Major : ");
                        scanf("%s", ptr->major);
                        printf("Age : ");
                        scanf("%d", &(ptr->age));
                        printf("Grade : ");
                        scanf("%f", &(ptr->grade));
                        sort(student);
                        returnM(3); break;
                    }

                    else {
                        returnM(3);
                        break;
                    }
                }
                ptr = ptr->next;
            }
            if (!boolFind) {
                printf("No students with that ID were found.\nIf you want return to the menu, type any key.");
                ch = _getch();
                returnM(2);
            }
        }
        else if (ch == '3') {
            Clear();
            int idCom;
            printf("Type the ID of the student you want to delete the information from : ");
            scanf("%d", &idCom);
            Student* ptr = student;
            Student* rawStu = student;
            int boolFind = 0;
            for (int i = 0; ptr->next != NULL; i++) {
                if (rawStu->id == idCom) {
                    boolFind = 1;
                    printf("Is this the right student information to delete ?\n------------------------------------\n");
                    printf("ID : %-3s | Name : %-15s | Age : %2d | Major : %-10s | Grade : %.2f\n", numToID(rawStu->id), rawStu->name, rawStu->age, rawStu->major, rawStu->grade);
                    printf("------------------------------------\nIf it is right, Press \"Y\" Key.");
                    ch = _getch();
                    if (ch == 'Y' || ch == 'y') {
                        student = student->next;
                        arrSize--;
                        returnM(3); break;
                    }

                    else {
                        returnM(3);
                        break;
                    }
                }
                else if (ptr->next->id == idCom) {
                    boolFind = 1;
                    printf("Is this the right student information to delete ?\n------------------------------------\n");
                    printf("ID : %-3s | Name : %-15s | Age : %2d | Major : %-10s | Grade : %.2f\n", numToID(ptr->next->id), ptr->next->name, ptr->next->age, ptr->next->major, ptr->next->grade);
                    printf("------------------------------------\nIf it is right, Press \"Y\" Key.");
                    ch = _getch();
                    if (ch == 'Y' || ch == 'y') {
                        ptr->next = ptr->next->next;
                        arrSize--;
                        if(ptr->next != NULL) (ptr->next)->next = NULL;
                        returnM(3); break;
                    }

                    else {
                        returnM(3);
                        break;
                    }
                }
                ptr = ptr->next;
            }
            if (!boolFind) {
                printf("No students with that ID were found.\nIf you want return to the menu, type any key.");
                ch = _getch();
                returnM(2);
            }
        }
        else if (ch == '4') {
            float avg = 0.0;
            int count = 0;
            Clear();
            Student* ptr = student;
            printf("| ID  |    Name    |Age |   Major    | GPA  |\n");
            for (int i = 0; ptr != NULL; i++) {
                avg += ptr->grade; count++;
                printf("| %-3s | %-10s | %2d | %-10s | %.2f |\n", numToID(ptr->id), ptr->name, ptr->age, ptr->major, ptr->grade);
                ptr = ptr->next;
            }

            printf("\nAverage of student's grade : %.2f\nIf you want return to the menu, type any key.", (float)(avg / count));
            ch = _getch();
        }
        else if (ch == '5') {
            Clear();
            int idCom;
            printf("Type the ID of the student you want to delete the information from : ");
            scanf("%d", &idCom);
            Student* ptr = student;
            int boolFind = 0;
            for (int i = 0; ptr != NULL; i++) {
                if (ptr->id == idCom) {
                    boolFind = 1;
                    printf("Search Result : \n------------------------------------\n");
                    printf("ID : %-3s | Name : %-15s | Age : %2d | Major : %-10s | Grade : %.2f\n", numToID(ptr->id), ptr->name, ptr->age, ptr->major, ptr->grade);
                    printf("------------------------------------\n\nIf you want return to the menu, type any key.");
                    ch = _getch();
                    returnM(3); break;
                }
                   
                ptr = ptr->next;
            }
            if (!boolFind) {
                printf("No students with that ID were found.\nIf you want return to the menu, type any key.");
                ch = _getch();
                returnM(2);
            }
        }
        else {
            Clear();
            Student* ptr = student;
            for (int i = 0; ptr != NULL; i++) {
                //printf("%s,%s,%d,%s,%.2f\n", numToID(ptr->id), ptr->name, ptr->age, ptr->major, ptr->grade);
                fprintf(output, "%s,%s,%d,%s,%.2f\n", numToID(ptr->id), ptr->name, ptr->age, ptr->major, ptr->grade);
                ptr = ptr->next;
            }
                //for (;;);
            printf("Thank you for using our service.");
            break;
        }
    }
    //current = student;
    while (current != NULL) {
        Student* temp = current;
        current = current->next;
        free(temp);
    }
    fclose(input);
    fclose(output);
    //free(student);
    return 0;
}

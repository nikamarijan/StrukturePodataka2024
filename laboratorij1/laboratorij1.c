#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define ERROR_OPENING_FILE -1
#define BUFFER_SIZE 1024
#define MAX_LINE 1024
#define MAX_LEN 50

typedef struct
{
	char name[MAX_LEN];
	char surname[MAX_LEN];
	double points;

}Student;

int count_rows(char* filename);
Student* memoryAlloc(int, Student*);
double readFile(int, Student*);
int printStudents(int, Student*, double);
int main()
{
	int noRows = 0;
	double maxPoint = 0.0;
	int i = 0;

	Student* studenti = NULL;


	noRows = countRows();
	printf("%d", noRows);

	if (noRows > 0) {
		studenti = memoryAlloc(noRows, studenti);

		maxPoint = readFile(noRows, studenti);

		printStudents(noRows, studenti, maxPoint);

		free(studenti);
	}

	return 0;
}

int count_rows(char* filename) {
	FILE* fp = NULL;
	char buffer[BUFFER_SIZE];
	int count = 0;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Error opening file\n");
		return ERROR_OPENING_FILE;
	}
	while (!feof(fp)) {
		fgets(buffer, BUFFER_SIZE, fp);
		//sscanf()
		++count;
	}
}
Student* memoryAlloc(int noRows, Student* studenti)
{

	studenti = (Student*)malloc(noRows * sizeof(Student));

	if (studenti == NULL) {
		printf("Neuspjela alokacija memorije");
		return NULL;
	}
	else {
		return studenti;
	}


}
double readFile(int noRows, Student* studenti)
{
	FILE* filePointer = NULL;
	char Name[MAX_LEN] = "";
	char Surname[MAX_LEN] = "";
	double Point, maxPoint = 0;



	filePointer = fopen("studenti.txt", "r");

	//error handling => ako se ne moze otvoriti file
	if (filePointer == NULL) {
		printf("Datoteka nije pronadena.");
		return -1.0;
	}

	for (int i = 0; i < noRows; i++) {
		fscanf(filePointer, "%s %s %lf", Name, Surname, &Point);

		strcpy(studenti[i].name, Name);
		strcpy(studenti[i].surname, Surname);
		studenti[i].points = Point;

		if (maxPoint < Point) {
			maxPoint = Point;
		}
	}


	fclose(filePointer);

	return maxPoint;

}

int printStudents(int noRows, Student* studenti, double maxPoints)
{
	printf("IME\tPREZIME\tAPS. BOD\tREL. BOD\n");

	for (int i = 0; i < noRows; i++) {
		printf("%s\t%s\t%.2lf\t\t%.2lf\n", studenti[i].name, studenti[i].surname, studenti[i].points, studenti[i].points / maxPoints * 100);
	}

	return 0;

}

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<iomanip>
using namespace std;

struct date;
struct scheduled;
struct Student;
struct Course;
struct UniversityCourseList;
struct EnrolledCourseList;
struct EnrolledStudent;
struct EnrolledCourse;

struct date {
	int h, m;
};

struct scheduled {
	int day;
	date starting;
	date ending;
};

struct EnrolledCourseList {
	EnrolledCourse* head, * tail;
};

struct Student {
	int studentID;
	string firstName, lastName, emailAddress, password;
	EnrolledCourseList* enrolledCourses;
	Student* next;
};

struct Course {
	int courseID, courseCapacity;
	string courseName, instructorName;
	scheduled timeSchedule;
	EnrolledStudent* attendees;
	Course* next;
	Course* previous;
};

struct UniversityCourseList {
	Course* head, * tail;
};

struct EnrolledStudent {
	Student* studentReference;
	EnrolledStudent* next;
};

struct EnrolledCourse {
	Course* courseReference;
	EnrolledCourse* next;
	EnrolledCourse* previous;
};

Student* InitializeStudentsList() {
	return NULL;
}

void InitializeEnrolledCoursesList(EnrolledCourseList* l) {
	l->head = NULL;
	l->tail = NULL;
}

void InitializeUniversityCoursesList(UniversityCourseList* l) {
	l->head = NULL;
	l->tail = NULL;
}

EnrolledStudent* InitializeEnrolledStudentsList() {
	return NULL;
}

bool IsEmptyStudents(Student* head) {
	return (head == NULL);
}

bool IsEmptyEnrolledCourses(EnrolledCourseList* l) {
	return (l->head == NULL || l->tail == NULL);
}

bool IsEmptyUniversityCourses(UniversityCourseList* l) {
	return (l->head == NULL || l->tail == NULL);
}

bool IsEmptyEnrolledStudents(EnrolledStudent* head) {
	return (head == NULL);
}

bool newstudent()
{
	char a;
	do
	{
		cout << "Are you a new student? (y/n) ";
		cin >> a;
		cin.ignore(INT_MAX, '\n');
		if (a == 'y' || a == 'Y')
			return true;
		if (a == 'n' || a == 'N')
			return false;
	} while (a != 'n' && a != 'N' && a != 'y' && a != 'Y');
}

string emailgeneration(int id)
{
	stringstream idstring;
	idstring << id;
	string idd;
	idstring >> idd;
	string e = idd + "@ua.edu.lb";
	return e;
}

string hashString(string strToHash)				
{
	hash<string> hasher;						
	stringstream sstream;						

	sstream << hex << hasher(strToHash);		
	return sstream.str();						
}

bool passwordverification(string s)				
{
	int n = s.length(), a = 0, b = 0, c = 0;
	if (n < 8)									
		return false;							
	else
	{
		for (int i = 0; i < n; i++)
		{
			if (isdigit(s[i]) != 0)
				a++;							
			else if (isalpha(s[i]) != 0)
				b++;							
			else
				c++;							
		}
		if (a == 0 || b == 0 || c == 0)			
			return false;						
		return true;							
	}
}

void PrintEnrolledCourses(EnrolledCourseList* l)
{
	EnrolledCourse* cur = l->head;
	if (IsEmptyEnrolledCourses(l)) {
		cout << "No enrolled courses" << endl;
		return;
	}
	string tmp;
	while (cur != NULL) {
		switch (cur->courseReference->timeSchedule.day)
		{
		case 1: tmp = "Monday"; break;
		case 2: tmp = "Tuesday"; break;
		case 3: tmp = "Wednesday"; break;
		case 4: tmp = "Thursday"; break;
		case 5: tmp = "Friday"; break;
		}
		cout << left << setw(5) << cur->courseReference->courseID;
		cout << left << setw(35) << cur->courseReference->courseName;
		cout << left << setw(10) << tmp << left << setw(2) << cur->courseReference->timeSchedule.starting.h << ":" << cur->courseReference->timeSchedule.starting.m << "\t" << left << setw(2) << cur->courseReference->timeSchedule.ending.h << ":" << cur->courseReference->timeSchedule.ending.m << "\n";
		cur = cur->next;
	}
}

Course* findUniversityCourse(UniversityCourseList* l, int val)
{
	if (IsEmptyUniversityCourses(l))
	{
		cout << "No university courses" << endl;
		return NULL;
	}
	Course* cur;
	cur = l->head;
	while (cur != NULL)
	{
		if (cur->courseID == val)
			return cur;
		cur = cur->next;
	}
	return NULL;
}

bool findEnrolledCourse(EnrolledCourseList* l, int val)
{
	if (IsEmptyEnrolledCourses(l))
	{
		cout << "No university courses" << endl;
		return NULL;
	}
	EnrolledCourse* cur;
	cur = l->head;
	while (cur != NULL)
	{
		if (cur->courseReference->courseID == val)
			return true;
		cur = cur->next;
	}
	return false;
}

bool UniversityCourseExist(UniversityCourseList* l, int val)
{
	if (IsEmptyUniversityCourses(l))
	{
		cout << "No university courses" << endl;
		return NULL;
	}
	Course* cur;
	cur = l->head;
	while (cur != NULL)
	{
		if (cur->courseID == val)
			return true;
		cur = cur->next;
	}
	return false;
}

bool StudentExist(Student* l, int val)
{
	if (IsEmptyStudents(l))
	{
		cout << "No university courses" << endl;
		return NULL;
	}
	Student* cur;
	cur = l;
	while (cur != NULL)
	{
		if (cur->studentID == val)
			return true;
		cur = cur->next;
	}
	return false;
}

bool EnrolledStudentExist(EnrolledStudent* l, int val)
{
	if (IsEmptyEnrolledStudents(l))
	{
		cout << "No university courses" << endl;
		return NULL;
	}
	EnrolledStudent* cur;
	cur = l;
	while (cur != NULL)
	{
		if (cur->studentReference->studentID == val)
			return true;
		cur = cur->next;
	}
	return false;
}

void InsertAtRear2(EnrolledCourseList* l, Course* val) 
{
	EnrolledCourse* tmp = new EnrolledCourse;
	if (tmp == NULL)
		exit(1);
	tmp->courseReference = val;
	if (IsEmptyEnrolledCourses(l)) {
		l->head = tmp;
		l->tail = tmp;
	}
	tmp->previous = l->tail;
	l->tail->next = tmp;
	l->tail = tmp;
}

EnrolledCourseList* removeLastEnrolledCourse(EnrolledCourseList* l)
{
	EnrolledCourse* tmp;
	if (IsEmptyEnrolledCourses(l))
	{
		cout << "Empty list" << endl;
		return NULL;
	}
	tmp = l->tail->previous;
	delete l->tail;
	l->tail = tmp;
	l->tail->next = NULL;
	return l;
}

void PrintEnrolledStudents(EnrolledStudent* head) 
{
	EnrolledStudent* cur;
	if (IsEmptyEnrolledStudents(head)) {
		cout << "No students" << endl;
		return;
	}
	cout << "The list is:" << endl;
	cur = head;
	int i = 1;
	while (cur != NULL) {
		cout << "Student " << i << ": ";
		cout << left << setw(10) << cur->studentReference->studentID;
		cout << left << setw(10) << cur->studentReference->firstName;
		cout << left << setw(10) << cur->studentReference->lastName << endl;
		cur = cur->next;
		i++;
	}
}

void PrintStudentsBrief(Student* head)
{
	Student* cur;
	if (IsEmptyStudents(head)) {
		cout << "No students" << endl;
		return;
	}
	cur = head;
	int i = 1;
	while (cur != NULL) {
		cout << "Student " << i << ": ";
		cout << left << setw(10) << cur->studentID;
		cout << left << setw(10) << cur->firstName;
		cout << left << setw(10) << cur->lastName << endl;
		cur = cur->next;
		i++;
	}
}

int SizeOfFile(string s)
{
	ifstream a(s.c_str());
	int i = 0;
	string temp;
	while (getline(a, temp))
	{
		i++;
	}
	return i;
	a.close();
}

EnrolledCourseList* insertsorted(EnrolledCourseList* l, Course* c)
{
	EnrolledCourse* tmp = new EnrolledCourse;
	if (tmp == NULL)
		exit(1);
	tmp->courseReference = c;
	tmp->next = NULL;
	tmp->previous = NULL;
	if (IsEmptyEnrolledCourses(l))
	{
		l->head = tmp;
		l->tail = tmp;
		return l;
	}
	if (l->head->courseReference->timeSchedule.day > c->timeSchedule.day || (l->head->courseReference->timeSchedule.day == c->timeSchedule.day && l->head->courseReference->timeSchedule.starting.h > c->timeSchedule.starting.h))
	{
		tmp->next = l->head;
		l->head->previous = tmp;
		l->head = tmp;
		return l;
	}
	if (l->tail->courseReference->timeSchedule.day < c->timeSchedule.day || (l->tail->courseReference->timeSchedule.day == c->timeSchedule.day && l->tail->courseReference->timeSchedule.starting.h < c->timeSchedule.starting.h))
	{
		tmp->previous = l->tail;
		l->tail->next = tmp;
		l->tail = tmp;
		return l;
	}
	EnrolledCourse* cur = l->head;
	while (cur->next != NULL && (cur->next->courseReference->timeSchedule.day < c->timeSchedule.day || (cur->next->courseReference->timeSchedule.day == c->timeSchedule.day && cur->next->courseReference->timeSchedule.starting.h < c->timeSchedule.starting.h)))
		cur = cur->next;
	tmp->next = cur->next;
	tmp->previous = cur;
	cur->next->previous = tmp;
	cur->next = tmp;
	return l;
}

EnrolledCourseList* fillEnrolledCourseList(UniversityCourseList* allcourses, Student& s)
{
	ifstream in("enrolled_courses.txt", ios::in);
	EnrolledCourseList* all = new EnrolledCourseList;
	InitializeEnrolledCoursesList(all);
	int cid, sid;
	string fn, ln;
	int i = 0;
	int size = SizeOfFile("enrolled_courses.txt");
	int test = 0;
	while (in)
	{
		in >> cid;
		in.ignore(INT_MAX, '\t');
		in >> sid;
		in.ignore(INT_MAX, '\t');
		getline(in, fn, '\t');
		getline(in, ln, '\n');
		i++;
		if (sid == s.studentID && i <= size)
		{
			Course* tmp = findUniversityCourse(allcourses, cid);
			all = insertsorted(all, tmp);
		}
	}
	in.close();
	return all;
}

void PrintStudents(Student* head) {
	Student* cur;
	if (IsEmptyStudents(head)) {
		cout << "No students" << endl;
		return;
	}
	cout << "The list is:" << endl;
	cur = head;
	int i = 1;
	while (cur != NULL) {
		cout << "Student " << i << ":" << endl;
		cout << "ID: " << cur->studentID << endl;
		cout << "First name: " << cur->firstName << endl;
		cout << "Last name: " << cur->lastName << endl;
		cout << "Email address: " << cur->emailAddress << endl;
		cout << "Enrolled courses: " << endl;
		PrintEnrolledCourses(cur->enrolledCourses);
		cur = cur->next;
		i++;
	}
	cout << endl;
}

Student* InsertAtQueue(Student* head, Student val)
{
	Student* tmp, * cur;
	tmp = new Student;
	if (tmp == NULL)
		exit(1);
	tmp->studentID = val.studentID;
	tmp->firstName = val.firstName;
	tmp->lastName = val.lastName;
	tmp->emailAddress = val.emailAddress;
	tmp->password = val.password;
	tmp->enrolledCourses = val.enrolledCourses;
	tmp->next = NULL;
	if (head == NULL) {
		head = tmp;
		return head;
	}
	cur = head;
	while (cur->next != NULL) {
		cur = cur->next;
	}
	cur->next = tmp;
	return head;
}

EnrolledStudent* InsertAtQueue2(EnrolledStudent* head, Student* val) 
{
	EnrolledStudent* tmp, * cur;
	tmp = new EnrolledStudent;
	if (tmp == NULL)
		exit(1);
	tmp->studentReference = val;
	tmp->next = NULL;
	if (IsEmptyEnrolledStudents(head))
	{
		head = tmp;
		return head;
	}
	if (head->studentReference->studentID > val->studentID)
	{
		tmp->next = head;
		head = tmp;
		return head;
	}
	cur = head;
	while (cur->next != NULL && cur->next->studentReference->studentID < val->studentID)
		cur = cur->next;
	tmp->next = cur->next;
	cur->next = tmp;
	return head;
}

Student* FindStudent(Student* head, string fn, string ln)
{
	Student* cur = head;
	if (IsEmptyStudents(head))
	{
		cout << "Empty list" << endl;
		return NULL;
	}
	while (cur != NULL) {
		if (cur->firstName == fn && cur->lastName == ln)
			return cur;
		cur = cur->next;
	}
	return NULL;
}

Student* FindStudent2(Student* head, int c)
{
	Student* cur = head;
	if (IsEmptyStudents(head))
	{
		cout << "Empty list" << endl;
		return NULL;
	}
	while (cur != NULL) {
		if (cur->studentID == c)
			return cur;
		cur = cur->next;
	}
	return NULL;
}

Student* removeLastNode(Student* head)
{
	if (IsEmptyStudents(head))
	{
		cout << "Empty list" << endl;
		return NULL;
	}
	if (head->next == NULL) {
		delete head;
		return NULL;
	}
	Student* cur = head;
	Student* prev = NULL;
	while (cur->next != NULL)
	{
		prev = cur;
		cur = cur->next;
	}
	prev->next = cur->next;
	delete cur;
	return head;
}

EnrolledStudent* removeLastNode2(EnrolledStudent* head)
{
	if (IsEmptyEnrolledStudents(head))
	{
		cout << "Empty list" << endl;
		return NULL;
	}
	if (head->next == NULL) {
		delete head;
		return NULL;
	}
	EnrolledStudent* cur = head;
	EnrolledStudent* prev = NULL;
	while (cur->next != NULL)
	{
		prev = cur;
		cur = cur->next;
	}
	prev->next = cur->next;
	delete cur;
	return head;
}

Student* fillStudentsList(ifstream& in, UniversityCourseList* allcourses)
{
	Student* all = InitializeStudentsList();
	Student cur;
	int i = 0;
	while (in)
	{
		i++;
		in >> cur.studentID;
		in.ignore(INT_MAX, '\t');
		getline(in, cur.firstName, '\t');
		getline(in, cur.lastName, '\t');
		getline(in, cur.emailAddress, '\t');
		getline(in, cur.password, '\n');
		cur.enrolledCourses = new EnrolledCourseList;
		InitializeEnrolledCoursesList(cur.enrolledCourses);
		cur.enrolledCourses = fillEnrolledCourseList(allcourses, cur);
		all = InsertAtQueue(all, cur);
	}
	all = removeLastNode(all);
	in.close();
	return all;
}

void InsertAtRear(UniversityCourseList* l, Course val) 
{
	Course* tmp;
	tmp = new Course;
	if (tmp == NULL)
		exit(1);
	tmp->courseID = val.courseID;
	tmp->courseCapacity = val.courseCapacity;
	tmp->courseName = val.courseName;
	tmp->instructorName = val.instructorName;
	tmp->timeSchedule = val.timeSchedule;
	tmp->attendees = val.attendees;
	tmp->next = NULL;
	tmp->previous = NULL;
	if (IsEmptyUniversityCourses(l)) {
		l->head = tmp;
		l->tail = tmp;
	}
	tmp->previous = l->tail;
	l->tail->next = tmp;
	l->tail = tmp;
}

UniversityCourseList* removeLastCourse(UniversityCourseList* l)
{
	Course* cur, * prev;
	if (IsEmptyUniversityCourses(l))
		return NULL;
	if (l->head->courseID == l->tail->courseID)
	{
		l->head = NULL;
		l->tail = NULL;
		return l;
	}
	cur = l->tail->previous;
	delete l->tail;
	l->tail = cur;
	l->tail->next = NULL;
	return l;
}

EnrolledStudent* fillEnrolledStudentsList(Student* allStudents, Course& c)
{
	ifstream in("enrolled_courses.txt", ios::in);
	EnrolledStudent* all = new EnrolledStudent;
	all = InitializeEnrolledStudentsList();
	int cid, sid;
	string fn, ln;
	int i = 0;
	int size = SizeOfFile("enrolled_courses.txt");
	int test = 0;
	while (in)
	{
		in >> cid;
		in.ignore(INT_MAX, '\t');
		in >> sid;
		in.ignore(INT_MAX, '\t');
		getline(in, fn, '\t');
		getline(in, ln, '\n');
		i++;
		if (cid == c.courseID && i <= size)
		{
			Student* tmp = FindStudent(allStudents, fn, ln);
			all = InsertAtQueue2(all, tmp);
		}
	}
	in.close();
	return all;
}

void fillAllAttendees(UniversityCourseList* l, Student* allStudents)
{
	Course* cur = l->head;
	if (IsEmptyUniversityCourses(l)) {
		cout << "The list is empty, no attendees can vbe added." << endl;
		return;
	}
	while (cur != NULL) {
		cur->attendees = fillEnrolledStudentsList(allStudents, *cur);
		cur = cur->next;
	}
}

UniversityCourseList* fillUniversityCourses(ifstream& in)
{
	UniversityCourseList* all = new UniversityCourseList;
	InitializeUniversityCoursesList(all);
	Course cur;
	int i = 0;
	while (in)
	{
		in >> cur.courseID;
		in.ignore(INT_MAX, '\t');
		in >> cur.courseCapacity;
		in.ignore(INT_MAX, '\t');
		getline(in, cur.courseName, '\t');
		getline(in, cur.instructorName, '\t');
		in >> cur.timeSchedule.day;
		in.ignore(INT_MAX, '\t');
		in >> cur.timeSchedule.starting.h;
		in.ignore(INT_MAX, ':');
		in >> cur.timeSchedule.starting.m;
		in.ignore(INT_MAX, '\t');
		in >> cur.timeSchedule.ending.h;
		in.ignore(INT_MAX, ':');
		in >> cur.timeSchedule.ending.m;
		in.ignore(INT_MAX, '\n');
		cur.attendees = InitializeEnrolledStudentsList();
		InsertAtRear(all, cur);
		i++;
	}
	all = removeLastCourse(all);
	in.close();
	return all;
}

int getStudentsNumber(EnrolledStudent*);

void printCourse(Course* cur)
{
	string tmp;
	int k = getStudentsNumber(cur->attendees);
	cout << "Course ID: " << cur->courseID << endl;
	cout << "Course capacity: " << cur->courseCapacity << endl;
	cout << "Course name: " << cur->courseName << endl;
	cout << "Intructor name: " << cur->instructorName << endl;
	cout << "Time schedule: " << endl;
	switch (cur->timeSchedule.day)
	{
	case 1: tmp = "Monday"; break;
	case 2: tmp = "Tuesday"; break;
	case 3: tmp = "Wednesday"; break;
	case 4: tmp = "Thursday"; break;
	case 5: tmp = "Friday"; break;
	}
	cout << "Day: " << tmp << endl;
	cout << "Starting time: " << cur->timeSchedule.starting.h << ":" << cur->timeSchedule.starting.m << endl;
	cout << "Ending time: " << cur->timeSchedule.ending.h << ":" << cur->timeSchedule.ending.m << endl;
	cout << "Taken seats: " << k << "/" << cur->courseCapacity << endl;
	cout << "Attendees: " << endl;
	PrintEnrolledStudents(cur->attendees);
}

void PrintUniversityCourses(UniversityCourseList* l)
{
	Course* cur = l->head;
	if (IsEmptyUniversityCourses(l)) {
		cout << "No courses" << endl;
		return;
	}
	string tmp;
	cout << "The list is:" << endl;
	int i = 1;
	while (cur != NULL) {
		cout << "Couse " << i << ":" << endl;
		printCourse(cur);
		cur = cur->next;
		i++;
	}
}

int getStudentsNumber(EnrolledStudent* head)
{
	if (head == NULL)
		return 0;
	return 1 + getStudentsNumber(head->next);
}

void PrintUniversityCoursesBrief(UniversityCourseList* l)
{
	Course* cur = l->head;
	if (IsEmptyUniversityCourses(l)) {
		cout << "No courses" << endl;
		return;
	}
	string tmp;
	cout << left << setw(5) << "ID" << left << setw(35) << "Name" << left << setw(35) << "Instructor" << left << setw(10) << "Day" << left << setw(6) << "Start" << left << setw(6) << "End" << left << setw(6) << "Places" << endl;
	int i = 1;
	int k;
	while (cur != NULL) 
	{
		k = getStudentsNumber(cur->attendees);
		cout << left <<setw(5) << cur->courseID;
		cout << left << setw(35) << cur->courseName;
		cout << left << setw(35) << cur->instructorName;
		switch (cur->timeSchedule.day)
		{
		case 1: tmp = "Monday"; break;
		case 2: tmp = "Tuesday"; break;
		case 3: tmp = "Wednesday"; break;
		case 4: tmp = "Thursday"; break;
		case 5: tmp = "Friday"; break;
		}
		cout << left << setw(10) << tmp;
		cout << left << setw(2) << cur->timeSchedule.starting.h << ":" << left << setw(3) << cur->timeSchedule.starting.m;
		cout << left << setw(2) << cur->timeSchedule.ending.h << ":" << left << setw(3) << cur->timeSchedule.ending.m;
		cout << left << setw(2) << k << "/" << left << setw(2) << cur->courseCapacity << endl;
		cur = cur->next;
		i++;
	}
}

string askForSecretPassword();

Student readinfostudent(ofstream& out, Student* head)
{
	Student s;
	cout << endl << "Account creation:\n";
	cout << "Please enter the following information: " << endl << endl;
	cout << "ID (provided by the admissions office) : ";
	cin >> s.studentID;
	cin.ignore(INT_MAX, '\n');
	out << s.studentID << "\t";
	cout << "First name: ";
	getline(cin, s.firstName);
	out << s.firstName << "\t";
	cout << "Last name: ";
	getline(cin, s.lastName);
	out << s.lastName << "\t";
	s.emailAddress = emailgeneration(s.studentID);
	cout << "Your automatically generated Email address is: " << s.emailAddress << endl;
	out << s.emailAddress << "\t";
	do
	{
		cout << "Create a password: ";
		cout << "(8 characters minimum, containing letters, numbers and special characters)\n";
		s.password = askForSecretPassword();
	} while (passwordverification(s.password) == false);
	out << hashString(s.password) << "\n";	
	s.enrolledCourses = new EnrolledCourseList;
	InitializeEnrolledCoursesList(s.enrolledCourses);
	out.close();
	head = InsertAtQueue(head, s);
	cout << endl << endl << s.firstName << ", you're connected!" << endl << endl;
	return s;
}

UniversityCourseList* newattendee(UniversityCourseList* l, Student* s, Course* c)
{
	if (IsEmptyUniversityCourses(l))
	{
		cout << "Empty list" << endl;
		return l;
	}
	Course* cur = l->head;
	while (cur != NULL)
	{
		if (cur->courseID == c->courseID)
		{
			cur->attendees = InsertAtQueue2(cur->attendees, s);
			return l;
		}
		cur = cur->next;
	}
	cout << "Not found" << endl;
	return l;
}

EnrolledStudent* removeattendee(EnrolledStudent* l, Student* s)
{
	EnrolledStudent* cur, * prev, * tmp;
	if (IsEmptyEnrolledStudents(l))
	{
		cout << "Empty list" << endl;
		return l;
	}
	if (l->studentReference->studentID == s->studentID)
	{
		tmp = l->next;
		delete l;
		l = tmp;
		return l;
	}
	prev = NULL;
	cur = l;
	while (cur != NULL && cur->studentReference->studentID != s->studentID)
	{
		prev = cur;
		cur = cur->next;
	}
	prev->next = cur->next;
	delete cur;
	return l;
}

Student* removestudent(Student* l, Student* s)
{
	Student* cur, * prev, * tmp;
	if (IsEmptyStudents(l))
	{
		cout << "Empty list" << endl;
		return l;
	}
	if (l->studentID == s->studentID)
	{
		tmp = l->next;
		delete l;
		l = tmp;
		return l;
	}
	prev = NULL;
	cur = l;
	while (cur != NULL && cur->studentID != s->studentID)
	{
		prev = cur;
		cur = cur->next;
	}
	prev->next = cur->next;
	delete cur;
	return l;
}

int locatestudentcourse(Course c, Student s)
{
	ifstream ec("enrolled_courses.txt", ios::in);
	int cid,sid;
	string fn, ln;
	int loc = 0;
	while (ec)									
	{
		loc++;									
		ec >> cid;
		ec.ignore(INT_MAX, '\t');
		ec >> sid;
		ec.ignore(INT_MAX, '\t');
		getline(ec, fn, '\t');
		getline(ec, ln, '\n');
		if (cid == c.courseID && sid == s.studentID)
			break;
	}
	ec.close();
	return loc;									
}

int locatecourse(Course c)
{
	ifstream ec("courses.txt", ios::in);
	int cid, cap, d, sh, sm, eh, em;
	string name, ins;
	int loc = 0;
	while (ec)
	{
		loc++;
		ec >> cid;
		ec.ignore(INT_MAX, '\t');
		ec >> cap;
		ec.ignore(INT_MAX, '\t');
		getline(ec, name, '\t');
		getline(ec, ins, '\t');
		ec >> d;
		ec.ignore(INT_MAX, '\t');
		ec >> sh;
		ec.ignore(INT_MAX, ':');
		ec >> sm;
		ec.ignore(INT_MAX, '\t');
		ec >> eh;
		ec.ignore(INT_MAX, ':');
		ec >> em;
		ec.ignore(INT_MAX, '\n');
		if (cid == c.courseID)
			break;
	}
	ec.close();
	return loc;
}

int locatestudent(Student c)
{
	ifstream ec("students.txt", ios::in);
	int sid;
	string fn, ln, em, pw;
	int loc = 0;
	while (ec)
	{
		loc++;
		ec >> sid;
		ec.ignore(INT_MAX, '\t');
		getline(ec, fn, '\t');
		getline(ec, ln, '\t');
		getline(ec, em, '\t');
		getline(ec, pw, '\n');
		if (sid == c.studentID)
			break;
	}
	ec.close();
	return loc;
}

void dropcoursefile(Course c, Student s)
{
	int n = SizeOfFile("enrolled_courses.txt");
	int k = locatestudentcourse(c, s);
	cout << endl << k << endl;
	
	ifstream re("enrolled_courses.txt", ios::in);
	ofstream temp;								
	temp.open("temp.txt");
	int linenb = 0;
	string line;
	while (re)
	{
		linenb++;								
		if (linenb > n)						
			break;
		getline(re, line, '\n');
		if (linenb != k)						
			temp << line << "\n";
	}
	temp.close();
	re.close();
	remove("enrolled_courses.txt");
	rename("temp.txt", "enrolled_courses.txt");
}

void deletecoursefile(Course c)
{
	int n = SizeOfFile("courses.txt");
	int k = locatecourse(c);
	ifstream re("courses.txt", ios::in);
	ofstream temp;
	temp.open("temp.txt");
	int linenb = 0;
	string line;
	while (re)
	{
		linenb++;
		if (linenb > n)
			break;
		getline(re, line, '\n');
		if (linenb != k)
			temp << line << "\n";
	}
	temp.close();
	re.close();
	remove("courses.txt");
	rename("temp.txt", "courses.txt");
}

void deletestudentfile(Student c)
{
	int n = SizeOfFile("students.txt");
	int k = locatestudent(c);
	ifstream re("students.txt", ios::in);
	ofstream temp;
	temp.open("temp.txt");
	int linenb = 0;
	string line;
	while (re)
	{
		linenb++;
		if (linenb > n)
			break;
		getline(re, line, '\n');
		if (linenb != k)
			temp << line << "\n";
	}
	temp.close();
	re.close();
	remove("students.txt");
	rename("temp.txt", "students.txt");
}

UniversityCourseList* dropattendee(UniversityCourseList* l, Student* s, Course* c)
{
	if (IsEmptyUniversityCourses(l))
	{
		cout << "Empty list" << endl;
		return l;
	}
	Course* cur = l->head;
	while (cur != NULL)
	{
		if (cur->courseID == c->courseID)
		{
			cur->attendees = removeattendee(cur->attendees, s);
			return l;
		}
		cur = cur->next;
	}
	cout << "Not found" << endl;
	return l;
}

EnrolledCourseList* dropcourse(EnrolledCourseList* l, int c)
{
	if (IsEmptyEnrolledCourses(l))
	{
		cout << "Empty list" << endl;
		return l;
	}
	EnrolledCourse* tmp;
	EnrolledCourse * cur, * prev;
	if (l->head == l->tail)
	{
		l->head = NULL;
		l->tail = NULL;
		return l;
	}
	if (l->head->courseReference->courseID == c)
	{
		tmp = l->head->next;
		tmp->previous = NULL;
		delete l->head;
		l->head = tmp;
		return l;
	}
	if (l->tail->courseReference->courseID == c)
	{
		tmp = l->tail->previous;
		delete l->tail;
		l->tail = tmp;
		l->tail->next = NULL;
		return l;
	}
	cur = l->head;
	prev = NULL;
	while (cur != NULL && cur->courseReference->courseID != c)
	{
		prev = cur;
		cur = cur->next;
	}
	if (cur == NULL)
	{
		cout << "Not found" << endl;
		return l;
	}
	prev->next = cur->next;
	cur->next->previous = cur->previous;
	delete cur;
	return l;
}

UniversityCourseList* deletecourse(UniversityCourseList* l, int c)
{
	if (IsEmptyUniversityCourses(l))
	{
		cout << "Empty list" << endl;
		return l;
	}
	Course* tmp;
	Course* cur, * prev;
	if (l->head == l->tail)
	{
		l->head = NULL;
		l->tail = NULL;
		return l;
	}
	if (l->head->courseID == c)
	{
		tmp = l->head->next;
		tmp->previous = NULL;
		delete l->head;
		l->head = tmp;
		return l;
	}
	if (l->tail->courseID == c)
	{
		tmp = l->tail->previous;
		delete l->tail;
		l->tail = tmp;
		l->tail->next = NULL;
		return l;
	}
	cur = l->head;
	prev = NULL;
	while (cur != NULL && cur->courseID != c)
	{
		prev = cur;
		cur = cur->next;
	}
	if (cur == NULL)
	{
		cout << "Not found" << endl;
		return l;
	}
	prev->next = cur->next;
	cur->next->previous = cur->previous;
	delete cur;
	return l;
}

string askForSecretPassword() 
{
	string password;
	cin >> password;
	int len = password.length();
	system("cls");
	cout << "Password: ";
	for (int i = 0; i < len; i++) {
		cout << "*";
	}cout << endl;
	return password;
};

Student* allstudentsdrop(Student* allstudents, Course c)
{
	Student* cur;
	if (IsEmptyStudents(allstudents))
	{
		cout << "No students" << endl << endl;
		return allstudents;
	}
	cur = allstudents;
	bool ex;
	while (cur != NULL)
	{
		ex = findEnrolledCourse(cur->enrolledCourses, c.courseID);
		if (ex)
		{
			cur->enrolledCourses = dropcourse(cur->enrolledCourses, c.courseID);
			dropcoursefile(c, *cur);
		}
		cur = cur->next;
	}
	return allstudents;
}

UniversityCourseList* allcoursessdrop(UniversityCourseList* allcourses, Student c)
{
	Course* cur;
	if (IsEmptyUniversityCourses(allcourses))
	{
		cout << "No courses" << endl << endl;
		return allcourses;
	}
	cur = allcourses->head;
	bool ex;
	while (cur != NULL)
	{
		ex = EnrolledStudentExist(cur->attendees, c.studentID);
		if (ex)
		{
			cur->attendees = removeattendee(cur->attendees, &c);
			dropcoursefile(*cur, c);
		}
		cur = cur->next;
	}
	return allcourses;
}

void adminfunctions(UniversityCourseList*, Student*);

void adminlogin(UniversityCourseList* allcourses, Student* allstudents)
{
	string pass1 = "adminadmin123456789";
	string pass2;
	int tries = 0;
	do
	{
		tries++;
		if (tries == 3)
		{
			cout << endl << endl << "Login attempts exceeded!" << endl;
			exit(1);
		}
		cout << endl << endl << "Enter admin password: ";
		getline(cin, pass2);
	} while (pass2 != pass1);
	adminfunctions(allcourses, allstudents);
}

Student login(Student* allstudents)
{
	Student p;
	int i = 0, id;
	int tries = 0;
	string email, fn, ln, ea, password1, password2, hashed;
	do
	{
		fstream in("students.txt", ios::in);
		cout << endl << "Please log in: " << endl << endl;
		cout << "Email address: ";
		getline(cin, email);
		while (in)
		{
			in >> id;
			in.ignore(INT_MAX, '\t');
			getline(in, fn, '\t');
			getline(in, ln, '\t');
			getline(in, ea, '\t');
			getline(in, password1, '\n');
			if (email == ea)
			{
				cout << endl << "Welcome " << fn << " " << ln << "!" << endl << endl;
				do
				{
					cout << "Password: ";
					password2 = askForSecretPassword();
					hashed = hashString(password2);
					if (hashed != password1)
					{
						tries++;
						cout << "Wrong password!\n";
						if (tries == 3)
						{
							cout << endl << "Login attemps exceeded.";
							exit(1);
						}
					}
				} while (hashed != password1);		
				cout << endl << fn << ", you're connected! \n";
				break;
			}
		}
		in.close();
	} while (ea != email);
	p = *FindStudent(allstudents, fn, ln);
	return p;
}

void appendcourse(Course* cc, Student s)
{
	ofstream ecout("enrolled_courses.txt", ios::out | ios::app);
	ecout << cc->courseID << "\t" << s.studentID << "\t" << s.firstName << "\t" << s.lastName << "\n";
	ecout.close();
}

void option1(Student s, UniversityCourseList* allcourses)
{
	cout << endl << "Your schedule: " << endl << endl;
	PrintEnrolledCourses(s.enrolledCourses);
	cout << endl;
	char an;
	int anss;
	bool exists;
	if (!IsEmptyEnrolledCourses(s.enrolledCourses))
	{
		do
		{
			cout << "Would you like to know more about a certain cours? (y/n) ";
			cin >> an;
		} while (an != 'y' && an != 'Y' && an != 'n' && an != 'N');
		if (an == 'n' || an == 'N')
			return;
		else
		{
			do
			{
				cout << "Enter the ID of the course you would like to know more about: ";
				cin >> anss;
				exists = UniversityCourseExist(allcourses, anss);
			} while (!exists);
			Course* cc;
			cc = findUniversityCourse(allcourses, anss);
			cout << endl << "All info related to this course: " << endl << endl;
			printCourse(cc);
		}
	}
}

void option2(Student s, UniversityCourseList* allcourses, ofstream& ecout)
{
	cout << endl << "All university courses available to you are: " << endl << endl;
	PrintUniversityCoursesBrief(allcourses);
	cout << endl;
	int anss;
	bool exists;
	do
	{
		cout << "Enter the ID of the course you would like to enroll in: ";
		cin >> anss;
		exists = UniversityCourseExist(allcourses, anss);
	} while (!exists);
	Course* cc;
	cc = findUniversityCourse(allcourses, anss);
	bool ex = findEnrolledCourse(s.enrolledCourses, cc->courseID);
	int k = getStudentsNumber(cc->attendees);
	if (k >= cc->courseCapacity)
	{
		cout << endl << "Full class, can't enroll" << endl;
		return;
	}
	else
	{
		if (ex)
		{
			cout << endl << "You are already enrolled in this course!" << endl;
			return;
		}
		else
		{
			insertsorted(s.enrolledCourses, cc);
			ecout << cc->courseID << "\t" << s.studentID << "\t" << s.firstName << "\t" << s.lastName << "\n";
			cout << endl << "Your schedule becomes: " << endl << endl;
			PrintEnrolledCourses(s.enrolledCourses);
			cout << endl;
			allcourses = newattendee(allcourses, &s, cc);
			ecout.close();
		}
	}
}

void option3(ofstream& ecout, Student s, UniversityCourseList* allcourses)
{
	ecout.close();
	int ans;
	cout << endl << "Your schedule is: " << endl << endl;
	PrintEnrolledCourses(s.enrolledCourses);
	bool exists;
	if (!IsEmptyEnrolledCourses(s.enrolledCourses))
	{
		do
		{
			cout << endl << "Enter the ID of the course you would like to drop: ";
			cin >> ans;
			exists = UniversityCourseExist(allcourses, ans);
		} while (!exists);
		Course* cc;
		cc = findUniversityCourse(allcourses, ans);
		s.enrolledCourses = dropcourse(s.enrolledCourses, cc->courseID);
		cout << endl << "Your schedule becomes: " << endl << endl;
		PrintEnrolledCourses(s.enrolledCourses);
		allcourses = dropattendee(allcourses, &s, cc);
		dropcoursefile(*cc, s);
	}
}

void option4(ofstream& ecout, Student s, UniversityCourseList* allcourses)
{
	ecout.close();
	option3(ecout, s, allcourses);
	ecout.open("enrolled_courses.txt", ios::out | ios::app);
	option2(s, allcourses, ecout);
	ecout.close();
}

void optionadmin1(Student* allstudents, UniversityCourseList* allcourses)
{
	ofstream out("courses.txt", ios::out | ios::app);
	Course newc;
	cout << endl << endl << "Enter the info of the new course you want to add: " << endl << endl;
	cout << "ID: ";
	cin >> newc.courseID;
	cout << "Capacity: ";
	cin >> newc.courseCapacity;
	cin.ignore(INT_MAX, '\n');
	cout << "Name: ";
	getline(cin, newc.courseName);
	cout << "Instructor: ";
	getline(cin, newc.instructorName);
	cout << "1 for Monday" << endl;
	cout << "2 for Tuesday" << endl;
	cout << "3 for Wednesday" << endl;
	cout << "4 for Thursday" << endl;
	cout << "5 fo Friday" << endl;
	cout << "Day: " << endl;
	cin >> newc.timeSchedule.day;
	cout << "Starting hour: ";
	cin >> newc.timeSchedule.starting.h;
	cout << "Starting minute: ";
	cin >> newc.timeSchedule.starting.m;
	cout << "Ending hour: ";
	cin >> newc.timeSchedule.ending.h;
	cout << "Ending minute: ";
	cin >> newc.timeSchedule.ending.m;
	newc.attendees = InitializeEnrolledStudentsList();
	out << newc.courseID << "\t" << newc.courseCapacity << "\t" << newc.courseName << "\t" << newc.instructorName << "\t" << newc.timeSchedule.day << "\t" << newc.timeSchedule.starting.h << ":" << newc.timeSchedule.starting.m << "\t" << newc.timeSchedule.ending.h << ":" << newc.timeSchedule.ending.m << "\n";
	InsertAtRear(allcourses, newc);
	out.close();
	cout << endl << endl << "University courses become: " << endl << endl;
	PrintUniversityCoursesBrief(allcourses);
}

void optionadmin2(Student* allstudents, UniversityCourseList* allcourses)
{
	int ans;
	bool exists;
	Course tmp;
	cout << endl << endl << "University courses are: " << endl << endl;
	PrintUniversityCoursesBrief(allcourses);
	do
	{
		cout << endl << "Enter the ID of the course you would like to drop: ";
		cin >> ans;
		exists = UniversityCourseExist(allcourses, ans);
	} while (!exists);
	Course* cc;
	cc = findUniversityCourse(allcourses, ans);
	tmp = *cc;
	allstudents = allstudentsdrop(allstudents, *cc);
	allcourses = deletecourse(allcourses, cc->courseID);
	cout << endl << endl << "Courses become: " << endl << endl;
	PrintUniversityCoursesBrief(allcourses);
	cout << endl << endl << "Students become: " << endl << endl;
	PrintStudents(allstudents);
	deletecoursefile(tmp);
}

void optionadmin3(Student* allstudents, UniversityCourseList* allcourses)
{
	cout << endl << endl << "The students are: " << endl << endl;
	PrintStudentsBrief(allstudents);
	int ans;
	bool exists;
	do
	{
		cout << endl << "Enter the ID of the student you would like to delete: ";
		cin >> ans;
		exists = StudentExist(allstudents, ans);
	} while (!exists);
	Student* ss = FindStudent2(allstudents, ans);
	Student tmp = *ss;
	allcourses = allcoursessdrop(allcourses, *ss);
	allstudents = removestudent(allstudents, ss);
	cout << endl << endl << "Students become: " << endl << endl;
	PrintStudentsBrief(allstudents);
	cout << endl << "Courses become: " << endl << endl;
	PrintUniversityCourses(allcourses);
	deletestudentfile(tmp);
}

void adminfunctions(UniversityCourseList* allcourses, Student* allstudents)
{
	char cont;
	do
	{
		cout << endl;
		cout << "Your offered services are: " << endl;
		cout << "1- Add university course" << endl;
		cout << "2- Delete a university course" << endl;
		cout << "3- Delete student" << endl;
		cout << endl << "Choose the number of the service you want: ";
		int ans;
		cin >> ans;
		switch (ans)
		{
		case 1:
			optionadmin1(allstudents, allcourses);
			break;
		case 2:
			optionadmin2(allstudents, allcourses);
			break;
		case 3:
			optionadmin3(allstudents, allcourses);
			break;
		default: break;
		}
		do
		{
			cout << endl << "Continue or exit? (c/e) ";
			cin >> cont;
		} while (cont != 'c' && cont != 'C' && cont != 'e' && cont != 'E');
	} while (cont == 'c' || cont == 'C');
	cout << endl << "Loging out, Goodbye!" << endl;
}

void studentfunctions(Student s, Student* allstudents, UniversityCourseList* allcourses)
{
	ofstream ecout("enrolled_courses.txt", ios::out | ios::app);
	char cont;
	do
	{
		cout << endl;
		cout << "Your offered services are: " << endl;
		cout << "1- View your schedule" << endl;
		cout << "2- Enroll in a course" << endl;
		cout << "3- Drop a course" << endl;
		cout << "4- Swap courses" << endl;
		cout << endl << "Choose the number of the service you want: ";
		int ans;
		cin >> ans;
		switch (ans)
		{
		case 1:
			option1(s, allcourses);
			break;
		case 2:
			option2(s, allcourses, ecout);
			break;
		case 3:
			option3(ecout, s, allcourses);
			break;
		case 4:
			option4(ecout, s, allcourses);
			break;
		default: break;
		}
		do
		{
			cout << endl << "Continue or exit? (c/e) ";
			cin >> cont;
		} while (cont != 'c' && cont != 'C' && cont != 'e' && cont != 'E');
	} while (cont == 'c' || cont == 'C');
	cout << endl << "Loging out, Goodbye!" << endl;
}

void user(Student* allstudents, UniversityCourseList* allcourses)
{
	ofstream studentout("students.txt", ios::out | ios::app);
	int ans;
	Student s;
	do
	{
		cout << endl << endl << "1- Admin" << endl << "2- Teacher" << endl << "3- Student" << endl << endl;
		cout << "Enter the number that describes the type of user that you are: ";
		cin >> ans;
		cin.ignore(INT_MAX, '\n');
	} while (ans != 1 && ans != 2 && ans != 3);
	switch (ans)
	{
	case 1:
		adminlogin(allcourses, allstudents);
		adminfunctions(allcourses, allstudents);
		break;
	case 2: break;
	case 3:
		if (newstudent() == true)
		{
			s = readinfostudent(studentout, allstudents);
			studentout.close();
		}
		else
			s = login(allstudents);
		studentfunctions(s, allstudents, allcourses);
		break;
	default: break;
	}
}

int main()
{
	ifstream studentin("students.txt", ios::in);
	ofstream studentout("students.txt", ios::out | ios::app);
	ifstream coursesin("courses.txt", ios::in);
	ifstream enrolledcoursesin("enrolled_courses.txt", ios::in);
	Student s;
	UniversityCourseList* allcourses = fillUniversityCourses(coursesin);
	Student* allstudents = fillStudentsList(studentin, allcourses);
	fillAllAttendees(allcourses, allstudents);
	enrolledcoursesin.close();
	studentin.close();
	studentout.close();
	cout << "====================================================================  Antonine  University  ===================================================================="<<endl<<endl;
	user(allstudents, allcourses);
	return 0;
}
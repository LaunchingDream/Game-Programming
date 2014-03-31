//201001046 ������
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
#include <queue>
#include <conio.h>

// �л��� ���ڸ� ����
// ����ڷκ��� Ű���带 �Է� �޾� ����ڰ� ���ϴ� ��� ������ �� ����
int STUDENT_COUNT = 6;	

#define ESC		27		// ����ڰ� Ű���� 'Esc' Ű�� ���� ��
#define SPACE	32		// ����ڰ� Ű���� 'Space bar' Ű�� ���� ��
#define ENTER	13		// ����ڰ� Ű���� 'Enter' Ű�� ���� ��

using namespace std;

// Studet - �л��� ������ �����ϴ� ����ü
// ���� int�� Score		- �л��� ����
// ���� int�� Number		- �л��� �й�
// ���ڿ� string�� Name	- �л��� ����
typedef struct {
	float Score;
	int Number;
	string Name;
}Student;

// ��ü������ ���� Stack Ŭ����
class Stack
{
public:
	int m_size;		// Stack�� ������ ����
	int m_top;		// Stack�� ���� ����

	// students Student ����ü�� Vector
	// �ַ� students[m_top]�� ���
	vector<Student> students;	

	void Initialize(int size = 6);	// Stack Ŭ������ �ʱ�ȭ
	void RemoveAll();				// Stack ��� ���� Ŭ����, ���������� ��� ����
	void Push(Student temp);		// Stack�� Push�� �ش��ϴ� �Լ�
	Student Pop(void);				// Stack�� Pop�� �ش��ϴ� �Լ�

};

// �л��� �̸����� �̸� �Է�
// �����Լ� rand�� ���� �л��� �̸��� ������ ����
string names[17]= {"������", "�嵿��", "������", "�Ӽ���", "�����", "������", 
	"������", "��ö��", "������", "����ȣ", "����ȯ", "��ä��", "������", "�����", "������", "���ؿ�", "�ֱԹ�"};

// ������ �����ִ� ����ü
struct GradeCompare{
	bool operator()(const Student s1, const Student s2)
		const { return s1.Score < s2.Score; }
};

// ������ �������� ����ü�� �������ִ� priority_queue
priority_queue<Student, vector<Student>, GradeCompare> pqueue;

void PrintStudent(Stack stack);		//  Stack�� ����� �л����� ������ ��ũ���� ���
void SaveStudentTxt(Stack stack);	// Stack�� �л����� ������ �ؽ�Ʈ ���Ϸ� ����(data.txt)
void LoadStudentTxt();				// �ؽ�Ʈ ���ϸ� ���� �л����� ������ �ҷ��ͼ� pqueue�� push��
void PrintPriorityQueue();			// �л����� ������ ���ĵ� pqueue(priority_queue) ���

int main()
{
	Stack stack;	// ����� Stack ����ü ����

	cout << "-----------------------------------------------------------" << endl;
	cout << "[ Ennter ] Ű�� ������ �л��� ���� �� �ٷ� ���" << endl;
	cout << "[  Space ] Ű�� ������ �⺻ 6������ ���" << endl;
	cout << "[   Esc  ] Ű�� ������ �ƿ�" << endl;

	// ����ڰ� �Է��� Ű�� ������ ���� int�� ���� keys
	int keys = 0;
	do {
		keys = _getch(); // ����ڷκ��� Ű�� �Է� ����

		// switch���� �� 4�� (ESC, ENTER, SPACE, Default)
		// 1. case ESC - while�� Ż��, ���α׷� ����
		// 2. case ENTER - �л��� �� ����, �л��� ������ ���� ���
		// 3. case SPACE - ���� ������ �л��� ���� ���ο� ������ ������ ������Ʈ
		// 4. case Default - �ƹ��͵� ���� ����
		switch(keys){
		case ESC :
			cout << "-----------------------------------------------------------" << endl;
			cout << "����: ";
			break;	
			
		case ENTER:
			system("cls");
			char ch;
			try
			{
				cout << "�л��� ���� �Է�(����): ";
				cin >> STUDENT_COUNT;
				cin.get(ch);
				if( cin.fail() || isalpha(ch) || ispunct(ch) )  
					throw "!!! �����Է¿���(���� ������ �ٽ� �Է�) !!!";
			}
			catch(char *error)
			{
				cin.clear();
				while((ch = cin.get()!='\n') && ch != EOF);
				cout << error << endl;
				break;
			}
			
		case SPACE :
			system("cls");
			cout << "���� �л� �� :  " << STUDENT_COUNT << endl;

			// stack�� �ʱ�ȭ, STUDENT_COUNT�� �Է¹޾� �迭�� ũ�� ����, �迭�� ���̸� -1�� ����
			stack.Initialize(STUDENT_COUNT); // STUDENT_COUNT �л� ���� ���� stack �ʱ�ȭ

			// ���� �Լ� rand�� ���� �л����� �й�, �̸�, ������ ����
			// Student ����ü temp�� �ӽ÷� ����� temp�� stack�� push��
			srand(time(NULL));
			for(int i=0; i<STUDENT_COUNT; i++) {
				Student temp; // �ӽ� Student ����ü temp
				temp.Number = ((rand()%14+2001)*100) + rand()%100;	// �й�
				temp.Name = names[rand()%16];	// �̸�
				temp.Score = (rand()%10001)/100.0;	// ����
				stack.Push(temp); // stack�� temp�� push
			}

			PrintStudent(stack);	//  Stack�� ����� �л����� ������ ��ũ���� ���
			SaveStudentTxt(stack);	//  Stack�� �л����� ������ �ؽ�Ʈ ���Ϸ� ����(data.txt)
			LoadStudentTxt();		// �ؽ�Ʈ ���ϸ� ���� �л����� ������ �ҷ��ͼ� pqueue�� push��
			PrintPriorityQueue();	// �л����� ������ ���ĵ� pqueue(priority_queue) ���

			cout << "-----------------------------------------------------------" << endl;
			cout << "���� ������ �л� �� = " << STUDENT_COUNT << endl;
			cout << "[ Ennter ] Ű�� ������ �л��� ����" << endl;
			cout << "[  Space ] Ű�� ������ ���ο� ������ �����" << endl;
			cout << "[   Esc  ] Ű�� ������ �ƿ�" << endl;

			break;	  
		default :
			break;
		}
	}while(keys != ESC);
	return 0;
}


// stack�� �ʱ�ȭ, STUDENT_COUNT�� �Է¹޾� �迭�� ũ�� ����, �迭�� ���̸� -1�� ����
void Stack::Initialize(int size) {
	m_size = size;
	m_top = -1;
	students.clear();
}

// Stack ��� ���� Ŭ����, ���������� ��� ����
void Stack::RemoveAll() {
	m_top = -1;
	students.clear();
}

// Stack�� Push�� �ش��ϴ� �Լ�
// Push(..)�� ����Ǹ� �켱 Stack�� ���� ���̸� ��Ÿ���� m_top�� ����
// �Ű����� Student ����ü temp�� �Է¹޾� students ���Ϳ� push_back��
void Stack::Push(Student temp) {
	++ m_top; 
	students.push_back(temp);
}

// Stack�� Pop�� �ش��ϴ� �Լ�
Student Stack::Pop(void) {
	if( !(m_top < 0 )){				// Pop�� ������ �Ǹ� �켱 m_top�� ������ �ƴ����� üũ
		return students[m_top--];	// Pop �Լ��� ��ȯ ������ Student ���͸� �̿��� Student ����ü�� ���
	}
}

// ���� Stack�� �����ϴ� �л����� ������ ����ϴ� �Լ�
void PrintStudent(Stack stack) {
	cout << "-----------------------------------------------------------" << endl;
	cout << "****************** Stack�� ��� ���� ��� *****************" << endl;
	for(int i=stack.m_top ; i>=0 ; i--) {
		cout << "�̸�: \t" << stack.students[i].Name << "\t\t";
		cout << "�й�: \t" << stack.students[i].Number << "\t\t";
		cout << "����: \t" << stack.students[i].Score << endl;
	}
	cout << endl;
}

//  ���� Stack�� �����ϴ� �л����� ������ �ؽ�Ʈ ���Ϸ� ����(data.txt)
void SaveStudentTxt(Stack stack) {

	ofstream fout; // ofstream Ŭ������ ��ü(fout)�� ����
	fout.open("data.txt"); // fout open() �޼ҵ带 ����Ͽ� ����ϱ� ���ϴ� ���ϸ�(data.txt)�� ����

	Student temp; // �ӽ� Student ����ü temp ����
	int count = 0; // �� ���� �л��� text ���Ͽ� �������� ī��Ʈ ���ִ� ����

	// - ��Ʈ�� ��ü�� ����Ͽ� ���. ex) fout << ... << endl;
	for(int i=stack.m_top ; i>=0 ; i--) {

		temp = stack.Pop(); // stack�� pop�Լ��� ���ϰ��� student ����ü temp�� ����

		fout << temp.Score << endl;	// �л��� ����
		fout << temp.Number << endl;	// �л��� �й�
		fout << temp.Name;					// �л��� �̸�

		if( i != 0 )		//������ element�� ������� ���� ����
			fout << endl;			//�������

		count ++ ; // �ؽ�Ʈ ���Ͽ� ����� �� ���� count ���� 1�� ����
	}

	fout.close(); // ���� ������ ����

	cout << "-----------------------------------------------------------" << endl;
	cout << "<" << count << ">���� �����Ͱ� �����(data.txt)" << endl << endl;

}

// �ؽ�Ʈ ���ϸ� ���� �л����� ������ �ҷ��ͼ� pqueue�� push��
void LoadStudentTxt() {
	cout << "-----------------------------------------------------------" << endl;
	cout << "********** data.txt�� ���� �л� �����͸� �о�� ***********" << endl;
	ifstream fin;			// ifstream class�� ��ü�� ����
	fin.open("data.txt");	// open() �޼ҵ带 ����Ͽ� �Է��ϱ� ���ϴ� ������ ����
	// ifstream�� �Է� �����̹Ƿ�, �б� �������� ���� ���������� ������� �ʾƵ� ��

	char buf[50];
	int n = 0;

	while(!fin.eof()) {

		Student s; // �ӽ� Student ����ü s ����, �Ʒ� pqueue�� push �� �� ���

		fin.getline(buf, 50);	//����
		s.Score = atof(buf);

		fin.getline(buf, 50);	//�й�
		s.Number = atoi(buf);

		fin.getline(buf, 50);	//�̸�
		s.Name = string(buf);

		cout << "�̸�: \t" << s.Name << "\t\t";
		cout << "�й�: \t" << s.Number << "\t\t";
		cout << "����: \t" << s.Score << endl;

		pqueue.push(s); // ���� text ������ ���� �ҷ��� �л��� �������� pqueue�� push
		n ++ ;

	}
	fin.close(); // ������ ������ ����
	cout << "- <" << n << ">���� ������ priority_queue�� Push �Ϸ�!" << endl << endl;

}

// �л����� ������ ���ĵ� pqueue(priority_queue) ������ִ� �Լ�
void PrintPriorityQueue() {
	cout << "-----------------------------------------------------------" << endl;
	cout << "**************** ���ĵ� priority_queue ��� ***************" << endl;
	while(!pqueue.empty()) {

		cout << "�̸�: \t" << pqueue.top().Name		<< "\t\t";	//�̸�
		cout << "�й�: \t" << pqueue.top().Number	<< "\t\t";	//�й�
		cout << "����: \t" << pqueue.top().Score		<< endl;	//����
		pqueue.pop();
	}
	cout << endl;
}
//201001046 유승현
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
#include <queue>
#include <conio.h>

// 학생의 숫자를 지정
// 사용자로부터 키보드를 입력 받아 사용자가 원하는 대로 세팅할 수 있음
int STUDENT_COUNT = 6;	

#define ESC		27		// 사용자가 키보드 'Esc' 키를 누를 때
#define SPACE	32		// 사용자가 키보드 'Space bar' 키를 누를 때
#define ENTER	13		// 사용자가 키보드 'Enter' 키를 누를 때

using namespace std;

// Studet - 학생의 정보를 저장하는 구조체
// 정수 int형 Score		- 학생의 성적
// 정수 int형 Number		- 학생의 학번
// 문자열 string형 Name	- 학생의 성적
typedef struct {
	float Score;
	int Number;
	string Name;
}Student;

// 자체적으로 만든 Stack 클래스
class Stack
{
public:
	int m_size;		// Stack의 사이즈 지정
	int m_top;		// Stack의 현재 높이

	// students Student 구조체의 Vector
	// 주로 students[m_top]를 사용
	vector<Student> students;	

	void Initialize(int size = 6);	// Stack 클래스의 초기화
	void RemoveAll();				// Stack 모든 내용 클리어, 과제에서는 사용 안함
	void Push(Student temp);		// Stack의 Push에 해당하는 함수
	Student Pop(void);				// Stack의 Pop에 해당하는 함수

};

// 학생의 이름들을 미리 입력
// 랜덤함수 rand를 통해 학생의 이름을 지정할 예정
string names[17]= {"유승현", "장동혁", "정승훈", "임성주", "김수빈", "유도현", 
	"강남규", "박철용", "이헌종", "김지호", "문은환", "김채령", "김은래", "유재승", "이종준", "김준원", "최규범"};

// 성적를 비교해주는 구조체
struct GradeCompare{
	bool operator()(const Student s1, const Student s2)
		const { return s1.Score < s2.Score; }
};

// 성적을 기준으로 구조체를 정렬해주는 priority_queue
priority_queue<Student, vector<Student>, GradeCompare> pqueue;

void PrintStudent(Stack stack);		//  Stack에 저장된 학생들의 정보를 스크린에 출력
void SaveStudentTxt(Stack stack);	// Stack의 학생들의 정보를 텍스트 파일로 저장(data.txt)
void LoadStudentTxt();				// 텍스트 파일를 통해 학생들의 정보를 불러와서 pqueue에 push함
void PrintPriorityQueue();			// 학생들의 정보가 정렬된 pqueue(priority_queue) 출력

int main()
{
	Stack stack;	// 사용할 Stack 구조체 선언

	cout << "-----------------------------------------------------------" << endl;
	cout << "[ Ennter ] 키를 누르면 학생수 설정 후 바로 출력" << endl;
	cout << "[  Space ] 키를 누르면 기본 6명으로 출력" << endl;
	cout << "[   Esc  ] 키를 누르면 아웃" << endl;

	// 사용자가 입력할 키를 저장할 정수 int형 변수 keys
	int keys = 0;
	do {
		keys = _getch(); // 사용자로부터 키를 입력 받음

		// switch문은 총 4개 (ESC, ENTER, SPACE, Default)
		// 1. case ESC - while문 탈출, 프로그램 종료
		// 2. case ENTER - 학색의 수 세팅, 학생의 정보와 정렬 출력
		// 3. case SPACE - 현재 설정된 학생의 수로 새로운 정보와 정렬을 업데이트
		// 4. case Default - 아무것도 실행 안함
		switch(keys){
		case ESC :
			cout << "-----------------------------------------------------------" << endl;
			cout << "종료: ";
			break;	
			
		case ENTER:
			system("cls");
			char ch;
			try
			{
				cout << "학생의 수를 입력(숫자): ";
				cin >> STUDENT_COUNT;
				cin.get(ch);
				if( cin.fail() || isalpha(ch) || ispunct(ch) )  
					throw "!!! 정수입력에러(엔터 눌러서 다시 입력) !!!";
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
			cout << "현재 학생 수 :  " << STUDENT_COUNT << endl;

			// stack의 초기화, STUDENT_COUNT를 입력받아 배열의 크기 고정, 배열의 높이를 -1로 설정
			stack.Initialize(STUDENT_COUNT); // STUDENT_COUNT 학생 수를 통해 stack 초기화

			// 랜덤 함수 rand를 통해 학생들의 학번, 이름, 성적을 저장
			// Student 구조체 temp를 임시로 만들고 temp를 stack에 push함
			srand(time(NULL));
			for(int i=0; i<STUDENT_COUNT; i++) {
				Student temp; // 임시 Student 구조체 temp
				temp.Number = ((rand()%14+2001)*100) + rand()%100;	// 학번
				temp.Name = names[rand()%16];	// 이름
				temp.Score = (rand()%10001)/100.0;	// 성적
				stack.Push(temp); // stack에 temp를 push
			}

			PrintStudent(stack);	//  Stack에 저장된 학생들의 정보를 스크린에 출력
			SaveStudentTxt(stack);	//  Stack의 학생들의 정보를 텍스트 파일로 저장(data.txt)
			LoadStudentTxt();		// 텍스트 파일를 통해 학생들의 정보를 불러와서 pqueue에 push함
			PrintPriorityQueue();	// 학생들의 정보가 정렬된 pqueue(priority_queue) 출력

			cout << "-----------------------------------------------------------" << endl;
			cout << "현재 설정된 학생 수 = " << STUDENT_COUNT << endl;
			cout << "[ Ennter ] 키를 누르면 학생수 변경" << endl;
			cout << "[  Space ] 키를 누르면 새로운 정보로 재출력" << endl;
			cout << "[   Esc  ] 키를 누르면 아웃" << endl;

			break;	  
		default :
			break;
		}
	}while(keys != ESC);
	return 0;
}


// stack의 초기화, STUDENT_COUNT를 입력받아 배열의 크기 고정, 배열의 높이를 -1로 설정
void Stack::Initialize(int size) {
	m_size = size;
	m_top = -1;
	students.clear();
}

// Stack 모든 내용 클리어, 과제에서는 사용 안함
void Stack::RemoveAll() {
	m_top = -1;
	students.clear();
}

// Stack의 Push에 해당하는 함수
// Push(..)가 실행되면 우선 Stack의 현재 높이를 나타내는 m_top를 증가
// 매개변수 Student 구조체 temp를 입력받아 students 벡터에 push_back함
void Stack::Push(Student temp) {
	++ m_top; 
	students.push_back(temp);
}

// Stack의 Pop에 해당하는 함수
Student Stack::Pop(void) {
	if( !(m_top < 0 )){				// Pop이 실행이 되면 우선 m_top이 음수가 아닌지를 체크
		return students[m_top--];	// Pop 함수의 반환 값으로 Student 벡터를 이용해 Student 구조체를 출력
	}
}

// 현재 Stack에 존재하는 학생들의 정보를 출력하는 함수
void PrintStudent(Stack stack) {
	cout << "-----------------------------------------------------------" << endl;
	cout << "****************** Stack의 모든 값을 출력 *****************" << endl;
	for(int i=stack.m_top ; i>=0 ; i--) {
		cout << "이름: \t" << stack.students[i].Name << "\t\t";
		cout << "학번: \t" << stack.students[i].Number << "\t\t";
		cout << "성적: \t" << stack.students[i].Score << endl;
	}
	cout << endl;
}

//  현재 Stack에 존재하는 학생들의 정보를 텍스트 파일로 저장(data.txt)
void SaveStudentTxt(Stack stack) {

	ofstream fout; // ofstream 클래스로 객체(fout)를 선언
	fout.open("data.txt"); // fout open() 메소드를 사용하여 출력하길 원하는 파일명(data.txt)를 지정

	Student temp; // 임시 Student 구조체 temp 선언
	int count = 0; // 몇 명의 학생이 text 파일에 저장됬는지 카운트 해주는 변수

	// - 스트림 객체를 사용하여 출력. ex) fout << ... << endl;
	for(int i=stack.m_top ; i>=0 ; i--) {

		temp = stack.Pop(); // stack의 pop함수의 리턴값을 student 구조체 temp에 저장

		fout << temp.Score << endl;	// 학생의 성적
		fout << temp.Number << endl;	// 학생의 학번
		fout << temp.Name;					// 학생의 이름

		if( i != 0 )		//마지막 element는 공백라인 넣지 않음
			fout << endl;			//공백라인

		count ++ ; // 텍스트 파일에 저장될 때 마다 count 변수 1씩 증가
	}

	fout.close(); // 오픈 파일을 닫음

	cout << "-----------------------------------------------------------" << endl;
	cout << "<" << count << ">명의 데이터가 저장됨(data.txt)" << endl << endl;

}

// 텍스트 파일를 통해 학생들의 정보를 불러와서 pqueue에 push함
void LoadStudentTxt() {
	cout << "-----------------------------------------------------------" << endl;
	cout << "********** data.txt를 통해 학생 데이터를 읽어옴 ***********" << endl;
	ifstream fin;			// ifstream class로 객체를 선언
	fin.open("data.txt");	// open() 메소드를 사용하여 입력하길 원하는 파일을 지정
	// ifstream은 입력 전용이므로, 읽기 전용인지 쓰기 전용인지를 명시하지 않아도 됨

	char buf[50];
	int n = 0;

	while(!fin.eof()) {

		Student s; // 임시 Student 구조체 s 선언, 아래 pqueue에 push 할 때 사용

		fin.getline(buf, 50);	//성적
		s.Score = atof(buf);

		fin.getline(buf, 50);	//학번
		s.Number = atoi(buf);

		fin.getline(buf, 50);	//이름
		s.Name = string(buf);

		cout << "이름: \t" << s.Name << "\t\t";
		cout << "학번: \t" << s.Number << "\t\t";
		cout << "성적: \t" << s.Score << endl;

		pqueue.push(s); // 현재 text 파일을 통해 불러온 학생의 정보들을 pqueue에 push
		n ++ ;

	}
	fin.close(); // 오픈한 파일을 닫음
	cout << "- <" << n << ">명의 데이터 priority_queue에 Push 완료!" << endl << endl;

}

// 학생들의 정보가 정렬된 pqueue(priority_queue) 출력해주는 함수
void PrintPriorityQueue() {
	cout << "-----------------------------------------------------------" << endl;
	cout << "**************** 정렬된 priority_queue 출력 ***************" << endl;
	while(!pqueue.empty()) {

		cout << "이름: \t" << pqueue.top().Name		<< "\t\t";	//이름
		cout << "학번: \t" << pqueue.top().Number	<< "\t\t";	//학번
		cout << "성적: \t" << pqueue.top().Score		<< endl;	//점수
		pqueue.pop();
	}
	cout << endl;
}
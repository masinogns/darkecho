//< 에러나는부분은모두수정했습니다. 일단함수2개가내용이없구요/ 
//< 모두주석달아놨으니한번확인해보세요 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <fcntl.h>
#include <unistd.h>

#pragma warning(disable:4996)

//---- #define 부분
#define MAX  100 
#define MAX_STUDENT 100 // 최대학생수
//< typedef으로재정의된카입은구조체에다른이름을지정해야합니다.(그렇지않으면경고가^^) 
typedef struct Join
{
char id[15];
char pass[15];
char name[30];
int age;
}Join;
Join student[MAX_STUDENT];
int i = 0; // 가입자번호
//---- 구조체부분
typedef struct Tenon
{
int ID;
}Tenon; //< 세임콜론이존재하지않습니다. 
//----- 함수선언부

void fnMenu();  // 메뉴
void fnExit();  // 프로그램종료
void fnSave();  // 파일에저장
void fnOpen();  // 파일을오픈
void MenuSystem();
void ShowMenu();
void InputStudentData();
void InputIDAndPassword();
void loginmenu();
//< 아래함수에서는char*형을인자로받습니다. 함수가일치하지않아에러입니다. 
int FindID(char* pID);
//----- MAIN부분
void main()
{
MenuSystem();
//---- 파일을오픈
fnOpen();
//----- 메뉴
fnMenu();
//---- 종료
fnExit();
//---- 파일에저장
fnSave();
}
void MenuSystem()
{
int num;
ShowMenu();
do
{
do
{
printf("번호를입력해주세요: ");
scanf("%d", &num); //번호입력
} while (num > 3 || num < 1);
printf("\n");
switch (num)
{
case 1:
InputStudentData();
break;
case 2:
InputIDAndPassword();
loginmenu();
break;
default:
break;
}
} while (num != 3);
}
void ShowMenu()
{
printf("\t 로그인프로그램\n\n");
printf("━━━━━━━━━━━━━━━\n");
printf("1. 가입  2. 로그인  3. 종료\n");
printf("━━━━━━━━━━━━━━━\n");
}
void InputStudentData()
{
char yesNo[2] = "n";
do
{
printf("이름을입력해주세요. : ");
scanf("%s", student[i].name);
printf("나이를입력해주세요. : ");
scanf("%d", &student[i].age);
printf("원하는아이디를입력해주세요. : ");
scanf("%s", student[i].id);
printf("패스워드를입력해주세요. : ");
scanf("%s", student[i].pass);
printf("확실한가요");
scanf("%s", yesNo); // 확실한지물음
} while (strcmp(yesNo, "y") != 0); // 확실하지않으면다시입력
i++; // 가입자수가1명늘었다
printf("\n");
}

void InputIDAndPassword()
{
//< 전달인자도없고함수형태도맞지않습니다. 
//FindID(); 
int num2 = 0;
char id[15];
char pass[15];
int found;
int corrected = 0; // 1 이되면로그인성공
if (i <= 0)
{
printf("입력된학생의자료가없습니다.\n");
InputStudentData();
}
do
{
printf("아이디를입력해주세요. : ");
scanf("%s", id);
found = FindID(id);
if (found >= 0)
{
// 아이디일치
printf("패쓰워드를입력해주세요. : ");
scanf("%s", pass);
if (strcmp(student[found].pass, pass) == 0)
{
// 패스워드일치
printf(" 성공적으로로그인되셨습니다.!\n");
printf(" 환영합니다!! %s\n\n", student[found].name);
printf("당신의가계부데이터를불러옵니다.\n");
corrected = 1;
scanf("%d", &num2);
fnMenu();
//---- 종료
fnExit();
//---- 파일에저장
fnSave();
}
else
{
printf("패스워드가일치하지않습니다.!\n\n"); // 패스워드실패
}
}
if (corrected != 1)
{
printf("아이디오류!\n\n"); // 아이디실패
}
} while (corrected == 0); // 로그인이성공할때까지입력
}
int FindID(char *id)
{
int position = 0;
int found = -1;
while ((position < i) && found < 0)
{
if (strcmp(student[position].id, id) == 0)
found = position;
else
position++;
}
return found;
}
//< 여기에서화면멈춤기능은의미가없습니다. 
// system("pause"); // 화면을멈추는기능
void fnExit()
{
system("cls"); // 화면을지운다
printf("┏━━━━━━━━━━━━━━━━━━━━━━━┓\n");
printf("┃       **** 프로그램을종료합니다****     ┃\n");
printf("┗━━━━━━━━━━━━━━━━━━━━━━━┛\n");
}
//---- 저장
void fnSave()
{
int fp;
int i; 
if ((fp = open("./test.txt",O_WRONLY|O_APPEND)) == -1)
{
printf("\a파일저장에실패하였습니다\n");
exit(1);
}
printf("파일에저장: Saving");
for (i = 0; i<5; i++)
{
putchar('.');
}
putchar('\n');
close(fp);
}
//----- 파일을오픈
void fnOpen()
{
int fp;
int i;
if ((fp = open("./test.txt", O_RDONLY|O_CREAT, 0644)) == -1)
{
printf("프로그램을처음으로시작합니다\n");
return;
}
}
//< 함수가없어링크에러입니다. 
void fnMenu()  // 메뉴
{
}
//< 함수가없어링크에러입니다. 
void loginmenu()
{
}

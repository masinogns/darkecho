/*
*
*DARK ECHO TEST OF FUCTION

*LAST MODIFIED : 2015/ 09 / 05
*
*/

#include "common.h"
#include "data.h"
#include "file.h"
#include "error.h"

/*
** :: Show Of Function Part
*/
void MenuSystem();   //Show of Menu System
void ShowSignUp(); //Show of Sign Up

/*
** :: Simple Working that do only one
*/
void ShowMenu(); //show menu
void ShowLogIn();
void ShowExit(); //show exit

/*
** :: Grobal Variable
*/
int sock; //socket that connect to server

/*
** :: Main() Part
*/
int main(int argc, char *argv[])
{
struct sockaddr_in serv_adr;

if(argc!=3)
{
printf("Usage: %s <IP> <PORT>\n",argv[0]);
exit(1);
}

/* CREATE SOCKET */
sock=socket(PF_INET, SOCK_STREAM, 0);
if(sock==-1)
error_output("SOCKET() ERROR");

/* ASSIGNMENT ADDRESS */
memset(&serv_adr, 0, sizeof(serv_adr));
serv_adr.sin_family=AF_INET;
serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
serv_adr.sin_port=htons(atoi(argv[2]));

if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
error_output("CONNECT() ERROR");
else
printf("....Connected with Server......\n");
//connected.... down page..... ok? 

MenuSystem();
//ShowSignUp();

}//Main() close

/*
** :: MenuSystem
*/
void MenuSystem()
{
int SelectNum;

//do{

system("clear");

do{
printf("=============Menu==========\n");
printf("1. SignUp \n");
printf("2. LogIn \n");
printf("3. Exit \n");
printf("===========================\n");

printf("SelectNum >> ");
scanf("%d",&SelectNum);

write(sock, &SelectNum, sizeof(SelectNum));

switch(SelectNum)
{
case 1: ShowSignUp(); break;
case 2: ShowLogIn(); break;
case 3: ShowExit(); break;
}
}while(SelectNum<1||SelectNum>3);
//}while(SelectNum!=3);
}

/*
** ::SignUP that Send to Server Account(Id, Pw)
**   for new account write test file
*/
void ShowSignUp()
{
Acnt UserInfo;
UserInfo.ControlNum=1;
//write(sock, &UserInfo.ControlNum, sizeof(UserInfo.ControlNum));

ResMsg Res;

char Yesno[2]="n";

	do{
//do{
printf("=========SignUp=========\n");
printf("Input Your New Id :");
scanf("%s",UserInfo.Id);
printf("Input Your New Pw :");
scanf("%s",UserInfo.Pw);
//printf("Are you sure that Your Id, Pw? (Y/N)\n");
//scanf("%s",Yesno);

write(sock, &UserInfo, sizeof(UserInfo));
//write(sock, Yesno, sizeof(Yesno));
read(sock, &Res, sizeof(Res));

//printf("ControlNum : %d\n",Res.ControlNum);
printf("Server to Msg : %s\n",Res.RtnMsg);
//printf("Res.RtnLen : %d\n", Res.RtnLen);
//}while(strcmp(Yesno,"y")!=0);	
	}while(Res.ControlNum!=1);

}

/*
** ::Login send to Server account(Id, Pw)
*/
void ShowLogIn()
{
Acnt UserInfo;
UserInfo.ControlNum=2;

do
{
system("clear");

fputc('\n',stdout);
fputc('\n',stdout);

printf("=============Login=============\n");
printf("Input Your ID: ");
scanf("%s",UserInfo.Id);
printf("Input Your PW: ");
scanf("%s",UserInfo.Pw);

write(sock, &UserInfo, sizeof(UserInfo));
read(sock, &Res, sizeof(Res));
printf("%s\n",Res.RtnMsg);

}while(Res.ControlNum>=0||Res.ControlNum<3);
}

void ShowExit()
{
//UserInfo.ControlNum=3;
//write(sock, &UserInfo.ControlNum, sizeof(UserInfo.ControlNum));

system("clear");

printf("=================================\n");
printf("================Exit=============\n");
printf("=================================\n");

exit(1);
}

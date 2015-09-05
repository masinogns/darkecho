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

/*Acnt UserInfo;
UserInfo.ControlNum=1;

ResMsg Res;

printf("Id :");
scanf("%s",UserInfo.Id);
printf("Pw :");
scanf("%s",UserInfo.Pw);

write(sock, &UserInfo, sizeof(UserInfo));
read(sock, &Res, sizeof(Res));
printf("%d",Res.ControlNum);*/


ShowSignUp();

}//Main() close

void ShowSignUp()
{
Acnt UserInfo;
UserInfo.ControlNum=1;

ResMsg Res;

printf("Id :");
scanf("%s",UserInfo.Id);
printf("Pw :");
scanf("%s",UserInfo.Pw);

write(sock, &UserInfo, sizeof(UserInfo));
read(sock, &Res, sizeof(Res));

printf("%d\n",Res.ControlNum);
printf("This is RtnMsg: %s\n",Res.RtnMsg);
}

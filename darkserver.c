/*DARK SERVER TEST FUNCTION

*LAST MODIFIED : 2015/ 09 / 05
*
*/

#include "common.h"
#include "data.h"
#include "file.h"
#include "error.h"

/*
** :: Process of Function Part
*/
void ProMenu();   //Process of Menu System
void ProSignUp(); //Process of Sign Up
int ProFindId(char *Id); //Process of Find Id and return found = position

/*
** :: File Process of Function Part
*/
void FileOpen();
void FileSaveHead();
void FileSaveTail();
void FileRead();
void AcntSave(char *Acnt); //Id, Pw save to text file

/*
** :: Grobal Variable Part
*/
int People = 0; //the number of people
int serv_sock, clnt_sock; //need for create socket. it will save socket descript
int fd; //need for create file. it will save file descript(fd)

/*
** :: Main Function Part
*/
int main(int argc, char *argv[])
{
struct sockaddr_in serv_adr, clnt_adr;
socklen_t clnt_adr_sz;

if(argc!=2) //How to use server
{
printf("Usage: %s <PORT>\n", argv[0]);
exit(1);
}

/* SOCKET CREATE */
serv_sock=socket(PF_INET, SOCK_STREAM, 0);
if(serv_sock==-1)
error_output("SOCKET() ERROR");

/* ASSGINMENT ADDRESS */
memset(&serv_adr, 0, sizeof(serv_adr));
serv_adr.sin_family=AF_INET;
serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
serv_adr.sin_port=htons(atoi(argv[1]));

if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
error_output("BIND() ERROR");

if(listen(serv_sock, 5)==-1)
error_output("LISTEN() ERROR");

/* ACCEPT */
clnt_adr_sz=sizeof(clnt_adr);
clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);

//CONNECTED.....
printf(".....Connected with Client......\n");
FileOpen();
/*Acnt UserRead;
ResMsg Res;
Res.ControlNum=2;read(clnt_sock, &UserRead, sizeof(UserRead));

printf("%s\n%s\n%d\n",UserRead.Id,UserRead.Pw,UserRead.ControlNum);

write(clnt_sock, &Res, sizeof(Res));*/
ProSignUp();
}//Main() close

void ProSignUp()
{
Acnt UserRead;
ResMsg Res;
Res.ControlNum=1;
read(clnt_sock, &UserRead, sizeof(UserRead));

printf("%s\n%s\n%d\n",UserRead.Id,UserRead.Pw,UserRead.ControlNum);

//this part is not working
sprintf(Res.RtnMsg,"Id:%s Pw:%s\n",UserRead.Id,UserRead.Pw);
Res.RtnLen=strlen(Res.RtnMsg);
//AcntSave(&Res);
printf("This is RtnMsg : %s",Res.RtnMsg);
write(clnt_sock, &Res, sizeof(Res));

FileSaveHead();
write(fd, &Res.RtnMsg, sizeof(Res.RtnMsg));
FileSaveTail();

People++;//the number of people +1
printf("the number of people : %d\n",People);
}

/*
** :: File Process of Function Part
*/
void FileOpen()
{
if((fd=open("./test.txt", O_RDONLY | O_CREAT, 0644))!=-1)
printf("....FILE OPEN SUCCESS.....\n");
else
printf("....FILE OPEN FAIL.....\n");
}

void FileSaveHead()
{
if((fd=open("./test.txt",O_WRONLY | O_APPEND))!=-1)
printf("Saving....\n");
else
{
printf("DO NOT SAVE\n");
exit(1);
}
}
void FileSaveTail()
{
close(fd);
}

void AcntSave(char *Acnt)
{
if((fd=open("./test.txt",O_WRONLY | O_APPEND))!=-1)
{
printf("ACNT Saving....\n");
write(fd, &Acnt, sizeof(Acnt));

close(fd);
}
else
{
printf("DO NOT SAVE\n");
exit(1);
}
}

void FileRead()
{

}

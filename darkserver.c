/*
*
*DARK SERVER TEST FUNCTION

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
void ProSignUp(char *YorN); //Process of Sign Up
int ProFindId(char *Id); //Process of Find Id and return found = position
void ProLogIn();
void ProExit();
/*
** :: File Process of Function Part
*/
void FileOpen();
void FileSaveHead();
void FileSaveTail();
int FileRead();
//void AcntSave(char *Acnt); //Id, Pw save to text file

/*
** :: Grobal Variable Part
*/
int serv_sock, clnt_sock; //need for create socket. it will save socket descript
int fd; //need for create file. it will save file descript(fd)
//int People;
FILE *fp;

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
ProMenu();
//ProSignUp();

}//Main() close

void ProMenu()
{
int SelectNum;
char Yesno[2]="n";

read(clnt_sock, &SelectNum, sizeof(SelectNum));
//read(clnt_sock, Yesno, sizeof(Yesno));
printf("Select Number : %d\n",SelectNum);

	//do
	//{
do
{
switch(SelectNum)
{
case 1: ProSignUp(Yesno); break;
case 2: ProLogIn(); break;
case 3: ProExit(); break;
}
}while(SelectNum<1||SelectNum>3);
	//}while(SelectNum!=3);

}

void ProSignUp(char *YorN)
{
Acnt UserRead;
Acnt User[MAX];
ResMsg Res;
static int People=0;


memset(&UserRead.Id, 0, sizeof(UserRead.Id));
memset(&UserRead.Pw, 0, sizeof(UserRead.Pw));
memset(&Res.RtnMsg, 0, sizeof(Res.RtnMsg));

Res.ControlNum=1;

read(clnt_sock, &UserRead, sizeof(UserRead));

printf("%s\n%s\n",UserRead.Id,UserRead.Pw);
//printf("ControlNum: %d\n",UserRead.ControlNum);

sprintf(User[People].Id, "\nID:%s", UserRead.Id);
sprintf(User[People].Pw, "\nPW:%s", UserRead.Pw);

//this part is not working
sprintf(Res.RtnMsg,"\nSign Up is Successful.\nThank you. Mr.%s\n",UserRead.Id);
Res.RtnLen=strlen(Res.RtnMsg);

write(clnt_sock, &Res, sizeof(Res));

FileSaveHead();
write(fd, User[People].Id, sizeof(User[People].Id));
write(fd, User[People].Pw, sizeof(User[People].Pw));
FileSaveTail();

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
printf("Your Id, Pw Saving is doing....\n");
else
{
printf("DO NOT SAVE\n");
exit(1);
}
}

void FileSaveTail()
{
ResMsg Res;
memset(&Res, 0, sizeof(Res));

close(fd);
sprintf(Res.RtnMsg,"Id, Pw save is Successful!!\n");
printf("%s",Res.RtnMsg);
write(clnt_sock, Res.RtnMsg, sizeof(Res.RtnMsg));
}

int FileRead()
{
int People=0;

if(fp=fopen("./test.txt","r"))
{
while(!feof(fp))
{

fscanf(fp, "%s", User[People].Id);
fscanf(fp, "%s", User[People].Pw);
printf("%s\n",User[People].Id);
printf("%s\n",User[People].Pw);

if(strncmp(User[People].Id,"ID:",3)==0)
{
People++;
printf("\nPeople number : %d\n",People);
}
fputc('\n',stdout);
}

}
return People;
//fclose(fp);
}

/*
** :: if SelectNum is 3, this func will work
*/
void ProExit()
{
close(clnt_sock);

exit(1);
}


/*
** :: Find Id in txt file. this used to function Signup and Login
*/
int ProFindId(char *Id)
{
int People=FileRead(); //the number of people saved test file
int Position=0; //array Position start 0~~
int Found=-1;   //return value start -1~~

while((Position<People)&&Found<0)
{
if(strcmp(User[Position].Id,Id)==0)
Found=Position;
else
Position++;
//if Position over number of people. return Found value -1
}
return Found;
}

void ProLogIn()
{
int Found;
int Collected=0; //if collected value became 1, login is successful

Acnt UserRead;
Acnt User[MAX];
ResMsg Res;

memset(&UserRead.Id, 0, sizeof(UserRead.Id));
memset(&UserRead.Pw, 0, sizeof(UserRead.Pw));
memset(&Res.RtnMsg, 0, sizeof(Res.RtnMsg));

read(clnt_sock, &UserRead, sizeof(UserRead));
printf("Id:%s \nPw:%s \n",UserRead.Id, UserRead.Pw);

Found=ProFindId(UserRead.Id);

if(Found>=0) //Found value >= 0, Id is existence
{
	if(strcmp(User[Found].Pw, UserRead.Pw)==0)//Password conform
	{
	//Login Successful!
	Collected=1;
	sprintf(Res.RtnMsg,"Login Successful!\nYour Id is %s\n",User[Found].Id);
	printf("%s\n",Res.RtnMsg);
	Res.RtnLen=strlen(Res.RtnMsg);
	Res.ControlNum=0;//login success control num;

	write(clnt_sock, &Res, sizeof(Res));
	}
	else
	{
	sprintf(Res.RtnMsg, "Password is wrong \nTry Again \n");
	printf("%s\n",Res.RtnMsg);
	Res.RtnLen=strlen(Res.RtnMsg);
	Res.ControlNum=1;//Password wrong control num;

	write(clnt_sock, &Res, sizeof(Res));
	}
}
if(Found<0) //Found value < 0, Id is not existence
{
	sprintf(Res.RtnMsg, "Id is not existence \nTry Again or Sign Up \n");
	printf("%s\n",Res.RtnMsg);
	Res.RtnLen=strlen(Res.RtnMsg);
	Res.ControlNum=2;//Id wrong control num;

	write(clnt_sock, &Res, sizeof(Res));
}
}//ProLogin close()

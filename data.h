/*NAME: data.h ver 1.0
*CONTENT: 구조체 data 선언 및 정의
*
*LAST MODIFIED 2015/08/25
*BY MASINO
*/

#ifndef __DATA_H__
#define __DATA_H__

#define IdLen 20 //아이디 길이
#define PwLen 20 //비밀번호 길이

#define MAX 100 //계정 최대 개수 설정

typedef struct
{
short ControlNum;
char Id[IdLen];
char Pw[PwLen];
}Acnt;
//account;

typedef struct
{
short ControlNum;
int RtnLen;
char RtnMsg[50];
}ResMsg;
//response message;

typedef struct
{
char *Account;
}Saving;

Acnt root = {0, "root", "root"};
Acnt User[MAX];
Acnt UserInfo;
ResMsg Res;
#endif

/* end of file */

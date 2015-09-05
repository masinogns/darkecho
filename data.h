/*NAME: data.h ver 1.0
*CONTENT: 구조체 data 선언 및 정의
*
*LAST MODIFIED 2015/08/25
*BY MASINO
*/

#ifndef __DATA_H__
#define __DATA_H__

#define ID_LEN 30 //아이디 길이
#define PW_LEN 30 //비밀번호 길이

#define MAX 100 //계정 최대 개수 설정

typedef struct
{
short ControlNum;
char Id[ID_LEN];
char Pw[PW_LEN];
}Acnt;
//account;

typedef struct
{
short ControlNum;
short RtnLen;
char RtnMsg[255];
}ResMsg;
//response message;

Acnt root = {0, "root", "root"};
Acnt User[MAX];
Acnt UserInfo;
ResMsg Res;
#endif

/* end of file */

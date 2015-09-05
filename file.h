/*NAME: file.h ver 1.0
*CONTENT: 리눅스 파일 관련 헤더 및 표준 입출력 정의, getch() 정의
*
*LAST MODIFIED: 2015/08/25
*BY MASINO
*/

#ifndef __FILE_H__
#define __FILE_H__

#include<fcntl.h>
#include<unistd.h>
#include<termios.h> //getch() 정의를 위해 필요한 헤더
#include<stdio.h>

#define STDIN 0  //표준 입력
#define STDOUT 1 //표준 출력
#define STDERR 2 //표준 에러

int getch(void){
    int ch;
    struct termios buf, save;
    tcgetattr(0,&save);
    buf = save;
    buf.c_lflag &= ~(ICANON|ECHO);
    buf.c_cc[VMIN] = 1;
    buf.c_cc[VTIME] = 0;
    tcsetattr(0, TCSAFLUSH, &buf);
    ch = getchar();
    tcsetattr(0, TCSAFLUSH, &save);
    return ch;
}
#endif
/* end of file */

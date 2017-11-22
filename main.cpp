#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#define MAX 100
#define _C 1046.502
#define _D 1108.731
#define _E 1318.510
#define _F 1396.913
#define _G 1567.982
#define _A 1760.000
#define _B 1975.533

void gotoxy(int x,int y){ /// 커서이동함수
    COORD pos= {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

struct LogForm{
	char loghead[10];
	char log[100];
} structuredLog;

void printLog(char Logheader[]){
	FILE *forLog = fopen("Log.log","a");
	if(forLog==NULL){
        puts("NO LOGFILE~");
        exit(1);
	}
	time_t now;
    time(&now);
	strcpy(structuredLog.loghead,Logheader);
	strcpy(structuredLog.log,ctime(&now));
	printf("%s %s",&structuredLog.loghead,&structuredLog.log);
	fprintf(forLog,"%s %s",&structuredLog.loghead,&structuredLog.log);
}

void LogIn(){
	puts("Free use!!\n");
	Beep(_E, 500);
	Beep(_D, 500);
	Beep(_C, 1000);
	Beep(_F, 1000);
	Beep(_D, 2000);
	Sleep(1234);
}
void NewFile(){ /// 새로운 파일 만들기, 아무것도 입력안했을시 다시한번 입력하게 해야함
	char FileContents[2048];
	printf("%s",FileContents);
	system("cls");
	char FileName[32];
	printf("Ex)Test.txt = Filename and Extension\nFilename : ");
	gets(FileName);
	FILE *f=fopen(FileName,"w");
	printf("\tFileContents, If you want finish, Enter & Press \"EOF\"\n");
	do{
		gets(FileContents);
		if(!strcmp("EOF",FileContents)){
			break;
		}
		fputs(FileContents, f);
		fputs("\n",f);
	}while(1);
	puts("");
	printf("\nSaving~");
	/// Sleep(5000);
	system("pause");
	fclose(f);
}
void OpenText_View(){ /// 파일을 버퍼에 가지고 온 다음 출력
	system("cls");
	char FileName[32],buf[2048];
	printf("Test.txt = Filename and Extension\nFilename : ");
	gets(FileName);
	FILE *f=fopen(FileName,"r");
	while(feof(f)=='\0'){
		fgets(buf,sizeof(f),f);
		printf("%s",buf);
	}
	puts("");
	system("pause");
	fclose(f);
}
void OpenText_Modify(){ ///파일수정 (임시파일을 만들어서 버퍼역할을 하게 한다.)
	system("cls");
	char select,NowBuf;
	char FileName[32],buf[3];
	long int fp=0,bp=0;
	printf("Test.txt = Filename and Extension\nFilename : ");
	gets(FileName);
	FILE *f=fopen(FileName,"r+");
	while(1){
		char select;
		FILE *b=fopen("Buf.buf","w+");
		puts("");
		puts("if you %'`%' ,  break;");
		puts("move: 1     write: 2     break: 3");
		select=getch();
		if(select=='1'){ /// 커서이동
			char move,SegFault='0';
			while(1){
				system("cls");
				rewind(f);
				while(feof(f)=='\0'){
					fgets(buf,/*sizeof(f)*/3,f);
					printf("%s",buf);
				}
				puts("");
				printf("Now cursor is [");
				fseek(f,fp,SEEK_SET);
				fscanf(f,"%c",&NowBuf);
				fseek(f,-1,SEEK_CUR);
				printf("%c]",NowBuf);
				move=getch();
				switch(move){  /// 위 아래키는 커서를 상하로 움직이게 하는 것이 아니라 10칸 움직임
					case 'w': fseek(f,-10,SEEK_CUR); fp=ftell(f); break;
					case 's': fseek(f,10,SEEK_CUR); fp=ftell(f); break;
					case 'a': fseek(f,-1,SEEK_CUR); fp=ftell(f); break;
					case 'd': fseek(f,1,SEEK_CUR); fp=ftell(f); break;
					case '`': SegFault='1'; break;
					default : break;
				}
				if(SegFault=='1'){
					break;
				}
			}
		}
		else if(select=='2'){ ///삽입 텍스트 수정형식은 못함,,
			char SegFault=0,Contents;
			fseek(f,fp,SEEK_SET);  ///버퍼파일 생성준비
			while(feof(f)=='\0'){/** 파일을 복사해서 버퍼역할을 하는 파일에 덮어쓴다 */
				fgets(buf,sizeof(f),f);
				fputs(buf,b);
			}
			rewind(f);
			rewind(b);
			while(1){
				system("cls");
				rewind(f);
				rewind(b);
				while(feof(f)=='\0'){
					fgets(buf,sizeof(f),f);
					printf("%s",buf);
				}
				fseek(f,fp,SEEK_SET);
				puts("");
				Contents=getch();
				switch(Contents){
					case '`': SegFault='1'; break;
					case '~': fprintf(f,"\n"); break;
					default :  fprintf(f,"%c",Contents); fp=ftell(f); bp++; while(feof(b)=='\0'){ fgets(buf,sizeof(b),b); fputs(buf,f); }
				}
				if(SegFault=='1'){
					remove("Buf.buf");
					break;
				}
			}
		}
		else if(select=='3'){
			return;
		}
	}
}
void ChooseMode(){ /// 모드 선택
	char Mode;
	while(1){
		system("cls");
		puts("Choose Mode");
		printf("New Text File : 1\nOpen Text File_View : 2\nOpen Text File_Modify : 3\nEND : 4");
		Mode=getch();
		if(Mode=='1'){
			NewFile();
		}
		else if(Mode=='2'){
			OpenText_View();
		}
		else if(Mode=='3'){
			OpenText_Modify();
		}
		else if(Mode=='4'){
			Beep(_A, 500);
			Beep(_F, 500);
			Beep(_D, 500);
			Beep(_C, 500);
			remove("Buf.buf");
			return;
		}
		else{
			printf("\n");
			puts("No Mode;");
			system("pause");
		}
	}
}
int main(){ ///메인함수
    system("mode con: cols=70 lines=40"); /// 콘솔창 크기설정
    char *pStringStart; ///전광판의 내용을 담고있는 배열의 주소를 가리킬 포인터
    int nStrlen = 0;  ///전광판의 내용의 길이를 저장할 변수
    char MainMenu;
    char msg[]="CirTex "; ///전광판의 내용
    pStringStart=msg; ///전광판의 내용의 주소를 대입
    nStrlen=strlen(pStringStart); ///전광판의 내용의 길이를 대입
    for(; *pStringStart!='\0';){ /// 전광판출력 & 아무키나 입력하면 메인메뉴로 바뀐다
        gotoxy(30,5);
        printf("%s",pStringStart);
        if(*pStringStart=='H'){
            Sleep(300);
        }
        pStringStart++;
        if(*pStringStart=='\0'){
            pStringStart=msg;
        }
        Sleep(300);
        if(kbhit()){  ///아무거나 입력받으면 탈출
            break;
        }
    }
    system("cls"); ///전광판 삭제
    gotoxy(30,6);
	system("cls");
	puts("This TextEditor is made by Circler"); // 내가 누군지 소개하는
	puts("       for UNIFOX project");            // 왜 만들었는지 소개
	printLog("Login_");
	system("pause");
	system("cls");
	ChooseMode();
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <process.h>
#define MAX 15
#define head "*사건 번호(=사건 종류): 1(=일반화재) 2(=특수화재) 3(=일반구급) 4(=변사자) 5(=환자이송) 6(=주취자) 7(=인명구조) 8(=생활안전구조)\n*사건 번호(가중치) 형태로 출력\n\n"

struct ACC {
	int acc_type;//사건 종류
	int acc_per;//요구조자 수
	double distance;
	double acc_type_grade, grade;//사건 종류에 대한 가중치, 거리, 가중치 계산 결과값
};//{{ 1, 29, 5, 7, 계산 결과},{2, 30, 1, 8, 계산결과}, ....}

int slec_type(int type);
void input_date();
void input(struct ACC *acc);
void calc(struct ACC* acc);
void def_type_grade(struct ACC* acc);
void sort(double* pt, int cnt);
void file_save(char[], int, double*);
void file_read();

int cnt, i;
char date[20];

int main()
{
	int type=0;
	struct ACC acc[15];

	type=slec_type(type); //정보 입력 및 순서 출력 or 정보 열람, 1-> 정보입력, 2-> 정보열람.
	switch (type)
	{
	case 1: {
		input_date();
		input(acc);//정보 입력 함수
		break; 
	}
		case 2: file_read();
			goto label;
	}
	def_type_grade(acc);//출동 종류에 따른 가중치부여
	calc(acc);//가중치 계산

	double acc_arr[MAX][2] = { 0 };

	for (i = 0; i < cnt; i++)
	{
		acc_arr[i][0] = acc[i].acc_type;
		acc_arr[i][1] = acc[i].grade;
	}

	sort(acc_arr, cnt);
	file_save(date, cnt, acc_arr);
		
label:
	

	return 0;
}

int slec_type(int t)
{
	do {
		printf("(1)사건 정보 입력 및 순서 출력, (2)이전 사건 정보 기록 열람 (1 or 2): ");
		scanf("%d", &t);
		getchar();
		printf("\n");
	} while (t != 1 && t != 2);
	
	return t;
}

void input_date()
{	
	do {
		one: 
		printf("날짜를 입력하세요(yyyy-mm-dd): ");
		gets(date);
		int i, j;

		for (i = 0; i < 4; i++)
		{
			int sum = 0;
			for (j = 48; j < 58; j++)
			{
				if (date[i] == j)
					sum++;
			}
			if (sum == 0)
			{
				printf("잘못된 형식입니다. 다시 입력해주세요\n");
				goto one;
			}
		}

		for (i = 5; i < 7; i++)
		{
			int sum = 0;
			for (j = 48; j < 58; j++)
			{
				if (date[i] == j)
					sum++;
			}
			if (sum == 0)
			{
				printf("잘못된 형식입니다. 다시 입력해주세요\n");
				goto one;
			}
		}

		for (i = 8; i < 10; i++)
		{
			int sum = 0;
			for (j = 48; j < 58; j++)
			{
				if (date[i] == j)
					sum++;
			}
			if (sum == 0)
			{
				printf("잘못된 형식입니다. 다시 입력해주세요\n");
				goto one;
			}
		}
		

		if (date[4] != '-' || date[7] != '-')
		{
			printf("잘못된 형식입니다. 다시 입력해주세요\n");
			continue;
		}
		else
			break;
	} while (1);
	printf("\n");
}

void input(struct ACC *acc)
{
label1:	printf("사건의 수를 입력하세요(최대 15까지 입력가능합니다): ");
	scanf("%d", &cnt);
	getchar();
	printf("\n");
	if (cnt <= 0 || cnt >= 16)
	{
		printf("1~15의 수만 입력 가능합니다!!\n");
		goto label1;
	}//입력 정보 검사
		
	printf("*사건 종류 : (1)일반화재 (2)특수화재 (3)일반구급 (4)변사자 (5)환자이송 (6)주취자 (7)인명구조 (8)생활안전구조\n");
	
	for (i = 0; i < cnt; i++)
	{
label2:		printf("%d번째 사건 종류, 요구조자 수, 거리(km)를 차례대로 입력하세요 ex) 1 29 5\n=> ",i+1);
			scanf("%d %d %lf", &acc[i].acc_type, &acc[i].acc_per, &acc[i].distance);
			getchar();
			printf("\n");
			/*입력 정보 검사*/
			if (acc[i].acc_type>=9||acc[i].acc_type<=0)
			{
				printf("사건 종류를 정확하게 입력하세요!!\n");
				goto label2;
			}
			if (acc[i].acc_per == 0)
			{
				printf("요구조자는 1명 이상입니다!!\n");
				goto label2;
			}
			if (acc[i].distance == 0)
			{
				printf("거리는 0km보다 커야 합니다!!");
				goto label2;
			}
	}

}

void calc(struct ACC* acc)
{
	for (i = 0; i < cnt; i++)
	{
		
		if (acc[i].acc_per <= 9)
			(acc[i].grade) = sqrt(acc[i].acc_type_grade *(sqrt(acc[i].acc_per))*(sqrt(acc[i].distance)));
		else
			(acc[i].grade) = sqrt(acc[i].acc_type_grade*3.1*(log10(acc[i].acc_per))*(sqrt(acc[i].distance)));
	}
}

void def_type_grade(struct ACC* acc)
{
	for(i=0;i<cnt;i++)
	{
		if (acc[i].acc_type== 1)
			acc[i].acc_type_grade = 7;
		if (acc[i].acc_type == 2)
			acc[i].acc_type_grade = 8;
		if (acc[i].acc_type == 3)
			acc[i].acc_type_grade = 4;
		if (acc[i].acc_type == 4)
			acc[i].acc_type_grade = 2;
		if (acc[i].acc_type == 5)
			acc[i].acc_type_grade = 5;
		if (acc[i].acc_type == 6)
			acc[i].acc_type_grade = 1;
		if (acc[i].acc_type == 7)
			acc[i].acc_type_grade = 6;
		if (acc[i].acc_type == 8)
			acc[i].acc_type_grade = 3;
	}
	
}

void sort(double* pt, int cnt)
{
	int i, j = 0;
	double temp1, temp2;

	for (i = 0; i < cnt - 1; i++)
		for (j = 0; j < cnt - 1; j++)
		{
			if (*(pt + 2 * j + 1) < *(pt + 2 * (j + 1) + 1))
			{
				temp1 = *(pt + 2 * j + 1);
				*(pt + 2 * j + 1) = *(pt + 2 * (j + 1) + 1);
				*(pt + 2 * (j + 1) + 1) = temp1;

				temp2 = *(pt + 2 * j);
				*(pt + 2 * j) = *(pt + 2 * (j + 1));
				*(pt + 2 * (j + 1)) = temp2;
			}
		}
}

void file_save(char date[], int cnt, double* pt)
{
	int i;
	FILE* f;

	f = fopen("record.txt", "a"); //파일 append로 열기
	if (f == NULL)
	{
		printf("Open error");
		exit(1);
	}

	fprintf(f, "%s, 사건 출동 순서: ", date);	//파일 저장
	for (i = 0; i < cnt; i++)
	{
		fprintf(f, "%d(%.2lf)  ", (int)(*(pt + 2 * i)), *(pt + 2 * i + 1));
	}
	fprintf(f, "\n");

	for (i = 0; i < cnt; i++) // 출력
	{
		if (i == (cnt - 1))
			printf("%d(%.2lf)\n", (int)(*(pt + 2 * i)), *(pt + 2 * i + 1));
		else
			printf("%d(%.2lf) - ", (int)(*(pt + 2 * i)), *(pt + 2 * i + 1));

	}
	printf("Successfully Saved!\n\n");
	fclose(f);
}

void file_read()
{
	char str[200], date[100], i = 0, ch;
	FILE* f;

	f = fopen("record.txt", "r");
	if (f == NULL)
	{
		printf("Open error");
		exit(1);
	}

	do {
		do {
		two:
			printf("날짜를 입력하세요(yyyy-mm-dd): ");
			gets(date);
			int i, j;

			for (i = 0; i < 4; i++)
			{
				int sum = 0;
				for (j = 48; j < 58; j++)
				{
					if (date[i] == j)
						sum++;
				}
				if (sum == 0)
				{
					printf("잘못된 형식입니다. 다시 입력해주세요\n");
					goto two;
				}
			}

			for (i = 5; i < 7; i++)
			{
				int sum = 0;
				for (j = 48; j < 58; j++)
				{
					if (date[i] == j)
						sum++;
				}
				if (sum == 0)
				{
					printf("잘못된 형식입니다. 다시 입력해주세요\n");
					goto two;
				}
			}

			for (i = 8; i < 10; i++)
			{
				int sum = 0;
				for (j = 48; j < 58; j++)
				{
					if (date[i] == j)
						sum++;
				}
				if (sum == 0)
				{
					printf("잘못된 형식입니다. 다시 입력해주세요\n");
					goto two;
				}
			}


			if (date[4] != '-' || date[7] != '-')
			{
				printf("잘못된 형식입니다. 다시 입력해주세요\n");
				continue;
			}
			else
				break;
		} while (1);
		printf("\n");
	



		fseek(f, 0L, SEEK_SET);

		system("cls");
		printf(head);
		fgets(str, 200, f);
		do {
			if (strstr(str, date) != NULL)
			{
				printf("%s", str);
				i++;
			}
			fgets(str, 200, f);
		} while (!feof(f));

		if (i == 0)
		{
			printf("해당 날짜를 찾을 수 없습니다. 다시 입력하시겠습니까?(y/n): ");
		}
		else
			break;

		ch = getchar();
		while (getchar() != '\n');

	} while (tolower(ch) != 'n');

	fclose(f);
}

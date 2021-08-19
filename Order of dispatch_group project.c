#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <process.h>
#define MAX 15
#define head "*��� ��ȣ(=��� ����): 1(=�Ϲ�ȭ��) 2(=Ư��ȭ��) 3(=�Ϲݱ���) 4(=������) 5(=ȯ���̼�) 6(=������) 7(=�θ���) 8(=��Ȱ��������)\n*��� ��ȣ(����ġ) ���·� ���\n\n"

struct ACC {
	int acc_type;//��� ����
	int acc_per;//�䱸���� ��
	double distance;
	double acc_type_grade, grade;//��� ������ ���� ����ġ, �Ÿ�, ����ġ ��� �����
};//{{ 1, 29, 5, 7, ��� ���},{2, 30, 1, 8, �����}, ....}

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

	type=slec_type(type); //���� �Է� �� ���� ��� or ���� ����, 1-> �����Է�, 2-> ��������.
	switch (type)
	{
	case 1: {
		input_date();
		input(acc);//���� �Է� �Լ�
		break; 
	}
		case 2: file_read();
			goto label;
	}
	def_type_grade(acc);//�⵿ ������ ���� ����ġ�ο�
	calc(acc);//����ġ ���

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
		printf("(1)��� ���� �Է� �� ���� ���, (2)���� ��� ���� ��� ���� (1 or 2): ");
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
		printf("��¥�� �Է��ϼ���(yyyy-mm-dd): ");
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
				printf("�߸��� �����Դϴ�. �ٽ� �Է����ּ���\n");
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
				printf("�߸��� �����Դϴ�. �ٽ� �Է����ּ���\n");
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
				printf("�߸��� �����Դϴ�. �ٽ� �Է����ּ���\n");
				goto one;
			}
		}
		

		if (date[4] != '-' || date[7] != '-')
		{
			printf("�߸��� �����Դϴ�. �ٽ� �Է����ּ���\n");
			continue;
		}
		else
			break;
	} while (1);
	printf("\n");
}

void input(struct ACC *acc)
{
label1:	printf("����� ���� �Է��ϼ���(�ִ� 15���� �Է°����մϴ�): ");
	scanf("%d", &cnt);
	getchar();
	printf("\n");
	if (cnt <= 0 || cnt >= 16)
	{
		printf("1~15�� ���� �Է� �����մϴ�!!\n");
		goto label1;
	}//�Է� ���� �˻�
		
	printf("*��� ���� : (1)�Ϲ�ȭ�� (2)Ư��ȭ�� (3)�Ϲݱ��� (4)������ (5)ȯ���̼� (6)������ (7)�θ��� (8)��Ȱ��������\n");
	
	for (i = 0; i < cnt; i++)
	{
label2:		printf("%d��° ��� ����, �䱸���� ��, �Ÿ�(km)�� ���ʴ�� �Է��ϼ��� ex) 1 29 5\n=> ",i+1);
			scanf("%d %d %lf", &acc[i].acc_type, &acc[i].acc_per, &acc[i].distance);
			getchar();
			printf("\n");
			/*�Է� ���� �˻�*/
			if (acc[i].acc_type>=9||acc[i].acc_type<=0)
			{
				printf("��� ������ ��Ȯ�ϰ� �Է��ϼ���!!\n");
				goto label2;
			}
			if (acc[i].acc_per == 0)
			{
				printf("�䱸���ڴ� 1�� �̻��Դϴ�!!\n");
				goto label2;
			}
			if (acc[i].distance == 0)
			{
				printf("�Ÿ��� 0km���� Ŀ�� �մϴ�!!");
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

	f = fopen("record.txt", "a"); //���� append�� ����
	if (f == NULL)
	{
		printf("Open error");
		exit(1);
	}

	fprintf(f, "%s, ��� �⵿ ����: ", date);	//���� ����
	for (i = 0; i < cnt; i++)
	{
		fprintf(f, "%d(%.2lf)  ", (int)(*(pt + 2 * i)), *(pt + 2 * i + 1));
	}
	fprintf(f, "\n");

	for (i = 0; i < cnt; i++) // ���
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
			printf("��¥�� �Է��ϼ���(yyyy-mm-dd): ");
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
					printf("�߸��� �����Դϴ�. �ٽ� �Է����ּ���\n");
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
					printf("�߸��� �����Դϴ�. �ٽ� �Է����ּ���\n");
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
					printf("�߸��� �����Դϴ�. �ٽ� �Է����ּ���\n");
					goto two;
				}
			}


			if (date[4] != '-' || date[7] != '-')
			{
				printf("�߸��� �����Դϴ�. �ٽ� �Է����ּ���\n");
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
			printf("�ش� ��¥�� ã�� �� �����ϴ�. �ٽ� �Է��Ͻðڽ��ϱ�?(y/n): ");
		}
		else
			break;

		ch = getchar();
		while (getchar() != '\n');

	} while (tolower(ch) != 'n');

	fclose(f);
}

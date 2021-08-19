#include <stdio.h>
#include <stdlib.h>
#define RAN_LIM 500000

double qMatrix[8][8], rMatrix[8][8], gammaLR = 0.8;
int max_index[8], available_acts[8];
int ran_top = 0, ran[RAN_LIM];

void printArray(double a[][8])
{
    int i, j;

    printf("\nMatrix: \n");
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            printf("%f\t", (a[i][j]));
        }
        printf("\n");
    }
}

int returnRandom()
{
    return ran[ran_top++];
}

double update(int current_state, int action, double rMatrix[][8], double qMatrix[][8])
{
    int i = 0, j = 0, k = 0, index_of_max;
    double temp_max = 0.0, max_value = 0.0, sumA = 0.0;

    //Collecting all the indexes where we have max in action row
    for (i = 0; i < 8; i++)
    {
        max_index[i] = 0;

        if (temp_max == qMatrix[action][i])
        {
            max_index[j] = i;
            j++;
        }
        else if (temp_max < qMatrix[action][i])
        {
            j = 0;
            temp_max = qMatrix[action][i];
            max_index[j] = i;
            j++;
        }
    }

    //Select a random out of all maximum
    int a = returnRandom() % j;
    index_of_max = max_index[a];

    max_value = qMatrix[action][index_of_max];


    //Main updation
    qMatrix[current_state][action] = rMatrix[current_state][action] + (gammaLR * max_value);
    temp_max = 0.0;
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (qMatrix[i][j] > temp_max)
            {
                temp_max = qMatrix[i][j];
            }
        }
    }

    //printf("\nQ Max: %d", temp_max);
    //printArray(qMatrix);
    if (temp_max > 0)
    {
        for (i = 0; i < 8; i++)
        {
            for (j = 0; j < 8; j++)
            {
                sumA += (qMatrix[i][j] / temp_max);
            }
        }

        sumA *= 100;
        return sumA;
    }
}

int available_actions(int state, int available_acts[], double rMatrix[][8])
{
    int k = 0, j = 0;
    while (j < 8)
    {
        if (rMatrix[state][j] >= 0.0)
        {
            available_acts[k] = j;
            k++;
        }
        j++;
    }
    printf("\n");
    return k;
}


int sample_next_action(int size, int available_acts[])
{
    int a = returnRandom();
    int next_action = available_acts[a % size];
    return next_action;
}

int main()
{
    int i, j;
    int initial_state, final_state;
    int current_state, size_av_actions, action;
    double final_max = 0.0, scores[100000], rMatrix[8][8], score = 0.0;

    printf("Enter the initial state: ");
    scanf("%d", &initial_state);
    printf("Enter the final state: ");
    scanf("%d", &final_state);

    for (int i = 0; i < RAN_LIM; i++)
    {
        ran[i] = rand() % 8;
    }


    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            rMatrix[i][j] = -1.0;
            qMatrix[i][j] = 0.0;

            if ((i == 0 && j == 1) || (i == 1 && j == 5) || (i == 5 && j == 6) || (i == 5 && j == 4) || (i == 1 && j == 2) || (i == 2 && j == 3) || (i == 2 && j == 7) || (i == 4 && j == 7) || (i == 1 && j == 4))
            {
                rMatrix[i][j] = 0.0;
            }

            if ((j == 0 && i == 1) || (j == 1 && i == 5) || (j == 5 && i == 6) || (j == 5 && i == 4) || (j == 1 && i == 2) || (j == 2 && i == 3) || (j == 2 && i == 7) || (j == 4 && i == 7) || (j == 1 && i == 4))
            {
                rMatrix[i][j] = 0.0;
            }
        }
    }

    switch (final_state)
    {
    case 0:
        rMatrix[1][0] = 100.0;
        rMatrix[0][0] = 100.0;
        break;
    case 1:
        rMatrix[2][1] = 100.0;
        rMatrix[4][1] = 100.0;
        rMatrix[0][1] = 100.0;
        rMatrix[5][1] = 100.0;
        rMatrix[1][1] = 100.0;
        break;
    case 2:
        rMatrix[3][2] = 100.0;
        rMatrix[7][2] = 100.0;
        rMatrix[1][2] = 100.0;
        rMatrix[2][2] = 100.0;
        break;
    case 3:
        rMatrix[2][3] = 100.0;
        rMatrix[3][3] = 100.0;
        break;
    case 4:
        rMatrix[1][4] = 100.0;
        rMatrix[7][4] = 100.0;
        rMatrix[5][4] = 100.0;
        rMatrix[4][4] = 100.0;
        break;
    case 5:
        rMatrix[1][5] = 100.0;
        rMatrix[4][5] = 100.0;
        rMatrix[6][5] = 100.0;
        rMatrix[5][5] = 100.0;
        break;
    case 6:
        rMatrix[5][6] = 100.0;
        rMatrix[6][6] = 100.0;
        break;
    case 7: 
        rMatrix[2][7] = 100.0;
        rMatrix[4][7] = 100.0;
        rMatrix[7][7] = 100.0;
        break;
    }


    while (getchar() != '\n');
    char ch;
    while (1)
    {
        printf("is there a traffic jam? (y/n): ");
        scanf("%c%*c", &ch);
        if (ch == 'y')
        {
            loop:
            printf("Enter the edge in traffic (i, j): ");
            scanf("%d, %d", &i, &j);
            rMatrix[i][j] = -1;
        }
        if (ch == 'n') break;
        printf("more? (y/n)");
        scanf(" %c", &ch);
        if (ch == 'n') break;
        goto loop;
    }
    
    
    printf("\nPoints Matrix : \n");
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            printf("%f\t", rMatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n");

    printf("%f", rMatrix[7][7]);


    // Training the Q Matrix
    for (i = 0; i < 500; i++)
    {

        current_state = returnRandom();
        size_av_actions = available_actions(current_state, available_acts, rMatrix);
        action = sample_next_action(size_av_actions, available_acts);

        //printf("\nNext Step: %d\n", action);
        score = update(current_state, action, rMatrix, qMatrix);
        scores[i] = score;

        printf("\nScore : %f", score);
    }


    //Finding the Max
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (final_max < qMatrix[i][j])
            {
                final_max = qMatrix[i][j];
            }
        }
    }


    printf("\n\nTrained Q Matrix: \n");
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            printf("%f\t", (qMatrix[i][j] / final_max * 100.0));
        }
        printf("\n");
    }


    int curr_state = initial_state;
    int visited[8] = { 0,0,0,0,0,0,0,0 };
    int no_way = 0;
    int row_max = 0, max_ind = 0;

    printf("Path: \n");
    while (1)
    {
        printf("%d-> ", curr_state);
        row_max = 0;
        max_ind = 0;

        for (int i = 0; i < 8; i++)
        {
            if (visited[i] == 0)
            {
                if (qMatrix[curr_state][i] > row_max)
                {
                    max_ind = i;
                    row_max = qMatrix[curr_state][i];
                }
            }
        }

        curr_state = max_ind;
        visited[max_ind] = 1;
        if (row_max == 0)
        {
            no_way = 1;
            break;
        }

        if (curr_state == final_state)
        {
            break;
        }
    }

    if (no_way == 1)
    {
        printf("%d | There's no way after this\n");
    }
    else
    {
        printf("%d is the shortest path\n", curr_state);
    }

}
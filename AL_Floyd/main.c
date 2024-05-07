//5��7�� ���� 
//�̾����� ���� vertex���̸� 0->INF �� ����
//���� Ʈ���� �̾����� ������ INF�� ���� [n][n](x=y)�κ��� ������ 0���� 

#include <stdio.h>
#include <limits.h>


// ������ ������ ����� ����================ ���� ���� �κ� 
#define MAX_VERTICES 9 //���� ���� 
#define EDGES 10       // ������Ʈ �� �м���
//==========================================================
#define INF 10000


//���� �迭�� �ʿ��Ѱ͵� ���� //dfs ��� ���� ��� �湮 �ƴϸ� �ٽ� 
#include <stdlib.h>
#include <time.h>
int randomPoolOk(int randomPool[]);
void printGraph(int graph[][MAX_VERTICES]);
void randomTree(int Graph[][MAX_VERTICES]);




//Random ���� ���鶧 ���
//dfs�ڵ� ------------------------------------------------------------------------
int visited[MAX_VERTICES]; // �湮 ���θ� �����ϴ� �迭
int stack[MAX_VERTICES]; // ����
int top = -1; // ������ ž

// ���ÿ� ���Ҹ� �߰��ϴ� �Լ�
void push(int vertex) {
    stack[++top] = vertex;
}

// ���ÿ��� ���Ҹ� �����ϰ� ��ȯ�ϴ� �Լ�
int pop() {
    return stack[top--];
}

// ������ ����ִ��� Ȯ���ϴ� �Լ�
int isEmpty() {
    return top == -1;
}



// DFS �Լ�
void dfs(int graph[][MAX_VERTICES], int start) {
    push(start); // ���� ������ ���ÿ� �߰�
    visited[start] = 1; // ���� ������ �湮�� ������ ǥ��

    //printf("%d ", start); // �湮�� ���� ���//----------------------------------------------------------debug

    while (!isEmpty()) {
        int current = stack[top]; // ������ �� ���� �ִ� ���� Ȯ��
        int next = -1;

        // ������ �� ���� �ִ� ������ ����� ���� �߿��� ���� �湮���� ���� ���� ã��
        for (int i = 0; i < MAX_VERTICES; i++) {
            if (graph[current][i] > 0 && graph[current][i] < INF && visited[i] == 0) {// 0�̾ƴϰ� �����̾ƴϸ� �̾����ִ°����� �Ǵ� //�湮���� 
                next = i;
                break;
            }
        }

        if (next != -1) { // �湮���� ���� ������ ���� ���
            push(next); // �ش� ������ ���ÿ� �߰�
            visited[next] = 1; // �ش� ������ �湮�� ������ ǥ��
            //printf("%d ", next); // �湮�� ���� ���//----------------------------------------------------------debug
        }
        else {
            pop(); // �湮���� ���� ������ ������ ���ÿ��� ����
        }
    }




}

int dfs1(int graph[][MAX_VERTICES]) {

    int flag = 1;
    //printf("DFS �湮 ����: ");                      //------------------------------------------dfs�� �ְ� �ƴϱ⶧���� �̰� ��Ȱ��ȭ
    dfs(graph, 1); // ���� 0���� �����Ͽ� DFS ����

    for (int i = 1; i < MAX_VERTICES; i++) {
        if (visited[i] == 0)
            flag = 0;
    }
    //printf("debug flag:%d\n", flag);  //--------------------------------------------debug
    return flag;    //��� ������ �湮 ó�� �Ǿ��ִٸ� 1 ��ȯ
}


//------------------------------------------------------------------------
//�׷��� ���//INF ������ 
void printGraph(int graph[][MAX_VERTICES]) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            if (graph[i][j] != INF) {
                printf(" %4d", graph[i][j]);
            }
            else {
                printf("  INF");
            }

        }
        printf("\n");
    }
}





//���� Ʈ�� ������� //�̾����� �����κ� INF�� ���� 
void randomTree(int Graph[][MAX_VERTICES]) {
    //��ȭ�迭 �ʱ�ȭ
    int edge1 = 0;
    int x, y;
    int dfsFlag = 0;

    //Graph �ʱ�ȭ
    //[n][n]�κ�(x=y)�� 0, �ٸ� �κ��� INF�� �ʱ�ȭ //-------5��7�� ���� -------------------
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            if (i != j) {
                Graph[i][j] = INF;
            }
            else {
                Graph[i][j] = 0;
            }

        }
    }
    srand(time(NULL));//�����Լ� �ʱ�ȭ 





    //������ ���� ���� ����  MAX~ Max(Max-1)/2�� ~~~~~~~~~~~~~~~/////////////////

    //int EdgeN = (MAX_VERTICES * (rand() % (MAX_VERTICES - 3) + 2) / 2);//�ּڰ��� MaxVertex���� �̻�����
    int EdgeN = 10;                                                                                         //===== �̹��� 10,11,12,13�������� ��
    printf("���� ���� %d\n", EdgeN);
    dfsFlag = dfs1(Graph);
    while (dfsFlag == 0) {
        while (edge1 < EdgeN) {
            x = rand() % MAX_VERTICES;
            y = rand() % MAX_VERTICES;
            if (x >= 0 && y >= 0 && Graph[x][y] == INF && Graph[y][x] == INF && x != y) {//�̾����������� INFȭ 5��7�� ����-----------
                int temp = (rand() % 20) + 1;// 1~20 ������ ����ġ
                Graph[x][y] = Graph[y][x] = temp;
                edge1++;


                printf("%d. random edge : ( %d , %d), ( %d , %d ), weight: %d\n", edge1, x, y, y, x, Graph[x][y]);
            }


        }
        printf("Number of Vertices : %d\n", MAX_VERTICES);
        printf("Number of Edges : %d\n", EdgeN);
        printGraph(Graph);
        //��� ������� ���� �׷����� �������� �׷��� �ٽû��� dfs �ٽ� ����ؼ� dfsFlag�� �Ҵ�
        dfsFlag = dfs1(Graph);
        edge1 = 0;//�������� �������� �׻� 0����  �ǵ� ��� x 

    }


}
// �ִ� ��θ� ����ϴ� �Լ�
void printSolution(int dist[]) {
    printf("����\t �ִܰŸ�\n");
    for (int i = 0; i < MAX_VERTICES; i++)
        printf("%d\t %d\n", i, dist[i]);
}




//Floyd-Warshall �ڵ�
void floydWarshall(int graph[MAX_VERTICES][MAX_VERTICES]) {
    // ��� �׷���
    int d[MAX_VERTICES][MAX_VERTICES];
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            d[i][j] = graph[i][j];
        }
    }


    // p : ���İ� ����
    for (int p = 0; p < MAX_VERTICES; p++) {
        for (int i = 0; i < MAX_VERTICES; i++) {
            for (int j = 0; j < MAX_VERTICES; j++) {
                if (d[i][p] + d[p][j] < d[i][j]) {
                    d[i][j] = d[i][p] + d[p][j];
                    // printf("debug %d (%d,%d) \n",d[i][j],i,j);  //-------------------------------------debug
                }
            }
        }
    }

    // ��� �׷��� ���
    printf("floyd warshall �ִܰŸ� \n");

    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            printf("%4d ", d[i][j]);
        }
        printf("\n");
    }

}



// �־��� �׷������� �ִ� ��θ� ã�� �Լ�
void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int src) {
    int dist[MAX_VERTICES];     // �ִ� �Ÿ��� �����ϴ� �迭
    int visited[MAX_VERTICES];  // �湮�� ������ ǥ���ϴ� �迭

    // �ʱ�ȭ
    for (int i = 0; i < MAX_VERTICES; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }

    dist[src] = 0;  // ���� ������ �Ÿ��� 0

    // ��� ������ �湮
    for (int count = 0; count < MAX_VERTICES - 1; count++) {
        // ������� �ִ� �Ÿ��� ���� ������ ã��
        int minDist = INF, minIndex;
        for (int v = 0; v < MAX_VERTICES; v++) {
            if (visited[v] == 0 && dist[v] <= minDist) {
                minDist = dist[v];
                minIndex = v;
            }
        }

        // ���� ������ �湮�� ������ ǥ��
        visited[minIndex] = 1;

        // ���� ������ ���� �� �� �ִ� ��� ��θ� �˻��Ͽ� �ִ� �Ÿ��� ������Ʈ
        for (int v = 0; v < MAX_VERTICES; v++) { //���⼭ �󸶵��� �ٲ�� �ִµ� ���翡���� �� Ȯ���̶�� ���� ����ϴ��� �ñ�.... 
            if (!visited[v] && graph[minIndex][v] != INF && dist[minIndex] != INF &&                                   //�̺κ� ������ �̾����� �������� 0 ���� ǥ�� ���� ------------------ 5��7�� ���� 
                dist[minIndex] + graph[minIndex][v] < dist[v]) {                                                //graph[minIndex][v] != INF �̸� �۵����� �ϸ� ���� 
                dist[v] = dist[minIndex] + graph[minIndex][v];
            }
        }
    }

    // �ִ� ��� ���
    printSolution(dist);
}

int main() {
    int graph[MAX_VERTICES][MAX_VERTICES];

    randomTree(graph);


    floydWarshall(graph);
    //dijkstra(graph, 0);  // 0�� ������ ���������� �ؼ� �ִ� ��� ã��

    return 0;
}
//5월7일 수정 
//이어지지 않은 vertex사이를 0->INF 로 변경
//랜덤 트리도 이어지지 않은곳 INF로 변경 [n][n](x=y)부분은 여전히 0으로 

#include <stdio.h>
#include <limits.h>


// 정점의 개수를 상수로 정의================ 조정 가능 부분 
#define MAX_VERTICES 9 //정점 갯수 
#define EDGES 10       // 프로젝트 비교 분석용
//==========================================================
#define INF 10000


//랜덤 배열에 필요한것들 모음 //dfs 사용 버전 모두 방문 아니면 다시 
#include <stdlib.h>
#include <time.h>
int randomPoolOk(int randomPool[]);
void printGraph(int graph[][MAX_VERTICES]);
void randomTree(int Graph[][MAX_VERTICES]);




//Random 정점 만들때 사용
//dfs코드 ------------------------------------------------------------------------
int visited[MAX_VERTICES]; // 방문 여부를 저장하는 배열
int stack[MAX_VERTICES]; // 스택
int top = -1; // 스택의 탑

// 스택에 원소를 추가하는 함수
void push(int vertex) {
    stack[++top] = vertex;
}

// 스택에서 원소를 삭제하고 반환하는 함수
int pop() {
    return stack[top--];
}

// 스택이 비어있는지 확인하는 함수
int isEmpty() {
    return top == -1;
}



// DFS 함수
void dfs(int graph[][MAX_VERTICES], int start) {
    push(start); // 시작 정점을 스택에 추가
    visited[start] = 1; // 시작 정점을 방문한 것으로 표시

    //printf("%d ", start); // 방문한 정점 출력//----------------------------------------------------------debug

    while (!isEmpty()) {
        int current = stack[top]; // 스택의 맨 위에 있는 정점 확인
        int next = -1;

        // 스택의 맨 위에 있는 정점과 연결된 정점 중에서 아직 방문하지 않은 정점 찾기
        for (int i = 0; i < MAX_VERTICES; i++) {
            if (graph[current][i] > 0 && graph[current][i] < INF && visited[i] == 0) {// 0이아니고 무한이아니면 이어져있는것으로 판단 //방문가능 
                next = i;
                break;
            }
        }

        if (next != -1) { // 방문하지 않은 정점이 있을 경우
            push(next); // 해당 정점을 스택에 추가
            visited[next] = 1; // 해당 정점을 방문한 것으로 표시
            //printf("%d ", next); // 방문한 정점 출력//----------------------------------------------------------debug
        }
        else {
            pop(); // 방문하지 않은 정점이 없으면 스택에서 제거
        }
    }




}

int dfs1(int graph[][MAX_VERTICES]) {

    int flag = 1;
    //printf("DFS 방문 순서: ");                      //------------------------------------------dfs가 주가 아니기때문에 이거 비활성화
    dfs(graph, 1); // 정점 0에서 시작하여 DFS 수행

    for (int i = 1; i < MAX_VERTICES; i++) {
        if (visited[i] == 0)
            flag = 0;
    }
    //printf("debug flag:%d\n", flag);  //--------------------------------------------debug
    return flag;    //모든 정점이 방문 처리 되어있다면 1 반환
}


//------------------------------------------------------------------------
//그래프 출력//INF 번역본 
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





//랜덤 트리 만들어줌 //이어지지 않은부분 INF로 수정 
void randomTree(int Graph[][MAX_VERTICES]) {
    //기화배열 초기화
    int edge1 = 0;
    int x, y;
    int dfsFlag = 0;

    //Graph 초기화
    //[n][n]부분(x=y)은 0, 다른 부분은 INF로 초기화 //-------5월7일 수정 -------------------
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
    srand(time(NULL));//랜덤함수 초기화 





    //간선수 고르기 위한 변수  MAX~ Max(Max-1)/2개 ~~~~~~~~~~~~~~~/////////////////

    //int EdgeN = (MAX_VERTICES * (rand() % (MAX_VERTICES - 3) + 2) / 2);//최솟값이 MaxVertex보다 이상으로
    int EdgeN = 10;                                                                                         //===== 이번엔 10,11,12,13개까지만 비교
    printf("간선 갯수 %d\n", EdgeN);
    dfsFlag = dfs1(Graph);
    while (dfsFlag == 0) {
        while (edge1 < EdgeN) {
            x = rand() % MAX_VERTICES;
            y = rand() % MAX_VERTICES;
            if (x >= 0 && y >= 0 && Graph[x][y] == INF && Graph[y][x] == INF && x != y) {//이어지지않은곳 INF화 5월7일 수정-----------
                int temp = (rand() % 20) + 1;// 1~20 까지의 가중치
                Graph[x][y] = Graph[y][x] = temp;
                edge1++;


                printf("%d. random edge : ( %d , %d), ( %d , %d ), weight: %d\n", edge1, x, y, y, x, Graph[x][y]);
            }


        }
        printf("Number of Vertices : %d\n", MAX_VERTICES);
        printf("Number of Edges : %d\n", EdgeN);
        printGraph(Graph);
        //모두 연결되지 않은 그래프가 나왔을때 그래프 다시생성 dfs 다시 계산해서 dfsFlag에 할당
        dfsFlag = dfs1(Graph);
        edge1 = 0;//지역변수 마지막엔 항상 0으로  되도 상관 x 

    }


}
// 최단 경로를 출력하는 함수
void printSolution(int dist[]) {
    printf("정점\t 최단거리\n");
    for (int i = 0; i < MAX_VERTICES; i++)
        printf("%d\t %d\n", i, dist[i]);
}




//Floyd-Warshall 코드
void floydWarshall(int graph[MAX_VERTICES][MAX_VERTICES]) {
    // 결과 그래프
    int d[MAX_VERTICES][MAX_VERTICES];
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            d[i][j] = graph[i][j];
        }
    }


    // p : 거쳐갈 정점
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

    // 결과 그래프 출력
    printf("floyd warshall 최단거리 \n");

    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            printf("%4d ", d[i][j]);
        }
        printf("\n");
    }

}



// 주어진 그래프에서 최단 경로를 찾는 함수
void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int src) {
    int dist[MAX_VERTICES];     // 최단 거리를 저장하는 배열
    int visited[MAX_VERTICES];  // 방문한 정점을 표시하는 배열

    // 초기화
    for (int i = 0; i < MAX_VERTICES; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }

    dist[src] = 0;  // 시작 정점의 거리는 0

    // 모든 정점을 방문
    for (int count = 0; count < MAX_VERTICES - 1; count++) {
        // 현재까지 최단 거리를 가진 정점을 찾음
        int minDist = INF, minIndex;
        for (int v = 0; v < MAX_VERTICES; v++) {
            if (visited[v] == 0 && dist[v] <= minDist) {
                minDist = dist[v];
                minIndex = v;
            }
        }

        // 현재 정점을 방문한 것으로 표시
        visited[minIndex] = 1;

        // 현재 정점을 통해 갈 수 있는 모든 경로를 검사하여 최단 거리를 업데이트
        for (int v = 0; v < MAX_VERTICES; v++) { //여기서 얼마든지 바뀔수 있는데 교재에서는 왜 확정이라는 말을 사용하는지 궁금.... 
            if (!visited[v] && graph[minIndex][v] != INF && dist[minIndex] != INF &&                                   //이부분 떄문에 이어지지 않은곳을 0 으로 표현 가능 ------------------ 5월7일 수정 
                dist[minIndex] + graph[minIndex][v] < dist[v]) {                                                //graph[minIndex][v] != INF 이면 작동으로 하면 가능 
                dist[v] = dist[minIndex] + graph[minIndex][v];
            }
        }
    }

    // 최단 경로 출력
    printSolution(dist);
}

int main() {
    int graph[MAX_VERTICES][MAX_VERTICES];

    randomTree(graph);


    floydWarshall(graph);
    //dijkstra(graph, 0);  // 0번 정점을 시작점으로 해서 최단 경로 찾기

    return 0;
}
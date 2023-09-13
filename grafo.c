#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 100

// Função para encontrar o vértice com a distância mínima que ainda não foi visitado
int encontrarMinimo(int dist[], int visited[], int n) {
    int min = INT_MAX, minIndex;

    for (int v = 0; v < n; v++) {
        if (visited[v] == 0 && dist[v] <= min) {
            min = dist[v];
            minIndex = v;
        }
    }

    return minIndex;
}

// Função para imprimir o caminho percorrido
void imprimirCaminho(int path[], int dest) {
    if (path[dest] == -1) {
        printf("%d ", dest);
        return;
    }

    imprimirCaminho(path, path[dest]);
    printf("%d ", dest);
}

// Função que implementa o algoritmo de Dijkstra
void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int n, int source, int destination) {
    int dist[MAX_VERTICES];
    int visited[MAX_VERTICES];
    int path[MAX_VERTICES];

    // Inicializa as distâncias como infinito, visitado como falso e caminho como -1
    for (int v = 0; v < n; v++) {
        dist[v] = INT_MAX;
        visited[v] = 0;
        path[v] = -1;
    }

    // A distância da origem para ela mesma é sempre zero
    dist[source] = 0;

    // Encontra o caminho mínimo para todos os vértices
    for (int count = 0; count < n - 1; count++) {
        int u = encontrarMinimo(dist, visited, n);
        visited[u] = 1;

        // Atualiza as distâncias dos vértices adjacentes ao vértice selecionado
        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                path[v] = u;
            }
        }
    }

    // Imprime o resultado
    printf("O menor caminho entre %d e %d: %d\n", source, destination, dist[destination]);

    // Imprime o caminho percorrido
    printf("Caminho percorrido: ");
    imprimirCaminho(path, destination);
    printf("\n");
}

int main() {
    FILE *file;
    int n, source, destination;
    int graph[MAX_VERTICES][MAX_VERTICES];

    // Abre o arquivo
    file = fopen("caminho.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Lê o número de vértices do arquivo
    fscanf(file, "%d", &n);

    // Lê a matriz de adjacência do arquivo
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(file, "%d", &graph[i][j]);
        }
    }

    // Lê a origem e o destino do arquivo
    fscanf(file, "%d %d", &source, &destination);

    // Fecha o arquivo
    fclose(file);

    // Chama a função Dijkstra para encontrar o menor caminho
    dijkstra(graph, n, source, destination);

    return 0;
}

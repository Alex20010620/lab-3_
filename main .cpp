#include "bellman_ford.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

int main() {
    examine_text();
    matrix = new int*[vertex_count];        // создаём матрицу смежности
    for (int i = 0; i < vertex_count; i++) {
        matrix[i] = new int[vertex_count];
        for (int j = 0; j < vertex_count; j++) {
            matrix[i][j] = INF;
            if (i == j) matrix[i][j] = 0;
        }
    }
    read_text();

    // список смежности:

    // узел: пара<узел, цена>, пара<узел,цена> ...
    // 1: <2, 10>, <3, N/A>
    // N: ...

    // матрица смежности
    //          destination:
    // source:  |cost|

    // Алгоритм можно остановить, если ничего не изменилось после итерации

    vector<int> dist;
    // dist[0] = 0
    // dist[1..n] = INF

    for (int i = 0; i < cities.size(); i++) {
        cout << i << " : " << cities[i] << endl;
    }
    cout << endl;

    for (int i = 0; i < vertex_count; i++) {
        for (int j = 0; j < vertex_count; j++) {
            if (matrix[i][j] != INF)
                cout << matrix[i][j] << "\t";
            else
                cout << "INF" << "\t";
        }
        cout << endl;
    }

    cout << "Enter source city: ";
    string city_source;
    getline(cin, city_source);

    cout << "Enter destination city: ";
    string city_destination;
    getline(cin, city_destination);

    int source_point = -1;
    int destination_point = -1;
    for (int i = 0; i < cities.size(); i++) {
        if (city_source == cities[i]) {
            source_point = i;
        }
        if (city_destination == cities[i]) {
            destination_point = i;
        }
        if (destination_point != -1 && source_point != -1)
            break;  // нашли соответствующие индексы строковым значениям городов
    }

    if (source_point == -1 || destination_point == -1) {
        cout << "There's no such city...";
        return -1;
    }

    if (source_point == destination_point) {
        cout << "Path is zero";
    }

    int cost = find_path(source_point, destination_point);
    cout << "The nearest way cost is: " << cost << endl;

    return 0;
}

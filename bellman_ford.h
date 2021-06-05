#ifndef LAB_3_BELLMAN_FORD_H
#define LAB_3_BELLMAN_FORD_H

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <sstream>

using namespace std;


#define INF INT16_MAX

vector<string> cities;      // соответствие индекс - название города
int ** matrix;              // матрица смежности
int vertex_count = 0;       // кол-во вершин (городов)

// Изучает текст на кол-во
void examine_text() {
    string line;
    set<string> vertexes;

    ifstream in("input.txt"); // окрываем файл для чтения
    if (in.is_open()) {
        int i = 0;
        while (getline(in, line))   // до \n
        {
            stringstream ss(line);
            while (getline(ss, line, ';')) {
                if (i == 4) {
                    i = 0;
                }
                if (i < 2)
                    vertexes.insert(line);
                i++;
            }
        }
    }

    in.close();

    vertex_count = vertexes.size();
    if (vertex_count == 0) {
        throw invalid_argument("empty input");
    }
}

void read_text() {
    string line;

    ifstream in("input.txt"); // окрываем файл для чтения
    if (in.is_open())
    {
        int i = 0, A = 0, B = 0, cost_A = INF, cost_B = INF;
        while (getline(in, line))   // до \n
        {
            stringstream ss(line);
            while (getline(ss, line, ';')) { // до ';'
                if (i == 4) {
                    matrix[A][B] = cost_A;
                    matrix[B][A] = cost_B;
                    i = 0; // обнуление
                }

                // Установление соответствия НОМЕР-НАЗВАНИЕ города
                if (i < 2) {
                    bool has_found = false;
                    for (int j = 0; j < cities.size(); j++) {
                        if (cities[j] == line) {
                            if (i == 0) A = j; // Установим узел А в значение int
                            else B = j;        // Установим узел В в значение int
                            has_found = true;
                            break; // Выйдем
                        }
                    }
                    if (!has_found) {
                        if (i == 0) A = cities.size();      // Установим узел А в значение int
                        else B = cities.size();             // Установим узел В в значение int

                        cities.push_back(line); // если нет элемента то добавляем
                    }
                } else {
                    if (line[0] != 'N') {
                        if (i == 2) cost_A = stoi(line);
                        else cost_B = stoi(line);
                    } else {
                        if (i == 2) cost_A = INF;
                        else cost_B = INF;
                    }
                }

                i++;
            }

            matrix[A][B] = cost_A;  // last iteration
            matrix[B][A] = cost_B;
        }
    }
    in.close();     // закрываем файл
}

int find_path(int source, int destination) {

    if (source == destination) return 0;

    vector<int> d (vertex_count, INF);
    d[source] = 0;   // начальный путь, до самого себя   (какой-то индекс)
    for (int i = 0; i < vertex_count-1; ++i) {
        // matrix search
        bool any_change = false;
        for (int x = 0; x < vertex_count; ++x)      // matrix[x] - source
            for (int y = 0; y < vertex_count; ++y) {    // matrix[x][y] - dest
                if (x == y) continue;   // пропускаем нулевые петли
                d[y] = min(d[y], d[x] + matrix[x][y]);
                any_change = true;
            }
        if (any_change == false)    // не гоняем бесмысленно цикл без изменений
            break;

    }

    for (int i = 0; i < d.size(); ++i) {
        cout << "d[" << i << "] =" << d[i] << endl;
    }
    cout << endl;
    return d[destination];
}

#endif //LAB_3_BELLMAN_FORD_H

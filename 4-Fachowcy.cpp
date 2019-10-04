#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;
struct para{
    int b;
    int efficient;
};
struct Node{
    int index;
    vector <para> neighbours;
    int previous;
};

//long zapytajJanusza(unsigned id) { //oczekiwana minimalna wartosc przeplywu
//    long value = 0;
//    switch( id ) {
//        case 6:
//            value = 19;
//            break;
//        case 7:
//            value = 5;
//            break;
//    }
//    return value;
//}

void kaczka(Node *graph, int start, int end, int l_wierzch, int minFlow) {
    int minimum = 30000, wynik = 0;
    queue<int> q;
    vector<int> path;
    bool *visited = new bool[l_wierzch];
    int temp;
    int temp_path;

    do {
        path.clear();
        for (long i = 0; i < l_wierzch; i++) {
            visited[i] = false;
        }
        while(!q.empty()){
            q.pop();
        }
        //bfs start
        
        visited[start] = true;
        q.push(start);
        bool found = false;
        
        while (!q.empty()) {
            temp = q.front();
            q.pop();
            for (int i = 0; i < graph[temp].neighbours.size(); i++) {
                if (graph[temp].neighbours[i].efficient > 0 && !visited[graph[temp].neighbours[i].b]) {
                    graph[graph[temp].neighbours[i].b].previous = graph[temp].index;
                    if (graph[temp].neighbours[i].b == end) {
                        temp_path = end;
                        while (temp_path != start) {
                            path.push_back(temp_path);
                            temp_path = graph[temp_path].previous;
                        }
                        path.push_back(temp_path);
                        found = true;
                        break;
                    }
                    visited[graph[temp].neighbours[i].b] = true;
                    q.push(graph[temp].neighbours[i].b);
                }
            }
            if (found) break;
        }
        //koniec bfsa
        if (path.empty()) {
            break;
        }
        minimum = 30000;
        //szukanie minimum
        for (int i = 1; i < path.size(); i++) {
            for (int j = 0; j < graph[path[i]].neighbours.size(); j++) {
                if (graph[path[i]].neighbours[j].b == path[i - 1] && graph[path[i]].neighbours[j].efficient < minimum) {
                    minimum = graph[path[i]].neighbours[j].efficient;
                }
            }
        }
        //odejmowanie przeplywu
        for (int i = 1; i < path.size(); i++) {
            for (int j = 0; j < graph[path[i]].neighbours.size(); j++) {
                if (graph[path[i]].neighbours[j].b == path[i - 1]) {
                    graph[path[i]].neighbours[j].efficient -= minimum;
                }
            }
        }

        wynik += minimum;
        if (wynik >= minFlow) {
            cout << end << " OK" << endl;
            return;
        }
    } while (!path.empty());
    cout << end << " NIE " << wynik << endl;

}

void copyy(Node *graph, Node* copy, short l_wierzch) {
    for (int i = 0; i < l_wierzch; i++) {
        copy[i].index = graph[i].index;
        copy[i].neighbours = graph[i].neighbours;
        copy[i].previous = graph[i].previous;
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    long l_wezlow, start, a, b, l_wierzch, efficient;
    para temp;
    cin >> l_wierzch >> l_wezlow >> start;
    Node *graph = new Node[l_wierzch];
    Node *copy = new Node[l_wierzch];

    for (long i = 0; i < l_wezlow; i++) {
        cin >> a >> b >> efficient;
        graph[a].index = a;
        graph[b].index = b;
        temp.b = b;
        temp.efficient = efficient;
        graph[a].neighbours.push_back(temp);

    }
    for (short i = l_wierzch - 1; i >= 0; --i) {
        if (graph[i].neighbours.empty()) {
            copyy(graph, copy, l_wierzch);
            kaczka(copy, start, i, l_wierzch, zapytajJanusza(i));
        }
    }
    return 0;
}
/*
6 8 0
0 1 2
0 2 4
0 3 3
0 4 3
2 3 5
1 4 2
2 5 4
4 5 4



5 NIE 8
3 OK
*/
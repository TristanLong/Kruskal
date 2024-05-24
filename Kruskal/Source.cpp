#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 20;

struct matrix {
    int maTranKe[MAX][MAX];
    int soDinh;
};

void readFile(matrix& mtk) {
    ifstream inFile("Text.txt");
    if (!inFile.is_open()) {
        cout << "\nKhong the mo tep";
        return;
    }

    inFile >> mtk.soDinh;
    for (int i = 0; i < mtk.soDinh; i++) {
        for (int j = 0; j < mtk.soDinh; j++) {
            inFile >> mtk.maTranKe[i][j];
        }
    }
    inFile.close();
}

void outputMatrix(const matrix& mtk) {
    cout << "\nMA TRAN KE: " << endl;
    for (int i = 0; i < mtk.soDinh; i++) {
        for (int j = 0; j < mtk.soDinh; j++) {
            cout << mtk.maTranKe[i][j] << "\t";
        }
        cout << endl;
    }
}

void DFS(int u, const matrix& graph, vector<bool>& visited) {
    visited[u] = true;
    for (int i = 0; i < graph.soDinh; ++i) {
        if (graph.maTranKe[u][i] != -1 && !visited[i]) {
            DFS(i, graph, visited);
        }
    }
}

bool isConnected(const matrix& graph) {
    vector<bool> visited(graph.soDinh, false);
    DFS(0, graph, visited);
    for (int i = 0; i < graph.soDinh; ++i) {
        if (!visited[i]) return false;
    }
    return true;
}

struct edge {
    int u, v, trongSo;
};

vector<edge> cayKhung;
void matrixToEdge(const matrix& graph) {
    for (int i = 0; i < graph.soDinh; i++) {
        for (int j = 0; j < graph.soDinh; j++) {
            if (graph.maTranKe[i][j] != 0 && i < j)
                cayKhung.push_back({ i, j, graph.maTranKe[i][j] }); // u, v, trongSo
        }
    }
}

bool comparater(const edge& canhA, const edge& canhB) {
    return canhA.trongSo > canhB.trongSo;
}

void kruskal(matrix graph) {
    vector<edge> mst; // minimum spanning tree
    int doLonCayKhung = 0;

    // sắp xếp cạnh giảm dần theo trọng số 
    sort(cayKhung.begin(), cayKhung.end(), comparater);

    for (const auto& canh : cayKhung) {
        // Remove the edge from the graph
        graph.maTranKe[canh.u][canh.v] = -1;
        graph.maTranKe[canh.v][canh.u] = -1;

        if (!isConnected(graph)) {
            // If the graph is not connected, add the edge back and include it in the MST
            graph.maTranKe[canh.u][canh.v] = canh.trongSo;
            graph.maTranKe[canh.v][canh.u] = canh.trongSo;
            mst.push_back(canh);
            doLonCayKhung += canh.trongSo;
        }

        // Stop if MST is complete
        if (mst.size() == graph.soDinh - 1) {
            break;
        }
    }

    if (mst.size() != graph.soDinh - 1)
        cout << "\nKhong ton tai cay khung";
    else {
        cout << "MST: " << doLonCayKhung << endl;
        for (const auto& canh : mst)
            cout << "(" << canh.u << "," << canh.v << "): " << canh.trongSo << endl;
    }
}

int main() {
    matrix graph;
    readFile(graph);
    outputMatrix(graph);
    matrixToEdge(graph);
    kruskal(graph);

    return 0;
}

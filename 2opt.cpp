#include <bits/stdc++.h>

using namespace std;

struct Point {
    double x;
    double y;
};

double distance(Point p1, Point p2) {
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}

double calculateRouteLength(vector<Point>& points, vector<int>& path) {
    double length = 0.0;

    for (int i = 0; i < path.size() - 1; i++) {
        int current = path[i];
        int next = path[i + 1];
        length += distance(points[current], points[next]);
    }

    return length;
}

int getRandom(int start, int end) {
    return start + rand() % (end - start + 1);
}

vector<int> tspRandomInsertion(vector<Point>& points) {
    int n = points.size();
    vector<int> path;
    vector<bool> added(n, false);

    int startVertex = getRandom(0, n - 1);
    path.push_back(startVertex);
    added[startVertex] = true;

    int secondVertex = getRandom(0, n - 1);
    while (secondVertex == startVertex) {
        secondVertex = getRandom(0, n - 1);
    }
    path.push_back(secondVertex);
    added[secondVertex] = true;

    for (int i = 2; i < n; i++) {
        int randomVertex = getRandom(0, n - 1);

        while (added[randomVertex]) {
            randomVertex = getRandom(0, n - 1);
        }

        int bestPosition = -1;
        double minIncrease = numeric_limits<double>::max();

        for (int j = 0; j < i; j++) {
            double increase = distance(points[path[j]], points[randomVertex]) +
                              distance(points[randomVertex], points[path[(j + 1) % i]]) -
                              distance(points[path[j]], points[path[(j + 1) % i]]);

            if (increase < minIncrease) {
                minIncrease = increase;
                bestPosition = j;
            }
        }

        path.insert(path.begin() + bestPosition + 1, randomVertex);
        added[randomVertex] = true;
    }

    return path;
}

void apply2Opt(vector<Point>& points, vector<int>& path) {
    int n = points.size();
    bool improved = true;

    while (improved) {
        improved = false;

        for (int i = 0; i < n - 2; i++) {
            for (int j = i + 2; j < n; j++) {
                double distCurrent = distance(points[path[i]], points[path[i + 1]]) +
                                    distance(points[path[j]], points[path[j % n]]);
                double distNew = distance(points[path[i]], points[path[j]]) +
                                 distance(points[path[i + 1]], points[path[(j + 1) % n]]);

                if (distNew < distCurrent) {
                    reverse(path.begin() + i + 1, path.begin() + j + 1);
                    improved = true;
                }
            }
        }
    }
}

int main() {
    srand(time(nullptr));

    vector<Point> points;

    int a;
    double x, y;
    while (cin >> a) {
        cin >> x >> y;
        points.push_back({x, y});
    }
    
    auto start = chrono::high_resolution_clock::now();

    vector<int> path = tspRandomInsertion(points);
    
    cout << calculateRouteLength(points, path) << endl;

    // 2-OPT

    apply2Opt(points, path);

    cout << calculateRouteLength(points, path) << endl;
    
    auto end = chrono::high_resolution_clock::now();
    double duration = chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000000.0;
    cout << duration << "s." << endl;


    return 0;
}

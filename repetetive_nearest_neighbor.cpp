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

int nearestNeighbor(vector<Point>& points, vector<bool>& visited, int current) {
    double minDist = numeric_limits<double>::max();
    int nearest = -1;
    
    for (int i = 0; i < points.size(); i++) {
        if (i != current && !visited[i]) {
            double dist = distance(points[current], points[i]);
            if (dist < minDist) {
                minDist = dist;
                nearest = i;
            }
        }
    }
    
    return nearest;
}

vector<int> tspNearestNeighbor(vector<Point>& points, int starting_vertex) {
    int n = points.size();
    vector<bool> visited(n, false);
    vector<int> path;
    
    int current = starting_vertex;
    
    path.push_back(current);
    visited[current] = true;
    
    for (int i = 0; i < n - 1; i++) {
        int next = nearestNeighbor(points, visited, current);
        path.push_back(next);
        visited[next] = true;
        current = next;
    }
    
    path.push_back(starting_vertex);
    
    return path;
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

vector<int> tspRepetetiveNearestNeighbor(vector<Point>& points) {

    int n = points.size();
    vector<int> best_path = tspNearestNeighbor(points, 0);
    double best_length = calculateRouteLength(points, best_path);

    for (int starting_vertex = 1; starting_vertex < n; starting_vertex++) {
        vector<int> path = tspNearestNeighbor(points, starting_vertex);
        double path_length = calculateRouteLength(points, path);

        if (best_length > path_length) {
            best_length = path_length;
            best_path = path;
        }
    }

    return best_path;
}


int main() {

    vector<Point> points;

    int a;
    double x, y;
    while (cin >> a) {
        cin >> x >> y;
        points.push_back({x, y});
    }

    auto start = chrono::high_resolution_clock::now();
    
    vector<int> path = tspRepetetiveNearestNeighbor(points);
    
    auto end = chrono::high_resolution_clock::now();
    double duration = chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000000.0;

    cout << calculateRouteLength(points, path) << endl;
    cout << "Execution Time: " << duration << " seconds" << endl;
    
    return 0;
}
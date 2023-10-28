#include <iostream>
#include <vector>
#include <queue>
#pragma GCC optimize("Ofast")

typedef struct Location {
    int x, y, z;
    Location() : x(0),y(0),z(0) {}
    Location(int x, int y, int z) : x(x), y(y), z(z) {}
} Location;

typedef std::vector<std::vector<std::vector<char>> > Grid3D;
typedef std::vector<std::vector<std::vector<bool>> > Visited3D;

int findPath(int L, int R, int C, Grid3D& gameGrid, Visited3D& visited, Location start, Location end) {

    const std::vector<int> dr = { -1, 1, 0, 0, 0, 0 };
    const std::vector<int> dc = { 0, 0, 1, -1, 0, 0 };
    const std::vector<int> dh = { 0, 0, 0, 0, -1, 1 };

    bool reached_end = false;

    std::queue<Location> q;
    q.push(start);
    visited[start.z][start.x][start.y] = true;

    int move_count = 0;
    int nodes_left_in_layer = 1;
    int nodes_in_next_layer = 0;

    while (!q.empty()) {
        Location current = q.front();
        q.pop();

        if (current.x == end.x && current.y == end.y && current.z == end.z) {
            reached_end = true;
            break;
        }

        for (int i = 0; i < 6; i++) {
            int rr = current.x + dr[i];
            int cc = current.y + dc[i];
            int hh = current.z + dh[i];

            if (rr < 0 || cc < 0 || hh < 0 || rr >= R || cc >= C || hh >= L || visited[hh][rr][cc] || gameGrid[hh][rr][cc] == '#') {
                continue;
            }

            Location next(rr, cc, hh);

            q.push(next);
            visited[hh][rr][cc] = true;
            nodes_in_next_layer++;
        }

        nodes_left_in_layer--;

        if (nodes_left_in_layer == 0) {
            nodes_left_in_layer = nodes_in_next_layer;
            nodes_in_next_layer = 0;
            move_count++;
        }
    }

    if (reached_end) {
        return move_count;
    }

    return -1;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int L, R, C;

    while (std::cin >> L >> R >> C) {
        if (L == 0 && R == 0 && C == 0) {
            break;
        }

        Grid3D gameGrid(L, std::vector<std::vector<char>>(R, std::vector<char>(C, '.')));
        Visited3D visited(L, std::vector<std::vector<bool>>(R, std::vector<bool>(C, false)));

        Location start, end;

        for (int h = 0; h < L; ++h) {
            for (int r = 0; r < R; ++r) {
                for (int c = 0; c < C; ++c) {
                    std::cin >> gameGrid[h][r][c];
                    if (gameGrid[h][r][c] == 'S') {
                        start = Location(r, c, h);
                    } else if (gameGrid[h][r][c] == 'E') {
                        end = Location(r, c, h);
                    }
                }
            }
        }

        int result = findPath(L, R, C, gameGrid, visited, start, end);
        if (result != -1) {
            std::cout << "Escaped in " << result << " minute(s)." << std::endl;
        } else {
            std::cout << "Trapped!" << std::endl;
        }
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>
#include <tuple>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<tuple<int, char, int>> events;
    int lo = INT_MAX, hi = 0;

    // Input handling and event generation
    for (int i = 0; i < n; ++i) {
        int a, d;
        cin >> a >> d;
        events.push_back(make_tuple(a, 'a', i));  // Arrival event
        events.push_back(make_tuple(d, 'd', i));  // Departure event
        lo = min(lo, a);
        hi = max(hi, d);
    }

    // Sorting events by time, with arrivals before departures at the same time
    sort(events.begin(), events.end());

    int max_rooms = 0, curr_rooms = 0;
    vector<int> assigned(n);
    vector<int> rooms;
    int room_i = 1;

    // Process events
    for (const auto& event : events) {
        int time;
        char type;
        int idx;
        tie(time, type, idx) = event;  // Unpack the tuple

        if (type == 'a') {  // Arrival
            if (rooms.empty()) {
                rooms.push_back(room_i++);  // Assign new room if no rooms are available
            }
            assigned[idx] = rooms.back();
            rooms.pop_back();
            curr_rooms++;
        } else {  // Departure
            rooms.push_back(assigned[idx]);  // Free the room
            curr_rooms--;
        }
        max_rooms = max(max_rooms, curr_rooms);
    }

    // Output the maximum number of rooms required
    cout << max_rooms << endl;

    // Output the room assignments
    for (int i = 0; i < n; ++i) {
        cout << assigned[i] << " ";
    }
    cout << endl;

    return 0;
}

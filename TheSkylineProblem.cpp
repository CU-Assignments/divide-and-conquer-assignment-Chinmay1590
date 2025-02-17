#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        vector<pair<int, int>> height;
        vector<vector<int>> result;

        // Step 1: Convert buildings into height points
        for (const auto& b : buildings) {
            height.emplace_back(b[0], -b[2]); // Start of building
            height.emplace_back(b[1], b[2]);  // End of building
        }

        // Step 2: Sort the height points
        sort(height.begin(), height.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.first != b.first) return a.first < b.first;
            return a.second < b.second;
        });

        // Step 3: Process the height points
        multimap<int, int, greater<int>> heightMap;
        heightMap.insert({0, 1}); // Initial ground height
        int prevMaxHeight = 0;

        for (const auto& h : height) {
            if (h.second < 0) {
                // Start of a building, add height
                heightMap.insert({-h.second, 1});
            } else {
                // End of a building, remove height
                auto it = heightMap.find(h.second);
                if (it != heightMap.end()) {
                    heightMap.erase(it);
                }
            }

            int curMaxHeight = heightMap.begin()->first;
            if (prevMaxHeight != curMaxHeight) {
                result.push_back({h.first, curMaxHeight});
                prevMaxHeight = curMaxHeight;
            }
        }

        return result;
    }
};

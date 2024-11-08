#include <vector>
using namespace std;

template <typename T>
int linear_search_last(const vector<T>& items, const T& target, size_t pos) {
    if (pos == items.size()) {
        return -1;
    }
    int found = linear_search_last(items, target, pos + 1);
    return (found == -1 && items[pos] == target) ? pos : found;
}

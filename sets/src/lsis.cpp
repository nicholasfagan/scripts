#include <vector>
#include <set>

template <class elem_t=double, class index_t=size_t>
class MaxPairs {
    std::set<std::pair<index_t, elem_t>> pairs;
public:
    void insert(const elem_t x, const index_t y) {
        pairs.emplace(y,x);
    }
    // assume this is a nice O(lg t) search instead of O(n). ( I'm lazy )
    const index_t *max(elem_t lo, elem_t hi) const {
        for(auto pair = pairs.rbegin(); pair != pairs.rend(); pair++) {
            if(lo <= pair->second && pair->second < hi) {
                return &pair->first;
            }
        }
        return nullptr;
    }
};

template<class elem_t>
size_t longestSlowlyIncreasingSubsequence(std::vector<elem_t> A, elem_t c) {
    MaxPairs<elem_t,size_t> S;
    elem_t max_value = -1;
    for(size_t i = 0; i < A.size(); i++) {
        if(A[i] > max_value) max_value = A[i];
        const size_t* len = S.max(A[i]/c, A[i]);
        if(!len) S.insert(A[i], 1);
        else S.insert(A[i], *len + 1);
    }
    return *S.max(-1, max_value+1);
}

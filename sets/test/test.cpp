//
// Created by nfagan on 10/18/19.
//

#include "test.h"
#include "sets.hpp"
int main() {

    TEST(empty_is_null, {
        sets::DisjointSets<int> s;
        s.create(11);
        s.create(21);
        s.join(-10, -20);
        assert(!s.find(10));
        assert(!s.find(20));
    });

    TEST(create_and_join, {
        sets::DisjointSets<int> s;
        s.create(10);
        s.create(20);
        s.join(10,20);
        assert(s.find(10));
        assert(s.find(10) == s.find(20));
    });

    TEST(unique_create, {
        sets::DisjointSets<int> s;
        s.create(10);
        s.create(20);
        assert(s.find(10));
        assert(s.find(20));
        assert_neq(s.find(10), s.find(20));
    });

    SKIP_TEST(size_adds_reps,{
        sets::DisjointSets<int> s;
        s.create(1); // count = 1
        s.create(2); // count = 1
        s.join(1,2); // find(1).count == find(2).count = 2
        assert(s.find(1));
        assert_eq(s.find(1), s.find(2));
        assert_eq(2, s.find(1)->count());
    });

    TEST(load_test_join, {
        sets::DisjointSets<int> s;
        // create 100K numbers
        int max = 100000;
        for(int i = 0; i < max; ++i) {
            s.create(i);
        }
        int num = 1000; // do a thousand joins
        int dist = max / num;
        // join every n
        for(int n = dist; n < max; n += dist) {
            s.join(n-dist, n );
        }
    });

}


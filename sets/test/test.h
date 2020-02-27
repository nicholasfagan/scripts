//
// Created by nfagan on 10/18/19.
//

#ifndef SETS_TEST_H
#define SETS_TEST_H

#include <iostream>
#include <pthread.h>
enum status {
    PASS, FAIL
};

const enum status PASSED = PASS;
const enum status FAILED = FAIL;

#define assert(expr) if(!(expr)){\
    fprintf(stderr, "[FAIL]: " __FILE__ ":%d assert("  #expr ")\n", __LINE__);\
    pthread_exit((void*)&FAILED);\
}

#define assert_eq(expected, actual) if((expected) != (actual)) {\
    std::cerr << "[FAIL]: " __FILE__ ":" << __LINE__ << std::endl << "\texpected: " #expected " = " << (expected) << std::endl << "\tactual: " #actual " = " << (actual) << std::endl ;\
    pthread_exit((void*)&FAILED);\
}

#define assert_neq(notexpected, actual) if((notexpected) == (actual)) {\
    std::cerr << "[FAIL]: " __FILE__ ":" << __LINE__ << std::endl << "\tnotexpected: " #notexpected " = " << (notexpected) << std::endl << "\tactual: " #actual " = " << (actual) << std::endl ;\
    pthread_exit((void*)&FAILED);\
}

#define __CLASS_NAME(name) Test_##name

#define SKIP_TEST(name, body) fprintf(stderr, "Test "#name" . . . \t[SKIP]\n");

#define TEST(name, body)        \
class    __CLASS_NAME(name) {   \
public:\
__CLASS_NAME(name) () {}; \
static void run() {\
    pthread_t t;\
    pthread_create(&t, NULL, &test_body, NULL);\
    pthread_join(t, NULL);\
};\
private:\
static void* test_body(void *) {              \
    fprintf(stderr,"Test "#name" . . . \t");\
    inner_test_body();\
    fprintf(stderr,"[PASS]\n");\
    return (void*)&PASSED;      \
};\
static void inner_test_body() body \
}; __CLASS_NAME(name)::run()

#endif //SETS_TEST_H

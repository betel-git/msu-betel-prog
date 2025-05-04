// TEST 1 (проверка ifdef и define)
#define DEBUG

#ifdef DEBUG
    printf("Debug mode\n");
#endif

// TEST 2 (проверка else)
#ifdef DEBUG
    printf("Debug mode\n");
#else
    printf("Release mode\n");
#endif

// TEST 3 (проверка ifndef)
#ifndef RELEASE
    printf("Not in release mode\n");
#endif

// TEST 4 (проверка вложенных директив)
#define FEATURE_A
#define FEATURE_B

#ifdef FEATURE_A
    printf("Feature A enabled\n");
    #ifdef FEATURE_B
        printf("Feature B also enabled\n");
    #endif
#endif

// TEST 5 (проверка вложенных директив + else)
#define FEATURE_A

#ifdef FEATURE_A
    printf("Feature A enabled\n");
    #ifdef FEATURE_B
        printf("Feature B also enabled\n");
    #else
        printf("Feature B disabled\n");
    #endif
#endif

// TEST 6 (проверка define внутри блока)
#ifdef FEATURE_A
    #define TEMP 1
    printf("TEMP = %d\n", TEMP);
#endif

// TEST 7 (проверка undef)
#define DEBUG
#ifdef DEBUG
    printf("Debug mode\n");
    #undef DEBUG
    #ifdef DEBUG
        printf("Still debug?\n");
    #endif
#endif

// TEST 8 (проверка на пустые блоки)
#ifdef DEBUG
#endif

#ifndef RELEASE
#endif

// TEST 9 (комплексная проверка)
#define A
#define B

#ifdef A
    printf("A enabled\n");
    #ifndef C
        printf("C disabled\n");
        #ifdef B
            printf("B enabled\n");
        #else
            printf("B disabled\n");
        #endif
    #endif
#else
    printf("A disabled\n");
#endif 

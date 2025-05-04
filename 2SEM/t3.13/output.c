// TEST 1 (проверка ifdef и define)

printf("Debug mode\n");

// TEST 2 (проверка else)
printf("Debug mode\n");

// TEST 3 (проверка ifndef)
printf("Not in release mode\n");

// TEST 4 (проверка вложенных директив)

printf("Feature A enabled\n");
printf("Feature B also enabled\n");

// TEST 5 (проверка вложенных директив + else)

printf("Feature A enabled\n");
printf("Feature B also enabled\n");

// TEST 6 (проверка define внутри блока)
printf("TEMP = %d\n", TEMP);

// TEST 7 (проверка undef)
printf("Debug mode\n");
printf("Still debug?\n");

// TEST 8 (проверка на пустые блоки)


// TEST 9 (комплексная проверка)

printf("A enabled\n");
printf("C disabled\n");
printf("B enabled\n");

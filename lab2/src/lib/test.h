#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "color.h"
#include "base.h"
#include "file.h"
#include "directory.h"

void test_all();
void printResult(int tot_tests, int errors);
void test_root();
void test_add_get_remove();
void test_ls();
void test_iterator();
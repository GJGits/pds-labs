#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <bits/stdc++.h>

#include "functions.h"
#include "duration.h"

void test_all();
void printResult(int tot_tests, int errors);
std::string parse(const std::string &target, const std::regex &rgx);
void mapReduceIp();
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <bits/stdc++.h>
#include <regex>
#include <thread>
#include <mutex>

#include "functions.h"
#include "duration.h"
#include "jobs.h"

void test_all();
void printResult(int tot_tests, int errors);
std::string parse(const std::string &target, const std::regex &rgx);
void mapReduceIp();
void lab4_12();
void lab4_3();
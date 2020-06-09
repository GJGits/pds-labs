#include "../lib/test.h"

Color::Modifier red1(Color::FG_RED);
Color::Modifier blue1(Color::FG_BLUE);
Color::Modifier def1(Color::FG_DEFAULT); // restore color

void printResult(int tot_tests, int errors)
{
    std::cout << "--> Passed: " << (tot_tests - errors) << "/" << tot_tests;
    if (errors != 0)
    {
        std::cout << " [" << red1 << "KO!" << def1 << "]" << std::endl;
    }
    else
    {
        std::cout << " [" << blue1 << "OK!" << def1 << "]" << std::endl;
    }
}

void mapReduceIp()
{
    std::cout << "##### TEST MAP-REDUCE IP #####\n";
    std::regex rgx_ip("\\d+\\.\\d+\\.\\d+\\.\\d+");
    auto mapIp = [&rgx_ip](SimpleMapperInputT input) {
        std::string token = parse(std::move(input.getInput()), rgx_ip);
        SimpleResult<int> res{token, 1};
        return res;
    };
    auto reduce = [](const SimpleReducerInput<int, int> &input) { return SimpleResult<int>{input.getKey(), (input.getValue() + input.getAccumulator())}; };
    std::map<std::string, SimpleResult<int>> results;
    {
        DurationLogger mip{"mapreduce_ip"};
        // localhost_access_log.2020
        results = mapReduceConcurrent<SimpleMapperInputT, SimpleResult<int>, SimpleReducerInput<int, int>>("../logs/localhost_access_log.2020.txt", mapIp, reduce);
    }

    //print first 100 rows
    int count = 0;
    for (std::pair<std::string, SimpleResult<int>> element : results)
    {
        std::cout << "(" << element.first << ", " << element.second.getValue() << ")\n";
        if (++count > 100)
            break;
    }
}

void lab4_12()
{

    StringJobs jobs{};
    std::mutex m;
    std::string path = "./files";
    std::vector<std::thread> consumers{};
    std::vector<std::thread> producers{};
    std::regex rgx("Secret message");

    // AGGIUNGO PRODUCER ALLA LISTA (IN QUESTA FASE ABBIAMO UN SOLO PRODUCER)
    producers.emplace_back([&path, &jobs]() {
        for (const auto &entry : std::filesystem::directory_iterator(path))
        {
            std::string fname = std::move(entry.path());
            std::ifstream ifs(fname);
            std::string s;
            std::string separator{","};
            int line = 1;
            while (ifs)
            {
                //std::cout << "called producer\n";
                std::getline(ifs, s);
                jobs.put(std::to_string(line) + separator + fname + separator + s);
                line++;
            }
            ifs.close();
        }
    });

    // CREO N CONSUMERS CON N = 10
    for (int i = 0; i < 10; i++)
    {
        consumers.emplace_back([&jobs, &rgx]() {
            std::string job;
            while (job.empty() || job.compare("CIAONE") != 0)
            {
                job = jobs.get();
                std::vector<std::string> tokens;
                // 0,file1.txt,ciaoneeeeee
                for (int i = 0; i < 3; i++)
                {
                    int pos = job.find(",");
                    tokens.push_back(job.substr(0, pos));
                    job.erase(0, pos + 1);
                }
                //std::cout << tokens[0] << ", " << tokens[1] << ", " << tokens[2] << "\n";
                if (std::regex_search(tokens[2], rgx))
                {
                    std::cout << "found message in: " << tokens[1] << ", at line: " << tokens[0] << "\n";
                }
            }
        });
    }

    producers[0].join();
    jobs.put(std::string("CIAONE"));

    for (int i = 0; i < 10; i++)
        consumers[i].join();
}

void lab4_3()
{

    StringJobs jobs{};
    StringJobs fileJobs{};
    std::mutex m;
    std::string path = "./files";
    std::vector<std::thread> fileConsumers{};
    std::vector<std::thread> lineConsumers{};
    std::regex rgx("Secret message");

    for (const auto &entry : std::filesystem::directory_iterator(path))
    {
        std::string fname = std::move(entry.path());
        fileJobs.put(fname);
    }

    fileJobs.put(std::string("CIAONE_FILE"));

    // Creo 3 file consumers
    for (int i = 0; i < 3; i++)
    {
        fileConsumers.emplace_back([&]() {
            std::string fileName;
            while (fileName.empty() || fileName.compare("CIAONE_FILE") != 0)
            {
                fileName = fileJobs.get();
                std::ifstream ifs(fileName);
                std::string s;
                std::string separator{","};
                int line = 1;
                while (ifs)
                {
                    std::getline(ifs, s);
                    jobs.put(std::to_string(line) + separator + fileName + separator + s);
                    line++;
                }
                ifs.close();
            }
        });
    }

    // Creo 10 line cosumers
    for (int j = 0; j < 10; j++)
    {
        lineConsumers.emplace_back([&]() {
            std::string job;
            while (job.empty() || job.compare("CIAONE") != 0)
            {
                job = jobs.get();
                std::vector<std::string> tokens;
                // 0,file1.txt,ciaoneeeeee
                for (int i = 0; i < 3; i++)
                {
                    int pos = job.find(",");
                    tokens.push_back(job.substr(0, pos));
                    job.erase(0, pos + 1);
                }
                //std::cout << tokens[0] << ", " << tokens[1] << ", " << tokens[2] << "\n";
                if (std::regex_search(tokens[2], rgx))
                {
                    std::cout << "found message in: " << tokens[1] << ", at line: " << tokens[0] << "\n";
                }
            }
        });
    }

    for (size_t c = 0; c < fileConsumers.size(); c++)
    {
        fileConsumers[c].join();
    }

    jobs.put(std::string("CIAONE"));

    for (size_t b = 0; b < lineConsumers.size(); b++)
    {
        lineConsumers[b].join();
    }
}

void test_all()
{
    std::cout << "\n\n";
    lab4_12();
    std::cout << "\n";
    lab4_3();
    std::cout << "\n\n";
}

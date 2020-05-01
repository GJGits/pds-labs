#include "../lib/test.h"

Color::Modifier red(Color::FG_RED);
Color::Modifier blue(Color::FG_BLUE);
Color::Modifier def(Color::FG_DEFAULT); // restore color

void printResult(int tot_tests, int errors)
{
    std::cout << "--> Passed: " << (tot_tests - errors) << "/" << tot_tests;
    if (errors != 0)
    {
        std::cout << " [" << red << "KO!" << def << "]" << std::endl;
    }
    else
    {
        std::cout << " [" << blue << "OK!" << def << "]" << std::endl;
    }
}

void test_root()
{

    std::cout << "##### TEST ROOT #####" << std::endl;

    int tot_tests = 0;
    int errors = 0;

    std::shared_ptr<Directory> root = Directory::getRoot();

    if (++tot_tests; root.use_count() == 0)
    {
        std::cout << " -> root shared_ptr is empty" << std::endl;
        errors++;
        printResult(tot_tests, errors);
        return;
    }

    if (++tot_tests; root->getName().compare("/") != 0)
    {
        std::cout << " -> root name is incorrect. Expected '/', got '" << root->getName() << "'" << std::endl;
        errors++;
    }

    if (++tot_tests; root->getDir(".").lock()->getName().compare("/") != 0)
    {
        std::cout << " -> root self name is incorrect. Expected '/', got '" << root->get(".").lock()->getName() << "'" << std::endl;
        errors++;
    }

    if (++tot_tests; root->getDir("..").lock()->getName().compare("/") != 0)
    {
        std::cout << " -> root parent name is incorrect. Expected '/', got '" << root->get("..").lock()->getName() << "'" << std::endl;
        errors++;
    }

    printResult(tot_tests, errors);
}

void test_add_get_remove()
{

    std::cout << "##### TEST ADD/GET/REMOVE #####" << std::endl;

    int tot_tests = 0;
    int errors = 0;

    std::shared_ptr<Directory> root = Directory::getRoot();

    // ADDING PHASE

    std::shared_ptr<Directory> alpha = root->addDirectory("alpha");
    std::shared_ptr<Directory> beta = root->addDirectory("beta");
    std::shared_ptr<Directory> beta_fake = root->addDirectory("beta"); // should be empty
    std::shared_ptr<File> beta1 = beta->addFile("beta1", 100);
    std::shared_ptr<File> beta2 = beta->addFile("beta2", 200);
    std::shared_ptr<File> beta2_fake = beta->addFile("beta2", 200); // should be empty

    if (++tot_tests; alpha->getName().compare("alpha") != 0)
    {
        std::cout << " -> addDirectory is not implemented properly. Expected 'alpha', got '" << alpha->getName() << "'" << std::endl;
        errors++;
    }

    if (++tot_tests; beta->getName().compare("beta") != 0)
    {
        std::cout << " -> addDirectory is not implemented properly. Expected 'beta', got '" << beta->getName() << "'" << std::endl;
        errors++;
    }

    if (++tot_tests; beta1->getName().compare("beta1") != 0 || beta1->getSize() != 100)
    {
        std::cout << " -> addFile is not implemented properly. Expected 'beta1, 100', got '" << beta1->getName() << "', " << beta1->getSize() << std::endl;
        errors++;
    }

    if (++tot_tests; beta2->getName().compare("beta2") != 0 || beta2->getSize() != 200)
    {
        std::cout << " -> addFile is not implemented properly. Expected 'beta2, 200', got '" << beta2->getName() << "', " << beta2->getSize() << std::endl;
        errors++;
    }

    if (++tot_tests; beta_fake.use_count() != 0)
    {
        std::cout << " -> addDirectory is not implemented properly. Allowed a duplicate of beta " << std::endl;
        errors++;
    }

    if (++tot_tests; beta2_fake.use_count() != 0)
    {
        std::cout << " -> addFile is not implemented properly. Allowed a duplicate of beta2 " << std::endl;
        errors++;
    }

    // GETTING PHASE

    if (++tot_tests; root->getDir("alpha").lock().get() == nullptr || root->getDir("alpha").lock()->getName().compare("alpha") != 0)
    {
        if (root->getDir("alpha").lock().get() == nullptr)
            std::cout << " -> getDir is not implemented properly. Expected 'alpha', got '"
                      << "nullptr"
                      << "'" << std::endl;
        else
            std::cout << " -> getDir is not implemented properly. Expected 'alpha', got '" << root->getDir("alpha").lock()->getName() << "'" << std::endl;
        errors++;
    }

    if (++tot_tests; beta->getFile("beta1").lock().get() == nullptr || beta->getFile("beta1").lock()->getName().compare("beta1") != 0)
    {
        if (beta->getFile("beta1").lock().get() == nullptr)
            std::cout << " -> getFile is not implemented properly. Expected 'beta1', got '"
                      << "nullptr"
                      << "'" << std::endl;
        else
            std::cout << " -> getDir is not implemented properly. Expected 'beta1', got '" << beta->getFile("beta1").lock()->getName() << "'" << std::endl;
        errors++;
    }

    // REMOVE PHASE

    if (++tot_tests; root->remove("beta") == false)
    {
        std::cout << "remove not implemented properly. Remove of previously created beta directory failed" << std::endl;
    }

    if (++tot_tests; root->getDir("beta").use_count() != 0)
    {
        std::cout << "remove not implemented properly. Previously removed beta is still in children container" << std::endl;
    }

    printResult(tot_tests, errors);
}

void test_ls()
{
    std::cout << "##### TEST LS #####" << std::endl;

    std::shared_ptr<Directory> root = Directory::getRoot();
    std::shared_ptr<Directory> alpha = root->addDirectory("alpha");
    std::shared_ptr<Directory> beta = root->addDirectory("beta");
    std::shared_ptr<File> beta1 = beta->addFile("beta1", 100);
    std::shared_ptr<File> beta2 = beta->addFile("beta2", 200);

    root.get()->ls(0);

    // clean fs

    root->remove("alpha");
    root->remove("beta");
}

void test_iterator()
{

    std::cout << "##### TEST FILESYSTEM_ITERATOR #####" << std::endl;

    std::shared_ptr<Directory> root = Directory::getRoot();
    std::shared_ptr<Directory> last_parent_dir{nullptr};

    for (auto &p : std::filesystem::recursive_directory_iterator("/home"))
    {
        std::stringstream ss(p.path().string());
        std::vector<std::string> tokens;
        std::string token;

        // collecting tokens
        while (std::getline(ss, token, '/'))
        {
            if (!token.empty())
            {
                tokens.push_back(token);
            }
        }

        // create structure
        for (std::vector<int>::size_type i = 0; i != tokens.size(); i++)
        {
            // sicuramente una directory
            if (i < tokens.size() - 1)
            {
                // se parent dir e' vuota allora sono nella root
                if (last_parent_dir.get() == nullptr)
                {
                    // se children non contiene la directory aggiungo
                    last_parent_dir = root->getDir(tokens[i]).lock().use_count() == 0 ? root->addDirectory(tokens[i]) : root->getDir(tokens[i]).lock();
                }
                else
                {
                    last_parent_dir = last_parent_dir->getDir(tokens[i]).lock().use_count() == 0 ? last_parent_dir->addDirectory(tokens[i]) : last_parent_dir->getDir(tokens[i]).lock();
                }
            }
        }

        if (p.is_directory())
        {
            last_parent_dir->addDirectory(p.path().filename().string());
        }

        if (p.is_regular_file())
        {
            last_parent_dir->addFile(p.path().filename().string(), p.file_size());
        }

        last_parent_dir = std::shared_ptr<Directory>{nullptr};
    }

    root->ls(0);
}

void test_all()
{
    std::cout << std::endl;
    std::cout << std::endl;
    test_root();
    std::cout << std::endl;
    test_add_get_remove();
    std::cout << std::endl;
    test_ls();
    std::cout << std::endl;
    test_iterator();
    std::cout << std::endl;
    std::cout << std::endl;
}

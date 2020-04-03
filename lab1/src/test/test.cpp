#include "../lib/test.h"
#include "../lib/func1.h"
#include "../lib/message.h"
#include "../lib/message_store.h"
#include "../lib/duration.h"
#include <string.h>

void test_constructor_0()
{

    Color::Modifier red(Color::FG_RED);
    Color::Modifier blue(Color::FG_BLUE);
    Color::Modifier def(Color::FG_DEFAULT); // restore color

    std::cout << "  #### TESTS ON FUNCTION: Message()" << std::endl;

    int count = 6;
    int errors = 0;

    Message m1{};
    Message m2{};

    long id1 = m1.getId();
    long id2 = m2.getId();
    int size1 = m1.getSize();
    int size2 = m2.getSize();

    if (id1 != -1)
    {
        std::cout << "called: getId(), expected: " << -1 << ", got: " << id1 << std::endl;
        errors++;
    }
    if (id2 != -1)
    {
        std::cout << "called: getId(), expected: " << -1 << ", got: " << id2 << std::endl;
        errors++;
    }

    if (size1 != 0)
    {
        std::cout << "called: getSize(), expected: " << 0 << ", got: " << size1 << std::endl;
        errors++;
    }
    if (size2 != 0)
    {
        std::cout << "called: getSize(), expected: " << 0 << ", got: " << size2 << std::endl;
        errors++;
    }

    if (strlen(m1.getData()) != 0)
    {
        std::cout << "called: getData(), expected: "
                  << "true"
                  << ", got: "
                  << "false" << std::endl;
        errors++;
    }

    if (strlen(m2.getData()) != 0)
    {
        std::cout << "called: getData(), expected: "
                  << "true"
                  << ", got: "
                  << "false" << std::endl;
        errors++;
    }

    if (errors == 0)
    {
        std::cout << "  Passed: " << (count - errors) << "/" << count << blue << " [OK!]" << def << std::endl;
    }
    else
    {
        std::cout << "  Passed: " << (count - errors) << "/" << count << red << " [KO!]" << def << std::endl;
    }
}

void test_constructor_1()
{

    Color::Modifier red(Color::FG_RED);
    Color::Modifier blue(Color::FG_BLUE);
    Color::Modifier def(Color::FG_DEFAULT); // restore color

    std::cout << "  #### TESTS ON FUNCTION: Message(int n)" << std::endl;

    int count = 6;
    int errors = 0;

    Message m1 = {10};
    Message m2 = {12};

    long id1 = m1.getId();
    long id2 = m2.getId();
    int size1 = m1.getSize();
    int size2 = m2.getSize();

    if (id1 != 0)
    {
        std::cout << "  called: getId(), expected: " << 0 << ", got: " << id1 << std::endl;
        errors++;
    }
    if (id2 != 1)
    {
        std::cout << "  called: getId(), expected: " << 1 << ", got: " << id2 << std::endl;
        errors++;
    }

    if (size1 != 10)
    {
        std::cout << "  called: getSize(), expected: " << 10 << ", got: " << size1 << std::endl;
        errors++;
    }
    if (size2 != 12)
    {
        std::cout << "  called: getSize(), expected: " << 12 << ", got: " << size2 << std::endl;
        errors++;
    }

    if (strcmp("raqisibuce", m1.getData()) != 0)
    {
        std::cout << "  called: getData(), expected: "
                  << "raqisibuce"
                  << ", got: " << m1.getData() << std::endl;
        errors++;
    }

    if (strcmp("raqisibucedo", m2.getData()) != 0)
    {
        std::cout << "  called: getData(), expected: "
                  << "raqisibucedo"
                  << ", got: " << m2.getData() << std::endl;
        errors++;
    }

    if (errors == 0)
    {
        std::cout << "  Passed: " << (count - errors) << "/" << count << blue << " [OK!]" << def << std::endl;
    }
    else
    {
        std::cout << "  Passed: " << (count - errors) << "/" << count << red << " [KO!]" << def << std::endl;
    }
}

void test_constructor_2()
{
    Color::Modifier red(Color::FG_RED);
    Color::Modifier blue(Color::FG_BLUE);
    Color::Modifier def(Color::FG_DEFAULT); // restore color

    std::cout << "  #### TESTS ON FUNCTION: Message(const Message &source)" << std::endl;

    int count = 3;
    int errors = 0;

    Message m1 = {10};
    Message m2 = {m1};

    long id1 = m1.getId();
    long id2 = m2.getId();
    int size1 = m1.getSize();
    int size2 = m2.getSize();

    if (id1 != id2)
    {
        std::cout << "  called: comp(id1,id2), expected: "
                  << "0,0"
                  << ", got: " << id1 << "," << id2 << std::endl;
        errors++;
    }

    if (size1 != size2)
    {
        std::cout << "  called: comp(size1,size2), expected: "
                  << "10,10"
                  << ", got: " << size1 << "," << size2 << std::endl;
        errors++;
    }
    if (strcmp(m1.getData(), m2.getData()) != 0)
    {
        std::cout << "  called: comp(m1.getData(), m2.getData()), expected: " << m1.getData() << ", " << m2.getData() << ", got: " << m1.getData() << "," << m2.getData() << std::endl;
        errors++;
    }

    if (errors == 0)
    {
        std::cout << "  Passed: " << (count - errors) << "/" << count << blue << " [OK!]" << def << std::endl;
    }
    else
    {
        std::cout << "  Passed: " << (count - errors) << "/" << count << red << " [KO!]" << def << std::endl;
    }
}

void test_constructor_3()
{
    Color::Modifier red(Color::FG_RED);
    Color::Modifier blue(Color::FG_BLUE);
    Color::Modifier def(Color::FG_DEFAULT); // restore color

    std::cout << "  #### TESTS ON FUNCTION: Message(Message &&source)" << std::endl;

    int count = 6;
    int errors = 0;

    Message m1 = {10};
    Message m2 = std::move(m1);

    long id1 = m1.getId();
    long id2 = m2.getId();
    int size1 = m1.getSize();
    int size2 = m2.getSize();

    if (id1 != 0)
    {
        std::cout << "  called: comp(id1,0), expected: "
                  << "0"
                  << ", got: " << id1 << std::endl;
        errors++;
    }

    if (size1 != 0)
    {
        std::cout << "  called: comp(size1,0), expected: "
                  << "0"
                  << ", got: " << size1 << std::endl;
        errors++;
    }
    if (m1.getData() != nullptr)
    {
        std::cout << "  called: comp(m1.getData(), nullptr), expected: "
                  << "nullptr"
                  << ", got: " << m1.getData() << std::endl;
        errors++;
    }

    if (id2 != 3)
    {
        std::cout << "  called: comp(id2,0), expected: "
                  << "0"
                  << ", got: " << id2 << std::endl;
        errors++;
    }

    if (size2 != 10)
    {
        std::cout << "  called: comp(size2,0), expected: "
                  << "10"
                  << ", got: " << size2 << std::endl;
        errors++;
    }
    if (strcmp(m2.getData(), "raqisibuce") != 0)
    {
        std::cout << "  called: comp(m2.getData(), raqisibuce), expected: "
                  << "raqisibuce"
                  << ", got: " << m2.getData() << std::endl;
        errors++;
    }

    if (errors == 0)
    {
        std::cout << "  Passed: " << (count - errors) << "/" << count << blue << " [OK!]" << def << std::endl;
    }
    else
    {
        std::cout << "  Passed: " << (count - errors) << "/" << count << red << " [KO!]" << def << std::endl;
    }
}

void test_constructor_4()
{

    Color::Modifier red(Color::FG_RED);
    Color::Modifier blue(Color::FG_BLUE);
    Color::Modifier def(Color::FG_DEFAULT); // restore color

    std::cout << "  #### TESTS ON FUNCTION: MessageStore(int n)" << std::endl;

    int count = 2;
    int errors = 0;

    MessageStore ms{10};

    if (ms.getN() != 10)
    {
        std::cout << "  called: getN(), expected: "
                  << "10"
                  << ", got: " << ms.getN() << std::endl;
        errors++;
    }

    if (ms.getDim() != 10)
    {
        std::cout << "  called: getN(), expected: "
                  << "10"
                  << ", got: " << ms.getDim() << std::endl;
        errors++;
    }

    if (errors == 0)
    {
        std::cout << "  Passed: " << (count - errors) << "/" << count << blue << " [OK!]" << def << std::endl;
    }
    else
    {
        std::cout << "  Passed: " << (count - errors) << "/" << count << red << " [KO!]" << def << std::endl;
    }
}

void test_clock()
{

    Color::Modifier red(Color::FG_RED);
    Color::Modifier blue(Color::FG_BLUE);
    Color::Modifier def(Color::FG_DEFAULT); // restore color

    std::cout << "  #### TESTS ON FUNCTION: clock" << std::endl;

    // test tempo assegnazione ripeto 5 volte per poi calcolare media
    for (int i = 0; i < 5; i++)
    {
        Message buff1[10];
        Message buff2[10];
        for (int j = 0; j < 10; j++)
        {
            buff1[j] = Message(1024 * 1024);
        }
        // scope duration
        {
            DurationLogger dl1{"assegnazione"};
            for (int j = 0; j < 10; j++)
            {
                buff2[j] = buff1[j];
            }
        }
    }

    // test tempo assegnazione per movimento ripeto 5 volte per poi calcolare media
    for (int i = 0; i < 5; i++)
    {
        Message buff1[10];
        Message buff2[10];
        for (int j = 0; j < 10; j++)
        {
            buff1[j] = Message(1024 * 1024);
        }
        // scope duration
        {
            DurationLogger dl2{"assegnazione per movimento"};
            for (int j = 0; j < 10; j++)
            {
                buff2[j] = std::move(buff1[j]);
            }
        }
    }
}

void test_add()
{

    Color::Modifier red(Color::FG_RED);
    Color::Modifier blue(Color::FG_BLUE);
    Color::Modifier def(Color::FG_DEFAULT); // restore color

    std::cout << "  #### TESTS ON FUNCTION: add(Message &m)" << std::endl;

    //int count = 2;
    //int errors = 0;

    MessageStore ms{10};
    Message *marr = new Message[100];
    for (int i = 0; i < 100; i++)
    {
        marr[i] = Message{1024 * 1024};
    }
    {
        DurationLogger dl{"add()"};
        for (int i = 0; i < 100; i++)
        {
            ms.add(marr[i]);
        }
    }
    delete[] marr;
}

void test_remove()
{
    Color::Modifier red(Color::FG_RED);
    Color::Modifier blue(Color::FG_BLUE);
    Color::Modifier def(Color::FG_DEFAULT); // restore color

    std::cout << "  #### TESTS ON FUNCTION: remove(long id)" << std::endl;

    int count = 2;
    int errors = 0;

    MessageStore ms{10};
    Message m1{100};
    long code1 = m1.getId();
    ms.add(m1);
    bool f1 = ms.remove(code1);
    bool f2 = ms.remove(1587);

    if (f1 != true)
    {
        std::cout << "  called: remove(), expected: "
                  << "true"
                  << ", got: "
                  << "false" << std::endl;
        errors++;
    }

    if (f2 != false)
    {
        std::cout << "  called: remove(), expected: "
                  << "false"
                  << ", got: "
                  << "true" << std::endl;
        errors++;
    }

    if (errors == 0)
    {
        std::cout << "  Passed: " << (count - errors) << "/" << count << blue << " [OK!]" << def << std::endl;
    }
    else
    {
        std::cout << "  Passed: " << (count - errors) << "/" << count << red << " [KO!]" << def << std::endl;
    }
}

void test_get()
{
    Color::Modifier red(Color::FG_RED);
    Color::Modifier blue(Color::FG_BLUE);
    Color::Modifier def(Color::FG_DEFAULT); // restore color

    std::cout << "  #### TESTS ON FUNCTION: get(long id)" << std::endl;

    int count = 2;
    int errors = 0;

    MessageStore ms{10};
    Message m1{100};
    long code1 = m1.getId();
    ms.add(m1);
    if (auto mex = ms.get(code1))
    {
        if (mex->getId() != code1)
        {
            std::cout << "  called: get(), expected: "
                      << "true"
                      << ", got: "
                      << "false" << std::endl;
            errors++;
        }
    }
    else
    {
        std::cout << "  called: get(), expected: "
                  << "true"
                  << ", got: "
                  << "false" << std::endl;
        errors++;
    }

    if (errors == 0)
    {
        std::cout << "  Passed: " << (count - errors) << "/" << count << blue << " [OK!]" << def << std::endl;
    }
    else
    {
        std::cout << "  Passed: " << (count - errors) << "/" << count << red << " [KO!]" << def << std::endl;
    }
}

void test_compact()
{
    Color::Modifier red(Color::FG_RED);
    Color::Modifier blue(Color::FG_BLUE);
    Color::Modifier def(Color::FG_DEFAULT); // restore color

    int count = 2;
    int errors = 0;

    std::cout << "  #### TESTS ON FUNCTION: compact()" << std::endl;

    long codes[100];
    MessageStore ms{10};

    for (int i = 0; i < 100; i++)
    {
        Message x{1024 * 1024};
        codes[i] = x.getId();
        ms.add(x);
    }

    for (int i = 0; i < 100; i++)
    {
        if (i % 2 == 0)
        {
            long id = codes[i];
            ms.remove(id);
        }
    }

    ms.compact();

    if (ms.getDim() != 50)
    {
        std::cout << "  called: compact(), expected: "
                  << "dim=50"
                  << ", got: "
                  << ms.getDim() << std::endl;
        errors++;
    }

    for (int i = 0; i < 100; i++)
    {
        if (i % 2 != 0)
        {
            long id = codes[i];
            if (!ms.get(id))
            {
                std::cout << "  called: compact(), expected: "
                          << "id=" << id
                          << ", got: not found"
                          << std::endl;
                errors++;
                break;
            }
        }
    }

    if (errors == 0)
    {
        std::cout << "  Passed: " << (count - errors) << "/" << count << blue << " [OK!]" << def << std::endl;
    }
    else
    {
        std::cout << "  Passed: " << (count - errors) << "/" << count << red << " [KO!]" << def << std::endl;
    }
}

void test_all()
{
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;
    test_constructor_0();
    std::cout << "" << std::endl;
    test_constructor_1();
    std::cout << "" << std::endl;
    test_constructor_2();
    std::cout << "" << std::endl;
    test_constructor_3();
    std::cout << "" << std::endl;
    //test_clock();
    test_constructor_4();
    std::cout << "" << std::endl;
    //test_add();
    test_remove();
    std::cout << "" << std::endl;
    test_get();
    std::cout << "" << std::endl;
    test_compact();
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;
}
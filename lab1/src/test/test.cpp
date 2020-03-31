#include "../lib/test.h"
#include "../lib/func1.h"
#include "../lib/color.h"
#include "../lib/message.h"
#include <string.h>

void test_constructor_0() {

    Color::Modifier red(Color::FG_RED);
    Color::Modifier blue(Color::FG_BLUE);
    Color::Modifier def(Color::FG_DEFAULT); // restore color
    
    std::cout << "  #### TESTS ON FUNCTION: Message()" << std::endl;
    
    int count = 6;
    int errors = 0;

    Message m1 = {};
    Message m2 = {};

    long id1 = m1.getId();
    long id2 = m2.getId();
    int size1 = m1.getSize();
    int size2 = m2.getSize();

    if (id1 != -1) {
        std::cout << "called: getId(), expected: " << -1 << ", got: " << id1 << std::endl;
        errors++;
    }
    if (id2 != -1) {
        std::cout << "called: getId(), expected: " << -1 << ", got: " << id2 << std::endl;
        errors++;
    }

    if (size1 != 0) {
        std::cout << "called: getSize(), expected: " << 0 << ", got: " << size1 << std::endl;
        errors++;
    }
    if (size2 != 0) {
        std::cout << "called: getSize(), expected: " << 0 << ", got: " << size2 << std::endl;
        errors++;
    }

    if (strlen(m1.getData()) != 0) {
        std::cout << "called: getData(), expected: " << "true" << ", got: " << "false" << std::endl;
        errors++;
    }

    if (strlen(m2.getData()) != 0) {
        std::cout << "called: getData(), expected: " << "true" << ", got: " << "false" << std::endl;
        errors++;
    }

    if (errors == 0) {
        std::cout << "  Passed: " << (count - errors) << "/" << count << blue << " [OK!]" << def <<  std::endl;
    } else {
        std::cout << "  Passed: " << (count - errors) << "/" << count << red << " [KO!]" << def <<  std::endl;
    }

}

void test_constructor_1() {

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

    if (id1 != 0) {
        std::cout << "  called: getId(), expected: " << 0 << ", got: " << id1 << std::endl;
        errors++;
    }
    if (id2 != 1) {
        std::cout << "  called: getId(), expected: " << 1 << ", got: " << id2 << std::endl;
        errors++;
    }

    if (size1 != 10) {
        std::cout << "  called: getSize(), expected: " << 10 << ", got: " << size1 << std::endl;
        errors++;
    }
    if (size2 != 12) {
        std::cout << "  called: getSize(), expected: " << 12 << ", got: " << size2 << std::endl;
        errors++;
    }

    if (strcmp("raqisibuce", m1.getData()) != 0) {
        std::cout << "  called: getData(), expected: " << "raqisibuce" << ", got: " << m1.getData() << std::endl;
        errors++;
    }

    if (strcmp("raqisibucedo", m2.getData()) != 0) {
        std::cout << "  called: getData(), expected: " << "raqisibucedo" << ", got: " << m2.getData() << std::endl;
        errors++;
    }

    if (errors == 0) {
        std::cout << "  Passed: " << (count - errors) << "/" << count << blue << " [OK!]" << def <<  std::endl;
    } else {
        std::cout << "  Passed: " << (count - errors) << "/" << count << red << " [KO!]" << def <<  std::endl;
    }

}

void test_constructor_2() {
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

    if (id1 != id2) {
        std::cout << "  called: comp(id1,id2), expected: " << "0,0" << ", got: " << id1 << "," << id2 << std::endl;
        errors++;
    }

    if (size1 != size2) {
        std::cout << "  called: comp(size1,size2), expected: " << "10,10" << ", got: " << size1 << "," << size2 << std::endl;
        errors++;
    }
    if (strcmp(m1.getData(), m2.getData()) != 0) {
        std::cout << "  called: comp(m1.getData(), m2.getData()), expected: " << m1.getData() << ", " << m2.getData() << ", got: " << m1.getData() << "," << m2.getData()  << std::endl;
        errors++;
    }

    if (errors == 0) {
        std::cout << "  Passed: " << (count - errors) << "/" << count << blue << " [OK!]" << def <<  std::endl;
    } else {
        std::cout << "  Passed: " << (count - errors) << "/" << count << red << " [KO!]" << def <<  std::endl;
    }
}

void test_constructor_3() {
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

    if (id1 != 0) {
        std::cout << "  called: comp(id1,0), expected: " << "0" << ", got: " << id1 << std::endl;
        errors++;
    }

    if (size1 != 0) {
        std::cout << "  called: comp(size1,0), expected: " << "0" << ", got: " << size1  << std::endl;
        errors++;
    }
    if (m1.getData() != nullptr) {
        std::cout << "  called: comp(m1.getData(), nullptr), expected: " << "nullptr" << ", got: " << m1.getData() << std::endl;
        errors++;
    }

    if (id2 != 3) {
        std::cout << "  called: comp(id2,0), expected: " << "0" << ", got: " << id2 << std::endl;
        errors++;
    }

    if (size2 != 10) {
        std::cout << "  called: comp(size2,0), expected: " << "10" << ", got: " << size2  << std::endl;
        errors++;
    }
    if (strcmp(m2.getData(), "raqisibuce") != 0) {
        std::cout << "  called: comp(m2.getData(), raqisibuce), expected: " << "raqisibuce" << ", got: " << m2.getData() << std::endl;
        errors++;
    }

    if (errors == 0) {
        std::cout << "  Passed: " << (count - errors) << "/" << count << blue << " [OK!]" << def <<  std::endl;
    } else {
        std::cout << "  Passed: " << (count - errors) << "/" << count << red << " [KO!]" << def <<  std::endl;
    }
}

void test_const() {
    Color::Modifier red(Color::FG_RED);
    Color::Modifier blue(Color::FG_BLUE);
    Color::Modifier def(Color::FG_DEFAULT); // restore color
    
    std::cout << "  #### TESTS ON FUNCTION: const getData()" << std::endl;
    
    int count = 1;
    int errors = 0;

    Message m1{10};
    char buf[11] = "newmessage";
    memcpy((char *)m1.getData(), buf, 11);

    if (strcmp(m1.getData(), "newmessage") == 0) {
        std::cout << "  called: comp(m1.getData(),newmessage), expected: " << "raqisibuce" << ", got: " << m1.getData() << std::endl;
        errors++;
    }

    if (errors == 0) {
        std::cout << "  Passed: " << (count - errors) << "/" << count << blue << " [OK!]" << def <<  std::endl;
    } else {
        std::cout << "  Passed: " << (count - errors) << "/" << count << red << " [KO!]" << def <<  std::endl;
    }
}

void test_all() {
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
    test_const();
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;
}
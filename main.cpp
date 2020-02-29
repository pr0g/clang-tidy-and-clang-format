#include <iostream>

int g_flag = 0;

int main(int argc, char **argv)
{
    bool condition = true;
    if (condition)
        std::cout << "hello, world!\n";

    auto fn = [condition]() {
        if (condition)
            g_flag = 1;
    };

    fn();

    return 0;
}

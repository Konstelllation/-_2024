// это предварительные объявления для функций в io.cpp
int readNumber();
void writeAnswer(int x);

int main()
{
    int x{ readNumber() };
    int y{ readNumber() };
    writeAnswer(x + y);
    return 0;
}
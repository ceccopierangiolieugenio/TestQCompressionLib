#ifndef TEST_LZMA_H
#define TEST_LZMA_H

#include <QString>

class Test_Lzma
{
public:
    Test_Lzma();
    void info();
    bool test(QString inFile, QString outFile);
};

#endif // TEST_LZMA_H

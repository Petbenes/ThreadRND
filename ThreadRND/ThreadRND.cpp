#include <iostream>
#include <Windows.h>

int pintRNDNumber;

DWORD WINAPI RNDGenerator (LPVOID lpParam)
{
    for (;;)
    {
        pintRNDNumber++;
        if (pintRNDNumber > 6) pintRNDNumber = 1; 
    }
    
    return 0;
}

DWORD WINAPI RNDReader(LPVOID lpParam)
{
    for (int i=0;i<20;i++)
    {
        printf("%i,", pintRNDNumber);
        Sleep(200);
    }

    return 0;
}

int main()
{
    DWORD ldwThread1Id, ldwThread2Id;
    HANDLE lhThread2Id;

    // int proměnné
    pintRNDNumber = 1;

    // spuštění RND threadu
    CreateThread(NULL, 0, RNDGenerator, NULL, 0, &ldwThread1Id);

    // spuštění čtecího threadu
    lhThread2Id = CreateThread(NULL, 0, RNDReader, NULL, 0, &ldwThread2Id);

    WaitForSingleObject(lhThread2Id, 20000);

    std::cout << "Hello World!\n";
}

#include <iostream>
#include <Windows.h>

int pintRNDNumber;
HANDLE pmMutex01;

DWORD WINAPI RNDGenerator (LPVOID lpParam)
{
    DWORD ldwRetVal;

    for (;;)
    {
        ldwRetVal=WaitForSingleObject(pmMutex01, 2000);

        if (ldwRetVal == WAIT_OBJECT_0)
        {
            __try
            {
                pintRNDNumber++;
                if (pintRNDNumber > 6) pintRNDNumber = 1;
            }
            __finally
            {
                ReleaseMutex(pmMutex01);
            }
        }
    }
    
    return 0;
}

DWORD WINAPI RNDReader(LPVOID lpParam)
{
    DWORD ldwRetVal;

    for (int i=0;i<25;i++)
    {
        ldwRetVal = WaitForSingleObject(pmMutex01, 2000);

        if (ldwRetVal == WAIT_OBJECT_0)
        {
            __try
            {
                printf("%i,", pintRNDNumber);
            }
            __finally
            {
                ReleaseMutex(pmMutex01);
            }
        }

        Sleep(200);
    }

    return 0;
}

int main()
{
    DWORD ldwThread1Id, ldwThread2Id;
    HANDLE lhThread2Id;

    // vytvoření mutexu
    pmMutex01 = CreateMutex(NULL, FALSE, NULL);

    // int proměnné
    pintRNDNumber = 1;

    // spuštění RND threadu
    CreateThread(NULL, 0, RNDGenerator, NULL, 0, &ldwThread1Id);

    // spuštění čtecího threadu
    lhThread2Id = CreateThread(NULL, 0, RNDReader, NULL, 0, &ldwThread2Id);

    WaitForSingleObject(lhThread2Id, 20000);

    std::cout << "Hello World!\n";
}

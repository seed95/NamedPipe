#include <QCoreApplication>

#include <windows.h>

#include "server_named_pipe.h"
//#include <stdio.h>
//#include <conio.h>
//#include <tchar.h>

QString getLastErrorMsg() {
    LPWSTR bufPtr = nullptr;
    DWORD err = GetLastError();
    FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                   FORMAT_MESSAGE_FROM_SYSTEM |
                   FORMAT_MESSAGE_IGNORE_INSERTS,
                   nullptr, err, 0, (LPWSTR)&bufPtr, 0, nullptr);
    const QString result =
        (bufPtr) ? QString::fromUtf16((const ushort*)bufPtr).trimmed() :
                   QString("Unknown Error %1").arg(err);
    LocalFree(bufPtr);
    return result;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ServerNamedPipe *pipe = new ServerNamedPipe();
    pipe->ListenPipe();

//    HANDLE hPipe;
//    char buffer[1024];
//    DWORD dwRead;


//    hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\ipc"),
//                            PIPE_ACCESS_INBOUND,// The flow of data in the pipe goes from client to server only
//                            PIPE_TYPE_BYTE | PIPE_WAIT,// FILE_FLAG_FIRST_PIPE_INSTANCE is not needed but forces CreateNamedPipe(..) to fail if the pipe already exists...
//                            1,
//                            1,//1024 * 16,
//                            1,//1024 * 16,
//                            NMPWAIT_USE_DEFAULT_WAIT,
//                            nullptr);
//    while (hPipe != INVALID_HANDLE_VALUE)
//    {
//        if (ConnectNamedPipe(hPipe, nullptr) != FALSE)   // wait for someone to connect to the pipe
//        {
//            while (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &dwRead, nullptr) != FALSE)
//            {
//                /* add terminating zero */
//                buffer[dwRead] = '\0';

//                /* do something with data in buffer */
//                printf("%s", buffer);
//            }
//        }

//        DisconnectNamedPipe(hPipe);
//    }

    return a.exec();
}



#include <QCoreApplication>

#include <QDebug>
#include <QDir>

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>

#include "client_named_pipe.h"

//QString getLastErrorMsg() {
//    LPWSTR bufPtr = NULL;
//    DWORD err = GetLastError();
//    FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER |
//                   FORMAT_MESSAGE_FROM_SYSTEM |
//                   FORMAT_MESSAGE_IGNORE_INSERTS,
//                   NULL, err, 0, (LPWSTR)&bufPtr, 0, NULL);
//    const QString result =
//        (bufPtr) ? QString::fromUtf16((const ushort*)bufPtr).trimmed() :
//                   QString("Unknown Error %1").arg(err);
//    LocalFree(bufPtr);
//    return result;
//}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ClientNamedPipe *pipe = new ClientNamedPipe();
    pipe->SendCommand("command1", "arg1 arg2 arg3");
    pipe->SendCommand("command2", "arg1");


//    HANDLE hPipe;
//    DWORD dwWritten;

//    QString pipeName("\\\\.\\pipe\\ipc");

//    if(WaitNamedPipeA(pipeName.toStdString().c_str(), NMPWAIT_USE_DEFAULT_WAIT)) {
////    if(WaitNamedPipe(TEXT("\\\\.\\pipe\\ipc"), NMPWAIT_USE_DEFAULT_WAIT)) {
////        hPipe = CreateFile(TEXT("\\\\.\\pipe\\ipc"),
//        hPipe = CreateFileA(pipeName.toStdString().c_str(),
//                           GENERIC_WRITE,
//                           0,
//                           nullptr,
//                           OPEN_EXISTING,
//                           0,
//                           nullptr);

//        qDebug() << "create pipe" << hPipe;
////        if (hPipe != INVALID_HANDLE_VALUE)
////        {
////            WriteFile(hPipe,
////                      "Hello Pipe\n",
////                      12,   // = length of string + terminating '\0' !!!
////                      &dwWritten,
////                      NULL);
////            qDebug() << dwWritten;
////            CloseHandle(hPipe);
////        }


//    }
//    else {
//        qDebug() << "first create pipe" << pipeName;
//        return -1;
//    }


//    QTextStream s(stdin);

//    while(1) {
//        QString line = s.readLine();
//        if (line == "q") {
//            exit(0);
//        }


//        if (hPipe != INVALID_HANDLE_VALUE)
//        {
////            QString strLength(line.length());
////            line.length()
//            if (WriteFile(hPipe,
//                      line.toStdString().c_str(),
//                      (DWORD)line.length(),   // = length of string + terminating '\0' !!!
//                      &dwWritten,
//                      NULL) )
//            {

//            }
//            qDebug() << dwWritten;
//        }


//    }
//    CloseHandle(hPipe);

//    if(WaitNamedPipeA(pipeName.toStdString().c_str(), NMPWAIT_WAIT_FOREVER)==1) {
//        hPipe = CreateFileA(pipeName.toStdString().c_str(),
//                           GENERIC_WRITE,
//                           0,
//                           NULL,
//                           OPEN_EXISTING,
//                           0,
//                           NULL);

//        if (hPipe != INVALID_HANDLE_VALUE)
//        {
//            WriteFile(hPipe,
//                      "Hello Pipe\n",
//                      12,   // = length of string + terminating '\0' !!!
//                      &dwWritten,
//                      NULL);
//            qDebug() << dwWritten;
//            CloseHandle(hPipe);
//        }


//    }
//    else {
//        qDebug() << "first create pipe" << pipeName;
//    }




    return a.exec();
}

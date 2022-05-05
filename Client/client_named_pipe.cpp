#include "client_named_pipe.h"

ClientNamedPipe::ClientNamedPipe(QObject *parent) : QObject(parent)
{
    QString pipeName(BUFFER_PATH);
    if(WaitNamedPipeA(pipeName.toStdString().c_str(), NMPWAIT_USE_DEFAULT_WAIT))
    {
        hPipe = CreateFileA(pipeName.toStdString().c_str(),
                           GENERIC_WRITE,                   // dwDesiredAccess
                           0,                               // dwShareMode
                           nullptr,                         // lpSecurityAttributes
                           OPEN_EXISTING,                   // dwCreationDisposition
                           0,                               // dwFlagsAndAttributes
                           nullptr);                        // hTemplateFile

        if (hPipe == INVALID_HANDLE_VALUE)
        {
            qFatal("Cannot create " BUFFER_PATH);
        }
    }
    else
    {
        qFatal("First create pipe " BUFFER_PATH);
    }

}

void ClientNamedPipe::SendCommand(QString command, QString args)
{
    QString line(command + SEPARATOR + args + "\r\n");
    if (hPipe != INVALID_HANDLE_VALUE)
    {
        DWORD dwWritten;
        if (!WriteFile(hPipe, line.toStdString().c_str(), (DWORD)line.length(), &dwWritten, nullptr))
        {
            qDebug() << "Send error" << GetLastError();
        }

        if (dwWritten != (DWORD)line.length())
        {
            qDebug() << "Send have a problem. Total send char:" << dwWritten << ", Total char:" << line.length();
        }
    }
    else
    {
        qFatal("Invalid handle pipe for " BUFFER_PATH);
    }
}

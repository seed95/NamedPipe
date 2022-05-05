#include "server_named_pipe.h"

ServerNamedPipe::ServerNamedPipe(QObject *parent) : QObject(parent)
{   
    // To create an instance of a named pipe by using CreateNamedPipe,
    // the user must have FILE_CREATE_PIPE_INSTANCE access to the named pipe object.
    hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\ipc"),
                            PIPE_ACCESS_INBOUND,            // dwOpenMode. The flow of data in the pipe goes from client to server only
                            PIPE_TYPE_BYTE | PIPE_WAIT,     // dwPipeMode
                            1,                              // nMaxInstances
                            OUTPUT_BUFFER_SIZE,             // nOutBufferSize
                            INPUT_BUFFER_SIZE,              // nInBufferSize
                            NMPWAIT_WAIT_FOREVER,           // nDefaultTimeOut
                            nullptr);                       // lpSecurityAttributes

    if (hPipe == INVALID_HANDLE_VALUE)
    {
        qFatal("Cannot create \\\\.\\pipe\\ipc");
    }
    qDebug() << "Create pipe \\\\.\\pipe\\ipc";
}

void ServerNamedPipe::ListenPipe()
{
    char buffer[BUFFER_SIZE];
    DWORD dwRead;
    QStringList all_line;
    QStringList list_data;
    while(hPipe != INVALID_HANDLE_VALUE)
    {
        // wait for someone to connect to the pipe
        if (ConnectNamedPipe(hPipe, nullptr) != FALSE)
        {
            qDebug() << "Connect client";
            while (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &dwRead, nullptr) != FALSE)
            {
                /* add terminating zero */
                buffer[dwRead] = '\0';

                /* do something with data in buffer */
                printf("Received: %s\n", buffer);

                QString data(buffer);
                qDebug() << data;

                all_line = data.split(LINE_SEPARATOR, QString::SkipEmptyParts);

                foreach (QString line, all_line)
                {
                    line = line.trimmed();
                    list_data = line.split(COMMAND_SEPARATOR, QString::SkipEmptyParts);
                    if ( list_data.length()!=2 )
                    {
                        qDebug() << "Invalid data `" + data + "`";
                        continue;
                    }

                    qDebug() << "Command:" << list_data[COMMAND_POSITION];
                    qDebug() << "Args:" << list_data[ARGUMENT_POSITION];
                    emit ReceivedNewCommand(list_data[COMMAND_POSITION], list_data[ARGUMENT_POSITION]);
                }
            }
        }

        qDebug() << "Disconnect client";
        DisconnectNamedPipe(hPipe);
    }
}

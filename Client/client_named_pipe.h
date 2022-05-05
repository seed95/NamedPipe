#ifndef CLIENT_NAMED_PIPE_H
#define CLIENT_NAMED_PIPE_H

#include <QObject>
#include <QDebug>
#include <QString>

#include <windows.h>


#define BUFFER_PATH "\\\\.\\pipe\\ipc"

#define SEPARATOR "###"
#define COMMAND_POSITION 0
#define ARGUMENT_POSITION 1


class ClientNamedPipe : public QObject
{
public:
    ClientNamedPipe(QObject *parent = nullptr);
    void SendCommand(QString command, QString args);

private:
    HANDLE hPipe;
};

#endif // CLIENT_NAMED_PIPE_H

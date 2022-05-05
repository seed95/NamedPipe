#ifndef SERVER_NAMED_PIPE_H
#define SERVER_NAMED_PIPE_H

#include <QObject>
#include <QDebug>
#include <QString>

#include <windows.h>


#define BUFFER_PATH "\\\\.\\pipe\\icp"

// The buffer size specified should be small enough that your process will not run out of nonpaged pool,
// but large enough to accommodate typical requests.
#define BUFFER_SIZE (1024 * 8)
#define INPUT_BUFFER_SIZE BUFFER_SIZE
#define OUTPUT_BUFFER_SIZE BUFFER_SIZE

#define LINE_SEPARATOR "\r\n"
#define COMMAND_SEPARATOR "###"
#define COMMAND_POSITION 0
#define ARGUMENT_POSITION 1


class ServerNamedPipe : public QObject
{
    Q_OBJECT
public:
    ServerNamedPipe(QObject *parent = nullptr);
    void ListenPipe();


signals:
    void ReceivedNewCommand(QString command, QString args);

private:
    HANDLE hPipe;
//    char buffer[1024];
//    DWORD dwRead;


};

#endif // SERVER_NAMED_PIPE_H

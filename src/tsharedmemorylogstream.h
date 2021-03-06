#ifndef TSHAREDMEMORYLOGSTREAM_H
#define TSHAREDMEMORYLOGSTREAM_H

#include <QBasicTimer>
#include "tabstractlogstream.h"

class QSharedMemory;


class T_CORE_EXPORT TSharedMemoryLogStream : public TAbstractLogStream
{
public:
    TSharedMemoryLogStream(const QList<TLogger *> loggers, int size = 4096, QObject *parent = 0);
    ~TSharedMemoryLogStream();

    void writeLog(const TLog &);
    void flush();
    QString errorString() const;
    void setNonBufferingMode();

protected:
    void loggerWriteLog(const QList<TLog> &logs);
    void clearBuffer();
    QList<TLog> smRead();
    bool smWrite(const QList<TLog> &logs);
    static int dataSizeOf(const QList<TLog> &logs);
    void timerEvent(QTimerEvent *event);

private:
    QSharedMemory *shareMem;
    QBasicTimer timer;

    Q_DISABLE_COPY(TSharedMemoryLogStream)
};

#endif // TSHAREDMEMORYLOGSTREAM_H


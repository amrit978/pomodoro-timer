#include "worker.h"
#include <QThread>

Worker::Worker(QObject *parent) : QObject(parent) {}

QString Worker::formatTime(int seconds)
{
    return QString("%1:%2")
        .arg(seconds / 60, 2, 10, QChar('0'))
        .arg(seconds % 60, 2, 10, QChar('0'));
}

void Worker::setSessionsBeforeLongBreak(int n)
{
    sessionsBeforeLongBreak = n;
}

void Worker::requestPause()  { paused = true; }
void Worker::requestResume() { paused = false; }
void Worker::requestStop()   { stopped = true; paused = false; }

// Counts one phase down from startSeconds to 0, one tick per second.
// Checks stopped/paused every loop so Stop and Pause react within ~100ms
// instead of waiting for the current second to finish.
bool Worker::runPhase(int startSeconds, int totalSeconds)
{
    int secondsLeft = startSeconds;

    while (secondsLeft >= 0)
    {
        if (stopped) return false;

        while (paused)
        {
            if (stopped) return false;
            QThread::msleep(100);
        }

        emit timeUpdate(formatTime(secondsLeft));
        int percent = totalSeconds > 0
            ? 100 - (secondsLeft * 100 / totalSeconds)
            : 0;
        emit progressUpdate(percent);

        QThread::msleep(1000);
        secondsLeft--;
    }
    return true;
}

void Worker::countdown()
{
    stopped = false;
    paused = false;

    int count = 0;
    const int workDuration = 25 * 60;
    const int shortBreakDuration = 5 * 60;
    const int longBreakDuration = 15 * 60;

    while (1)
    {
        emit stateChanged("Work");
        if (!runPhase(workDuration, workDuration)) break;

        count++;
        emit sessionUpdate(count);

        emit stateChanged("Short break");
        if (!runPhase(shortBreakDuration, shortBreakDuration)) break;

        if (count == sessionsBeforeLongBreak)
        {
            emit stateChanged("Long break");
            if (!runPhase(longBreakDuration, longBreakDuration)) break;
            count = 0;
        }
    }

    emit finished();
}

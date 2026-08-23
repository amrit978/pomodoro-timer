#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QString>
#include <atomic>

class Worker : public QObject
{
    Q_OBJECT

public:
    explicit Worker(QObject *parent = nullptr);

    // Set BEFORE calling countdown() - how many work sessions before a long break.
    void setSessionsBeforeLongBreak(int n);

    // Safe to call anytime from the GUI thread - just flips a flag the
    // worker thread checks. No need to route these through invokeMethod.
    void requestPause();
    void requestResume();
    void requestStop();

public slots:
    void countdown();

signals:
    void timeUpdate(QString text);
    void stateChanged(QString label);
    void sessionUpdate(int count);
    void progressUpdate(int percent); // 0-100, for the QProgressBar
    void finished();

private:
    static QString formatTime(int seconds);

    // Runs one phase (work / short break / long break) second by second.
    // Returns false if a stop was requested mid-phase.
    bool runPhase(int startSeconds, int totalSeconds);

    std::atomic<bool> paused{false};
    std::atomic<bool> stopped{false};
    int sessionsBeforeLongBreak = 4;
};

#endif // WORKER_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QThread>
#include <QSoundEffect>
#include "worker.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStart();
    void onPause();
    void onReset();
    void onCyclesDecrease();
    void onCyclesIncrease();

private:
    QLabel *stateLabel;
    QLabel *timerLabel;
    QLabel *sessionLabel;
    QProgressBar *progressBar;

    QLabel *cyclesValueLabel;   // shows the current number, e.g. "4"
    QPushButton *cyclesMinusBtn;
    QPushButton *cyclesPlusBtn;
    int cyclesValue = 4;
    static constexpr int CYCLES_MIN = 1;
    static constexpr int CYCLES_MAX = 12;

    QPushButton *startBtn;
    QPushButton *pauseBtn;
    QPushButton *resetBtn;

    QThread workerThread;
    Worker *worker;
    QSoundEffect *notificationSound;

    bool isPaused = false;
    bool isRunning = false;
    bool isFirstPhaseAfterStart = true;

    void setupUi();
    void applyStyles();
    void updateCyclesLabel();
    void resetUiToDefault(); // shared by Reset button and startup
};

#endif // MAINWINDOW_H
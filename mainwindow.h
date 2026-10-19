#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QThread>
<<<<<<< HEAD
#include <QSoundEffect>
=======
>>>>>>> 5242169cbfb87be66719702b5bf9ff9102a8d01f
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
<<<<<<< HEAD
=======
    void onStop();
>>>>>>> 5242169cbfb87be66719702b5bf9ff9102a8d01f
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
<<<<<<< HEAD
=======
    QPushButton *stopBtn;
>>>>>>> 5242169cbfb87be66719702b5bf9ff9102a8d01f
    QPushButton *resetBtn;

    QThread workerThread;
    Worker *worker;
<<<<<<< HEAD
    QSoundEffect *notificationSound;

    bool isPaused = false;
    bool isRunning = false;
    bool isFirstPhaseAfterStart = true;
=======

    bool isPaused = false;
    bool isRunning = false;
>>>>>>> 5242169cbfb87be66719702b5bf9ff9102a8d01f

    void setupUi();
    void applyStyles();
    void updateCyclesLabel();
    void resetUiToDefault(); // shared by Reset button and startup
};

#endif // MAINWINDOW_H
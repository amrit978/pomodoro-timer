#include "mainwindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIcon>
<<<<<<< HEAD
#include <QUrl>
=======
>>>>>>> 5242169cbfb87be66719702b5bf9ff9102a8d01f

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
    applyStyles();
    setWindowIcon(QIcon(":/icon.ico")); // loaded from icon.qrc, embedded in the binary

<<<<<<< HEAD
    notificationSound = new QSoundEffect(this);
    notificationSound->setSource(QUrl("qrc:/notification.wav"));
    notificationSound->setVolume(0.6);

=======
>>>>>>> 5242169cbfb87be66719702b5bf9ff9102a8d01f
    worker = new Worker();
    worker->moveToThread(&workerThread);

    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);

    connect(worker, &Worker::timeUpdate, this, [this](QString text) {
        timerLabel->setText(text);
    });
    connect(worker, &Worker::stateChanged, this, [this](QString label) {
        stateLabel->setText(label);
<<<<<<< HEAD
        if (!isFirstPhaseAfterStart) {
            notificationSound->play();
        }
        isFirstPhaseAfterStart = false;
=======
>>>>>>> 5242169cbfb87be66719702b5bf9ff9102a8d01f
    });
    connect(worker, &Worker::sessionUpdate, this, [this](int count) {
        sessionLabel->setText(QString("Sessions completed: %1").arg(count));
    });
    connect(worker, &Worker::progressUpdate, this, [this](int percent) {
        progressBar->setValue(percent);
    });
    connect(worker, &Worker::finished, this, [this]() {
        isRunning = false;
        isPaused = false;
        startBtn->setEnabled(true);
        pauseBtn->setEnabled(false);
        pauseBtn->setText("Pause");
<<<<<<< HEAD
=======
        stopBtn->setEnabled(false);
>>>>>>> 5242169cbfb87be66719702b5bf9ff9102a8d01f
        cyclesMinusBtn->setEnabled(true);
        cyclesPlusBtn->setEnabled(true);
        if (stateLabel->text() != "Ready")
            stateLabel->setText("Stopped");
    });

    connect(startBtn, &QPushButton::clicked, this, &MainWindow::onStart);
    connect(pauseBtn, &QPushButton::clicked, this, &MainWindow::onPause);
<<<<<<< HEAD
=======
    connect(stopBtn, &QPushButton::clicked, this, &MainWindow::onStop);
>>>>>>> 5242169cbfb87be66719702b5bf9ff9102a8d01f
    connect(resetBtn, &QPushButton::clicked, this, &MainWindow::onReset);
    connect(cyclesMinusBtn, &QPushButton::clicked, this, &MainWindow::onCyclesDecrease);
    connect(cyclesPlusBtn, &QPushButton::clicked, this, &MainWindow::onCyclesIncrease);

    workerThread.start();
    resetUiToDefault();
}

MainWindow::~MainWindow()
{
    worker->requestStop();
    workerThread.quit();
    workerThread.wait();
}

void MainWindow::setupUi()
{
    setWindowTitle("Pomodoro");
    resize(400, 480);

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->setContentsMargins(30, 40, 30, 30);
    layout->setSpacing(16);

    stateLabel = new QLabel("Ready", this);
    stateLabel->setObjectName("stateLabel");
    stateLabel->setAlignment(Qt::AlignCenter);

    timerLabel = new QLabel("25:00", this);
    timerLabel->setObjectName("timerLabel");
    timerLabel->setAlignment(Qt::AlignCenter);

    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    progressBar->setTextVisible(false);

    sessionLabel = new QLabel("Sessions completed: 0", this);
    sessionLabel->setObjectName("sessionLabel");
    sessionLabel->setAlignment(Qt::AlignCenter);

    // Big, easy-to-tap +/- controls instead of the tiny default spin arrows
    QHBoxLayout *cyclesRow = new QHBoxLayout();
    cyclesRow->setSpacing(14);

    QLabel *cyclesCaption = new QLabel("Sessions before long break", this);
    cyclesCaption->setObjectName("sessionLabel");
    cyclesCaption->setAlignment(Qt::AlignCenter);
    layout->addWidget(cyclesCaption); // placed just above the row below

    cyclesMinusBtn = new QPushButton("-", this);
    cyclesMinusBtn->setObjectName("cyclesBtn");
    cyclesMinusBtn->setFixedSize(48, 48);

    cyclesValueLabel = new QLabel("4", this);
    cyclesValueLabel->setObjectName("cyclesValueLabel");
    cyclesValueLabel->setAlignment(Qt::AlignCenter);
    cyclesValueLabel->setFixedWidth(50);

    cyclesPlusBtn = new QPushButton("+", this);
    cyclesPlusBtn->setObjectName("cyclesBtn");
    cyclesPlusBtn->setFixedSize(48, 48);

    cyclesRow->addStretch();
    cyclesRow->addWidget(cyclesMinusBtn);
    cyclesRow->addWidget(cyclesValueLabel);
    cyclesRow->addWidget(cyclesPlusBtn);
    cyclesRow->addStretch();

    QHBoxLayout *btnRow = new QHBoxLayout();
    btnRow->setSpacing(10);
    startBtn = new QPushButton("Start", this);
    pauseBtn = new QPushButton("Pause", this);
<<<<<<< HEAD
    resetBtn = new QPushButton("Reset", this);

    // Slightly taller than default so the whole row is easy to hit
    for (QPushButton *b : {startBtn, pauseBtn, resetBtn}) {
=======
    stopBtn = new QPushButton("Stop", this);
    resetBtn = new QPushButton("Reset", this);

    // Slightly taller than default so the whole row is easy to hit
    for (QPushButton *b : {startBtn, pauseBtn, stopBtn, resetBtn}) {
>>>>>>> 5242169cbfb87be66719702b5bf9ff9102a8d01f
        b->setMinimumHeight(44);
    }

    btnRow->addWidget(startBtn);
    btnRow->addWidget(pauseBtn);
<<<<<<< HEAD
=======
    btnRow->addWidget(stopBtn);
>>>>>>> 5242169cbfb87be66719702b5bf9ff9102a8d01f
    btnRow->addWidget(resetBtn);

    layout->addWidget(stateLabel);
    layout->addWidget(timerLabel);
    layout->addWidget(progressBar);
    layout->addWidget(sessionLabel);
    layout->addLayout(cyclesRow);
    layout->addStretch();
    layout->addLayout(btnRow);
}

void MainWindow::applyStyles()
{
    setStyleSheet(R"(
        QMainWindow, QWidget {
            background-color: #1e1e1e;
        }
        QLabel#timerLabel {
            font-size: 60px;
            font-weight: 700;
            color: #ff6b6b;
        }
        QLabel#stateLabel {
            font-size: 18px;
            font-weight: 600;
            color: #cfcfcf;
            letter-spacing: 2px;
        }
        QLabel#sessionLabel {
            font-size: 13px;
            color: #8a8a8a;
        }
        QLabel#cyclesValueLabel {
            font-size: 22px;
            font-weight: 700;
            color: white;
        }
        QPushButton {
            background-color: #2d2d30;
            color: white;
            border: none;
            border-radius: 8px;
            padding: 10px 18px;
            font-size: 14px;
        }
        QPushButton:hover:!disabled {
            background-color: #3e3e42;
        }
        QPushButton:disabled {
            color: #666666;
        }
        QPushButton#cyclesBtn {
            font-size: 22px;
            font-weight: 700;
            border-radius: 24px;
            padding: 0px;
        }
        QProgressBar {
            background-color: #2d2d30;
            border-radius: 6px;
            height: 10px;
        }
        QProgressBar::chunk {
            background-color: #ff6b6b;
            border-radius: 6px;
        }
    )");
}

void MainWindow::updateCyclesLabel()
{
    cyclesValueLabel->setText(QString::number(cyclesValue));
    cyclesMinusBtn->setEnabled(!isRunning && cyclesValue > CYCLES_MIN);
    cyclesPlusBtn->setEnabled(!isRunning && cyclesValue < CYCLES_MAX);
}

void MainWindow::onCyclesDecrease()
{
    if (cyclesValue > CYCLES_MIN) {
        cyclesValue--;
        updateCyclesLabel();
    }
}

void MainWindow::onCyclesIncrease()
{
    if (cyclesValue < CYCLES_MAX) {
        cyclesValue++;
        updateCyclesLabel();
    }
}

void MainWindow::onStart()
{
    worker->setSessionsBeforeLongBreak(cyclesValue);
<<<<<<< HEAD
    isFirstPhaseAfterStart = true;
=======
>>>>>>> 5242169cbfb87be66719702b5bf9ff9102a8d01f

    isRunning = true;
    isPaused = false;
    startBtn->setEnabled(false);
    pauseBtn->setEnabled(true);
    pauseBtn->setText("Pause");
<<<<<<< HEAD
=======
    stopBtn->setEnabled(true);
>>>>>>> 5242169cbfb87be66719702b5bf9ff9102a8d01f
    updateCyclesLabel(); // disables +/- while running

    QMetaObject::invokeMethod(worker, "countdown", Qt::QueuedConnection);
}

void MainWindow::onPause()
{
    if (!isRunning) return;

    if (!isPaused) {
        worker->requestPause();
        isPaused = true;
        pauseBtn->setText("Resume");
        stateLabel->setText(stateLabel->text() + " (paused)");
    } else {
        worker->requestResume();
        isPaused = false;
        pauseBtn->setText("Pause");
    }
}

<<<<<<< HEAD
=======
void MainWindow::onStop()
{
    // Halts the current cycle but keeps the session count and cycle
    // setting as they were - use Reset if you want a clean slate.
    worker->requestStop();
}

>>>>>>> 5242169cbfb87be66719702b5bf9ff9102a8d01f
void MainWindow::onReset()
{
    worker->requestStop();
    resetUiToDefault();
}

void MainWindow::resetUiToDefault()
{
    stateLabel->setText("Ready");
    timerLabel->setText("25:00");
    progressBar->setValue(0);
    sessionLabel->setText("Sessions completed: 0");
    cyclesValue = 4;
    isRunning = false;
    isPaused = false;
    startBtn->setEnabled(true);
    pauseBtn->setEnabled(false);
    pauseBtn->setText("Pause");
<<<<<<< HEAD
=======
    stopBtn->setEnabled(false);
>>>>>>> 5242169cbfb87be66719702b5bf9ff9102a8d01f
    updateCyclesLabel();
}
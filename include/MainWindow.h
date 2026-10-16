
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "VdiSession.h"

class QListWidget;
class QListWidgetItem;
class QLabel;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(
        const QVector<VdiSession>& sessions,
        QWidget *parent = nullptr
    );

private slots:
    void updateSessionDetails(
        QListWidgetItem *current,
        QListWidgetItem *previous
    );

private:
    QVector<VdiSession> m_sessions;

    QListWidget *m_sessionList;
    QLabel *m_nameLabel;
    QLabel *m_hostLabel;
    QLabel *m_portLabel;
    QLabel *m_protocolLabel;
    QLabel *m_resolutionLabel;
    QPushButton *m_connectButton;

    void setupUi();
    void applyDarkTheme();
};

#endif // MAINWINDOW_H


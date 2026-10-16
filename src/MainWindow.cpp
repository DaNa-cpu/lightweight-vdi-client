
#include "MainWindow.h"

#include <QListWidget>
#include <QListWidgetItem>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(
    const QVector<VdiSession>& sessions,
    QWidget *parent
)
    : QMainWindow(parent),
      m_sessions(sessions),
      m_sessionList(nullptr),
      m_nameLabel(nullptr),
      m_hostLabel(nullptr),
      m_portLabel(nullptr),
      m_protocolLabel(nullptr),
      m_resolutionLabel(nullptr),
      m_connectButton(nullptr)
{
    setupUi();
    applyDarkTheme();

    for (const VdiSession& session : m_sessions) {
        m_sessionList->addItem(session.getName());
    }

    if (!m_sessions.isEmpty()) {
        m_sessionList->setCurrentRow(0);
    }
}

void MainWindow::setupUi()
{
    setWindowTitle("Lightweight VDI Client");
    resize(1000, 620);

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QHBoxLayout *mainLayout = new QHBoxLayout(central);
    mainLayout->setContentsMargins(24, 24, 24, 24);
    mainLayout->setSpacing(20);

    // Panoul din stanga
    QFrame *leftPanel = new QFrame(central);
    leftPanel->setObjectName("leftPanel");
    leftPanel->setFixedWidth(280);

    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);
    leftLayout->setContentsMargins(18, 20, 18, 20);
    leftLayout->setSpacing(14);

    QLabel *appTitle = new QLabel("VDI CLIENT", leftPanel);
    appTitle->setObjectName("appTitle");

    QLabel *sessionsTitle =
        new QLabel("Available sessions", leftPanel);
    sessionsTitle->setObjectName("sectionTitle");

    m_sessionList = new QListWidget(leftPanel);
    m_sessionList->setObjectName("sessionList");
    m_sessionList->setSpacing(6);

    leftLayout->addWidget(appTitle);
    leftLayout->addSpacing(18);
    leftLayout->addWidget(sessionsTitle);
    leftLayout->addWidget(m_sessionList, 1);

    // Panoul din dreapta
    QFrame *rightPanel = new QFrame(central);
    rightPanel->setObjectName("rightPanel");

    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);
    rightLayout->setContentsMargins(30, 28, 30, 28);
    rightLayout->setSpacing(18);

    QLabel *detailsHeading =
        new QLabel("Session details", rightPanel);
    detailsHeading->setObjectName("sectionTitle");

    m_nameLabel = new QLabel("No session selected", rightPanel);
    m_nameLabel->setObjectName("sessionName");
    m_nameLabel->setWordWrap(true);

    QFrame *detailsCard = new QFrame(rightPanel);
    detailsCard->setObjectName("detailsCard");

    QVBoxLayout *detailsLayout = new QVBoxLayout(detailsCard);
    detailsLayout->setContentsMargins(20, 20, 20, 20);
    detailsLayout->setSpacing(8);

    QLabel *hostCaption = new QLabel("HOST", detailsCard);
    m_hostLabel = new QLabel("-", detailsCard);

    QLabel *portCaption = new QLabel("PORT", detailsCard);
    m_portLabel = new QLabel("-", detailsCard);

    QLabel *protocolCaption = new QLabel("PROTOCOL", detailsCard);
    m_protocolLabel = new QLabel("-", detailsCard);

    QLabel *resolutionCaption = new QLabel("RESOLUTION", detailsCard);
    m_resolutionLabel = new QLabel("-", detailsCard);

    const QList<QLabel*> captions = {
        hostCaption, portCaption, protocolCaption, resolutionCaption
    };

    for (QLabel *caption : captions) {
        caption->setStyleSheet(
            "color: #9CA3AF; font-size: 11px; font-weight: bold;"
        );
    }

    detailsLayout->addWidget(hostCaption);
    detailsLayout->addWidget(m_hostLabel);
    detailsLayout->addSpacing(8);

    detailsLayout->addWidget(portCaption);
    detailsLayout->addWidget(m_portLabel);
    detailsLayout->addSpacing(8);

    detailsLayout->addWidget(protocolCaption);
    detailsLayout->addWidget(m_protocolLabel);
    detailsLayout->addSpacing(8);

    detailsLayout->addWidget(resolutionCaption);
    detailsLayout->addWidget(m_resolutionLabel);

    m_connectButton = new QPushButton("Connect", rightPanel);
    m_connectButton->setObjectName("connectButton");
    m_connectButton->setMinimumHeight(52);
    m_connectButton->setEnabled(false);

    QLabel *footer = new QLabel(
        "Select a session to view its configuration.",
        rightPanel
    );
    footer->setObjectName("mutedText");
    footer->setWordWrap(true);

    rightLayout->addWidget(detailsHeading);
    rightLayout->addWidget(m_nameLabel);
    rightLayout->addWidget(detailsCard);
    rightLayout->addStretch();
    rightLayout->addWidget(m_connectButton);
    rightLayout->addWidget(footer);

    mainLayout->addWidget(leftPanel);
    mainLayout->addWidget(rightPanel, 1);

    // Signals & Slots
    connect(
        m_sessionList,
        &QListWidget::currentItemChanged,
        this,
        &MainWindow::updateSessionDetails
    );
}

void MainWindow::updateSessionDetails(
    QListWidgetItem *current,
    QListWidgetItem *previous
)
{
    Q_UNUSED(previous);

    if (current == nullptr) {
        m_nameLabel->setText("No session selected");
        m_hostLabel->setText("-");
        m_portLabel->setText("-");
        m_protocolLabel->setText("-");
        m_resolutionLabel->setText("-");
        m_connectButton->setEnabled(false);
        return;
    }

    const int index = m_sessionList->row(current);

    if (index < 0 || index >= m_sessions.size()) {
        return;
    }

    const VdiSession& session = m_sessions.at(index);

    m_nameLabel->setText(session.getName());
    m_hostLabel->setText(session.getHost());
    m_portLabel->setText(QString::number(session.getPort()));
    m_protocolLabel->setText(session.getProtocol());
    m_resolutionLabel->setText(session.getResolution());

    m_connectButton->setEnabled(true);
}

void MainWindow::applyDarkTheme()
{
    setStyleSheet(R"(
        QMainWindow, QWidget {
            background-color: #111827;
            color: #E5E7EB;
            font-family: "Segoe UI", sans-serif;
            font-size: 14px;
        }

        QFrame#leftPanel, QFrame#rightPanel {
            background-color: #1F2937;
            border: 1px solid #374151;
            border-radius: 14px;
        }

        QLabel#appTitle {
            color: #60A5FA;
            font-size: 20px;
            font-weight: bold;
        }

        QLabel#sectionTitle {
            color: #F9FAFB;
            font-size: 17px;
            font-weight: bold;
        }

        QLabel#sessionName {
            color: #F9FAFB;
            font-size: 25px;
            font-weight: bold;
            padding: 4px 0 12px 0;
        }

        QFrame#detailsCard {
            background-color: #111827;
            border: 1px solid #374151;
            border-radius: 10px;
        }

        QListWidget#sessionList {
            background-color: #111827;
            border: 1px solid #374151;
            border-radius: 8px;
            padding: 6px;
            outline: none;
        }

        QListWidget#sessionList::item {
            padding: 12px 10px;
            border-radius: 6px;
        }

        QListWidget#sessionList::item:selected {
            background-color: #2563EB;
            color: white;
        }

        QListWidget#sessionList::item:hover:!selected {
            background-color: #374151;
        }

        QPushButton#connectButton {
            background-color: #2563EB;
            color: white;
            border: none;
            border-radius: 8px;
            font-size: 16px;
            font-weight: bold;
        }

        QPushButton#connectButton:hover:enabled {
            background-color: #1D4ED8;
        }

        QPushButton#connectButton:disabled {
            background-color: #374151;
            color: #9CA3AF;
        }

        QLabel#mutedText {
            color: #9CA3AF;
            font-size: 12px;
        }
    )");
}

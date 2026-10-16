#ifndef VDISESSION_H
#define VDISESSION_H

#include <QString>

class VdiSession
{
private:
    int m_id;
    QString m_name;
    QString m_protocol;
    QString m_host;
    int m_port;
    QString m_resolution;

public:
    VdiSession(int id,
               const QString& name,
               const QString& protocol,
               const QString& host,
               int port,
               const QString& resolution);

    int getId() const;
    QString getName() const;
    QString getProtocol() const;
    QString getHost() const;
    int getPort() const;
    QString getResolution() const;
};

#endif // VDISESSION_H

#include "VdiSession.h"

VdiSession::VdiSession(int id,
                       const QString& name,
                       const QString& protocol,
                       const QString& host,
                       int port,
                       const QString& resolution)
    : m_id(id),
      m_name(name),
      m_protocol(protocol),
      m_host(host),
      m_port(port),
      m_resolution(resolution)
{
}

int VdiSession::getId() const
{
    return m_id;
}

QString VdiSession::getName() const
{
    return m_name;
}

QString VdiSession::getProtocol() const
{
    return m_protocol;
}

QString VdiSession::getHost() const
{
    return m_host;
}

int VdiSession::getPort() const
{
    return m_port;
}

QString VdiSession::getResolution() const
{
    return m_resolution;
}


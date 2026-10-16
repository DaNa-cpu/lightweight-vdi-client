#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include <QString>
#include <QVector>
#include "VdiSession.h"

class ConfigLoader{
public:
	static QVector<VdiSession> loadSessions(const QString& filePath);
};

#endif

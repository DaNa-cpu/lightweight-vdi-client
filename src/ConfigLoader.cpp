#include "ConfigLoader.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <QDebug>

QVector<VdiSession> ConfigLoader::loadSessions(const QString& filePath)
{
	QVector<VdiSession> sessions;
	
	// 1. Open JSON File
	QFile file(filePath);

	if(!file.open(QIODevice::ReadOnly)){
		qWarning() << "Cannot open file"
			<< filePath
			<< file.errorString();
		return sessions;
	}
	
	// 2. Read file content
	QByteArray jsonData = file.readAll();
	file.close();

	// 3. Parse JSON text
	QJsonParseError parseError;
	QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);

	if(parseError.error!=QJsonParseError::NoError){
		qWarning() << "JSON Error"<< parseError.errorString();
		return sessions;
	}

	// 4. Check if doc contain an object
	if(!doc.isObject()){
		qWarning() << "JSON Doc doesn't contain an object";
		return sessions;
	}

	QJsonObject root = doc.object();

	// 5. Extract "sessions" array
	QJsonValue sessionsValue = root.value("sessions");

	if(!sessionsValue.isArray()){
		qWarning() << "'sessions' key is missing or is not an array";
		return sessions;
	}

	QJsonArray sessionArray = sessionsValue.toArray();

	// 6. Iterate through each session
	
	for(const QJsonValue& value: sessionArray){
		if(!value.isObject()){
			qWarning() << "Sessions element is not an object";
			continue;
		}

		QJsonObject obj = value.toObject();

		// 7. Extract fields
		int id = obj.value("id").toInt();
		QString name = obj.value("name").toString();
                QString protocol = obj.value("protocol").toString();
		QString host = obj.value("host").toString();
		int port = obj.value("port").toInt();
		QString resolution = obj.value("resolution").toString();

		// 8. Build the object and add it to vector
		VdiSession session(id, name, protocol, host, port, resolution);
		sessions.append(session);

	}

	return sessions;

}

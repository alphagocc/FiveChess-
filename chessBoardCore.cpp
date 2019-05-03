#include "chessboardcore.h"
#include <QDebug>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <cctype>
#define FOR(i,j,k) for (int i=(j);i<(k);i++)
// 共享的全局变量定义
ChessBoardCore chessBoard;

ChessBoardCore::ChessBoardCore()
{
	init();
}

ChessBoardCore::~ChessBoardCore()
{

}

void ChessBoardCore::dataPrint()
{
	FOR(i, 0, 15) {
		FOR(j, 0, 15)
		{
			qDebug("%d", static_cast<int>(m_data[i][j]));
		}
		qDebug() << endl;
	}
}

void ChessBoardCore::clearData()
{
	FOR(i, 0, 15)
		FOR(j, 0, 15)
	{
		m_data[i][j] = DataType::none;
	}
}

bool ChessBoardCore::searchWin(ChessBoardCore::DataType chess)
{
	FOR(i, 0, 11)FOR(j, 0, 15)
		if (m_data[i][j] == chess && m_data[i + 1][j] == chess && m_data[i + 2][j] == chess && m_data[i + 3][j] == chess && m_data[i + 4][j] == chess)
			return true;

	FOR(i, 0, 15)FOR(j, 0, 11)
		if (m_data[i][j] == chess && m_data[i][j + 1] == chess && m_data[i][j + 2] == chess && m_data[i][j + 3] == chess && m_data[i][j + 4] == chess)
			return true;

	FOR(i, 0, 11)FOR(j, 0, 11)
		if (m_data[i][j] == chess && m_data[i + 1][j + 1] == chess && m_data[i + 2][j + 2] == chess && m_data[i + 3][j + 3] == chess && m_data[i + 4][j + 4] == chess)
			return true;

	FOR(i, 0, 11)FOR(j, 4, 15)
		if (m_data[i][j] == chess && m_data[i + 1][j - 1] == chess && m_data[i + 2][j - 2] == chess && m_data[i + 3][j - 3] == chess && m_data[i + 4][j - 4] == chess)
			return true;

	return false;
}

bool ChessBoardCore::saveBoard()
{
	QString fileName = QFileDialog::getSaveFileName(nullptr,
		tr("Save Chess Board File"),
		QString("."),
		tr("ChessBoardFile(*.chessbrd)"));
	if (!fileName.isNull())
	{
		QFile file(fileName);
		if (!file.open(QFile::Text | QFile::WriteOnly))
		{
			qDebug() << file.errorString() << endl; return false;
		}
		QJsonObject jsonObj;
        jsonObj.insert("usedTime", m_usedTime);
        jsonObj.insert("flag", m_flag);
		QString tempString;
		FOR(i, 0, 15)
		{
			FOR(j, 0, 15)
			{
                tempString.append(static_cast<int>(m_data[i][j])+48);
			}
		}
        jsonObj.insert("chessBoard", tempString);
		QJsonDocument jsonDoc;
		jsonDoc.setObject(jsonObj);
        qDebug() << jsonDoc.toJson();
        file.write(jsonDoc.toJson());
		file.close();
	}
	qDebug() << fileName << endl;
	return true;
}

bool ChessBoardCore::loadBoard()
{
	QString filename = QFileDialog::getOpenFileName(nullptr,
		tr("Open Chess Board File"),
		QString("."),
		tr("ChessBoardFile(*.chessbrd)"));
	if (!filename.isNull())
	{
		QFile file(filename);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			qDebug() << file.errorString() << endl;
			return false;
        }
        QByteArray ba=file.readAll();
        //qDebug() << ba;
        QJsonDocument jsonDoc;
        jsonDoc=QJsonDocument::fromJson(ba);
        QJsonObject jsonObj = jsonDoc.object();
        qDebug() << jsonDoc.toJson() ;
        m_usedTime = jsonObj["usedTime"].toInt();
		m_flag = jsonDoc["flag"].toInt();
		qDebug() << m_usedTime;
		qDebug() << m_flag;
        QString tempStr = jsonObj["chessBoard"].toString();
		FOR(i, 0, 15) {
			FOR(j, 0, 15)
			{
                int tempData = tempStr[i*15+j].toLatin1();
                qDebug() << tempData;
				if (!std::isdigit(tempData))
				{
					file.close();
					init();
					return false;
				}
				m_data[i][j] = static_cast<DataType>(tempData - 48);
			}
		}
        //dataPrint();
		file.close();
		return true;
	}
	else
	{
		return false;
	}
}

void ChessBoardCore::init()
{
	clearData();
	m_opt = ChessBoardCore::PaintOptType::onlyChessBoard;
	m_flag = 0;
	m_usedTime = 0;
}

#ifndef POSITION_H
#define POSITION_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QMap>
#include <QDebug>

/*
 Storage Notes: Store PWMRepeat and SequenceReplay as 0-->15, use lookup for actual value.
*/
class Position : public QObject
{
    Q_OBJECT
public:
    enum SpecialFunction {PWMRepeat = 13, PWMSweep = 14, SeqDelay = 15};
    explicit Position(QObject *parent = 0);

    //The byte array is NULL terminated, can't just get a pointer to it
    QByteArray toServoSerialData();
    QString toString();//Human readable string
    bool fromString(QString input);
    int getBoardNumber();
    bool setBoardNumber(int boardNumber);
signals:

public slots:

private:
    void init();
    void addTerminatingComma(QString& string);
    QString createStartOfString();
    bool parseStartOfString(QStringList& input);
    bool parseServoPositions(QStringList& input);
    void bitSet(quint8& byte, int position);
    void bitClear(quint8& byte, int position);

    QMap<quint8,int> m_PWMRepeatMap;
    QMap<quint8,quint8> m_data;
    int m_boardNumber;
    bool m_hasData;
    bool m_isFreeze;
    bool m_hasDelay;
    bool m_hasPWM;

};

#endif // POSITION_H
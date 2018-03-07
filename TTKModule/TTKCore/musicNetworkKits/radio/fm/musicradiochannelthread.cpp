#include "musicradiochannelthread.h"
#///QJson import
#include "qjson/parser.h"

#include <QNetworkRequest>
#include <QNetworkCookieJar>
#include <QNetworkAccessManager>

MusicRadioChannelThread::MusicRadioChannelThread(QObject *parent, QNetworkCookieJar *cookie)
    : MusicRadioThreadAbstract(parent, cookie)
{

}

MusicRadioChannelThread::~MusicRadioChannelThread()
{
    deleteAll();
}

QString MusicRadioChannelThread::getClassName()
{
    return staticMetaObject.className();
}

void MusicRadioChannelThread::startToDownload(const QString &id)
{
    Q_UNUSED(id);
    m_manager = new QNetworkAccessManager(this);

    QNetworkRequest request;
    request.setUrl(QUrl(MusicUtils::Algorithm::mdII(RADIO_CHANNEL_URL, false)));
#ifndef QT_NO_SSL
    connect(m_manager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
                       SLOT(sslErrors(QNetworkReply*,QList<QSslError>)));
    M_LOGGER_INFO(QString("%1 Support ssl: %2").arg(getClassName()).arg(QSslSocket::supportsSsl()));
    setSslConfiguration(&request);
#endif
    if(m_cookJar)
    {
        m_manager->setCookieJar(m_cookJar);
        m_cookJar->setParent(nullptr);
    }
    m_reply = m_manager->get(request);
    connect(m_reply, SIGNAL(finished()), SLOT(downLoadFinished()));
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(replyError(QNetworkReply::NetworkError)));

}

void MusicRadioChannelThread::downLoadFinished()
{
    if(!m_reply)
    {
        deleteAll();
        return;
    }

    if(m_reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = m_reply->readAll();
        m_channels.clear();

        QJson::Parser parser;
        bool ok;
        QVariant data = parser.parse(bytes, &ok);
        if(ok)
        {
            QVariantMap value = data.toMap();
            QVariantList channels = value["channel_list"].toList();
            foreach(const QVariant &var, channels)
            {
                value = var.toMap();
                MusicRadioChannelInfo channel;
                channel.m_id = value["channel_id"].toString();
                channel.m_name = value["channel_name"].toString();
                m_channels << channel;
            }
        }
    }

    emit downLoadDataChanged("query finished!");
    deleteAll();
}

#ifndef QReklamViewer_H
#define QReklamViewer_H

#include <QtWebKit/QWebView>
#include <QLocale>
#include <QtDesigner/QDesignerExportWidget>

//Adak Teknoloji programlarinda reklam lari gosterir. Uygun sekilde ekran resize olduktan sonra
//ui->reklamWidget->SHOW_REKLAM(); fonksiyonu cagirilmalidirki reklam gosterilsin.

#ifdef WIN32
class QReklamViewer : public QWebView
#else
class QDESIGNER_WIDGET_EXPORT QReklamViewer : public QWebView
#endif
{
    Q_OBJECT

public:
                    QReklamViewer                            (QWidget *parent = 0);
                    ~QReklamViewer                           ();

    void            SHOW_REKLAM                              (QString gosterilen_ekran);

    //Kernel tarafindan kullanilan method disarindan cagrilmasi gereksiz.
    void            EXEC                                     ();

private slots:
    void            URL_CLICKED                              (QUrl);

private:
    QString         m_reklam_ekrani;
    QString         m_reklam_html_str;

    int             m_width;
    int             m_height;

    void            SHOW_ADAK_REKLAMLAR                     ();
};

#endif // QReklamViewer_H




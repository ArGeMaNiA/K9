#include <QtGui/QApplication>
#include <QStringList>
#include "yonetim.h"
#include "adak_sql_struct.h"
#include "adak_utils.h"
#include "adak_sql.h"
#include "k9_console_utils.h"
#include "k9_yetki.h"
#include "k9_ana_menu_open.h"
#include "k9_console_utils.h"
#include "k9_yetki.h"
#include "k9_db.h"

extern ADAK_SQL * G_YONETIM_DB;
extern ADAK_SQL * DB;

/**************************************************************************************
                   main
***************************************************************************************/

int main ( int argc, char * argv[] )
{
    QApplication a(argc, argv);
    QIcon icon;
    icon.addPixmap(QPixmap(QString::fromUtf8(":/k9_icons/K9_ICONS/k9_logo.png")), QIcon::Normal, QIcon::Off);
    a.setWindowIcon(icon);

    INIT_PROGRAM( &k9_db, &K9_KULLANICIYI_TAM_YETKILENDIR );

    if ( PROGRAMA_GIRIS ( argc, argv, K9_PROGRAMI, K9_PROGRAMI, NULL ) EQ ADAK_OK ) {
        K9_CHECK_AND_PREPARE();
        OPEN_K9_ANA_MENU( NULL);
        a.exec();
    }
    if (DB NE NULL) {
        DB->~ADAK_SQL();
    }

    if (G_YONETIM_DB NE NULL) {
        G_YONETIM_DB->~ADAK_SQL();
    }

    return 0;
}

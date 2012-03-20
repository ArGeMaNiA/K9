#include <QComboBox>
#include <QtGui>
#include <QAdakDate.h>
#include "adak_sql.h"
#include "adak_utils.h"
#include "k9_gui_utils.h"
#include "k9_enum.h"
#include "k9_console_utils.h"
#include "sube_console_utils.h"

extern ADAK_SQL * DB;

static int                      g_kdv_orani_sayisi                      = 0;
static int                      g_otv_orani_sayisi                      = 0;
static double                   G_KDV_ORANLARI_ARRAY [KDV_OTV_ORANLARI_SAYISI];
static double                   G_OTV_ORANLARI_ARRAY [KDV_OTV_ORANLARI_SAYISI];



//*******************************************************************************
//             K9_FILL_COMBOBOX_AYLAR
//*******************************************************************************

void K9_FILL_COMBOBOX_AYLAR ( QComboBox * p_combo_box )
{
    QStringList month_list;
    month_list  << "OCAK"   << "ŞUBAT"      << "MART"
                << "NİSAN"  << "MAYIS"      << "HAZİRAN"
                << "TEMMUZ" << "AĞUSTOS"    << "EYLÜL"
                << "EKİM"   << "KASIM"      << "ARALIK";

    p_combo_box->addItems( month_list );

}

/********************************************************************************************************
                                       K9_FILL_KDV_ORANLARI_COMBOBOX
*********************************************************************************************************/

void K9_FILL_KDV_ORANLARI_COMBOBOX ( QComboBox * p_comboBox )
{
    if ( K9_GET_KDV_ORANLARI_OKUNDUMU_FLAG() EQ false ) {
        SQL_QUERY sql_query ( DB );
        sql_query.PREPARE_SELECT("k9_sabit_degerler","kdv_orani_sayisi,kdv_oranlari_array ");
        if ( sql_query.SELECT() EQ 0 ) {
            return;
        }
        sql_query.NEXT();
        g_kdv_orani_sayisi = sql_query.VALUE(0).toInt();
        UNPACK_DOUBLE_ARRAY(sql_query.VALUE(1).toString() , G_KDV_ORANLARI_ARRAY , KDV_OTV_ORANLARI_SAYISI);

        K9_SET_KDV_ORANLARI_OKUNDUMU_FLAG(true);
    }

    for ( int i = 0; i < g_kdv_orani_sayisi; i++ ) {
        p_comboBox->addItem ( QVariant ( G_KDV_ORANLARI_ARRAY[i] ).toString() );
    }
    p_comboBox->setEditable(false);
}

/********************************************************************************************************
                                       K9_FILL_OTV_ORANLARI_COMBOBOX
*********************************************************************************************************/

void K9_FILL_OTV_ORANLARI_COMBOBOX ( QComboBox * p_comboBox )
{
    if ( K9_GET_OTV_ORANLARI_OKUNDUMU_FLAG() EQ false ) {
        SQL_QUERY sql_query ( DB );
        sql_query.PREPARE_SELECT("k9_sabit_degerler","otv_orani_sayisi,otv_oranlari_array");
        if ( sql_query.SELECT() EQ 0 ) {
            return;
        }
        sql_query.NEXT();
        g_otv_orani_sayisi = sql_query.VALUE(0).toInt();
        UNPACK_DOUBLE_ARRAY(sql_query.VALUE(1).toString() , G_OTV_ORANLARI_ARRAY , KDV_OTV_ORANLARI_SAYISI);

        K9_SET_OTV_ORANLARI_OKUNDUMU_FLAG(true);
    }

    for ( int i = 0; i < g_otv_orani_sayisi; i++ ) {
        p_comboBox->addItem ( QVariant ( G_OTV_ORANLARI_ARRAY[i] ).toString() );
    }
    p_comboBox->setEditable(false);
}

/**************************************************************************************
                   K9_FILL_COMBOBOX_FIS_FILTRESI()
***************************************************************************************/

void K9_FILL_COMBOBOX_FIS_FILTRESI(QComboBox *combobox_entegre_filtresi)
{

    combobox_entegre_filtresi->addItems(QStringList() << QObject::tr("Hepsi")
                                        << QObject::tr("1.Şirkete Ait Olanlar") << QObject::tr("2.Şirkete Ait Olanlar"));
}

/********************************************************************************************************
                                    K9_FILL_COMBOBOX_ADAK_MODULES
*********************************************************************************************************/

void K9_FILL_COMBOBOX_ADAK_MODULES ( QComboBox * p_comboBox )
{
    p_comboBox->addItems ( QStringList () << QObject::tr ("Muhasebe") << QObject::tr ("İşletme")
                                          << QObject::tr ("Döviz")    << QObject::tr ("Adres")
                                          << QObject::tr ("Cari")     << QObject::tr ("ÇekSenet")
                                          << QObject::tr ("Banka")    << QObject::tr ("Şube / Ünite / Depo")
                                          << QObject::tr ("Fatura")   << QObject::tr ("İrsaliye")
                                          << QObject::tr ("Stok")     << QObject::tr ("Demirbaş")
                                          << QObject::tr ("Personel") << QObject::tr ("Faiz")
                                          << QObject::tr ("K9 Yönetim"));

}

/**************************************************************************************
                   K9_SET_WINDOW_ICON
***************************************************************************************/

void K9_SET_WINDOW_ICON ( QWidget * p_window )
{
    p_window->setWindowIcon( QIcon( ":/k9_icons/K9_ICONS/k9_logo.png" ) );
}

/**************************************************************************************
                   K9_SUBEYE_UNITE_KAYDI_YAPILDI_MI()
***************************************************************************************/

bool K9_SUBEYE_UNITE_KAYDI_YAPILDI_MI ()
{
    if ( SUBE_GET_UNITE_ID() EQ -1 ) {
        ADAK_INFO( QObject::tr("Bu bilgisayarın kayıtlı olduğu bir ünite bulunamadı."
                           "\nLütfen Şubeler / Depolar menüsünden bir şubeye üniteyi kaydediniz."), NULL,NULL);
        return false;
    }
    return true;
}

/**************************************************************************************
                   K9_FILL_COMBOBOX_KAYDEDILECEK_SIRKET
***************************************************************************************/

void K9_FILL_COMBOBOX_KAYDEDILECEK_SIRKET(QComboBox *combobox_kaydedilecek_sirket)
{
    combobox_kaydedilecek_sirket->clear();

    combobox_kaydedilecek_sirket->addItems(QStringList() << QObject::tr("Her İki Şirkete")<<
                                   QObject::tr("Sadece 2.şirkete"));
}

/**************************************************************************************
                   K9_FILL_COMBOBOX_RAPOR_SIRKET_FILTRESI
***************************************************************************************/

void K9_FILL_COMBOBOX_RAPOR_SIRKET_FILTRESI (QComboBox *combobox_sirket_turu)
{
    combobox_sirket_turu->clear();

    combobox_sirket_turu->addItems(QStringList()<< QObject::tr("Her İki Şirket")
                                   << QObject::tr("Birinci Şirket")<<
                                   QObject::tr("İkinci Şirket"));
}

/**************************************************************************************
                   K9_MALI_YIL_TARIH_ARALIGI_KONTROLU
***************************************************************************************/

int K9_MALI_YIL_TARIH_ARALIGI_KONTROLU(QAdakDate *p_baslangic_tarihi, QAdakDate *p_bitis_tarihi)
{
    if ( p_baslangic_tarihi->QDATE() > p_bitis_tarihi->QDATE() ) {
        ADAK_WARNING( QObject::tr("Başlangıç tarihi,bitiş tarihinden büyük olamaz."), p_baslangic_tarihi, NULL );
        return ADAK_FAIL;
    }
    if ( p_bitis_tarihi->QDATE() < p_baslangic_tarihi->QDATE() ) {
        ADAK_WARNING( QObject::tr("Bitiş tarihi,başlangıç tarihinden büyük olamaz."), p_bitis_tarihi, NULL );
        return ADAK_FAIL;
    }
    return ADAK_OK;
}

/**************************************************************************************
                   K9_FILL_KULLANICININ_CALISTIGI_SIRKETLER
***************************************************************************************/

void K9_FILL_KULLANICININ_CALISTIGI_SIRKETLER(QComboBox *p_combo_box)
{
    QStringList kullanici_calistigi_sirket;
    kullanici_calistigi_sirket << "Şirket 1" << "Şirket 2";
    p_combo_box->addItems( kullanici_calistigi_sirket );
    p_combo_box->setCurrentIndex( 0 );
}

/**************************************************************************************
                   K9_GET_KULLANICININ_CALISTIGI_SIRKET_ENUM
***************************************************************************************/

int K9_GET_KULLANICININ_CALISTIGI_SIRKET_ENUM(QString p_sirket)
{
    if( p_sirket EQ "Şirket 1") {
        return SIRKET_1;
    }
    else if( p_sirket EQ "Şirket 2" ) {
        return SIRKET_2;
    }

    return -1;
}

/**************************************************************************************
                   K9_GET_KULLANICININ_CALISTIGI_SIRKET_STRING
***************************************************************************************/

QString K9_GET_KULLANICININ_CALISTIGI_SIRKET_STRING(int p_sirket)
{
    if ( p_sirket EQ SIRKET_1 ) {
        return "Şirket 1";
    }
    else if ( p_sirket EQ SIRKET_2 ) {
        return "Şirket 2";
    }

    return "NULL";
}

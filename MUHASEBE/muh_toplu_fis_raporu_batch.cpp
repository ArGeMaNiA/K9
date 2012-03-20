#include <QDate>
#include "muh_toplu_fis_raporu_batch_class.h"
#include "muh_toplu_fis_raporu_batch_open.h"
#include "ui_muh_toplu_fis_raporu_batch.h"
#include "print.h"
#include "muh_enum.h"
#include "muh_struct.h"
#include "k9_enum.h"
#include "k9_log.h"
#include "adak_std_utils.h"
#include "k9_console_utils.h"
#include "k9_gui_utils.h"
#include "muh_toplu_fis_raporu_open.h"

extern ADAK_SQL * DB;

/**************************************************************************************
                   OPEN_TOPLU_FIS_RAPORU_BATCH
***************************************************************************************/

void OPEN_MUH_TOPLU_FIS_RAPORU_BATCH ( QWidget * parent )
{
    MUH_TOPLU_FIS_RAPORU_BATCH * B = new MUH_TOPLU_FIS_RAPORU_BATCH ( parent );
    B->EXEC( NOT_FULL_SCREEN );
}

/**************************************************************************************
                   MUH_TOPLU_FIS_RAPORU_BATCH::MUH_TOPLU_FIS_RAPORU_BATCH
***************************************************************************************/

MUH_TOPLU_FIS_RAPORU_BATCH::MUH_TOPLU_FIS_RAPORU_BATCH ( QWidget *parent ) : BATCH_KERNEL ( parent ) ,
m_ui ( new Ui::MUH_TOPLU_FIS_RAPORU_BATCH )
{
    m_ui->setupUi      ( this );
    START_BATCH_KERNEL ( this, DB );
}

/**************************************************************************************
                   MUH_TOPLU_FIS_RAPORU_BATCH::SETUP_FORM
***************************************************************************************/

void MUH_TOPLU_FIS_RAPORU_BATCH::SETUP_FORM()
{
    SET_HELP_PAGE           (  "genel-muhasebe_toplu-fis-dokumu" );
    SET_PAGE_TITLE          ( tr ( "MUH - TOPLU FİŞ DÖKÜMÜ" ) );

    REGISTER_BUTTON_WIDGET ( m_ui->widget_batch_buttons );

    SET_SETTING_NAME        ( "MUH_TOPLU_FIS_RAPORU_BATCH" );

    m_ui->adakDate_bas_tarihi->SET_DATE( MALI_YIL_FIRST_DATE() );
    m_ui->adakDate_bitis_tarihi->SET_DATE( MALI_ARRAY_LAST_DATE() );

    SET_NAME_OF_RUN_BATCH_BUTTON ( "Rapor Al" );
    SET_FIRST_FOCUS_WIDGET       ( m_ui->adakDate_bas_tarihi );

    if( K9_KULLANICININ_CALISTIGI_SIRKET() EQ 1 ){
        m_ent_filtre_turu = FIS_BIRINCI_SIRKET;
    }
    else {
        m_ent_filtre_turu = FIS_HER_IKI_SIRKET;
    }

    K9_FILL_COMBOBOX_RAPOR_SIRKET_FILTRESI( m_ui->comboBox_sirket_turu );

    m_ui->comboBox_sirket_turu->setHidden(true );
    m_ui->label_sirket_turu->setHidden(true);

    if( K9_KULLANICI_SIRKET_DEGISTIRE_BILIR_MI() EQ EVET ){

        m_ui->comboBox_sirket_turu->setHidden(false);
        m_ui->label_sirket_turu->setHidden(false);
    }
    FIND_AND_SET_COMBOBOX_TEXT( m_ui->comboBox_sirket_turu, K9_GET_RAPOR_SIRKET_FILTRESI_STRING(m_ent_filtre_turu ) );
}

/**************************************************************************************
                   MUH_TOPLU_FIS_RAPORU_BATCH::CHECK_VAR
***************************************************************************************/

int MUH_TOPLU_FIS_RAPORU_BATCH::CHECK_VAR ( QObject * object )
{
    if ( object EQ m_ui->comboBox_sirket_turu ){

        m_ent_filtre_turu = K9_GET_RAPOR_SIRKET_FILTRESI_ENUM(m_ui->comboBox_sirket_turu->currentText());

    }

    return ADAK_OK;
}

/**************************************************************************************
                   MUH_TOPLU_FIS_RAPORU_BATCH::CHECK_RUN
***************************************************************************************/

int MUH_TOPLU_FIS_RAPORU_BATCH::CHECK_RUN()
{
    if ( K9_MALI_YIL_TARIH_ARALIGI_KONTROLU( m_ui->adakDate_bas_tarihi, m_ui->adakDate_bitis_tarihi ) NE ADAK_OK ) {
        return ADAK_FAIL;
    }
    return ADAK_OK;
}

/**************************************************************************************
                   MUH_TOPLU_FIS_RAPORU_BATCH::RUN_BATCH
***************************************************************************************/

void MUH_TOPLU_FIS_RAPORU_BATCH::RUN_BATCH()
{
    MUH_RAPOR_VARS * MUH_RV   = new MUH_RAPOR_VARS;

    MUH_RV->baslangic_tarihi   =  m_ui->adakDate_bas_tarihi->QDATE();
    MUH_RV->bitis_tarihi       =  m_ui->adakDate_bitis_tarihi->QDATE();
    MUH_RV->entegre_filtresi   =  m_ent_filtre_turu;


    QString log_detaylari = QObject::tr ( "Toplu Fiş Raporu , \n" ) +
                            QObject::tr ( "Tarih Aralığı    : " ) +
                            m_ui->adakDate_bas_tarihi->QDATE().toString("dd MMMM yyyy") + " - " +
                            m_ui->adakDate_bitis_tarihi->QDATE().toString("dd MMMM yyyy") ;

    DB->START_TRANSACTION();
    K9_LOG_KAYDI_EKLE ( MUHASEBE_MODULU , LOG_MUH_RAPORLAR , LOG_ISLEM_RAPOR_ALINDI, log_detaylari );
    DB->COMMIT_TRANSACTION();

    OPEN_REPORT_SHOWER ( GET_TOPLU_FIS_RAPORU (-1,MUH_RV), nativeParentWidget() );

    delete MUH_RV;
}


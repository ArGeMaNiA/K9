#include "k9_kul_kitapcigi_ve_yardim_sayfasi_batch_open.h"
#include "k9_kul_kitapcigi_ve_yardim_sayfasi_batch_class.h"
#include "ui_k9_kul_kitapcigi_ve_yardim_sayfasi_batch.h"
#include "print.h"

extern ADAK_SQL *           DB;

/**************************************************************************************
                   OPEN_K9_KUL_KITAPCIGI_VE_YARDIM_SAYFASI_BATCH
***************************************************************************************/

void OPEN_K9_KUL_KITAPCIGI_VE_YARDIM_SAYFASI_BATCH ( int p_kitapcik_mi, QWidget * parent )
{
    K9_KUL_KITAPCIGI_VE_YARDIM_SAYFASI_BATCH * F = new K9_KUL_KITAPCIGI_VE_YARDIM_SAYFASI_BATCH ( p_kitapcik_mi, parent );
    F->EXEC( FULL_SCREEN );
}

/**************************************************************************************
                   K9_KUL_KITAPCIGI_VE_YARDIM_SAYFASI_BATCH::K9_KUL_KITAPCIGI_VE_YARDIM_SAYFASI_BATCH
***************************************************************************************/

K9_KUL_KITAPCIGI_VE_YARDIM_SAYFASI_BATCH::K9_KUL_KITAPCIGI_VE_YARDIM_SAYFASI_BATCH ( int p_kitapcik_mi, QWidget * parent ) :  BATCH_KERNEL ( parent ), m_ui ( new Ui::K9_KUL_KITAPCIGI_VE_YARDIM_SAYFASI_BATCH )
{
    m_kitapcik_mi = p_kitapcik_mi;
    m_ui->setupUi      ( this );    
    START_BATCH_KERNEL ( this, DB );
}

/**************************************************************************************
                   K9_KUL_KITAPCIGI_VE_YARDIM_SAYFASI_BATCH::SETUP_FORM
***************************************************************************************/

void K9_KUL_KITAPCIGI_VE_YARDIM_SAYFASI_BATCH::SETUP_FORM ()
{

    SET_FIRST_FOCUS_WIDGET ( m_ui->webView );
    SET_SETTING_NAME  ("K9_KUL_KITAPCIGI_VE_YARDIM_SAYFASI_BATCH");

    if( m_kitapcik_mi EQ 1 ) {
        SET_PAGE_TITLE(tr("KULLANIM KITAPÇIĞI"));
        m_ui->webView->load( QUrl("http://www.k9ticaripaket.com/kullanim-kitapcigi") );
    }
    else {
        SET_PAGE_TITLE(tr("YARDIM (SIK SORULAN SORULAR)"));
         m_ui->webView->load( QUrl("http://www.k9ticaripaket.com/sik-sorulan-sorular") );
    }

}

/**************************************************************************************
                   K9_KUL_KITAPCIGI_VE_YARDIM_SAYFASI_BATCH::CHECK_VAR
***************************************************************************************/

int K9_KUL_KITAPCIGI_VE_YARDIM_SAYFASI_BATCH::CHECK_VAR ( QObject * object )
{
    Q_UNUSED( object );
    return ADAK_OK;
}

/**************************************************************************************
                   K9_KUL_KITAPCIGI_VE_YARDIM_SAYFASI_BATCH::CHECK_RUN
***************************************************************************************/

int K9_KUL_KITAPCIGI_VE_YARDIM_SAYFASI_BATCH::CHECK_RUN ()
{
    return ADAK_OK;
}

/**************************************************************************************
                   K9_KUL_KITAPCIGI_VE_YARDIM_SAYFASI_BATCH::RUN_BATCH
***************************************************************************************/

void K9_KUL_KITAPCIGI_VE_YARDIM_SAYFASI_BATCH::RUN_BATCH ()
{
}

/**************************************************************************************
                   K9_KUL_KITAPCIGI_VE_YARDIM_SAYFASI_BATCH::CHECK_EXIT
***************************************************************************************/

int K9_KUL_KITAPCIGI_VE_YARDIM_SAYFASI_BATCH::CHECK_EXIT ()
{
    return ADAK_OK;
}

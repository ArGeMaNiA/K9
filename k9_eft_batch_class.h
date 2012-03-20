#ifndef K9_EFT_BATCH_H
#define K9_EFT_BATCH_H

#include "batch_kernel.h"

struct K9_ISLEM_DETAYLARI;

namespace Ui {
    class K9_EFT_BATCH;
}

class K9_EFT_BATCH : public BATCH_KERNEL
{
    Q_OBJECT



public:
                           K9_EFT_BATCH     ( int p_fis_turu , int p_islem_turu , int p_fis_satiri_id ,
                                              int p_makbuz_para_birimi_id ,
                                              K9_ISLEM_DETAYLARI * P_ISLEM_DETAYLARI ,
                                              int p_modul_id, QWidget * parent = 0 );
                           ~K9_EFT_BATCH                           () {}

    bool   *               m_kayit_degistirildi_mi;

private:
    Ui::K9_EFT_BATCH *        m_ui;


    int                    m_hesap_no_id;
    int                    m_fis_satiri_id;
    int                    m_fis_turu;
    int                    m_islem_turu;
    int                    m_modul_id;
    int                    m_makbuz_para_birimi_id;

    K9_ISLEM_DETAYLARI *   M_ISLEM_DETAYLARI;


    void                   SETUP_FORM                           ();

    int                    CHECK_VAR                            ( QObject * object );
    int                    CHECK_RUN                            ();
    void                   RUN_BATCH                            ();

};

#endif // K9_EFT_BATCH_H

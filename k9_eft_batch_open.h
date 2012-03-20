#ifndef K9_EFT_BATCH_OPEN_H
#define K9_EFT_BATCH_OPEN_H

class QWidget;
struct K9_ISLEM_DETAYLARI;

bool        OPEN_K9_EFT_BATCH                           ( int p_fis_turu      , int p_islem_turu , int p_fis_satiri_id ,int p_makbuz_para_birimi_id,
                                                          K9_ISLEM_DETAYLARI * P_ISLEM_DETAYLARI,int p_modul_id , QWidget * parent );


#endif // K9_EFT_BATCH_OPEN_H

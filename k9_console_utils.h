#ifndef K9_UTILS_H
#define K9_UTILS_H

#include <QDate>
#include <QStringList>

class ADAK_SQL;

struct K9_SABIT_DEGERLER_STRUCT {
    int     acik_kapali_fatura;
};

struct K9_ENT_DETAYLARI_STRUCT;
struct K9_KULLANICI_YETKILERI_STRUCT;
struct SYSTEM_MENU_ITEMS;

void        K9_ADD_DEFAULT_BELGELER                        ();

QString     K9_GET_DELIMETER                               ();
void        K9_DELIMETER_UPDATE                            ( const QString p_old_delimeter,
                                                           const QString p_new_delimeter, QWidget * p_parent );
void        K9_CREATE_SABIT_DEGERLER                       ();
void        K9_SET_SABIT_DEGERLER_STRUCT                   ();

void        K9_SET_DEFAULT_VALUES                          ();

int         K9_GET_ACIK_KAPALI_FATURA_SABIT_DEGER           ();
void        K9_SET_ACIK_KAPALI_FATURA_SABIT_DEGER          ( int p_acik_kapali_fatura );

int         K9_GET_ADAK_MODULES_ENUM                      ( QString     p_adak_module_name );
QString     K9_GET_ADAK_MODULES_STRING                    ( int         p_adak_module_enum );

void        K9_KULLANICI_YETKILERI_STRUCT_DOLDUR           ( int kullanici_id       );
void        K9_CLEAR_KULLANICI_YETKILERI_STRUCT            ( K9_KULLANICI_YETKILERI_STRUCT * P_K9_KULLANICI_YETKILERI);

void        K9_SET_KDV_ORANLARI_OKUNDUMU_FLAG              ( bool p_flag_value );
void        K9_SET_OTV_ORANLARI_OKUNDUMU_FLAG              ( bool p_flag_value );

bool        K9_GET_KDV_ORANLARI_OKUNDUMU_FLAG              ();
bool        K9_GET_OTV_ORANLARI_OKUNDUMU_FLAG              ();

int         K9_GET_FIS_NO                                  ( int p_modul_id , int fis_id );

int         K9_KULLANICI_SIRKET_DEGISTIRE_BILIR_MI         ();

int         K9_KULLANICININ_CALISTIGI_SIRKET               ();

int         K9_KULLANICI_ENT_BILGILERINI_DEGISTIREBILIR_MI ();

int         K9_KULLANICI_FISIN_URETTIGI_ENT_FISLERINI_GOREBILIR_MI();

int         K9_KULLANICI_URUN_HAREKETLERINI_GOREBILIR_MI    ();

int         K9_KULLANICI_CARI_HAREKETLERINI_GOREBILIR_MI    ();

void        K9_CLEAR_ENT_DETAYLARI_STRUCT                  ( K9_ENT_DETAYLARI_STRUCT * P_ENT_DETAYLARI );

int         K9_GET_FIS_FILTRESI_ENUM                       ( QString entegre_filtresi);

QString     K9_GET_FIS_FILTRESI_STRING                     ( int entegre_filtresi);


void        K9_UPDATE_TANIMLANMAMIS_ENT_HESAPLARI          ( ADAK_SQL * P_GELEN_DB = NULL);
void        K9_CHECK_AND_PREPARE                           ();

int         K9_GET_TAH_ODM_SEKLI_ENUM                      ( QString tah_odm_sekli );
QString     K9_GET_TAH_ODM_SEKLI_STRING                    ( int     tah_odm_sekli , int fis_turu = -1);

void        K9_DISABLE_MUHASEBE_ALAMLARI                   ();
void        K9_ENABLE_MUHASEBE_ALAMLARI                    ();
void        K9_RESTORE_MUHASEBE_ALAMLARI_VALUE             ();
bool        K9_MUHASEBE_ALARMLARI_KAPALIMI                 ();

void        K9_SUBE_ENT_HESAPLARINI_GUNCELLE               ( int p_sube_id ,ADAK_SQL * P_GELEN_DB = NULL);

void        K9_COPY_TABLES                                 ( ADAK_SQL * P_SOURCE_DB, ADAK_SQL * P_TARGET_DB,
                                                             QString p_table_name, QString p_where_condition  = NULL, QStringList p_where_set_values = QStringList() );
int         K9_GET_AYLAR_ENUM                              ( QString ay );
QString     K9_GET_AYLAR_STRING                            ( int ay );

void *      K9_GET_KULLANICI_YETKILERI                     ();

int         K9_GET_KAYDEDILECEK_SIRKET_ENUM                ( QString kaydedilecek_sirket);

QString     K9_GET_KAYDEDILECEK_SIRKET_STRING              ( int kaydedilecek_sirket );

int         K9_GET_RAPOR_SIRKET_FILTRESI_ENUM              ( QString rapor_sirket_turu);

QString     K9_GET_RAPOR_SIRKET_FILTRESI_STRING            ( int rapor_sirket_turu     );

QString     K9_GET_SM_SICIL_NUMARASI                       ();

void        K9_GET_SISTEM_KULLANICI_YETKILERI              ( int p_kullanici_id, SYSTEM_MENU_ITEMS &SISTEM_STRUCT );

void        K9_SET_FIRMA_ISMI                              ( QString p_firma_ismi );

QString     K9_GET_FIRMA_ISMI                              ();

void        LOAD_K9_KOMPLE_PAKET                           ();


#endif // K9_UTILS_H

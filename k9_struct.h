#ifndef K9_STRUCT_H
#define K9_STRUCT_H

#include<QDate>
#include<QVariant>
#include <QStringList>
class QString;

struct K9_ENT_DETAYLARI_STRUCT {

    int         muh_fis_no;
    QStringList banka_fis_no;
    int         cari_fis_no;
    int         cek_fis_no;
    int         senet_fis_no;
    int         firma_cek_fis_no;
    int         firma_senet_fis_no;
    int         muh_kasa_hesap_id;

};

struct K9_ISLEM_DETAYLARI{
    QDate       vade_tarihi;
    QDate       keside_tarihi;
    QString     banka_ismi;
    QString     sube_kodu;
    QString     sube_adi;
    QString     kesideci;
    QString     portfoy_no;
    QString     valor;
    QString     cek_senet_no;
    QString     hesap_no;
    int         bnk_hesap_no_id;
    int         pos_id;
    QString     kredi_karti_numarasi;
    QString     kredi_karti_sahibi;
    int         kredi_karti_id;
};


#endif // K9_STRUCT_H

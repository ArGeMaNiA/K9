#include "k9_version_upgrade.h"
#include "adak_sql.h"
#include "adak_utils.h"
#include <stdlib.h>
#include "prs_enum.h"
#include "prs_con_utils.h"
#include "k9_enum.h"
#include "sube_console_utils.h"
#include "k9_console_utils.h"
#include "muh_console_utils.h"
#include "cari_enum.h"
#include "stok_enum.h"
#include "fat_console_utils.h"
#include "fat_fis_utils.h"
#include "irs_console_utils.h"
#include "irs_enum.h"
#include "stok_fis_utils.h"
#include "fat_enum.h"
#include "stok_console_utils.h"
#include "k9_onar_utils.h"
#include "dvz_console_utils.h"
#include "cek_console_utils.h"
#include "cek_enum.h"
#include "belge_kernel_defines.h"
#include "k9_belge.h"
#include "dvz_console_utils.h"
#include "cari_console_utils.h"
#include "isl_enum.h"

extern ADAK_SQL * DB;
extern ADAK_SQL * G_YONETIM_DB;

/**************************************************************************************
                         K9_V2_33_TO_V2_34_UPGRADE
***************************************************************************************/

void K9_V2_33_TO_V2_34_UPGRADE()
{
    SQL_QUERY   query( DB );
    SQL_QUERY s_query( DB );

    query.PREPARE_SELECT("smm_makbuzlar" , "smm_numarasi, makbuz_id ");

    if ( query.SELECT() NE  0 ) {

        while ( query.NEXT() ) {

            QString smm_numarasi = query.VALUE( 0 ).toString();
            int     makbuz_id    = query.VALUE( 1 ).toInt();

            s_query.PREPARE_UPDATE("smm_makbuzlar" ,"makbuz_id" ,
                                   "sm_sicil_numarasi" , "makbuz_id = :makbuz_id");
            s_query.SET_VALUE(":sm_sicil_numarasi"  , smm_numarasi);
            s_query.SET_VALUE(":makbuz_id"          , makbuz_id);
            s_query.UPDATE();
        }
    }

    QStringList table_names_list;

    table_names_list << "bnk_defter_fisler" << "bnk_hareket_fisler"
                     << "bnk_makro_fisler"  << "bnk_virman_fisler"
                     << "car_fisler"        << "fat_faturalar"
                     << "muh_fisler"        << "prk_fisler"
                     << "stk_fisler";

    for ( int i = 0 ; i < table_names_list.size() ; i++ ) {

        QString table_name = table_names_list.at(i);

        query.PREPARE_SELECT(table_name , "entegre_mi,fis_id","");

        if ( query.SELECT() NE 0 ) {

            while ( query.NEXT() ) {

                int entegre_mi = query.VALUE(0).toInt();
                int fis_id     = query.VALUE(1).toInt();

                s_query.PREPARE_UPDATE ( table_name ,"fis_id" ,"kaydedilecek_sirket",
                                       "fis_id = :fis_id");
                s_query.SET_VALUE(":kaydedilecek_sirket" , entegre_mi);
                s_query.SET_VALUE(":fis_id"              , fis_id);
                s_query.UPDATE();

            }
        }
    }

    table_names_list.clear();
    table_names_list << "bnk_defter_fis_satirlari" << "bnk_hareket_fis_satirlari"
                     << "bnk_makro_fis_satirlari"  << "bnk_virman_fis_satirlari"
                     << "car_fis_satirlari"        << "fat_fatura_satirlari"
                     << "muh_fis_satirlari"        << "prk_fis_satirlari"
                     << "stk_fis_satirlari";

    for ( int i = 0 ; i < table_names_list.size() ; i++ ) {

        QString table_name = table_names_list.at(i);

        query.PREPARE_SELECT(table_name , "entegre_mi,fis_satiri_id" ,"");

        if ( query.SELECT() NE 0 ) {

            while ( query.NEXT() ) {

                int entegre_mi    = query.VALUE(0).toInt();
                int fis_satiri_id = query.VALUE(1).toInt();

                s_query.PREPARE_UPDATE(table_name , "fis_satiri_id" , "kaydedilecek_sirket",
                                       "fis_satiri_id = :fis_satiri_id");
                s_query.SET_VALUE(":kaydedilecek_sirket" , entegre_mi);
                s_query.SET_VALUE(":fis_satiri_id"       , fis_satiri_id);
                s_query.UPDATE();
            }
        }
    }

    query.PREPARE_SELECT ( "cek_cekler_senetler" , "entegre_mi,cek_senet_id","");

    if ( query.SELECT() NE 0 ) {

        while ( query.NEXT() ) {

            int entegre_mi    = query.VALUE(0).toInt();
            int cek_senet_id  = query.VALUE(1).toInt();

            s_query.PREPARE_UPDATE ( "cek_cekler_senetler" ,"cek_senet_id" ,
                                    "kaydedilecek_sirket" , "cek_senet_id = :cek_senet_id");
            s_query.SET_VALUE(":kaydedilecek_sirket" , entegre_mi);
            s_query.SET_VALUE(":cek_senet_id"        , cek_senet_id);
            s_query.UPDATE();

        }
    }

    query.PREPARE_SELECT ( "cek_bordrolar" , "entegre_mi,bordro_id","");

    if ( query.SELECT() NE 0 ) {

        while ( query.NEXT() ) {

            int entegre_mi    = query.VALUE(0).toInt();
            int bordro_id     = query.VALUE(1).toInt();

            s_query.PREPARE_UPDATE ( "cek_bordrolar" ,"bordro_id" ,
                                    "kaydedilecek_sirket" , "bordro_id = :bordro_id");
            s_query.SET_VALUE(":kaydedilecek_sirket" , entegre_mi);
            s_query.SET_VALUE(":bordro_id"           , bordro_id);
            s_query.UPDATE();

        }
    }

    query.PREPARE_SELECT ( "cek_bordro_satirlari" , "entegre_mi,bordro_satiri_id","");

    if ( query.SELECT() NE 0 ) {

        while ( query.NEXT() ) {

            int entegre_mi           = query.VALUE(0).toInt();
            int bordro_satiri_id     = query.VALUE(1).toInt();

            s_query.PREPARE_UPDATE ( "cek_bordro_satirlari" ,"bordro_satiri_id" ,
                                    "kaydedilecek_sirket" , "bordro_satiri_id = :bordro_satiri_id");
            s_query.SET_VALUE(":kaydedilecek_sirket" , entegre_mi);
            s_query.SET_VALUE(":bordro_satiri_id"    , bordro_satiri_id);
            s_query.UPDATE();

        }
    }

}

/**************************************************************************************
                         K9_V2_40_TO_V2_41_UPGRADE
***************************************************************************************/

void K9_V2_40_TO_V2_41_UPGRADE()
{
    SQL_QUERY f_query( DB );
    SQL_QUERY s_query( DB );
    SQL_QUERY t_query( DB );

    // once adr_kayit_id ---> adres_id ; adres_id bos olanlar ataniyor.

    f_query.PREPARE_SELECT( "car_hesaplar", "adres_id, adr_kayit_id, cari_hesap_id, cari_kart_turu ", "");
    if ( f_query.SELECT() NE 0 ) {

        while ( f_query.NEXT() EQ true ) {
            int adres_id            = f_query.VALUE(0).toInt();
            int adr_kayit_id        = f_query.VALUE(1).toInt();
            int cari_hesap_id       = f_query.VALUE(2).toInt();
            int cari_kart_turu      = f_query.VALUE(3).toInt();

            if ( adres_id EQ 0 ) {
                t_query.PREPARE_UPDATE   ( "car_hesaplar", "cari_hesap_id", "adres_id", "cari_hesap_id =:cari_hesap_id");
                t_query.SET_VALUE        ( ":adres_id"       , adr_kayit_id  );
                t_query.SET_VALUE        ( ":cari_hesap_id"  , cari_hesap_id );
                t_query.UPDATE();

                adres_id = adr_kayit_id;
            }

            // adres_kart_turu guncelleniyor
            s_query.PREPARE_SELECT  ("adr_adresler", "adres_kart_turu", " adres_id = :adres_id");
            s_query.SET_VALUE       (":adres_id"    , adres_id );
            if ( s_query.SELECT() NE 0 ) {
               s_query.NEXT();
               int  adres_kart_turu = s_query.VALUE(0).toInt();
               if ( adres_kart_turu EQ 0 ) {
                   t_query.PREPARE_UPDATE   ( "adr_adresler", "adres_id", "adres_kart_turu", "adres_id =:adres_id");
                   t_query.SET_VALUE        ( ":adres_kart_turu", cari_kart_turu );
                   t_query.SET_VALUE        ( ":adres_id"       , adres_id       );
                   t_query.UPDATE();
               }
            }
        }
    }

}

/**************************************************************************************
                         K9_V2_42_TO_V2_43_UPGRADE
***************************************************************************************/

void   K9_V2_42_TO_V2_43_UPGRADE()
{
    SQL_QUERY query( DB );

    query.PREPARE_UPDATE   ( "k9_sabit_degerler", "sabit_deger_id", "stok_birim_fiyat_hassasiyeti", "sabit_deger_id =:sabit_deger_id");
    query.SET_VALUE        ( ":stok_birim_fiyat_hassasiyeti" , 2  );
    query.SET_VALUE        ( ":sabit_deger_id"  , 1 );
    query.UPDATE();

}

/**************************************************************************************
                         K9_V2_43_TO_V2_44_UPGRADE
***************************************************************************************/

void   K9_V2_43_TO_V2_44_UPGRADE()
{
    SQL_QUERY query( DB );

    query.PREPARE_UPDATE   ( "k9_sabit_degerler", "sabit_deger_id", "stok_birim_miktar_hassasiyeti", "sabit_deger_id =:sabit_deger_id");
    query.SET_VALUE        ( ":stok_birim_miktar_hassasiyeti" , 2  );
    query.SET_VALUE        ( ":sabit_deger_id"  , 1 );
    query.UPDATE();

}

/**************************************************************************************
                         K9_V2_44_TO_V2_45_UPGRADE
***************************************************************************************/

void   K9_V2_44_TO_V2_45_UPGRADE()
{
    SQL_QUERY f_query( DB );
    SQL_QUERY s_query( DB );

    f_query.PREPARE_SELECT( "car_hesaplar, adr_adresler", "cari_hesap_id, firma_sahis_adi", " car_hesaplar.adres_id = adr_adresler.adres_id" );

    if ( f_query.SELECT() NE 0 ) {

        while( f_query.NEXT() EQ true ) {
            s_query.PREPARE_UPDATE( "car_hesaplar", "cari_hesap_id", "cari_hesap_ismi", "cari_hesap_id = :cari_hesap_id" );
            s_query.SET_VALUE     ( ":cari_hesap_ismi", f_query.VALUE( 1 ).toString() );
            s_query.SET_VALUE     ( ":cari_hesap_id", f_query.VALUE( 0 ).toInt() );
            s_query.UPDATE();
        }
    }

}

/**************************************************************************************
                         K9_V2_46_TO_V2_47
***************************************************************************************/

void K9_V2_46_TO_V2_47_UPGRADE()
{
    SQL_QUERY s_query( DB );

    s_query.PREPARE_UPDATE( "sub_uniteler", "unite_id", "irsaliyeli_fat_belge_seri, irsaliyeli_fat_belge_numarasi", "" );
    s_query.SET_VALUE     ( ":irsaliyeli_fat_belge_seri",     "A" );
    s_query.SET_VALUE     ( ":irsaliyeli_fat_belge_numarasi", "1" );
    s_query.UPDATE();

}

/**************************************************************************************
                         K9_V2_48_TO_V2_49_UPGRADE
***************************************************************************************/

void K9_V2_48_TO_V2_49_UPGRADE()
{
    SQL_QUERY f_query( DB );
    SQL_QUERY s_query( DB );

    f_query.PREPARE_SELECT( "stk_urunler", "urun_id, otv_orani, kdv_orani, hizmet_mi ");

    if ( f_query.SELECT() NE 0 ) {

        while( f_query.NEXT() EQ true ) {
            int    urun_id   = f_query.VALUE( 0 ).toInt();
            double otv_orani = f_query.VALUE( 1 ).toDouble();
            double kdv_orani = f_query.VALUE( 2 ).toDouble();
            int    hizmet_mi = f_query.VALUE( 3 ).toInt();

            if ( hizmet_mi EQ ENUM_HIZMET_KARTI ) {
                s_query.PREPARE_UPDATE( "stk_urunler", "urun_id", "alis_kdv_orani, satis_kdv_orani", " urun_id = :urun_id" );
                s_query.SET_VALUE     ( ":alis_kdv_orani",  kdv_orani );
                s_query.SET_VALUE     ( ":satis_kdv_orani", kdv_orani );
                s_query.SET_VALUE     ( ":urun_id", urun_id );
                s_query.UPDATE();
            }
            else {
                s_query.PREPARE_UPDATE( "stk_urunler", "urun_id", "alis_kdv_orani, alis_otv_orani, satis_kdv_orani, satis_otv_orani ", " urun_id = :urun_id" );
                s_query.SET_VALUE     ( ":alis_kdv_orani",  kdv_orani );
                s_query.SET_VALUE     ( ":alis_otv_orani",  otv_orani );
                s_query.SET_VALUE     ( ":satis_kdv_orani", kdv_orani );
                s_query.SET_VALUE     ( ":satis_otv_orani", otv_orani );
                s_query.SET_VALUE     ( ":urun_id", urun_id );
                s_query.UPDATE();
            }
        }
    }
}

/**************************************************************************************
                         K9_V2_50_TO_V2_51_UPGRADE
***************************************************************************************/

void K9_V2_50_TO_V2_51_UPGRADE()
{

    SQL_QUERY f_query( DB );

    FATURA_FISI_STRUCT       FAT_FIS;
    FATURA_FIS_SATIRI_STRUCT FAT_FIS_SATIRI;

    FAT_FIS.KDV_ORANLARI_ARRAY                     =   new double  [KDV_OTV_ORANLARI_SAYISI];
    FAT_FIS.KDV_HESAPLARI_ID_ARRAY                 =   new int     [KDV_OTV_ORANLARI_SAYISI];
    FAT_FIS.KDV_ORANINA_GORE_TUTARLAR_ARRAY        =   new double  [KDV_OTV_ORANLARI_SAYISI];

    FAT_FIS.OTV_ORANLARI_ARRAY                     =   new double  [KDV_OTV_ORANLARI_SAYISI];
    FAT_FIS.OTV_HESAPLARI_ID_ARRAY                 =   new int     [KDV_OTV_ORANLARI_SAYISI];
    FAT_FIS.OTV_ORANINA_GORE_TUTARLAR_ARRAY        =   new double  [KDV_OTV_ORANLARI_SAYISI];

    FAT_FIS.TEVKIFATLI_KDV_HESAPLARI_ID_ARRAY      =   new int     [KDV_OTV_ORANLARI_SAYISI];

    FATURA_CLEAR_FIS_STRUCT       ( &FAT_FIS );
    FATURA_CLEAR_FIS_SATIRI_STRUCT( &FAT_FIS_SATIRI);

    STK_IRS_FIS_STRUCT       IRS_FIS;
    STK_IRS_FIS_SATIR_STRUCT IRS_FIS_SATIRI;

    STK_IRS_CLEAR_FIS_STRUCT   ( &IRS_FIS );
    STK_IRS_CLEAR_SATIR_STRUCT ( &IRS_FIS_SATIRI );


    //! UPGRADE TASINMASI LAZIM
    // ELLE FATURA IRSALIYELESTIRMEDE FAT_IRS_BAGLANTISINA KAYIT EKLEMIYOR EKLEMELI

    f_query.PREPARE_SELECT( "fat_irs_satir_baglantisi", "fatura_satiri_id, irsaliye_satiri_id" );

    if ( f_query.SELECT() NE 0 ) {
        while ( f_query.NEXT() EQ true ) {
            int fatura_satiri_id    = f_query.VALUE( 0 ).toInt();
            int irsaliye_satiri_id  = f_query.VALUE( 1 ).toInt();

            int fatura_id   = FAT_GET_FATURA_ID( fatura_satiri_id );
            int irsaliye_id = STK_GET_IRS_ID   ( irsaliye_satiri_id );

            FATURA_CLEAR_FIS_STRUCT( &FAT_FIS );
            FATURA_FIS_BILGILERINI_OKU( &FAT_FIS, fatura_id );

            STK_IRS_CLEAR_FIS_STRUCT ( &IRS_FIS );
            STK_IRS_FIS_BILGILERINI_OKU( irsaliye_id, &IRS_FIS );

            // EGER ELLE IRSALIYE FATURALASTIRILMIS ISE
            if ( FAT_FIS.fatura_turu EQ ENUM_FAT_ELLE_IRSALIYE_FATURALASTIRMA_ALIS OR
                 FAT_FIS.fatura_turu EQ ENUM_FAT_ELLE_IRSALIYE_FATURALASTIRMA_SATIS ) {
                 // IRSALIYE BAGLANTISI EKLENIYOR
                 FAT_IRS_BAGLANTISI_EKLE( fatura_id, irsaliye_id );
            }
            // EGER ELLE FATURA IRSALIYELESTIRILMIS ISE
            else if ( IRS_FIS.fis_turu EQ ENUM_IRS_ELLE_FATURA_IRSALIYELESTIRME_ALIS OR
                      IRS_FIS.fis_turu EQ ENUM_IRS_ELLE_FATURA_IRSALIYELESTIRME_SATIS ) {
                 // IRSALIYE BAGLANTISI EKLENIYOR
                 FAT_IRS_BAGLANTISI_EKLE( fatura_id, irsaliye_id );
            }
        }
    }

    FATURA_VE_IRSALIYE_FISLERINI_ONAR();
}

/**************************************************************************************
                         K9_V2_52_TO_V2_53_UPGRADE
***************************************************************************************/

void K9_V2_52_TO_V2_53_UPGRADE()
{
    SQL_QUERY f_query( DB );
    SQL_QUERY s_query( DB );

    f_query.PREPARE_SELECT( "car_fisler", "iptal_mi, yazdirildi_mi, fis_id");
    if ( f_query.SELECT() NE 0 ) {
        while ( f_query.NEXT() EQ true ) {
            int iptal_mi        = f_query.VALUE( 0 ).toUInt();
            int yazdirildi_mi   = f_query.VALUE( 1 ).toUInt();
            int fis_id          = f_query.VALUE( 2 ).toUInt();

            bool guncelle_yapilsin_mi = false;
            if ( iptal_mi NE 1 ){
                iptal_mi = 0;
                guncelle_yapilsin_mi = true;
            }
            if ( yazdirildi_mi NE 1 ) {
                yazdirildi_mi = 0;
                guncelle_yapilsin_mi = true;
            }

            if ( guncelle_yapilsin_mi EQ true ) {
                s_query.PREPARE_UPDATE( "car_fisler", "fis_id", "iptal_mi, yazdirildi_mi ", "fis_id = :fis_id");
                s_query.SET_VALUE     ( ":iptal_mi"     , iptal_mi );
                s_query.SET_VALUE     ( ":yazdirildi_mi", yazdirildi_mi );
                s_query.SET_VALUE     ( ":fis_id"       , fis_id );
                s_query.UPDATE();
            }
        }
    }
}

/**************************************************************************************
                         K9_V2_56_TO_V2_57_UPGRADE
***************************************************************************************/

void K9_V2_56_TO_V2_57_UPGRADE()
{
    SQL_QUERY f_query( DB );
    SQL_QUERY s_query( DB );

    s_query.PREPARE_UPDATE( "prs_personel_kisisel_blgler", "kisisel_bilgi_id", "isten_cikis_tarihi", "");
    s_query.SET_VALUE     ( ":isten_cikis_tarihi", "9999.99.99" );
    s_query.UPDATE();

    f_query.PREPARE_SELECT( "prs_isten_ayrilanlar", "personel_id, isten_ayrilma_tarihi");

    if ( f_query.SELECT() NE 0 ) {
        while( f_query.NEXT() EQ true ) {
            int     personel_id          = f_query.VALUE( 0 ).toInt();
            QString isten_ayrilma_tarihi = f_query.VALUE( 1 ).toString();

            s_query.PREPARE_UPDATE( "prs_personel_kisisel_blgler", "kisisel_bilgi_id", "isten_cikis_tarihi", "personel_id = :personel_id");
            s_query.SET_VALUE     ( ":isten_cikis_tarihi", isten_ayrilma_tarihi );
            s_query.SET_VALUE     ( ":personel_id", personel_id );
            s_query.UPDATE();
        }
    }
}

/**************************************************************************************
                         K9_V2_60_TO_V2_61_UPGRADE
***************************************************************************************/

void K9_V2_60_TO_V2_61_UPGRADE()
{
    SQL_QUERY f_query( DB );
    SQL_QUERY s_query( DB );

    f_query.PREPARE_SELECT( "k9_kullanici_yetkileri", "k9_entegre_calisiyor_mu, yetki_id" );

    if ( f_query.SELECT() NE 0 ) {
        while( f_query.NEXT() EQ true  ) {
            int entegre_calisiyormu = f_query.VALUE( 0 ).toInt();
            int yetki_id            = f_query.VALUE( 1 ).toInt();

            s_query.PREPARE_UPDATE( "k9_kullanici_yetkileri", "yetki_id", "k9_kullanicinin_sirketi, k9_sirket_degistire_bilir_mi", " yetki_id = :yetki_id");
            s_query.SET_VALUE     ( ":k9_kullanicinin_sirketi", entegre_calisiyormu );
            s_query.SET_VALUE     ( ":k9_sirket_degistire_bilir_mi", 0 ); // degistiremez
            s_query.SET_VALUE     ( ":yetki_id", yetki_id );
            s_query.UPDATE();
        }
    }

}

/**************************************************************************************
                         K9_V2_62_TO_V2_63_UPGRADE
***************************************************************************************/

void K9_V2_62_TO_V2_63_UPGRADE()
{
    SQL_QUERY f_query( DB );
    SQL_QUERY s_query( DB );

    int temel_para_birim_id = DVZ_GET_TEMEL_PARA_BIRIMI_ID();

    f_query.PREPARE_SELECT( "fat_faturalar", "fis_id" );

    if ( f_query.SELECT() NE 0 ) {
        while( f_query.NEXT() EQ true  ) {
            int fat_fis_id = f_query.VALUE( 0 ).toInt();

            s_query.PREPARE_UPDATE( "fat_faturalar", "fis_id", "fatura_para_birimi_id, parite, doviz_kuru", " fis_id = :fis_id");
            s_query.SET_VALUE     ( ":fatura_para_birimi_id", temel_para_birim_id  );
            s_query.SET_VALUE     ( ":parite",             1.0000 );
            s_query.SET_VALUE     ( ":doviz_kuru",         1.0000 );
            s_query.SET_VALUE     ( ":fis_id",fat_fis_id );
            s_query.UPDATE();
        }
    }

    f_query.PREPARE_SELECT( "stk_fisler", "fis_id" );

    if ( f_query.SELECT() NE 0 ) {
        while( f_query.NEXT() EQ true  ) {
            int fat_fis_id = f_query.VALUE( 0 ).toInt();

            s_query.PREPARE_UPDATE( "stk_fisler", "fis_id", "stk_irs_para_birim_id, parite, doviz_kuru", " fis_id = :fis_id");
            s_query.SET_VALUE     ( ":stk_irs_para_birim_id", temel_para_birim_id  );
            s_query.SET_VALUE     ( ":parite",             1.0000 );
            s_query.SET_VALUE     ( ":doviz_kuru",         1.0000 );
            s_query.SET_VALUE     ( ":fis_id",fat_fis_id );
            s_query.UPDATE();
        }
    }
}

/**************************************************************************************
                         K9_V2_63_TO_V2_64_UPGRADE
***************************************************************************************/

void K9_V2_63_TO_V2_64_UPGRADE()
{
    SQL_QUERY f_query( DB );
    SQL_QUERY s_query( DB );
    SQL_QUERY t_query( DB );

    f_query.PREPARE_UPDATE("stk_urunun_seri_nolari", "seri_numarasi_id", "fatura_satiri_id", "");
    f_query.SET_VALUE     (":fatura_satiri_id", 0 );
    f_query.UPDATE();

    f_query.PREPARE_SELECT( "fat_irs_satir_baglantisi", "fatura_satiri_id, irsaliye_satiri_id" );
    if ( f_query.SELECT() NE 0 ) {
        while( f_query.NEXT() EQ true ) {
            int fatura_satiri_id    = f_query.VALUE( 0 ).toInt();
            int irsaliye_satiri_id  = f_query.VALUE( 1 ).toInt();

            QList< int > seri_numrasi_list;
            s_query.PREPARE_SELECT( "stk_satirdaki_seri_nolari", "seri_numarasi_id", "irsaliye_satiri_id = :irsaliye_satiri_id");
            s_query.SET_VALUE     ( ":irsaliye_satiri_id", irsaliye_satiri_id );

            if ( s_query.SELECT() NE 0 ) {
                while( s_query.NEXT() EQ  true ) {
                    seri_numrasi_list << s_query.VALUE( 0 ).toInt();
                }
            }

            s_query.PREPARE_SELECT( "fat_fatura_satirlari", "urun_id, satirdaki_urun_miktari", "fis_satiri_id = :fatura_satiri_id");
            s_query.SET_VALUE     ( ":fatura_satiri_id", fatura_satiri_id );

            if( s_query.SELECT() NE 0 ) {
                s_query.NEXT();
                int urun_id                = s_query.VALUE( 0 ).toInt();
                int satirdaki_urun_miktari = s_query.VALUE( 1 ).toInt();

                if( STK_GET_URUN_TAKIP_SEKLI( urun_id ) EQ ENUM_SERI_NO_ILE_TAKIP ) {
                    for (int i = 0; i < satirdaki_urun_miktari; ++i) {
                        if( i < seri_numrasi_list.size() ) {
                            t_query.PREPARE_UPDATE( "stk_urunun_seri_nolari", "seri_numarasi_id", "fatura_satiri_id", "seri_numarasi_id = :seri_numarasi_id");
                            t_query.SET_VALUE     ( ":fatura_satiri_id", fatura_satiri_id );
                            t_query.SET_VALUE     ( ":seri_numarasi_id", seri_numrasi_list.at( i ) );
                            t_query.UPDATE();
                        }
                    }
                }
            }
        }
    }
}

/**************************************************************************************
                         K9_V2_64_TO_V2_65_UPGRADE
***************************************************************************************/

void K9_V2_64_TO_V2_65_UPGRADE()
{
    SQL_QUERY f_query( DB );
    SQL_QUERY s_query( DB );

    f_query.PREPARE_UPDATE("sub_subeler", "sube_id", "alis_iskontolari_hesap_id", "");
    f_query.SET_VALUE     (":alis_iskontolari_hesap_id", MUH_GET_TALI_HESAP_ID( "649" ) );
    f_query.UPDATE();

    // yapilan_indirim_hesap_id ----> satis_iskontolari_hesap_id
    f_query.PREPARE_SELECT( "fat_faturalar", "fis_id, yapilan_indirim_hesap_id" );
    if ( f_query.SELECT() NE 0 ) {
        while( f_query.NEXT() EQ true ) {
            int fis_id = f_query.VALUE( 0 ).toInt();
            int yapilan_indirim_hesap_id = f_query.VALUE( 1 ).toInt();

            s_query.PREPARE_UPDATE( "fat_faturalar", "fis_id", "satis_iskontolari_hesap_id", "fis_id = :fis_id");
            s_query.SET_VALUE     ( ":satis_iskontolari_hesap_id", yapilan_indirim_hesap_id );
            s_query.SET_VALUE     ( ":fis_id", fis_id );
            s_query.UPDATE();
        }
    }


    // sube_yap_indirim_hsp_id ----> satis_iskontolari_hesap_id
    f_query.PREPARE_SELECT( "sub_subeler", "sube_id, sube_yap_indirim_hsp_id" );
    if ( f_query.SELECT() NE 0 ) {
        while( f_query.NEXT() EQ true ) {
            int sube_id = f_query.VALUE( 0 ).toInt();
            int sube_yap_indirim_hsp_id = f_query.VALUE( 1 ).toInt();

            s_query.PREPARE_UPDATE( "sub_subeler", "sube_id", "satis_iskontolari_hesap_id", "sube_id = :sube_id");
            s_query.SET_VALUE     ( ":satis_iskontolari_hesap_id", sube_yap_indirim_hsp_id );
            s_query.SET_VALUE     ( ":sube_id", sube_id );
            s_query.UPDATE();
        }
    }
}

/**************************************************************************************
                         K9_V2_65_TO_V2_66_UPGRADE
***************************************************************************************/

void K9_V2_65_TO_V2_66_UPGRADE()
{
    SQL_QUERY f_query( DB );
    SQL_QUERY s_query( DB );

    f_query.PREPARE_SELECT( "fat_iade_satir_baglantisi, fat_fatura_satirlari", "fis_id",
                            "fat_iade_satir_baglantisi.fat_satir_id = fat_fatura_satirlari.fis_satiri_id ");

    if ( f_query.SELECT() NE 0 ) {

        while( f_query.NEXT() EQ true ) {
            int fatura_id = f_query.VALUE( 0 ).toInt();

            s_query.PREPARE_SELECT("fat_faturalar", "iade_faturasi_mi, fatura_alis_satis_turu", "fis_id = :fis_id");
            s_query.SET_VALUE     (":fis_id", fatura_id );

            if ( s_query.SELECT() EQ 0 ) {
                continue;
            }

            s_query.NEXT();
            int iade_faturasi_mi        = s_query.VALUE( 0 ).toInt();
            int fatura_alis_satis_turu  = s_query.VALUE( 1 ).toInt();

            s_query.PREPARE_SELECT( "fat_irs_baglantisi", "irsaliye_id", "fatura_id = :fatura_id");
            s_query.SET_VALUE     ( ":fatura_id", fatura_id );

            if( s_query.SELECT() EQ 0 ) {
                continue;
            }

            s_query.NEXT();

            int irsaliye_id = s_query.VALUE( 0 ).toInt();

            s_query.PREPARE_SELECT( "stk_fisler", "fis_id", "fis_id = :fis_id" );
            s_query.SET_VALUE     ( ":fis_id", irsaliye_id );

            if( s_query.SELECT() EQ 0 ) {
                continue;
            }

            int irs_fis_turu;
            int irsaliye_alis_satis_turu;
            int iade_irsaliyesi_mi;

            if ( fatura_alis_satis_turu EQ ENUM_ALIS_IRSALIYESI_FATURASI ) {
                irsaliye_alis_satis_turu = ENUM_SATIS_IRSALIYESI_FATURASI;
                irs_fis_turu = ENUM_IRS_NORMAL_CIKIS;
            }
            else {
                irs_fis_turu = ENUM_IRS_NORMAL_GIRIS;
                irsaliye_alis_satis_turu = ENUM_ALIS_IRSALIYESI_FATURASI;
            }

            if ( iade_faturasi_mi EQ ENUM_FAT_IADE ) {
                iade_irsaliyesi_mi = ENUM_IRS_IADE;
            }
            else {
                iade_faturasi_mi = ENUM_IRS_NORMAL;
            }

            s_query.PREPARE_UPDATE( "stk_fisler", "fis_id", "fis_turu, irsaliye_alis_satis_turu, iade_irsaliyesi_mi", "fis_id = :fis_id" );
            s_query.SET_VALUE     ( ":fis_turu", irs_fis_turu );
            s_query.SET_VALUE     ( ":irsaliye_alis_satis_turu", irsaliye_alis_satis_turu );
            s_query.SET_VALUE     ( ":iade_irsaliyesi_mi", iade_irsaliyesi_mi );
            s_query.SET_VALUE     ( ":fis_id", irsaliye_id );
            s_query.UPDATE();

        }
    }
}

/**************************************************************************************
                         K9_V2_66_TO_V2_67_UPGRADE
***************************************************************************************/

void K9_V2_66_TO_V2_67_UPGRADE()
{
    SQL_QUERY f_query( DB );
    SQL_QUERY s_query( DB );


    f_query.PREPARE_SELECT( "stk_fisler, stk_fis_satirlari", "fis_satiri_id",
                            "stk_fisler.fis_id = stk_fis_satirlari.fis_id "
                            "AND ( stk_fisler.fis_turu = :fis_turu_1 OR stk_fisler.fis_turu = :fis_turu_2 ) ");

    f_query.SET_VALUE      ( ":fis_turu_1", ENUM_IRS_OTO_FATURA_IRSALIYELESTIRME_ALIS );
    f_query.SET_VALUE      ( ":fis_turu_2", ENUM_IRS_OTO_FATURA_IRSALIYELESTIRME_SATIS );

    if( f_query.SELECT() EQ 0 ) {
        return;
    }

    while( f_query.NEXT() EQ true ) {
        int fis_satiri_id = f_query.VALUE( 0 ).toInt();

        int fatura_satiri_id = FAT_GET_FAT_IRS_STR_BAGLANTISI_FATURA_SATIRI_ID( fis_satiri_id );

        s_query.PREPARE_SELECT( "fat_fatura_satirlari", "kaydedilecek_sirket", "fis_satiri_id = :fis_satiri_id");
        s_query.SET_VALUE     ( ":fis_satiri_id", fatura_satiri_id );

        if ( s_query.SELECT() EQ 0 ) {
            continue;
        }

        s_query.NEXT();

        int kaydedilecek_sirket = s_query.VALUE( 0 ).toInt();

        s_query.PREPARE_UPDATE( "stk_fis_satirlari", "fis_satiri_id", "kaydedilecek_sirket", "fis_satiri_id = :fis_satiri_id");
        s_query.SET_VALUE     ( ":kaydedilecek_sirket", kaydedilecek_sirket );
        s_query.SET_VALUE     ( ":fis_satiri_id", fis_satiri_id );
        s_query.UPDATE();

    }
}

/**************************************************************************************
                         K9_V2_67_TO_V2_68_UPGRADE
***************************************************************************************/

void K9_V2_67_TO_V2_68_UPGRADE()
{
    SQL_QUERY query( DB );

    query.PREPARE_UPDATE( "k9_kullanici_yetkileri", "yetki_id", "k9_urettigi_fisleri_grbilir_mi", "" );
    query.SET_VALUE     ( ":k9_urettigi_fisleri_grbilir_mi", EVET );
    query.UPDATE();
}

/**************************************************************************************
                         K9_V2_68_TO_V2_69_UPGRADE
***************************************************************************************/

void K9_V2_68_TO_V2_69_UPGRADE()
{
    SQL_QUERY f_query( DB );
    SQL_QUERY s_query( DB );

    f_query.PREPARE_SELECT( "car_fisler", "fis_id", "kaydedilecek_sirket = :kaydedilecek_sirket" );
    f_query.SET_VALUE     ( ":kaydedilecek_sirket", -1 );

    if( f_query.SELECT() NE 0 ) {
        while( f_query.NEXT() EQ true ) {
            int fis_id =  f_query.VALUE( 0 ).toInt();

            s_query.PREPARE_UPDATE( "car_fisler", "fis_id", "kaydedilecek_sirket", "fis_id = :fis_id");
            s_query.SET_VALUE     ( ":kaydedilecek_sirket", 1);
            s_query.SET_VALUE     ( ":fis_id", fis_id );
            s_query.UPDATE();
        }
    }

    f_query.PREPARE_SELECT( "car_fis_satirlari", "fis_satiri_id", "kaydedilecek_sirket = :kaydedilecek_sirket" );
    f_query.SET_VALUE     ( ":kaydedilecek_sirket", -1 );

    if( f_query.SELECT() NE 0 ) {
        while( f_query.NEXT() EQ true ) {
            int fis_satiri_id = f_query.VALUE( 0 ).toInt();

            s_query.PREPARE_UPDATE( "car_fis_satirlari", "fis_satiri_id", "kaydedilecek_sirket", "fis_satiri_id = :fis_satiri_id");
            s_query.SET_VALUE     ( ":kaydedilecek_sirket", 1);
            s_query.SET_VALUE     ( ":fis_satiri_id", fis_satiri_id );
            s_query.UPDATE();
        }
    }

    f_query.PREPARE_UPDATE( "k9_kullanici_yetkileri", "yetki_id", "stk_urun_hareketlerini_grb_mi, car_hesap_hareketleri_grb_mi", "" );
    f_query.SET_VALUE     ( ":stk_urun_hareketlerini_grb_mi", EVET );
    f_query.SET_VALUE     ( ":car_hesap_hareketleri_grb_mi", EVET );
    f_query.UPDATE();
}

/**************************************************************************************
                         K9_V2_70_TO_V2_71_UPGRADE
***************************************************************************************/

void K9_V2_70_TO_V2_71_UPGRADE()
{

    SQL_QUERY f_query( DB );
    SQL_QUERY s_query( DB );

    QMap< int, int > cek_hareletleri;

    f_query.PREPARE_SELECT( "cek_cekler_senetler", "cek_senet_id"  );
    if( f_query.SELECT() NE 0 ) {
        while( f_query.NEXT() EQ true ) {

            int cek_senet_id = f_query.VALUE( 0 ).toInt();
            cek_hareletleri.clear();
            s_query.PREPARE_SELECT( "cek_hareketleri", "cek_hareketi, cek_hareketi_id", "cek_senet_id = :cek_senet_id" );
            s_query.SET_VALUE     ( ":cek_senet_id", cek_senet_id );

            if( s_query.SELECT( "cek_hareketi_id ASC" ) NE 0 ) {
                while( s_query.NEXT() EQ true ) {
                    int cek_hareketi    = s_query.VALUE( 0 ).toInt();
                    int cek_hareketi_id = s_query.VALUE( 1 ).toInt();

                    cek_hareletleri.insert( cek_hareketi_id, cek_hareketi );

                }
            }

            for (int i = 1; i < cek_hareletleri.size(); ++i) {

                s_query.PREPARE_UPDATE( "cek_hareketleri", "cek_hareketi_id",
                                        "cek_onceki_hareketi, cek_son_hareketi",
                                        "cek_hareketi_id = :cek_hareketi_id" );
                s_query.SET_VALUE     ( ":cek_hareketi_id", cek_hareletleri.keys().at(i) );

                if( i EQ 1 ) {
                    s_query.SET_VALUE( ":cek_onceki_hareketi", -1 );
                    s_query.SET_VALUE( ":cek_son_hareketi", cek_hareletleri.values().at(i) );
                }
                else {
                    s_query.SET_VALUE( ":cek_onceki_hareketi", cek_hareletleri.values().at( i - 1)); // bir onceki durum
                    s_query.SET_VALUE( ":cek_son_hareketi", cek_hareletleri.values().at(i) );
                }

                s_query.UPDATE();
            }
            // ilk satir siliniyor.
            s_query.PREPARE_DELETE( "cek_hareketleri", "cek_hareketi_id = :cek_hareketi_id");
            s_query.SET_VALUE     ( ":cek_hareketi_id", cek_hareletleri.keys().at(0));
            s_query.DELETE();
        }
    }
}

/**************************************************************************************
                         K9_V2_71_TO_V2_72_UPGRADE
***************************************************************************************/

void K9_V2_71_TO_V2_72_UPGRADE()
{
    TUM_CEK_DURUMLARINI_ONAR();
}

/**************************************************************************************
                         K9_V2_73_TO_V2_74_UPGRADE
***************************************************************************************/

void K9_V2_73_TO_V2_74_UPGRADE()
{

    SQL_QUERY query( G_YONETIM_DB );
    SQL_QUERY s_query( G_YONETIM_DB );

    query.PREPARE_SELECT( "ynt_belge_degiskenleri, ynt_belge_tasarimlari",
                          "belge_degisken_id, degisken_id, grup, yazi_boyutu, belge_id",
                          "ynt_belge_tasarimlari.tasarim_id = ynt_belge_degiskenleri.tasarim_id " );

    if ( query.SELECT() NE 0 ) {
        while( query.NEXT() EQ true ) {

            int belge_degisken_id = query.VALUE(0).toInt();
            int degisken_id       = query.VALUE(1).toInt();
            QString grup          = query.VALUE(2).toString();
            int   text_size       = query.VALUE(3).toInt();
            int   belge_id        = query.VALUE(4).toInt();

            int grup_enum = grup.toInt();

            if ( grup EQ "USER_TEXT_VARIABLE" ) {
                grup_enum = 40;
            }
            if ( grup EQ "USER_PIXMAP_VARIABLE" ) {
                grup_enum = 50;
            }

            if ( text_size EQ 0 ) {

                for (int  j = 0;  j < ADAK_BELGE_COUNT; ++ j) {
                    if ( k9_belge_struct[j].belge_id EQ belge_id ) {

                        if ( grup_enum EQ HEADER ) {
                            for (int i = 0; i < k9_belge_struct[j].header_struct_size; ++i) {
                                if ( k9_belge_struct[j].header_struct[i].degisken_id EQ degisken_id ) {
                                    text_size = k9_belge_struct[j].header_struct[i].karakter_sayisi;
                                }
                            }
                        }
                        else if ( grup_enum EQ LINE ) {
                            for (int i = 0; i < k9_belge_struct[j].line_struct_size; ++i) {
                                if ( k9_belge_struct[j].line_struct[i].degisken_id EQ degisken_id ) {
                                    text_size = k9_belge_struct[j].line_struct[i].karakter_sayisi;
                                }

                            }
                        }
                        else { // FOOTER
                            for (int i = 0; i < k9_belge_struct[j].footer_struct_size; ++i) {
                                if ( k9_belge_struct[j].footer_struct[i].degisken_id EQ degisken_id ) {
                                    text_size = k9_belge_struct[j].footer_struct[i].karakter_sayisi;
                                }
                            }
                        }
                    }
                }

            }
            G_YONETIM_DB->START_TRANSACTION();
            s_query.PREPARE_UPDATE( "ynt_belge_degiskenleri", "belge_degisken_id",
                                    "grup_enum, text_size", "belge_degisken_id = :belge_degisken_id");
            s_query.SET_VALUE     ( ":grup_enum", grup_enum );
            s_query.SET_VALUE     ( ":text_size", text_size );
            s_query.SET_VALUE     ( ":belge_degisken_id", belge_degisken_id);
            s_query.UPDATE();
            G_YONETIM_DB->COMMIT_TRANSACTION();

        }
    }
}

/**************************************************************************************
                         K9_V2_74_TO_V2_75_UPGRADE
***************************************************************************************/

void K9_V2_74_TO_V2_75_UPGRADE()
{
    // cek senet onar
    CEK_SON_DURUMLARI_DUZELT();

    SQL_QUERY f_query(DB);
    SQL_QUERY s_query(DB);

    f_query.PREPARE_SELECT("fat_faturalar",
                           "fis_id, cari_para_birimi_tutari, fatura_tutari, "
                           "fatura_para_birimi_id, doviz_kuru, parite, cari_hesap_id");

    if ( f_query.SELECT() NE 0 ) {
        while( f_query.NEXT() EQ true ) {

            int    fis_id                  = f_query.VALUE(0).toInt();
            double cari_para_birimi_tutari = f_query.VALUE(1).toDouble();
            double fatura_tutari           = f_query.VALUE(2).toDouble();
            int    fatura_para_birimi_id   = f_query.VALUE(3).toInt();
            double doviz_kuru              = f_query.VALUE(4).toDouble();
            double parite                  = f_query.VALUE(5).toDouble();
            int    cari_hesap_id           = f_query.VALUE(6).toInt();

            int    temel_para_birim_id     = DVZ_GET_TEMEL_PARA_BIRIMI_ID();
            int    cari_para_birim_id      = CARI_GET_PARA_BIRIM_ID(cari_hesap_id);

            if ( cari_para_birimi_tutari NE 0.00 ) {

                if ( cari_para_birim_id EQ fatura_para_birimi_id ) {
                    if ( cari_para_birimi_tutari EQ fatura_tutari ) {
                        continue;
                    }
                }
            }

            if ( fatura_para_birimi_id EQ cari_para_birim_id ) {
                cari_para_birimi_tutari = fatura_tutari;
            }
            else {
                if ( cari_para_birim_id NE temel_para_birim_id AND fatura_para_birimi_id NE temel_para_birim_id ) {
                    cari_para_birimi_tutari = ROUND( fatura_tutari* parite );
                }
                else {
                    cari_para_birimi_tutari = ROUND( fatura_tutari * doviz_kuru );
                }
            }

            s_query.PREPARE_UPDATE("fat_faturalar","fis_id",
                                   "cari_para_birimi_tutari", "fis_id = :fis_id");

            s_query.SET_VALUE     (":cari_para_birimi_tutari", cari_para_birimi_tutari );
            s_query.SET_VALUE     (":fis_id", fis_id );
            s_query.UPDATE();
        }
    }
}

/**************************************************************************************
                         K9_V2_76_TO_V2_77_UPGRADE
***************************************************************************************/

void K9_V2_76_TO_V2_77_UPGRADE()
{
    SQL_QUERY query(DB);

    int ilk_degerler_atandi_mi = -1;
    query.PREPARE_SELECT("k9_degiskenler", "ilk_degerler_atandi_mi", "");
    if ( query.SELECT() NE 0 ) {
        query.NEXT();

        ilk_degerler_atandi_mi = query.VALUE(0).toInt();
    }

    if ( ilk_degerler_atandi_mi NE -1 ) {

        query.PREPARE_UPDATE("k9_sabit_degerler", "sabit_deger_id", "k9_sabit_degerler_atandi_mi", "");
        query.SET_VALUE     (":k9_sabit_degerler_atandi_mi", ilk_degerler_atandi_mi );
        query.UPDATE();
    }

}

/**************************************************************************************
                         K9_V2_81_TO_V2_82_UPGRADE
***************************************************************************************/

void K9_V2_81_TO_V2_82_UPGRADE()
{
    ISL_ENT_FISLERINI_SIL(K9_PROGRAMI, ISLETME_MODULU);

    SQL_QUERY f_query(DB);
    SQL_QUERY s_query(DB);
    SQL_QUERY t_query(DB);

    f_query.PREPARE_SELECT("isl_fisi", "fis_id, fis_turu");

    if ( f_query.SELECT() NE 0 ) {

        while( f_query.NEXT() EQ true ) {
            int fis_id   = f_query.VALUE(0).toInt();
            int fis_turu = f_query.VALUE(1).toInt();

            if ( fis_turu EQ ENUM_GIDER_FISI ) {
                continue;
            }

            s_query.PREPARE_SELECT("isl_fis_satirlari", "fis_satiri_id, gider_turu ", "fis_id = :fis_id");
            s_query.SET_VALUE     ( ":fis_id", fis_id );

            if( s_query.SELECT() NE 0 ) {
                while( s_query.NEXT() EQ true ) {

                    int fis_satiri_id = s_query.VALUE("fis_satiri_id").toInt();
                    int islem_turu    = s_query.VALUE("gider_turu").toInt();

                    if ( islem_turu EQ -1 ) {
                        t_query.PREPARE_UPDATE("isl_fis_satirlari", "fis_satiri_id", "gider_turu", "fis_satiri_id = :fis_satiri_id");
                        t_query.SET_VALUE     (":gider_turu", ENUM_MAL_SATISI );
                        t_query.SET_VALUE     (":fis_satiri_id", fis_satiri_id );
                        t_query.UPDATE();
                    }
                }
            }
        }
    }
}

#ifndef K9_ENUM_H
#define K9_ENUM_H

#define K9_ARRAY_SIZE              501
#define K9_SON_BAKIYE             ( K9_ARRAY_SIZE - 1 )
#define KDV_OTV_ORANLARI_SAYISI    10

enum K9_0_AND_1 {
    EVET  = 1,
    HAYIR = 0
};

enum KULLANICININ_SIRKETI {
    SIRKET_1      = 1, // ent
    SIRKET_2      = 0  // ent olmayan
};

enum FIS_FILTRESI {
    FIS_HER_IKI_SIRKET  = 10,
    FIS_BIRINCI_SIRKET  = 11,
    FIS_IKINCI_SIRKET   = 12
};

enum K9_TAH_ODM_SEKILLERI {
    ENUM_NAKIT           = 100,
    ENUM_MUSTERI_CEKI    = 200,
    ENUM_MUSTERI_SENEDI  = 300,
    ENUM_KENDI_CEKIMIZ   = 400,
    ENUM_KENDI_SENEDIMIZ = 500,
    ENUM_KREDI_KARTI     = 600,
    ENUM_HAVALE          = 700,
    ENUM_EFT             = 800
};

enum DVZ_EKLE_SIL {
    DOVIZ_EKLE = 300,
    DOVIZ_SIL  = 400
};

enum AYLAR {
    ENUM_OCAK    = 1,
    ENUM_SUBAT   = 2,
    ENUM_MART    = 3,
    ENUM_NISAN   = 4,
    ENUM_MAYIS   = 5,
    ENUM_HAZIRAN = 6,
    ENUM_TEMMUZ  = 7,
    ENUM_AGUSTOS = 8,
    ENUM_EYLUL   = 9,
    ENUM_EKIM    = 10,
    ENUM_KASIM   = 11,
    ENUM_ARALIK  = 12
};

// cari tahsilar, cari odeme, fatura ve irsaliyede kullaniliyor.
enum FIS_YAZICI_DURMU {
    ENUM_FIS_YAZILMADI  = 0,
    ENUM_FIS_YAZILDI    = 1
};

#endif // K9_ENUM_H

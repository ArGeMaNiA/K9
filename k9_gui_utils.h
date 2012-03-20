#ifndef K9_GUI_ITULS_H
#define K9_GUI_ITULS_H

class QString;
class QAdakDate;
class QComboBox;
class QWidget;


void        K9_FILL_COMBOBOX_AYLAR                         ( QComboBox * p_combo_box );

void        K9_FILL_KDV_ORANLARI_COMBOBOX                  ( QComboBox * p_comboBox );
void        K9_FILL_OTV_ORANLARI_COMBOBOX                  ( QComboBox * p_comboBox );

void        K9_FILL_COMBOBOX_FIS_FILTRESI                  ( QComboBox * combobox_entegre_filtresi);

void        K9_FILL_COMBOBOX_KAYDEDILECEK_SIRKET           ( QComboBox * combobox_kaydedilecek_sirket);

void        K9_FILL_COMBOBOX_ADAK_MODULES                 ( QComboBox * p_comboBox          );

void        K9_SET_WINDOW_ICON                             ( QWidget * p_window );

bool        K9_SUBEYE_UNITE_KAYDI_YAPILDI_MI               ( );

void        K9_FILL_COMBOBOX_RAPOR_SIRKET_FILTRESI         ( QComboBox * combobox_sirket_turu );

int         K9_MALI_YIL_TARIH_ARALIGI_KONTROLU             ( QAdakDate * p_baslangic_tarihi, QAdakDate * p_bitis_tarihi );

int         K9_GET_KULLANICININ_CALISTIGI_SIRKET_ENUM      ( QString p_sirket );

QString     K9_GET_KULLANICININ_CALISTIGI_SIRKET_STRING    ( int p_sirket );

void        K9_FILL_KULLANICININ_CALISTIGI_SIRKETLER       ( QComboBox * p_combo_box  );



#endif // K9_GUI_ITULS_H

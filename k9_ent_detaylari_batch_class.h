#ifndef K9_ENT_DETAYLARI_BATCH_H
#define K9_ENT_DETAYLARI_BATCH_H

#include "batch_kernel.h"

struct K9_ENT_DETAYLARI_STRUCT;

namespace Ui {
    class K9_ENT_DETAYLARI_BATCH;
}
class QLineEdit;

class K9_ENT_DETAYLARI_BATCH : public BATCH_KERNEL
{
    Q_OBJECT


public:
                           K9_ENT_DETAYLARI_BATCH                            ( K9_ENT_DETAYLARI_STRUCT * P_ENT_DETAYLARI, bool kasa_hesabi_gosterilecek ,QWidget * parent = 0 );
                           ~K9_ENT_DETAYLARI_BATCH                           () {}
private:

    Ui::K9_ENT_DETAYLARI_BATCH *        m_ui;

    bool                       m_kasa_hesabi_gosterilecek;

    K9_ENT_DETAYLARI_STRUCT * M_ENT_DETAYLARI;

    void                   SETUP_FORM                           ();

    int                    CHECK_VAR                            ( QObject * object );
    int                    CHECK_RUN                            ();
    void                   RUN_BATCH                            ();

    void                   SEARCH_EDIT_CLICKED                  (QWidget *widget, QLineEdit *line_edit);

};

#endif // K9_ENT_DETAYLARI_BATCH_H

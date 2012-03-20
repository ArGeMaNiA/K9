#ifndef K9_ONAR_BATCH_H
#define K9_ONAR_BATCH_H

#include "batch_kernel.h"

namespace Ui {
    class K9_ONAR_BATCH;
}

class K9_ONAR_BATCH : public BATCH_KERNEL
{
    Q_OBJECT

private:
    Ui::K9_ONAR_BATCH *   m_ui;

    bool                  m_tum_sistemi_onar;

public:
                           K9_ONAR_BATCH                            (QWidget * parent = 0);
                           ~K9_ONAR_BATCH                           () {}
protected:
    void                   SETUP_FORM                           ();
    int                    CHECK_VAR                            (QObject * object);
    int                    CHECK_RUN                            ();
    int                    CHECK_EXIT                           ();
    void                   RUN_BATCH                            ();

    void                   TUM_SISTEMI_ONAR                                ( );

    void                   BILGILENDIR                          (QString message);

};

#endif // K9_ONAR_BATCH_H

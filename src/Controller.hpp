#ifndef CONTROLLER_HPP__
#define CONTROLLER_HPP__

#include "PdfViewer.hpp"

class Controller: public QObject
{
Q_OBJECT

public:
   Controller(QObject *parent=0);
   ~Controller();

private:
   MuPDF::Document  *m_doc;
   QList<PdfViewer*> m_lViewers;

   int m_iCurrentPage;
   int m_iMaxpage;
private slots:
   void slotAddPdfViewer(int offset);
   void slotSwitchPage(int direction);
   void slotGotoStart();
   void slotGotoEnd();
};

#endif /* CONTROLLER_HPP__ */

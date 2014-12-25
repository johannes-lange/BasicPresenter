#ifndef CONTROLLER_HPP__
#define CONTROLLER_HPP__

#include "PdfViewer.hpp"

class Controller: public QObject
{
Q_OBJECT

public:
   Controller(QObject *parent=0);
   ~Controller();

   void addPdfViewer(int offset);
private:
   MuPDF::Document  *m_doc;
   QList<PdfViewer*> m_lViewers;

   int m_iCurrentPage;
   int m_iMaxpage;
private slots:
   void slotSwitchPage(int direction);
};

#endif /* CONTROLLER_HPP__ */

#include "Controller.hpp"

#include <QDebug>
#include <QObject>

Controller::Controller(QString filename, QObject *parent):
   QObject(parent),
   m_iCurrentPage(0)
{
   m_doc = MuPDF::loadDocument(filename);
   m_iMaxpage = m_doc->numPages()-1;
}

Controller::~Controller()
{
   delete m_doc;
   foreach(PdfViewer *v, m_lViewers){
      delete v;
   }
}

void Controller::addPdfViewer(int offset)
{
   PdfViewer* p = new PdfViewer(m_doc,offset);
   p->show();
   p->showPage(0);

   connect(p   , SIGNAL(signalSwitchPage(int)),
           this, SLOT  (slotSwitchPage  (int)));

   m_lViewers.append(p);
}

void Controller::slotSwitchPage(int direction)
{
   int newPage = m_iCurrentPage+direction;
   if (newPage < 0 || newPage > m_iMaxpage) return;
   m_iCurrentPage=newPage;
   foreach(PdfViewer *v, m_lViewers){
      v->showPage(m_iCurrentPage);
   }
}

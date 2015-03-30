#include "Controller.hpp"

#include <QApplication>
//#include <QDebug>
#include <QObject>

Controller::Controller(QObject *parent):
   QObject(parent),
   m_doc(0),
   m_iCurrentPage(0)
{
   // parse command line arguments
   QStringList args =  QApplication::arguments().mid(1);

   // get filename
   QString filename="";
   foreach (QString arg, args){
      if (arg.endsWith(".pdf",Qt::CaseInsensitive)){
         filename=arg;
         args.removeAll(arg);
         break;
      }
   }

   if (filename.isEmpty()) qFatal("Error: no valid filename found (*.pdf)");
   m_doc = MuPDF::loadDocument(filename);
   if (!m_doc) qFatal("Error: cannot open file %s",filename.toStdString().c_str());
   m_iMaxpage = m_doc->numPages()-1;
   // show "master" viewer
   slotAddPdfViewer(0);
   m_lViewers.last()->setWindowTitle("BasicPresenter - Master");

   // create user viewers
   foreach (QString arg, args){
      bool ok;
      int offset;
      offset=arg.toInt(&ok);
      if (ok) slotAddPdfViewer(offset);
      else    qWarning("unrecognized argument: %s",arg.toStdString().c_str());
   }
}

Controller::~Controller()
{
   delete m_doc;
   foreach(PdfViewer *v, m_lViewers){
      delete v;
   }
}

void Controller::slotAddPdfViewer(int offset)
{
   PdfViewer* p = new PdfViewer(m_doc,offset);
   p->show();
   p->showPage(m_iCurrentPage);

   connect(p   , SIGNAL(signalSwitchPage(int)),
           this, SLOT  (slotSwitchPage  (int)));
   connect(p   , SIGNAL(signalGotoStart()),
           this, SLOT  (slotGotoStart()));
   connect(p   , SIGNAL(signalGotoEnd()),
           this, SLOT  (slotGotoEnd()));
   connect(p   , SIGNAL(signalSpawnViewer(int)),
           this, SLOT(slotAddPdfViewer(int)));

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

void Controller::slotGotoStart()
{
   m_iCurrentPage=0;
   foreach(PdfViewer *v, m_lViewers){
      v->showPage(m_iCurrentPage);
   }
}

void Controller::slotGotoEnd()
{
   m_iCurrentPage=m_iMaxpage;
   foreach(PdfViewer *v, m_lViewers){
      v->showPage(m_iCurrentPage);
   }
}

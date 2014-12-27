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
   if (!m_doc) qFatal(("Error: cannot open file "+filename).toStdString().c_str());
   m_iMaxpage = m_doc->numPages()-1;
   // show "master" viewer
   addPdfViewer(0);

   // create user viewers
   foreach (QString arg, args){
      bool ok;
      int offset;
      offset=arg.toInt(&ok);
      if (ok) addPdfViewer(offset);
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

#include "PdfViewer.hpp"

//#include <QDebug>
#include <QApplication>
#include <QMouseEvent>
#include <QShortcut>

PdfViewer::PdfViewer(MuPDF::Document const *doc, int offset, QWidget *parent):
   QWidget(parent),
   m_document(doc),
   m_iOffset(offset),
   m_page(0)
{
   m_layout.addWidget(&m_labelContent);
   this->setLayout(&m_layout);
   createKeybindings();
}

PdfViewer::~PdfViewer()
{
   delete m_page;
}

void PdfViewer::createKeybindings()
{
   // shortcuts are deleted by qt
   QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+W"),this);
   connect(shortcut, SIGNAL(activated()),
           this    , SLOT   (close()));
   shortcut = new QShortcut(QKeySequence("Ctrl+Q"),this);
   connect(shortcut                , SIGNAL(activated()),
           QApplication::instance(), SLOT  (closeAllWindows()));

   // Navigation
   shortcut = new QShortcut(QKeySequence("Right"),this);
   connect(shortcut, SIGNAL(activated()),
           this    , SLOT  (slotEmitNext()));
   shortcut = new QShortcut(QKeySequence("Down"),this);
   connect(shortcut, SIGNAL(activated()),
           this    , SLOT  (slotEmitNext()));
   shortcut = new QShortcut(QKeySequence("Left"),this);
   connect(shortcut, SIGNAL(activated()),
           this    , SLOT  (slotEmitPrev()));
   shortcut = new QShortcut(QKeySequence("Up"),this);
   connect(shortcut, SIGNAL(activated()),
           this    , SLOT  (slotEmitPrev()));
}

void PdfViewer::showPage(int iPage)
{
   if (m_page) delete m_page;
   m_page = m_document->page(iPage+m_iOffset);
   if (m_page)
      m_labelContent.setPixmap(QPixmap::fromImage(m_page->renderImage(2,2)));
   else
      m_labelContent.setText(QString::number(iPage+m_iOffset+1));
}

void PdfViewer::mouseReleaseEvent(QMouseEvent * event)
{
   int switchDirection = 0;
   switch (event->button())
   {
      case Qt::LeftButton : switchDirection= 1; break;
      case Qt::RightButton: switchDirection=-1; break;
      default: return;
   }
   emit signalSwitchPage(switchDirection);
}

void PdfViewer::slotEmitNext()
{
   emit signalSwitchPage(1);
}

void PdfViewer::slotEmitPrev()
{
   emit signalSwitchPage(-1);
}

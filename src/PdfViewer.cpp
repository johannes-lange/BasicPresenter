#include "PdfViewer.hpp"

#include <algorithm>

//#include <QDebug>
#include <QApplication>
#include <QMouseEvent>
#include <QShortcut>

PdfViewer::PdfViewer(MuPDF::Document const *doc, int offset, QWidget *parent):
   QWidget(parent),
   m_document(doc),
   m_iOffset(offset),
   m_iMaxpage(doc->numPages()-1),
   m_page(0)
{
   QPalette pal = this->palette();
   pal.setColor(this->backgroundRole(), Qt::black);
   pal.setColor(this->foregroundRole(), Qt::gray);
   this->setPalette(pal);

   QFont font = this->font();
   font.setPointSize(72);
   this->setFont(font);

   m_labelContent.setAlignment(Qt::AlignCenter);

   m_layout.addWidget(&m_labelContent);
   m_layout.setContentsMargins(0,0,0,0);
   this->setLayout(&m_layout);

   resize(600,450);
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
   shortcut = new QShortcut(QKeySequence("Home"),this);
   connect(shortcut, SIGNAL(activated()),
           this    , SIGNAL(signalGotoStart()));
   shortcut = new QShortcut(QKeySequence("End"),this);
   connect(shortcut, SIGNAL(activated()),
           this    , SIGNAL(signalGotoEnd()));
}

void PdfViewer::showPage(int iPage)
{
   int const iNew = iPage+m_iOffset;
   if (iNew < 0 || iNew > m_iMaxpage){
      m_labelContent.setText(QString("%1/%2").arg(iNew+1).arg(m_iMaxpage+1));
   }else{
      if (m_page) delete m_page;
      m_page = m_document->page(iNew);
      updatePage();
   }
}

void PdfViewer::updatePage()
{
   if (!m_page) return;

   // render page according to window size
   QSizeF pdfSize=m_page->size();
   float scale = std::min(
                    size().width()/pdfSize.width(),
                    size().height()/pdfSize.height()
                 );
   m_labelContent.setPixmap(QPixmap::fromImage(m_page->renderImage(scale,scale)));
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

void PdfViewer::wheelEvent(QWheelEvent *event)
{
   static int delta = 0;
   delta += event->delta();
   int const iSteps = delta / 8 / 15;
   delta -= iSteps* 8 * 15;
   emit signalSwitchPage(-iSteps);
}

void PdfViewer::resizeEvent(QResizeEvent *event)
{
   // re-render pdf page
   updatePage();
}

void PdfViewer::slotEmitNext()
{
   emit signalSwitchPage(1);
}

void PdfViewer::slotEmitPrev()
{
   emit signalSwitchPage(-1);
}

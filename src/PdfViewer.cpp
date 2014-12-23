#include "PdfViewer.hpp"

//#include <QDebug>
#include <QMouseEvent>

PdfViewer::PdfViewer(MuPDF::Document const *doc, int offset, QWidget *parent):
   QWidget(parent),
   m_document(doc),
   m_iOffset(offset),
   m_page(0)
{
   m_layout.addWidget(&m_labelContent);
   this->setLayout(&m_layout);
}

PdfViewer::~PdfViewer()
{
   delete m_page;
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

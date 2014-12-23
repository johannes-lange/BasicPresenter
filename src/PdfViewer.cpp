#include "PdfViewer.hpp"


PdfViewer::PdfViewer(MuPDF::Document const * doc, QWidget *parent):
   QWidget(parent),
   m_document(doc),
   m_page(0)
{
   m_layout.addWidget(&m_labelContent);
   this->setLayout(&m_layout);

   showPage(1);
   showPage(0);
}

PdfViewer::~PdfViewer()
{
   delete m_page;
}

void PdfViewer::showPage(int iPage)
{
   if (m_page) delete m_page;
   m_page = m_document->page(iPage);

   m_labelContent.setPixmap(QPixmap::fromImage(m_page->renderImage(2,2)));
}

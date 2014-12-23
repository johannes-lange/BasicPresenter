#ifndef PDFVIEWER_HPP__
#define PDFVIEWER_HPP__

#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

#include "mupdf-qt.h"


class PdfViewer: public QWidget
{

public:
   PdfViewer(MuPDF::Document const * doc, QWidget *parent = 0);
   ~PdfViewer();

   void showPage(int iPage);

private:
   MuPDF::Document const *const m_document;
   MuPDF::Page *m_page;
   QVBoxLayout  m_layout;
   QLabel       m_labelContent;

};

#endif /* PDFVIEWER_HPP__ */

#ifndef PDFVIEWER_HPP__
#define PDFVIEWER_HPP__

#include <QLabel>
#include <QGridLayout>
#include <QWidget>

#include "mupdf-qt.h"


class PdfViewer: public QWidget
{
Q_OBJECT

public:
   PdfViewer(MuPDF::Document const *doc, int offset, QWidget *parent = 0);
   ~PdfViewer();

   void showPage(int iPage);

private:
   MuPDF::Document const *const m_document;
   MuPDF::Page *m_page;
   QGridLayout  m_layout;
   QLabel       m_labelContent;

   int m_iOffset;

   void createKeybindings();
   void updatePage();

protected:
   virtual void mouseReleaseEvent(QMouseEvent *event);
   virtual void resizeEvent(QResizeEvent *event);

signals:
   void signalSwitchPage(int direction);
   void signalGotoStart();
   void signalGotoEnd();
private slots:
   void slotEmitNext();
   void slotEmitPrev();
};

#endif /* PDFVIEWER_HPP__ */

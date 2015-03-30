BasicPresenter
==============

Basic presentation tool for pdf presentations to show a master viewer and an arbitrary number of
additional viewers.

![Screenshot](https://raw.githubusercontent.com/johannes-lange/BasicPresenter/master/example-usage.png)

### Usage ###
    BasicPresenter <pdf-file> [<additional viewers>]
Starts a master viewer showing the pdf file and optionally additional viewers.

Options:

- `<additional viewers>`: arbitrary number of integers specifying the page-offset
  of additional viewers

Controls:

- `Ctrl`+`W`     : close single viewer
- `Ctrl`+`Q`     : quit application (close all viewers)
- `Right`/`Down` : next page
- `Left`/`Up`    : previous page
- `Home`/`End`   : go to first/last page
- `F`/`F5`       : toggle fullscreen mode
- `Esc`          : leave fullscreen mode
- `A`            : add viewer (with same offset as active one)
- `Shift`+`Left`/`Right`: De-/Increase viewer offset


### Building ###
Fetch source code via git (or download manually)

    $ git clone https://github.com/johannes-lange/BasicPresenter.git
    $ cd BasicPresenter

Get dependencies

    $ git submodule update --init --recursive
    $ cd 3rdParty/mupdf-qt/mupdf
    $ make
    $ cd ..; mkdir build; cd build
    $ cmake ..
    $ make

Build actual project

    $ cd /path/to/BasicPresenter
    $ mkdir build; cd build
    $ cmake ..
    $ make

### TODO ###
- Bug: cannot decrease window size in Xfce (Probably concerns most other Window
managers, too. Works in i3.)
- minimize dependencies

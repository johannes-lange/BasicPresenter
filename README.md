BasicPresenter
==============

Basic presentation tool for pdf presentations to show a master viewer and an arbitrary number of
additional viewers.


### Usage ###
    BasicPresenter <pdf-file> [<additional viewers>]
Starts a master viewer showing the pdf file and optionally additional viewers.

Options:

- `<additional viewers>`: arbitrary number of integers specifying the page-offset
  of additional viewers

Controls:

- `Ctrl+W`           : close single viewer
- `Ctrl+Q`           : quit application (close all viewers)
- `Right`/`Down`-key : next page
- `Left`/`Up`-key    : previous page
- `Home`/`End`       : go to first/last page
- `f`/`F5`           : toggle fullscreen mode
- `Esc`              : leave fullscreen mode



### Building ###
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

    


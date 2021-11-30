# ECE496

Sound Synthesizer for Learning Purposes

Initializing submodules

```
git submodule init
git submodule update

cd external/ECE496-Backend
git submodule init
git submodule sync
git submodule update
```

Updated submodule:

Submodules can be updated recusively by running `git submodule update -- recursive` from the current directory

### Getting QT Multimedia

Go to **QT Maintanence Tool** located in your downloaded directory

Click **next > add or remove components >**

Expand **Qt > Qt 6.2.1**

`MinGW` does not work with QT multimedia so you do not have to install this compiler

Select **MSVC 2019 64-bit** which is a compiler that works with QT multimedia

Expand **Qt > Qt 6.2.1 > Additional Libraries** and select **Qt multimedia**

This library is required to output sound out of QT

### Building Error FAQ

must have VS2019 installed for compiler

deselect shadow build

Contributors:
Max
Kyu Bum Kim (kb.kim@mail.utoronto.ca)
Eduardo Ortenblad (edu.ortenblad@mail.utoronto.ca)

Acknowledgements:

This code uses STK

This code uses QCustomPlot which is built on QT (https://www.qcustomplot.com)

The TimeDomain widget draws from code written by StackOverflow user thibsc.

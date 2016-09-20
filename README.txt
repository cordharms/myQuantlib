
Getting Startet
===============

The QuantLib solution consists of two git repositories:
   quantlib-old (super repo containing projects that exports QuantLib to Excel)
   QunantLib (sub-repo containing the project for core QuantLib - only C++)   

1) Clone your local repository
   git clone --recursive git@moco.d-fine.de:quantlib.git quantlib
   The option '--recursive' also clones the QuantLib repository

2) Include Boost into VS 2012
   The following projects require Boost:
   - ohxllib
   - QuantLib
   - QuantLibObjects
   - QuantLibXLStatic
   Boost is incorporated via a separate property sheet Microsoft.Cpp.Win32.Boost.props.
   The sheet is located  in quantlib-old/ but added to .gitignore to prevent frequent
   updates.
   Edit Microsoft.Cpp.Win32.Boost.props in a text editor and update paths to your
   local Boost installation
   Note: You need to have Boost libraries compiled with VS 2012 and corresponding
   single/multi threading and release/debug options
   
2) Open Solution ..\quantlib\QuantLibXL\QuantLibXL_full_vc11.sln

3) Build Solution and create Excel Addin (e.g. ...\quantlib\QuantLibXL\xll\QuantLibXL-vc90-mt-gd-1_1_0.xll)

Develop a feature
=================

1) Create a branch in QuantLib and check it out, e.g. git checkout -b myfeature

2) Add QuantLib source code
   - Create a new folder ..\quantlib\QuantLib\ql\experimental\myfeature
   - Create your source files (e.g. myfeature.hpp and myfeature.cpp)
   - In VS add a new filter QuantLib / experimental / myfeature
   - Add your source files in filter myfeature
   - Code your features and make sure they compile properly

3) Create a branch in quantlib-old and check it out, e.g. git checkout -b myfeature
   
4) Add QuantLibObjects source code (for Excel and other interfaces)
   - Create your object source files (e.g. myfeature.hpp and myfeature.cpp) in ..\quantlib\QuantLibAddin\qlo
   - In VS add a new filter QuantLibObjects / Experimental / MyFeature
   - Add your object source files in filter MyFeature
   - Make sure they compile properly
   
5) Add interface specification in qlgensrc (i.e. include your feature in Excel interface)
   - create a new file ..\quantlib\QuantLibAddin\gensrc\metadata\functions\myfeature.xml
   - In VS add the new file in qlgensrc / functions / experimental / myfeature.xml
   - Add myfeature in qlgensrc / config / categories.xml
   - Add new object types in qlgensrc / config / types.xml
   - Build qlgensrc
   - Add new created object files to QuantLibObjects
     valueobjects: vo_myfeature.hpp/.cpp
	 serialization / create: create_myfeature.hpp/.cpp
	 serialization / register: serialization_myfeature.hpp/.cpp
   - check that QuantLibObjects builds properly
   - Add new created files to QuantLibXLStatic
     functions: functions / sabrswaptioncube.cpp
	 register: register / register_sabrswaptioncube.cpp
   - Build QuantLibXLStatic
   
6) Document your feature
   - Create a standalone example workbook that documents your feature
   - Add it to ..\quantlib\QuantLibXL\Workbooks\Experimental
   
7) Make feature available for others
   - commit your modifications and push them to both repositories
   - if everything is fine merge your branch into master

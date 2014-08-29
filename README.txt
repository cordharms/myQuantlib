
Getting Startet

1) Clone your local repository

2) Open Solution QuantLibXL_full_vc11.sln

2) Include Boost into VS 2012
   - Go to Property Manager
   - Select a project (e.g. QuantLib)
   - Navigate to a Win32 Property Sheet (e.g. Debug | Win32)
   - Open (double click) Microsoft.Cpp.Win32.user
   - Go to Common Properties / VC++ Directories
   - Edit Include Directories (e.g. add C:\Program Files\boost\boost_1_54_0)
   - Edit Library Directories (e.g. add C:\Program Files\boost\boost_1_54_0\stage\lib)
   - Close Property Page
   - IMPORTANT: Right click on Microsoft.Cpp.Win32.user, select 'Save Microsoft.Cpp.Win32.user'
   This should make Boost available globally for your solutions
   
3) Build Solution and create Excel Addin (e.g. ...\quantlib\QuantLibXL\xll\QuantLibXL-vc90-mt-gd-1_1_0.xll)

Develop a feature

1) Create a branch and check it out, e.g. git checkout -b myfeature

2) Add QuantLib source code
   - Create a new folder ..\quantlib\QuantLib\ql\experimental\myfeature
   - Create your source files (e.g. myfeature.hpp and myfeature.cpp)
   - In VS add a new filter QuantLib / experimental / myfeature
   - Add your source files in filter myfeature
   - Code your features and make sure they compile properly
   
3) Add QuantLibObjects source code (for Excel and other interfaces)
   - Create your object source files (e.g. myfeature.hpp and myfeature.cpp) in ..\quantlib\QuantLibAddin\qlo
   - In VS add a new filter QuantLibObjects / Experimental / MyFeature
   - Add your object source files in filter MyFeature
   - Make sure they compile properly
   
4) Add interface specification in qlgensrc (i.e. include your feature in Excel interface)
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
   
5) Document your feature
   - Create a standalone example workbook that documents your feature
   - Add it to ..\quantlib\QuantLibXL\Workbooks\Experimental
   
6) Make feature available for others
   - commit your modifications and push them to repository
   - if everything is fine merge your branch into master

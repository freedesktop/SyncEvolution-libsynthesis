@rem  This file was contributed by Ralf Junker, and touched up by
@rem  Daniel Richard G. Test 10 added by Philip H.
@rem
@rem  MS Windows batch file to run pcretest on testfiles with the correct
@rem  options.
@rem
@rem  Output is written to a newly created subfolder named "testdata".

setlocal

if [%srcdir%]==[]   set srcdir=.
if [%pcretest%]==[] set pcretest=pcretest

if not exist testout md testout

%pcretest% -q      %srcdir%\testdata\testinput1 > testout\testoutput1
%pcretest% -q      %srcdir%\testdata\testinput2 > testout\testoutput2
%pcretest% -q      %srcdir%\testdata\testinput3 > testout\testoutput3
%pcretest% -q      %srcdir%\testdata\testinput4 > testout\testoutput4
%pcretest% -q      %srcdir%\testdata\testinput5 > testout\testoutput5
%pcretest% -q      %srcdir%\testdata\testinput6 > testout\testoutput6
%pcretest% -q -dfa %srcdir%\testdata\testinput7 > testout\testoutput7
%pcretest% -q -dfa %srcdir%\testdata\testinput8 > testout\testoutput8
%pcretest% -q -dfa %srcdir%\testdata\testinput9 > testout\testoutput9
%pcretest% -q      %srcdir%\testdata\testinput10 > testout\testoutput10

fc /n %srcdir%\testdata\testoutput1 testout\testoutput1
fc /n %srcdir%\testdata\testoutput2 testout\testoutput2
rem fc /n %srcdir%\testdata\testoutput3 testout\testoutput3
fc /n %srcdir%\testdata\testoutput4 testout\testoutput4
fc /n %srcdir%\testdata\testoutput5 testout\testoutput5
fc /n %srcdir%\testdata\testoutput6 testout\testoutput6
fc /n %srcdir%\testdata\testoutput7 testout\testoutput7
fc /n %srcdir%\testdata\testoutput8 testout\testoutput8
fc /n %srcdir%\testdata\testoutput9 testout\testoutput9
fc /n %srcdir%\testdata\testoutput10 testout\testoutput10

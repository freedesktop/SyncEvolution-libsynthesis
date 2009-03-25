@rem
@rem Copyright Notice
@rem Copyright (c) Ericsson, IBM, Lotus, Matsushita Communication
@rem Industrial Co., Ltd., Motorola, Nokia, Openwave Systems, Inc.,
@rem Palm, Inc., Psion, Starfish Software, Symbian, Ltd. (2001).
@rem All Rights Reserved.
@rem Implementation of all or part of any Specification may require
@rem licenses under third party intellectual property rights,
@rem including without limitation, patent rights (such a third party
@rem may or may not be a Supporter). The Sponsors of the Specification
@rem are not responsible and shall not be held responsible in any
@rem manner for identifying or failing to identify any or all such
@rem third party intellectual property rights.
@rem
@rem THIS DOCUMENT AND THE INFORMATION CONTAINED HEREIN ARE PROVIDED
@rem ON AN "AS IS" BASIS WITHOUT WARRANTY OF ANY KIND AND ERICSSON, IBM,
@rem LOTUS, MATSUSHITA COMMUNICATION INDUSTRIAL CO. LTD, MOTOROLA,
@rem NOKIA, PALM INC., PSION, STARFISH SOFTWARE AND ALL OTHER SYNCML
@rem SPONSORS DISCLAIM ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING
@rem BUT NOT LIMITED TO ANY WARRANTY THAT THE USE OF THE INFORMATION
@rem HEREIN WILL NOT INFRINGE ANY RIGHTS OR ANY IMPLIED WARRANTIES OF
@rem MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT
@rem SHALL ERICSSON, IBM, LOTUS, MATSUSHITA COMMUNICATION INDUSTRIAL CO.,
@rem LTD, MOTOROLA, NOKIA, PALM INC., PSION, STARFISH SOFTWARE OR ANY
@rem OTHER SYNCML SPONSOR BE LIABLE TO ANY PARTY FOR ANY LOSS OF
@rem PROFITS, LOSS OF BUSINESS, LOSS OF USE OF DATA, INTERRUPTION OF
@rem BUSINESS, OR FOR DIRECT, INDIRECT, SPECIAL OR EXEMPLARY, INCIDENTAL,
@rem PUNITIVE OR CONSEQUENTIAL DAMAGES OF ANY KIND IN CONNECTION WITH
@rem THIS DOCUMENT OR THE INFORMATION CONTAINED HEREIN, EVEN IF ADVISED
@rem OF THE POSSIBILITY OF SUCH LOSS OR DAMAGE.
@rem
@rem The above notice and this paragraph must be included on all copies
@rem of this document that are made.
@rem
@rem

@rem
@rem The above notice and this paragraph must be included on all copies of this
@rem document that are made.
@rem
@rem

@rem
@rem test, if environment variable is set
@rem
@if exist %MINGW32_LOCATION% goto continue1
@echo Please set the environment variable MINGW32_LOCATION. See README.win for details
@goto end
:continue1

@rem
@rem test commandline parameter
@rem
@if "%1" == "" goto usage
@if %1 == all goto start
@if %1 == sml goto start
@if %1 == xpt goto start
@if %1 == clean goto start
@goto usage

:start

@rem
@rem to avoid conflicts with other compiler, we set
@rem the environment for compiling here
@rem
@setlocal
@set PATH=%MINGW32_LOCATION%\bin;
@set GCC_EXEC_PREFIX=

@rem
@rem now compile
@rem
@cd win
make %1
@cd ..

@endlocal

@goto end

:usage
@echo USAGE: "makewin all|sml|xpt|clean"

:end

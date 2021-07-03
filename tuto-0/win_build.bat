@set CC=%MINGW_HOME%\bin\gcc.exe
@set LIBXML2_PATH=..\install\i686-mingw
@%CC% -Wall -Werror -o.\app ^
	-DLIBXML_STATIC ^
	-I%LIBXML2_PATH%\include\libxml2 ^
	-L%LIBXML2_PATH%\lib ^
	.\main.c ^
	-lxml2 ^
	-liconv ^
	-lws2_32

mkdir %outdir%\server\relay
mkdir %outdir%\server\settings_s\maps
mkdir %outdir%\server\script
mkdir %outdir%\server\settings_s\settings

mkdir %outdir%\client\clientpkg\maps
mkdir %outdir%\client\clientpkg\script
mkdir %outdir%\client\clientpkg\settings
mkdir %outdir%\client\clientpkg\ui

xcopy %outdir%\out\����������ļ�\relay %outdir%\server\relay /e/y/r/k
xcopy %outdir%\out\����������ļ�\gamesvr\maps %outdir%\server\settings_s\maps /e/y/r/k
xcopy %outdir%\out\����������ļ�\gamesvr\script %outdir%\server\script /e/y/r/k
xcopy %outdir%\out\����������ļ�\gamesvr\settings %outdir%\server\settings_s\settings /e/y/r/k

xcopy %outdir%\out\�趨�ļ�\script %outdir%\server\script /e/y/r/k
xcopy %outdir%\out\�趨�ļ�\settings %outdir%\server\settings_s\settings /e/y/r/k

xcopy %outdir%\out\�ͻ��������ļ�\maps %outdir%\client\clientpkg\maps /e/y/r/k
xcopy %outdir%\out\�ͻ��������ļ�\script %outdir%\client\clientpkg\script /e/y/r/k
xcopy %outdir%\out\�ͻ��������ļ�\settings %outdir%\client\clientpkg\settings /e/y/r/k
xcopy %outdir%\out\�ͻ��������ļ�\ui %outdir%\client\clientpkg\ui /e/y/r/k

xcopy %outdir%\out\�趨�ļ�\script %outdir%\client\clientpkg\script /e/y/r/k
xcopy %outdir%\out\�趨�ļ�\settings %outdir%\client\clientpkg\settings /e/y/r/k

PackFile P -P%outdir%\server\settings_s.pak -R%outdir%\server\settings_s\ -D.
PackFile P -P%outdir%\client\clientpkg.pak -R%outdir%\client\clientpkg -D.

path=%envpath%\gz;%path%
cd %outdir%\server
tar.gz.bat script
cd %envpath%
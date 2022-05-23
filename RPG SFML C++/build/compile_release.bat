@echo off

del *.obj *.ilk *.pdb *.exe *.ini

rmdir /q /s .vs

cls

cl /MP /nologo /O2 /MD /EHs /W4 /DSFML_STATIC /c -I ../include/sql ../src/sql/sqlite3.c

cl /MP /nologo /O2 /MD /EHs /W4 /DSFML_STATIC /c -I ../include -I ../include/utils -I ../include/sql -I ../deps/sfml/x86/include ../src/utils/*.cc

cl /MP /nologo /O2 /MD /EHs /W4 /DSFML_STATIC /c -I ../include -I ../include/imgui -I ../deps/sfml/x86/include ../src/imgui/*.cc

cl /MP /nologo /O2 /MD /EHs /W4 /DSFML_STATIC /c -I ../include -I ../include/utils -I ../include/sql -I ../deps/sfml/x86/include -I ../include/scenes ../src/*.cc

cl /MP /nologo /O2 /MD /EHs /W4 /DSFML_STATIC /c -I ../include -I ../include/utils -I ../include/sql -I ../deps/mka_list/include ../src/sql/*.cc

cl /MP /nologo /O2 /MD /EHs /W4 /DSFML_STATIC /c -I ../include -I ../include/utils -I ../include/sql -I ../deps/mka_list/include -I ../deps/sfml/x86/include -I ../include/scenes ../src/scenes/*.cc

cl /MP /nologo /O2 /MD /EHs /W4 /Fe:game.exe *.obj ../deps/sfml/x86/lib/sfml-system-s.lib ../deps/sfml/x86/lib/sfml-window-s.lib ../deps/sfml/x86/lib/sfml-graphics-s.lib ../deps/sfml/x86/lib/sfml-audio-s.lib ../deps/sfml/x86/lib/vorbisfile.lib ../deps/sfml/x86/lib/ogg.lib ../deps/sfml/x86/lib/flac.lib ../deps/sfml/x86/lib/vorbis.lib ../deps/sfml/x86/lib/vorbisenc.lib ../deps/sfml/x86/lib/openal32.lib ../deps/sfml/x86/lib/freetype.lib winmm.lib opengl32.lib shell32.lib gdi32.lib user32.lib advapi32.lib 

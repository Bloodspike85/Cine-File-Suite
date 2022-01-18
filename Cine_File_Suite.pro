QT += widgets

RC_ICONS = Images/Cine-file-suite.ico


SOURCES += \
    Cine_File_Suite.cpp \
    GAMES/Boule/bimbamboule.cpp \
    GAMES/Boule/player_bubble.cpp \
    GAMES/Casse_brique/CB_balle.cpp \
    GAMES/Casse_brique/CB_brick.cpp \
    GAMES/Casse_brique/CB_player.cpp \
    GAMES/Casse_brique/casse_brique.cpp \
    GAMES/Commune/PainterObject.cpp \
    GAMES/GameOfLife/gameoflife.cpp \
    GAMES/Pong/balle.cpp \
    GAMES/Pong/player.cpp \
    GAMES/Pong/pong.cpp \
    GAMES/Snake/fruit.cpp \
    GAMES/Snake/snake.cpp \
    GAMES/Snake/snake_game.cpp \
    GAMES/game.cpp \
    GAMES/Boule/bubble.cpp \
    gestions_des_informations.cpp \
    main.cpp \
    mainwindow.cpp \
    Gestions_Des_Dossiers.cpp \
    Gestions_Des_Fichiers.cpp \
    Gestions_des_kdms.cpp \
    Gestions_Des_Projecteurs.cpp \
    KDM_Manager.cpp \
    message_box.cpp \
    kdm_lister.cpp

HEADERS += \
    Cine_File_Suite.h \
    GAMES/Boule/bimbamboule.h \
    GAMES/Boule/player_bubble.h \
    GAMES/Casse_brique/CB_balle.h \
    GAMES/Casse_brique/CB_brick.h \
    GAMES/Casse_brique/CB_player.h \
    GAMES/Casse_brique/casse_brique.h \
    GAMES/Commune/PainterObject.h \
    GAMES/Commune/Vector.h \
    GAMES/GameOfLife/gameoflife.h \
    GAMES/Pong/balle.h \
    GAMES/Pong/player.h \
    GAMES/Pong/pong.h \
    GAMES/Snake/fruit.h \
    GAMES/Snake/snake.h \
    GAMES/Snake/snake_game.h \
    GAMES/game.h \
    GAMES/Boule/bubble.h \
    gestions_des_informations.h \
    mainwindow.h \
    Gestions_Des_Dossiers.h \
    Gestions_Des_Fichiers.h \
    Gestions_des_kdms.h \
    Gestions_Des_Projecteurs.h \
    KDM_Manager.h \
    message_box.h \
    main.h \
    kdm_lister.h \
    structure.h

DISTFILES +=

RESOURCES += \
    resource.qrc

CONFIG += static
QMAKE_LFLAGS += -static-libgcc -static-libstdc++ -lpthread






#ifndef ROGUELIKE_CONFIG_H_
#define ROGUELIKE_CONFIG_H_

// Project configurations.



#define GAME_VERSION L"0.0.0 Alpha"

#ifndef ISMAC
# ifndef INSTALLED
#  define INSTALL_PATH "./data"
# else  
#  define INSTALL_PATH ""
# endif
#else
# define INSTALL_PATH ""
#endif


#endif

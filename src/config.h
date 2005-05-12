/*** compilation time configuration of AVInfo ***/
/*** this file include before any system header***/
#ifndef _H_CONFIG_H
#define _H_CONFIG_H

/*** # Global compilation option ***/

#define _POSIX_C_SOURCE 200112L


/*** # Path section # ***/


/**note about config paths:
	if you set up a relative name of configuration file (f.e.  ../someconf )
	it will takes as a path from application placement 	(not a working
	directory!), this needs for Windows configuration files.
	Please choose your path style by commenting/uncommenting
*/



#define CFG_PATH_STYLE_WINDOWS 1
/*
#define CFG_PATH_STYLE_UNIX 1
*/

#ifndef CFG_PATH_STYLE_WINDOWS
	#ifndef CFG_PATH_STYLE_UNIX
		#error "Please, edit config.h, uncomment one of followed defines: CFG_PATH_STYLE_[WINDWS/UNIX]"
	#endif
#endif


/**	WINDOWS VARIANT (os/2) **/
#ifdef CFG_PATH_STYLE_WINDOWS
	#define CFG_PREFIX ""
	#define CFG_SYSTEM_MANDATORY_CONFIG ""
	#define CFG_SYSTEM_DEFAULT_CONFIG ""
	#define CFG_USER_DEFAULT_CONFIG "avinfo.cfg"
	#define CFG_SYSTEM_DEFAULT_TEMPLATE "avinfo.tpl"
	#define CFG_DEFAULT_TEMPLATE_NAME "default"
#endif


/** UNIX VARIANT (linux, freeBSD, etc) **/
#ifdef CFG_PATH_STYLE_UNIX
	#define CFG_PREFIX "/usr/local"
	#define CFG_SYSTEM_MANDATORY_CONFIG CFG_PREFIX "/etc/avinfo/mandatory.conf"
	#define CFG_SYSTEM_DEFAULT_CONFIG CFG_PREFIX "/etc/avinfo/default.conf"
	#define CFG_USER_DEFAULT_CONFIG "~/.avinfo/config"
	#define CFG_SYSTEM_DEFAULT_TEMPLATE CFG_PREFIX "/etc/avinfo/templates"
	#define CFG_DEFAULT_TEMPLATE_NAME "default"
#endif


#endif

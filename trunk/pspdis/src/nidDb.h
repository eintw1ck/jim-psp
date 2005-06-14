/*                          ____  _     
#         ____  _________  / __ \(_)____
#        / __ \/ ___/ __ \/ / / / / ___/
#       / /_/ (__  ) /_/ / /_/ / (__  ) 
#      / .___/____/ .___/_____/_/____/  
#     /_/        /_/
#     
# Copyright 2005, pspdev - http://www.pspdev.org
# Author:       John Kelley
# Date:         June 13 2005
# File:         nidDb.h
# Description:  Class to map NIDs to Function Prototypes from an xml
#               file such as pspDev's libdoc project. Based off of 
#               code from Tyranid's prxTool.
*/
#ifndef _NIDDB_H_
#define _NIDDB_H_

#include <map>
#include <vector>
#include <string>
#include <tinyxml/tinyxml.h>
#include "util.h"

#define MAX_SYMBOL_LEN	128
#define MAX_LIBNAME_LEN	64



typedef enum {
	nidType_Function,
	nidType_Variable	
} nidType;

typedef struct {
	std::string name;
	nidType type;
	std::string returnType;
	std::vector<std::string> argTypes;
	std::vector<std::string> argNames;
}  nidInfo;

typedef std::map<u32, nidInfo> nidMap;
typedef std::map<std::string, nidMap> libMap;

class nidDb {
public:
	nidDb();
	~nidDb();
	bool loadFromXml(std::string filename);
	const char *resolveNid(char* libName, u32 nid);
	const char *resolveNid(char* libName, char* txtNid);
	const nidType getNidType(char* libName, u32 nid);
	const nidType getNidType(char* libName, char* txtNid);
	
private:
	void parsePRXFileElement(TiXmlElement *elemPrxFile);
	void parseLibraryElement(TiXmlElement *elemLibrary);
	const u32 readNidInfo(TiXmlElement *elemNidEntry, nidInfo &entry);
	libMap db;
};

#endif

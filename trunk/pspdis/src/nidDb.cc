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
#include "nidDb.h"

nidDb::nidDb() {
}

nidDb::~nidDb() {
}

const char* nidDb::resolveNid(char *libName, u32 nid) {
	return db[libName][nid].name.c_str();
}

const char* nidDb::resolveNid(char *libName, char* txtNid) {
	u32 nid = strtoul(libName, NULL, 16);
	return resolveNid(libName, nid);
}

const nidType nidDb::getNidType(char *libName, u32 nid){
	return db[libName][nid].type;
}

const nidType nidDb::getNidType(char *libName, char* txtNid){
	u32 nid = strtoul(libName, NULL, 16);
	return getNidType(libName, nid);
}

bool nidDb::loadFromXml(std::string filename) {
	TiXmlDocument doc(filename.c_str());

	if(doc.LoadFile()) {
		//COutput::Printf(LEVEL_DEBUG, "Loaded XML file %s", szFilename);
		TiXmlHandle docHandle(&doc);
		TiXmlElement *elmPrxfile;

		elmPrxfile = docHandle.FirstChild("PSPLIBDOC").FirstChild("PRXFILES").FirstChild("PRXFILE").Element();
		while(elmPrxfile) {
			//COutput::Puts(LEVEL_DEBUG, "Found PRXFILE");
			parsePRXFileElement(elmPrxfile);
			elmPrxfile = elmPrxfile->NextSiblingElement("PRXFILE");
		}
	} else {
		printf("Couldn't load xml file %s\n", filename.c_str());
		return false;
	}

	return true;
}

void nidDb::parsePRXFileElement(TiXmlElement *elemPrxFile) {
	TiXmlHandle prxHandle(elemPrxFile);
	TiXmlElement *elmLibrary;
	TiXmlText *txtName;

	txtName = prxHandle.FirstChild("PRXNAME").FirstChild().Text();

	elmLibrary = prxHandle.FirstChild("LIBRARIES").FirstChild("LIBRARY").Element();
	while(elmLibrary) {
		if(txtName != NULL)
			parseLibraryElement(elmLibrary);
		elmLibrary = elmLibrary->NextSiblingElement("LIBRARY");
	}
}

void nidDb::parseLibraryElement(TiXmlElement *elemLibrary) {
	TiXmlHandle libHandle(elemLibrary);
	TiXmlText *libName;
	TiXmlElement *elemFunction;
	TiXmlElement *elemVariable;
	u32 nid;
	nidInfo info;
	
	//get library name
	libName = libHandle.FirstChild("NAME").FirstChild().Text();
	if(libName) {
		//printf("Library %s\n", libName->Value());
		
		//get initial elements
		elemFunction = libHandle.FirstChild("FUNCTIONS").FirstChild("FUNCTION").Element();
		elemVariable = libHandle.FirstChild("VARIABLES").FirstChild("VARIABLE").Element();

		//load Functions
		while(elemFunction != NULL) {
			//memset(&info, 0, sizeof(info));
			nid = readNidInfo(elemFunction, info);
			if(info.name.length() > 0) {
				db[libName->Value()][nid] = info;
				//printf("Read func: %s nid:0x%08X\n", info.name.c_str(), nid);
			}
			elemFunction = elemFunction->NextSiblingElement("FUNCTION");
		}
		
		//load Variables
		while(elemVariable != NULL) {
			//memset(&info, 0, sizeof(info));
			nid = readNidInfo(elemVariable, info);
			if(info.name.length() > 0) {
				db[libName->Value()][nid] = info;
				//printf("Read var: %s nid:0x%08X\n", info.name.c_str(), nid);
			}
			elemVariable = elemVariable->NextSiblingElement("VARIABLE");
		}
	}
}

const u32 nidDb::readNidInfo(TiXmlElement *elemNidEntry, nidInfo &info) {
	TiXmlHandle nidHandle(elemNidEntry);
	TiXmlElement *elemArg;
	TiXmlText *nidTxt;
	TiXmlText *name;
	TiXmlText *returnType;
	TiXmlText *argType;
	TiXmlText *argName;
	const char *type;
	u32 nid = 0;
	
	nidTxt = nidHandle.FirstChild("NID").FirstChild().Text();
	name = nidHandle.FirstChild("NAME").FirstChild().Text();
	returnType = nidHandle.FirstChild("RETURNTYPE").FirstChild().Text();
	elemArg = nidHandle.FirstChild("ARGS").FirstChild("ARG").Element();

	if((nidTxt != NULL) && (name != NULL)) {
		nid = strtoul(nidTxt->Value(), NULL, 16);
		info.name = name->Value();
		if (returnType != NULL)
			info.returnType = returnType->Value();
		
		type = nidHandle.Node()->Value();
		if (type && strcmp(type, "FUNCTION") == 0)			
			info.type = nidType_Function;
		else 
			info.type = nidType_Variable;
			
		while (elemArg != NULL) {
			argName = elemArg->FirstChild("NAME")->FirstChild()->ToText();
			argType = elemArg->FirstChild("TYPE")->FirstChild()->ToText();
			info.argTypes.push_back(argType->Value());
			info.argNames.push_back(argName->Value());
			elemArg = elemArg->NextSiblingElement("ARG");
		}
	}
	return nid;
}

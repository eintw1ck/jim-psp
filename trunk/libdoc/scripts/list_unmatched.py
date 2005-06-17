#!/bin/sh
""""exec ${PYTHON:-python} -tu $0 "$@";" """
#
# list_unmatched.py - List all unmatched NIDs.
#
# Written by Marcus R. Brown

import re, sys

re_nid = re.compile('<NID>(.*)</NID>')
re_name = re.compile('<NAME>(.*)</NAME>')
re_library = re.compile('<LIBRARY>')

def main():
    # TODO: Don't hardcode this.
    sFileName = 'psplibdoc.xml'
    try:
        fDoc = file(sFileName)
    except IOError:
        print "Error: Couldn't open '%s'" % sFileName
        sys.exit(1)

    sNid = ""
    sLibName = ""
    bNeedLibraryName = False
    bNeedLibraryOutput = False
    bSkipSyslib = False

    for line in fDoc:
        line = line.strip()

        # If we've found a library entry, the next name entry is the name of the library.
        srMatch = re_library.search(line)
        if srMatch:
            bNeedLibraryName = True
            bNeedLibraryOutput = True
            bSkipSyslib = False

        srMatch = re_name.search(line)
        if srMatch:
            sName = srMatch.group(1)
            if bNeedLibraryName:
                sLibName = sName
                if sLibName == 'syslib':
                    bSkipSyslib = True
                bNeedLibraryName = False
            elif sNid:
                if sName.find(sNid[2:]) > 0 and not bSkipSyslib:
                    if bNeedLibraryOutput:
                        print '# %s' % sLibName
                        bNeedLibraryOutput = False
                    print sNid
                sNid = ""

        srMatch = re_nid.search(line)
        if srMatch:
            sNid = srMatch.group(1)

if __name__ == "__main__":
    main()

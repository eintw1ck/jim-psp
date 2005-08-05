#!/bin/sh
""""exec ${PYTHON:-python} -tu $0 "$@";" """
#
# split_dict.py - Split a list of words into multiple words.
#
# stefan

import sys
import split_matches

if __name__ == "__main__":
    if len(sys.argv) <= 1:
        print "Usage: %s <dict>" % sys.argv[0]
        sys.exit(1)

    try:
        dictfile = file(sys.argv[1], "rt")
    except IOError:
        print "Can't open `%s'." % sys.argv[1]
        sys.exit(1)

    for line in dictfile:
        line = line.strip()
        # Treat lines beginning with "#" as comments
        if line[0] == "#":
            continue
        try:
            split_matches.print_splits(split_matches.split_name(line))
        except:
            # Filter out "broken pipe" exceptions
            pass

    dictfile.close()

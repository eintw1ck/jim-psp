#!/bin/sh
""""exec ${PYTHON:-python} -tu $0 "$@";" """
#
# split_matches.py - Split each NID match into multiple words.
#
# Written by Tim Styer.

import re, string, sys

try:
    test_set = set()
except NameError:
    try:
        from sets import Set as set
    except:
        print "You need a version of Python that supports sets."
        sys.exit(1)
test_set = None

re_nid = re.compile('<NID>(.*)</NID>')
re_name = re.compile('<NAME>(.*)</NAME>')

lowercase = string.lowercase
uppercase = string.uppercase
digits = string.digits + '_'


def split_name (name):

	splits = set()

	# lowercase SPLIT uppercase
	for i in xrange(len(name)-1):
		if lowercase.find(name[i])>=0 and uppercase.find(name[i+1])>=0:
			splits.add(i+1)

	# SPLIT digit|underscore SPLIT
	for i in xrange(len(name)):
		if digits.find(name[i])>=0:
			splits.add(i)
			splits.add(i+1)

	# uppercase SPLIT uppercase lowercase
	for i in xrange(len(name)-2):
		if uppercase.find(name[i])>=0 and uppercase.find(name[i+1])>=0 and lowercase.find(name[i+2])>=0:
			splits.add(i+1)

	# do the splitting
	split_name = []
	prev_split = 0
	for split in xrange(1,len(name)):
		if split in splits:
			split_name.append(name[prev_split:split])
			prev_split = split
	split_name.append(name[prev_split:])
	return split_name


def has_uppercase_uppercase (name):

	for i in xrange(0,len(name)-1):
		if uppercase.find(name[i])>=0 and uppercase.find(name[i+1])>=0:
			return True
	return False


def print_splits (split_name_list):

	for i in xrange(len(split_name_list)):
		for j in xrange(i,len(split_name_list)):
			print ''.join(split_name_list[i:j+1])


def main ():

	file = open('psplibdoc.xml')

	nid = None

	for line in file:

		line = line.strip()

		result = re_nid.search(line)
		if result:
			nid = result.group(1)

		result = re_name.search(line)
		if result:
			if nid:
				name = result.group(1)
				if name.find(nid[2:]) < 0:
					words = split_name(name)
#					print nid, name, words
					print_splits(words)
				nid = None

	file.close()


def test ():

	names = [
		'sceKernelUtilsMt19937Init',
		'jklsajfdlsdfjdEEa',
		'jklsajfdlsdfdEE2AAE',
		'jklsajfdlsdfdEE2AaE',
	]

	for name in names:
		words = split_name(name)
		print name, words
		print_splits(words)


if __name__ == "__main__":

	main()
#	test()


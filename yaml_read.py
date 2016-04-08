#!/usr/bin/python

import yaml
import sys

fp = open(sys.argv[1], "r")

yaml_struct = yaml.load_all(fp)
for yaml_item in yaml_struct:
	for k,v in yaml_item.items():
		print k, "->", v
	print "\n",

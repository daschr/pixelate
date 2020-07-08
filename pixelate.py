#!/usr/bin/python3

import pyvips
import os
import sys

def pixelate(infile, outfile, scale=0.2, quality=24):
	im=pyvips.Image.new_from_file(infile)
	
	im=im.resize(scale, kernel="VIPS_KERNEL_NEAREST")
	im=im.resize(1.0/scale, kernel="VIPS_KERNEL_NEAREST")
	
	im.pngsave(outfile, palette=True, Q=quality)

if __name__ == "__main__":
	args=sys.argv	

	if  len(args) < 3:
		print(f"Usage: {args[0]} [infile] [outfile] [?scale] [?quality]", file=sys.stderr)
	
	if len(args) == 3:
		pixelate(*args[1:3])
	elif len(args) == 4:
		pixelate(*args[1:3], scale=float(args[3]))
	else:
		pixelate(*args[1:3], scale=float(args[3]), quality=float(args[4]))

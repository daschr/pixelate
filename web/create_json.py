#!/usr/bin/python3

# need mustach for rendering
# ./create_json.py | mustach - index.mst > index.html

import os

# adjust
path="/mnt/down/pixelart/html/images"

l=[{"name":x, "url":"images/"+x} for x in os.listdir(path)]
d=[x["name"] for x in l] 

r={"images":l, "lookup":d}
print(r)

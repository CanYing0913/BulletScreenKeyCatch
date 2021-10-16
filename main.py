# import numpy as np
import pinyin   # using pip install pinyin


# Initializing Search Space
kw_list = []
openf = open("input.txt", "r")
kw_list = openf.readlines()
openf.close()
# print(type(kw_list[0]))
openf = open("testFile.txt", "r")
context = openf.readlines()
search_context = []
for str in context:
    str_search = pinyin.get(str, format="strip", delimiter="")
    search_context.append(str_search)
openf.close()
writef = open("output.txt", "rw")
for kw in kw_list:
    writef.write("Result for keyword " + kw + ":\n")
    for cur_line in search_context:
        if kw in cur_line:
            writef.write(cur_line + "\n")
writef.close()
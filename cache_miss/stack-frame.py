import mmap

addr_pairs=[
    [5122, 5182],
    [5190, 5218],
    [5226, 5266],
    [5274, 5426],
    [5434, 5586],
    [5594, 5674],
    [5682, 5998]
]


def recur(file, array, index, indent):
    if index >= 0:
        for i in range(0, 12, 4):
            file.seek(array[index][0])
            print("\n{:>{width}}{}: ({:02x},{:02x},offset={})".format(" ", array[index],file.read_byte(),file.read_byte(),i,width=indent*4),end="")
            recur(file, array, index-1, indent+1)


with open("mod-img", "r+b") as f:
    mm = mmap.mmap(f.fileno(), 0)

    mm.seek(5122)
    # mm.write_byte(0x01)
    # mm.write_byte(0xfc)

    recur(mm,addr_pairs,6,0)
    print()
    mm.close()


# recur(len(addr_pairs),0)

# for pair in addr_pairs:
#     print(pair)


# with open("mod-img", "r+b") as f:
#     mm = mmap.mmap(f.fileno(), 0)

#     mm.seek(5122)
#     mm.write_byte(0x01)
#     mm.write_byte(0xfc)

#     mm.close()

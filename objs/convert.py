vert_coords = []
text_coords = []
norm_coords = []
vert_indices = []
text_indices = []
norm_indices = []

with open("base.obj", "r") as f:
    lines = f.readlines()
    for line in lines:
        if line.startswith("v "):
            # print("vertices coordinates: ")
            for coord in line.split()[1:]:
                vert_coords.append(coord)
            print()
        if line.startswith("vt "):
            # print("texture coordinates: ")
            for coord in line.split()[1:]:
                text_coords.append(coord)
            print()
        if line.startswith("vn "):
            # print("normals: ")
            for coord in line.split()[1:]:
                norm_coords.append(coord)
            print()
        if line.startswith("f "):
            # print("vertex indices: ")
            for coord in line.split()[1:]:
                vert_indices.append(int(coord.split("/")[0])-1)
            print()
        if line.startswith("f "):
            # print("texture indices: ")
            for coord in line.split()[1:]:
                text_indices.append(int(coord.split("/")[1])-1)
            print()
        if line.startswith("f "):
            # print("normal indices: ")
            for coord in line.split()[1:]:
                norm_indices.append(int(coord.split("/")[2])-1)
            print()

print("vertices coordinates: ", vert_coords)
print("texture coordinates: ", text_coords)
print("normals: ", norm_coords)
print("vertex indices: ", vert_indices)
print("texture indices: ", text_indices)
print("normal indices: ", norm_indices)

combined = []

# for i in range(len(vert_indices)):


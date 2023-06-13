vert_coords = []
text_coords = []
norm_coords = []
vert_indices = []
text_indices = []
norm_indices = []

with open("base2.obj", "r") as f:
    lines = f.readlines()
    for line in lines:
        temp = []
        if line.startswith("v "):
            for coord in line.split()[1:]:
                temp.append(coord)
            temp.append(1.0)
            vert_coords.append(temp)
        if line.startswith("vt "):
            for coord in line.split()[1:]:
                temp.append(coord)
            text_coords.append(temp)
        if line.startswith("vn "):
            for coord in line.split()[1:]:
                temp.append(coord)
            temp.append(1.0)
            norm_coords.append(temp)
        if line.startswith("f "):
            for coord in line.split()[1:]:
                vert_indices.append(int(coord.split("/")[0]) - 1)
        if line.startswith("f "):
            for coord in line.split()[1:]:
                text_indices.append(int(coord.split("/")[1]) - 1)
        if line.startswith("f "):
            for coord in line.split()[1:]:
                norm_indices.append(int(coord.split("/")[2]) - 1)

# print("vertices coordinates: ", vert_coords)
# print("texture coordinates: ", text_coords)
# print("normals: ", norm_coords)
# print("vertex indices: ", vert_indices)
# print("texture indices: ", text_indices)
# print("normal indices: ", norm_indices)

combined = []

for i in range(len(vert_indices)):
    for coord in vert_coords[vert_indices[i]]:
        combined.append(float(coord))
    for coord in norm_coords[norm_indices[i]]:
        combined.append(float(coord))
    for coord in text_coords[text_indices[i]]:
        combined.append(float(coord))

print("vertices count: ", len(vert_indices))

print("combined: ", combined)

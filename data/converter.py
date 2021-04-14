from matplotlib import pyplot
import geojson
from geojson.geometry import Point, Polygon
import os
import sys
from pyproj import Proj
from sys import argv
import random
import string

projWSG84 = Proj(proj='utm', zone=33, ellps='WGS84', preserve_units=False)


def conToLocal(lat, lon):
    return projWSG84(lat, lon)


def loadFile(fileName):
    with open(f"{fileName}.geojson", "r") as f:
        a = f.read()
    b = geojson.loads(a)
    return b


def prepere(dump):

    objx = []
    objy = []

    lights = {0: [], 1: []}
    trees = {0: [], 1: []}

    all = []

    for i in dump.features:
        if type(i.geometry) == Polygon:
            thisx = []
            thisy = []
            thisprop = {}

            for prop in i.properties:
                if prop in ["building", "landuse", "height", "building:levels"]:
                    thisprop[prop] = i.properties[prop]

            for coord in i.geometry.coordinates[0]:
                x, y = conToLocal(*coord)
                objx.append(x)
                objy.append(y)
                thisx.append(x)
                thisy.append(y)

            all.append([thisx, thisy, thisprop])
        elif type(i.geometry) == Point:
            x, y = conToLocal(*i.geometry.coordinates)
            objx.append(x)
            objy.append(y)

            # for prop in i.properties:
            #     if prop in ["highway", "natural", "height"]:
            if i.properties.get("highway") == "street_lamp":
                lights[0].append(x)
                lights[1].append(y)
            elif i.properties.get("natural") == "tree":
                trees[0].append(x)
                trees[1].append(y)

    centerx = (max(objx)+min(objx))/2
    centery = (max(objy)+min(objy))/2
    trees[0] = [x-centerx for x in trees[0]]
    trees[1] = [y-centery for y in trees[1]]
    lights[0] = [x-centerx for x in lights[0]]
    lights[1] = [y-centery for y in lights[1]]

    for i in range(len(all)):
        all[i][0] = [x-centerx for x in all[i][0]]
        all[i][1] = [y-centery for y in all[i][1]]

    ret = {"areas": all, "points": {"trees": trees, "lights": lights}}
    return ret


def exportArea(file, obj):
    stdout = sys.stdout
    sys.stdout = file

    print("BEGIN")

    print("PROP")
    print(len(obj[2].keys()))
    for i in obj[2].keys():
        print(i, obj[2][i])

    print("COORDS")
    print(len(obj[0]))
    for j in range(len(obj[0])):
        print(obj[0][j], obj[1][j])

    print("END")
    print()

    sys.stdout = stdout


def exportPoints(file, obj):
    stdout = sys.stdout
    sys.stdout = file

    print("BEGIN")

    print("COORDS")
    print(len(obj[0]))
    for j in range(len(obj[0])):
        print(obj[0][j], obj[1][j])

    print("END")
    print()

    sys.stdout = stdout
    ...


def export(data, path):
    # path += ''.join(random.choices(string.ascii_uppercase +
    #                                string.digits, k=15))
    try:
        os.mkdir(path)
    except OSError:
        exit()

    buildings = open(f"{path}/buildings", "w")
    grass = open(f"{path}/grass", "w")
    for i in data["areas"]:
        if "building" in i[2].keys():
            file = buildings
        elif i[2].get("landuse") == "grass":
            file = grass
        exportArea(file, i)

    lights = open(f"{path}/lights", "w")
    exportPoints(lights, data["points"]["lights"])
    trees = open(f"{path}/trees", "w")
    exportPoints(trees, data["points"]["trees"])


def plot(data):
    for x, y, d in data["areas"]:
        if "building" in d.keys():
            color = "brown"
        else:
            color = "green"
        pyplot.fill(x, y, color=color, zorder=1)
    for i in data["points"].keys():
        pyplot.scatter(data["points"][i][0], data["points"][i][1],  zorder=2)
    pyplot.axis('equal')
    pyplot.show()


def main(fileName, path, show=True):
    dump = loadFile(fileName)
    data = prepere(dump)
    export(data, path)
    if show:
        plot(data)


if __name__ == "__main__":
    fileName = argv[1]
    path = argv[2]
    show = True if len(argv) > 4 and argv[3] == "y" else False
    main(fileName, path, show=show)

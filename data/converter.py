from matplotlib import pyplot
import geojson
from geojson.geometry import Point, Polygon
import os
import sys
from pyproj import Proj
from sys import argv
import random
import string

csvsep = "|"

interestingAreaProps = ["building", "landuse",
                        "height", "building:levels", "area:highway", "building:part"]
interestingPointProps = ["highway", "natural",
                         "amenity", "height", "direction"]

projWSG84 = Proj(proj='utm', zone=33, ellps='WGS84', preserve_units=False)


def conToLocal(lat, lon):
    return projWSG84(lat, lon)


def loadFile(fileName):
    with open(f"{fileName}", "r") as f:
        a = f.read()
    b = geojson.loads(a)
    return b


def prepere(dump):

    objx = []
    objy = []

    lights = {0: [], 1: [], "prop": []}
    trees = {0: [], 1: [], "prop": []}
    benches = {0: [], 1: [], "prop": []}

    all = []

    for i in dump.features:
        if type(i.geometry) == Polygon:
            thisx = []
            thisy = []
            thisprop = {}

            for key, val in i.properties.items():
                if key in interestingAreaProps:
                    thisprop[key] = val

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

            thisprop = {}

            for key, val in i.properties.items():
                if key in interestingPointProps:
                    thisprop[key] = val

            if i.properties.get("highway") == "street_lamp":
                lights[0].append(x)
                lights[1].append(y)
                lights["prop"].append(thisprop)
            elif i.properties.get("natural") == "tree":
                trees[0].append(x)
                trees[1].append(y)
                trees["prop"].append(thisprop)
            elif i.properties.get("amenity") == "bench":
                benches[0].append(x)
                benches[1].append(y)
                benches["prop"].append(thisprop)

    centerx = (max(objx)+min(objx))/2
    centery = (max(objy)+min(objy))/2
    trees[0] = [x-centerx for x in trees[0]]
    trees[1] = [y-centery for y in trees[1]]
    lights[0] = [x-centerx for x in lights[0]]
    lights[1] = [y-centery for y in lights[1]]
    benches[0] = [x-centerx for x in benches[0]]
    benches[1] = [y-centery for y in benches[1]]

    for i in range(len(all)):
        all[i][0] = [x-centerx for x in all[i][0]]
        all[i][1] = [y-centery for y in all[i][1]]

    points = {"trees": trees, "lights": lights, "benches": benches}
    ret = {"areas": all, "points": points}
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

    print("x|y", *interestingPointProps, sep=csvsep)
    print("COORDS")
    print(len(obj[0]))
    for j in range(len(obj[0])):
        print(obj[0][j], obj[1][j], sep=csvsep, end=csvsep)
        for key in interestingPointProps:
            print(obj["prop"][j].get(key, " "), end="|")
        print()

    print("END")
    print()

    sys.stdout = stdout


def export(data, path):
    path += ''.join(random.choices(string.ascii_uppercase +
                                   string.digits, k=15))
    try:
        os.mkdir(path)
    except OSError:
        print("Path already exists or can't be created")
        exit(1)

    buildings = open(f"{path}/buildings", "w")
    grass = open(f"{path}/grass", "w")
    areas = open(f"{path}/areas", "w")
    dump = open(f"{path}/dump", "w")

    for i in data["areas"]:
        if "building" in i[2].keys() or "building:part" in i[2].keys():
            file = buildings
        elif i[2].get("landuse") == "grass":
            file = grass
        elif "area:highway" in i[2].keys():
            file = areas
        else:
            file = dump
        exportArea(file, i)

    lights = open(f"{path}/lights", "w")
    exportPoints(lights, data["points"]["lights"])
    trees = open(f"{path}/trees", "w")
    exportPoints(trees, data["points"]["trees"])
    benches = open(f"{path}/benches", "w")
    exportPoints(benches, data["points"]["benches"])


def plot(data):
    for x, y, d in data["areas"]:
        if "building" in d.keys():
            color = "brown"
        elif d.get("landuse") == "grass":
            color = "green"
        elif d.get("area:highway") == "cycleway":
            color = "red"
        elif d.get("area:highway") == "footway":
            color = "grey"
        elif "area:highway" in d.keys():
            color = "black"
        else:
            color = "yellow"
        pyplot.fill(x, y, color=color, zorder=1)
    for i in data["points"].keys():
        pyplot.scatter(data["points"][i][0], data["points"][i][1],  zorder=2)
    pyplot.axis('equal')
    pyplot.show()


def main(fileName, path, show=True):
    dump = loadFile(fileName)
    data = prepere(dump)
    if show:
        plot(data)
    else:
        export(data, path)


if __name__ == "__main__":
    fileName = argv[1]
    path = argv[2]
    show = True if len(argv) >= 4 and argv[3] == "y" else False
    main(fileName, path, show=show)

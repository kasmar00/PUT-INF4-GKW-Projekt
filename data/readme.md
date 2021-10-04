# OSM data converter

## Data export:

1. Go to: https://overpass-turbo.eu/
2. Paste the Query:
   (or go directly to it: https://overpass-turbo.eu/s/198N)

   ```
   {{bbox=52.39899, 16.946, 52.40796, 16.95495}}
   [out:json][timeout:25];
   (
     relation["type"="building"]({{bbox}});
     >>;
   )->.all_build;
   (
     wr["building"]({{bbox}});
   )->.buildings;
   (
     (.buildings; - .all_build;);
     wr["building:part"]({{bbox}});
     node["natural"="tree"]({{bbox}});
     node["highway"="street_lamp"]({{bbox}});
     node["amenity"="bench"]({{bbox}});
     way["landuse"="grass"]({{bbox}});
     way["leisure"="garden"]({{bbox}});
     way["area:highway"]({{bbox}});
     relation["area:highway"]({{bbox}});
   );
   out body;
   >;
   out skel qt;
   ```

3. Select `run` then `export` -> `geojson` and download data
4. Install requirements from `requirements.txt` file using `$ pip install -r ./requirements.txt` 
5. Run the converter:
   - from makefile: `$ make` (exports from `export.geojson` to `export` dir)
   - from command line: `$ python3 converter.py export.geojson path`

## Processed data

This table lists the data exported from OSM and converted with our script:

| Type   | File        | Description                      | Tag                   |
| ------ | ----------- | -------------------------------- | --------------------- |
| Area   | `buildings` | Buildings - areas and relations  | `building=*`          |
| Area   | `grass`     | Lawns - areas                    | `landuse=grass`       |
| Area   | `grass`     | Gardens - areas                  | `leisure=garden`      |
| Area   | `areas`     | Sidewalks and roadways - areas   | `area:highway=*`      |
| Point  | `lights`    | Outdoor lamps - points           | `highway=street_lamp` |
| Point  | `trees`     | Trees - points                   | `natural=tree`        |

The following tags are passed on for further processing:

- for areas (definied in script with variable `interestingAreaProps`): `building`, `landuse`, `height`, `building:levels`, `area:highway`, `building:part`, `building:min_level`, `leisure`
- for points (definied in script with variable `interestingPointProps`): `highway`, `natural`, `amenity`, `height`, `direction`


# Konwerter danych z OSM

## Eksport danych:

1. Przejdź do: https://overpass-turbo.eu/
2. Wklej zapytanie:
   (lub wejdź bezpośrednio na: https://overpass-turbo.eu/s/198N)

   ```
   {{bbox=52.39899, 16.946, 52.40796, 16.95495}}
   [out:json][timeout:25];
   (
     relation["type"="building"]({{bbox}});
     >>;
   )->.all_build;
   (
     wr["building"]({{bbox}});
   )->.buildings;
   (
     (.buildings; - .all_build;);
     wr["building:part"]({{bbox}});
     node["natural"="tree"]({{bbox}});
     node["highway"="street_lamp"]({{bbox}});
     node["amenity"="bench"]({{bbox}});
     way["landuse"="grass"]({{bbox}});
     way["leisure"="garden"]({{bbox}});
     way["area:highway"]({{bbox}});
     relation["area:highway"]({{bbox}});
   );
   out body;
   >;
   out skel qt;
   ```

3. Wybierz `run`, następnie `export` -> `geojson` i pobierz dane
4. Zainstaluj wymagane biblioteki z pliku `requirements.txt` wykorzystując polecenie `$ pip install -r ./requirements.txt` 
5. Uruchom konwerter:
   - z makefile: `$ make` (exports from `export.geojson` to `export` dir)
   - z terminala: `$ python3 converter.py export.geojson path`

## Przetwarzane dane

Tabela zawiera spis danych eksportowanych z OSM i konwertowanych przez skrypt:

| Typ    | Plik        | Opis                         | Tag                   |
| ------ | ----------- | ---------------------------- | --------------------- |
| Obszar | `buildings` | Budynki - obszary i relacje  | `building=*`          |
| Obszar | `grass`     | Trawniki - obszary           | `landuse=grass`       |
| Obszar | `grass`     | Ogrody - obszary             | `leisure=garden`      |
| Obszar | `areas`     | Chodniki i jezdnie - obszary | `area:highway=*`      |
| Punkt  | `lights`    | Lampy zewnętrzne - punkty    | `highway=street_lamp` |
| Punkt  | `trees`     | Drzewa - punkty              | `natural=tree`        |

Do dalszego przetwarzania przekazywane są następujące tagi:

- dla obszarów (zmienna w skrypcie `interestingAreaProps`): `building`, `landuse`, `height`, `building:levels`, `area:highway`, `building:part`, `building:min_level`, `leisure`
- dla punktów (zmienna w skrypcie `interestingPointProps`): `highway`, `natural`, `amenity`, `height`, `direction`

# Konwerter danych z OSM

## Eksport danych:

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
4. Run the converter:
   - from makefile: `$ make` (exports from `export.geojson` to `export` dir)
   - from command line: `$ python3 converter.py export.geojson path`

## Przetwarzane dane

Tabela zawiera spis danych eksportowanych z osm i konwertowanych:

| Typ    | Plik        | Opis                         | Tag                   |
| ------ | ----------- | ---------------------------- | --------------------- |
| Obszar | `buildings` | Budynki - obszary i relacje  | `building=*`          |
| Obszar | `grass`     | trawniki - obszary           | `landuse=grass`       |
| Obszar | `grass`     | ogrody - obszary             | `leisure=garden`      |
| Obszar | `areas`     | Chodniki i jezdnie - obszary | `area:highway=*`      |
| Punkt  | `lights`    | Lampy zewnętrzne - punkty    | `highway=street_lamp` |
| Punkt  | `trees`     | Drzewa - punkty              | `natural=tree`        |

Do dalszego przetwarzania przekazywane są następujące tagi:

- dla obszarów (zmienna w skrypcie `interestingAreaProps`): `building`, `landuse`, `height`, `building:levels`, `area:highway`, `building:part`, `building:min_level`, `leisure`
- dla punktów (zmienna w skrypcie `interestingPointProps`): `highway`, `natural`, `amenity`, `height`, `direction`

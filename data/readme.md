## Eksport danych:

1. https://overpass-turbo.eu/
2. Query:
   ```
   {{bbox=52.39899, 16.946, 52.40796, 16.95495}}
   [out:json][timeout:25];
   (
     node["natural"="tree"]({{bbox}});
     node["highway"="street_lamp"]({{bbox}});
     way["building"]({{bbox}});
     relation["building"]({{bbox}});
     way["landuse"="grass"]({{bbox}});
     way["area:highway"]({{bbox}});
     relation["area:highway"]({{bbox}});
   );
   out body;
   >;
   out skel qt;
   ```
3. Export->geojson
4. `$ python converter.py export.geojson path`

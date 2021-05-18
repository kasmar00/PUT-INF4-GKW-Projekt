FILE=export.geojson
DEST=./export

data: dataclean
	python3 converter.py $(FILE) $(DEST)

dataclean:
	$(RM) -r $(DEST)
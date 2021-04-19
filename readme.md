# Grafika Komputerowa i Wizualizacja Projekt

## Kompilacja

Docelowy system: Linux (Ubuntu)

1. Zainstaluj konieczne biblioteki:
   - `glew` (apt: `libglew-dev`)
   - `glm` (apt: `libglm-dev`)
   - `glfw` (apt: `libglfw3-dev`)
   - `gl` (apt: `libgl-dev`)
2. Kompiluj w głównym katalogu przy pomocy `$ make`
3. Uruchom przy pomocy `$ make run`

## Struktura projektu

Foldery:

- `data/` - dane wejściowe oraz programy do ich preprocessingu
- `libs/` - biblioteki wykorzystywane w programie (część pobierana `wget` przez makefile)
- `models/` - modele dla projektu
- `shaders/` - shadery w GLSL
- `src/` - źródło programu
- `textures/` - tekstury dla modeli

Pliki:

- `makefile` - makefile dla kompilacji całego projektu, opis funkcji w `$ make help`
- `.clang-format` - specyfikacja dla formatera kodu
- `.github/workflows/format.yml` - specyfikacja github actions, weryfikująca formatowanie kodu

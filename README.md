Simple aquarium lights
=======================

This sketch implements a very simple lamp for my aquarium. An LED stripe (IP67 waterproof) is driven by an arduino. Currently an external plug switches on power, and then the strips gradually fade to various ambient settings (morning, noon, ..., night).

Building
--------

Building is done via [platformio](http://platformio.org):

```shell
platformio run  # compile
platformio run --target upload # upload
```

Testing
---------

Testing support in [platformio](http://platformio.org) is currently quite limited. I managed to hack together a way to use one C file for tests. Luckily this is enough for this small sketch.

```shell
./run_local_unit_tests.sh
```

Layout
=========

![Breadboard](layout/fritzing_layout_bb.png)

![Schematic view](layout/fritzing_layout_schem.png)

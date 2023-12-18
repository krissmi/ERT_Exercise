
# TODO: this is HIGHLY problematic; refactor with real namespace support
import os
from importlib import import_module
from pathlib import Path

for file in os.listdir(path=__path__[0]):
    if file.endswith('.py') and file != os.path.basename(__file__):
        module = Path(file).stem
        globals()[module] = import_module(".{}".format(module), package=__package__)

# END-OF-FILE

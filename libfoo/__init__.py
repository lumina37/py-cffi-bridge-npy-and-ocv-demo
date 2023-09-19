import os
from pathlib import Path

if os.name == 'nt':
    ocv_path = None
    path_env = os.environ.get('PATH')
    for path in path_env.split(';'):
        path = Path(path)
        for p in path.glob('opencv_*.dll'):
            ocv_path = p.parent
            break
        if ocv_path is not None:
            break
    if ocv_path is not None:
        os.add_dll_directory(str(ocv_path))

from . import algorithm

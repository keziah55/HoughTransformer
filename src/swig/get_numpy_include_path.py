from pathlib import Path


def get_numpy_include_path() -> str:

    try:
        import numpy as np
    except ImportError:
        msg = "Building DetectorBank python extension requires numpy. "
        msg += "Please ensure numpy is installed. "
        msg += "(You may need to active a virtual environment before running this.)"
        raise Exception(msg)
    else:
        numpy_dir = Path(np.__file__).parent
        core_dirs = ["_core", "core"]
        valid_path_found = False
        for core_dir in core_dirs:
            numpy_include_path = numpy_dir.joinpath(core_dir, "include")
            arrayobject_file = numpy_include_path.joinpath("numpy", "arrayobject.h")
            if arrayobject_file.exists():
                valid_path_found = True
                break

        if not valid_path_found:
            msg = f"Could not find numpy/arrayobject.h in 'core' or '_core' in . "
            msg += "Build will fail. "
            raise Exception(msg)

        numpy_include_path = str(numpy_include_path)

        return numpy_include_path


if __name__ == "__main__":
    p = get_numpy_include_path()
    print(p)

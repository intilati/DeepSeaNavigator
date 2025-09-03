

import csv
import argparse
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D  


def read_csv_coords(fname):
    """
    Read a CSV with header "x,y,z" and return an (N,3) numpy array of ints.
    If file is missing or empty, returns an empty array with shape (0,3).
    """
    try:
        # Use numpy to read numbers, but handle header safely.
        with open(fname, 'r', newline='') as f:
            reader = csv.reader(f)
            header = next(reader, None)  # skip header (if present)
            rows = []
            for row in reader:
                if not row:
                    continue
                # Convert to ints, strip whitespace
                x = int(row[0].strip())
                y = int(row[1].strip())
                z = int(row[2].strip())
                rows.append([x, y, z])
        if len(rows) == 0:
            return np.zeros((0,3), dtype=int)
        return np.array(rows, dtype=int)
    except FileNotFoundError:
        print(f"File not found: {fname}")
        return np.zeros((0,3), dtype=int)
    except Exception as e:
        print(f"Error reading {fname}: {e}")
        return np.zeros((0,3), dtype=int)



def plot_3d(path_pts, occ_pts, out_img=None, show=True):
    """
    Plot 3D view: obstacles as black squares, path as a connected line with markers.
    If out_img is provided, save image. If show==True, call plt.show().
    """
    fig = plt.figure(figsize=(9,7))
    ax = fig.add_subplot(111, projection='3d')

    # obstacles
    if occ_pts.size:
        ax.scatter(occ_pts[:,0], occ_pts[:,1], occ_pts[:,2],
                   marker='s', s=10, c='k', alpha=0.7, label='obstacle')

    # patht
    if path_pts.size:
        ax.plot(path_pts[:,0], path_pts[:,1], path_pts[:,2],
                marker='o', markersize=4, linewidth=2, label='path')
        # start / goal
        ax.scatter(path_pts[0,0], path_pts[0,1], path_pts[0,2],
                   c='green', s=60, label='start')
        ax.scatter(path_pts[-1,0], path_pts[-1,1], path_pts[-1,2],
                   c='red', s=60, label='goal')

    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    ax.legend()
    ax.grid(True)

    if out_img:
        plt.savefig(out_img, bbox_inches='tight', dpi=500)
        print(f"Saved 3D image to {out_img}")
    if show and not out_img:
        plt.show()
    plt.close(fig)


def main():
    parser = argparse.ArgumentParser(description="Plot voxnav output ")
    parser.add_argument("--path",    default="build/out_path.csv", help="waypoint CSV (x,y,z)")
    parser.add_argument("--occ",     default="build/out_occupied.csv", help="occupied voxels CSV (x,y,z)")
    parser.add_argument("--out-3d",  default=None, help="save 3D image to file")

    args = parser.parse_args()

    # read CSV files with simple helper (returns numpy arrays)
    path_pts = read_csv_coords(args.path)
    occ_pts  = read_csv_coords(args.occ)

    if path_pts.size == 0:
        print("Warning: no path points read from", args.path)
    if occ_pts.size == 0:
        print("Warning: no occupied voxels read from", args.occ)

    # plot 3D (if out_3d provided, file will be saved; otherwise it will show)
    plot_3d(path_pts, occ_pts, out_img=args.out_3d, show=(args.out_3d is None))


if __name__ == "__main__":
    main()



